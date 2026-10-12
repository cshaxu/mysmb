"""Run current native area chains against retained owner-local ROM evidence.

All output paths must remain inside the ignored repository build tree.
Original recordings are inputs, never rewritten or treated as native output.
"""
import argparse
import hashlib
import json
import shutil
import struct
import subprocess
import sys
from pathlib import Path

SIZE = 4409
FAMILIES = [('castle', 16, 7), ('ground', 17, 23),
            ('underground', 18, 3), ('water', 19, 3)]


def read_frames(path, magic, count):
    data = path.read_bytes()
    assert data[:8] == magic + bytes([2, 0, 0, 0]), path
    assert struct.unpack_from('<I', data, 8)[0] == count, path
    assert len(data) == 12 + count * SIZE, path
    return [data[12+i*SIZE:12+(i+1)*SIZE] for i in range(count)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--recorder', required=True, type=Path)
    parser.add_argument('--references', required=True, type=Path)
    parser.add_argument('--output', required=True, type=Path)
    parser.add_argument('--rom', required=True, type=Path)
    parser.add_argument('--asm', required=True, type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    build = (root/'build').resolve()
    output = args.output.resolve()
    assert output != build and output.is_relative_to(build), 'Output must be below build'
    assert args.references.resolve().is_relative_to(build), 'References must remain local'
    output.mkdir(parents=True, exist_ok=True)
    recorder = args.recorder.resolve()
    scene_results = []
    fingerprints = {}
    for family, subtask, routes in FAMILIES:
        source = args.references / ('m2-t30-s%d' % subtask)
        target = output / family
        target.mkdir(exist_ok=True)
        for case in range(routes):
            count = 257 if family == 'ground' and case == 22 else 129
            for name in ['rom-%d.msfr', 'pc-%d.txt', 'reads-%d.csv']:
                origin = source / (name % case)
                fingerprints[str(origin.relative_to(args.references))] = hashlib.sha256(origin.read_bytes()).hexdigest()
                shutil.copyfile(origin, target / origin.name)
            subprocess.run([str(recorder), str(target/('native-%d.msfn' % case)),
                            str(count), '0', '1', '--warmup=1',
                            '--fixture=t30-%s-scene=%d' % (family, case),
                            '--bootstrap-title'], check=True, timeout=20,
                           stdout=subprocess.DEVNULL)
        subprocess.run([sys.executable, '-B', str(root/'test/verify_castle_scene_routes.py'),
                        str(target), '--family', family, '--rom', str(args.rom),
                        '--asm', str(args.asm)], check=True, timeout=20)
        summary = json.loads((target/'route-summary.json').read_text())
        scene_results.append(dict(family=family, routes=routes,
                                  samples=summary['samples'], bytes=summary['bytesBoundAndConsumed']))
    source = args.references/'m2-t30-s14'
    target = output/'pointers'
    target.mkdir(exist_ok=True)
    excluded = set(range(8)) | set(range(256, 512)) | {0x778, 0x779}
    for case in range(71):
        count = 1 if case == 70 else 2
        native_path = target/('native-%d.msfn' % case)
        subprocess.run([str(recorder), str(native_path), str(count), '0', '1',
                        '--warmup=1', '--fixture=t30-area-pointer=%d' % case],
                       check=True, timeout=20, stdout=subprocess.DEVNULL)
        original = source/('rom-%d.msfr' % case)
        rom = read_frames(original, b'MSFR', count)
        current = read_frames(native_path, b'MSFN', count)
        # This fixture starts at the pointer/header boundary and deliberately
        # does not recreate the renderer's complete caller state.  Its ROM
        # oracle therefore covers persistent pointer/header RAM only; scene
        # routes above own visible-output equivalence.
        for frame, (a, b) in enumerate(zip(rom, current)):
            delta = {j for j in range(2048) if a[j+4] != b[j+4]}
            assert delta <= excluded, (case, frame, sorted(delta-excluded))
        fingerprints[str(original.relative_to(args.references))] = hashlib.sha256(original.read_bytes()).hexdigest()
    size = sum(p.stat().st_size for p in output.rglob('*.msf*'))
    assert size < 45000000, size
    summary = dict(sceneFamilies=scene_results, sceneSamples=sum(x['samples'] for x in scene_results),
                   pointerRoutes=71, pointerSamples=141, rawBytes=size,
                   recorderSha256=hashlib.sha256(recorder.read_bytes()).hexdigest(),
                   referenceHashes=fingerprints,
                   limits='Scenes: original persistent RAM and full output. Pointers: original persistent RAM only; the fixture does not establish renderer caller state.')
    (output/'summary.json').write_text(json.dumps(summary, indent=2)+'\n')
    print('Area integration: 36 scene routes, 71 pointer/terminal routes passed')


if __name__ == '__main__':
    main()
