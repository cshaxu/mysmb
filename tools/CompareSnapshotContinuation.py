"""Compare bounded local snapshot continuation;host floating values explicit."""
import argparse
import json
import math
from pathlib import Path


def real(data):
    exponent = int.from_bytes(data[1:3], 'little')
    mantissa = int.from_bytes(data[3:10], 'little')
    return (-1 if data[0] else 1) * math.ldexp(float(mantissa), exponent - 1127) if exponent else 0.0


def compare(first, second, receipt):
    build = Path(__file__).resolve().parents[1] / 'build'
    for path in [first, second, receipt]:
        assert path.resolve().is_relative_to(build.resolve()), 'local outputs must remain under build'
    size = 240 * (4622 + 64 + 61440 + 1470)
    stream1 = first.with_name(first.name + '.stream')
    stream2 = second.with_name(second.name + '.stream')
    assert stream1.stat().st_size == stream2.stat().st_size == size
    with stream1.open('rb') as a, stream2.open('rb') as b:
        while True:
            x, y = a.read(65536), b.read(65536)
            assert x == y, 'game/pixels/integer-audio/PCM byte difference'
            if not x:
                break
    audio1 = first.with_name(first.name + '.audio').read_bytes()
    audio2 = second.with_name(second.name + '.audio').read_bytes()
    assert len(audio1) == len(audio2) == 240 * 124
    maxima, counts = [0.0] * 6, [0] * 6
    for frame in range(240):
        x, y = audio1[frame * 124:(frame + 1) * 124], audio2[frame * 124:(frame + 1) * 124]
        assert x[:64] == y[:64]
        for field in range(6):
            start = 64 + field * 10
            delta = abs(real(x[start:start + 10]) - real(y[start:start + 10]))
            assert math.isfinite(delta)
            maxima[field] = max(maxima[field], delta)
            counts[field] += bool(delta)
    # This finite path accepts normal x87/SSE rounding while comparing actual
    # audible PCM exactly. It does not infer all-input synthesis equivalence.
    assert max(maxima[:4]) < 1e-10 and max(maxima[4:]) < 1e-8
    result = {'frames': 240, 'pcmSamples': 176400, 'comparedBytes': size,
              'gamePixelIntegerAudioPcmByteDifferences': 0,
              'maximumHostNumericDifferences': maxima, 'numericFrameCounts': counts,
              'romCredit': 0, 'exhaustiveEquivalence': False}
    receipt.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(result))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('first', type=Path)
    parser.add_argument('second', type=Path)
    parser.add_argument('receipt', type=Path)
    args = parser.parse_args()
    compare(args.first, args.second, args.receipt)
