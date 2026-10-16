# DOS16 application integration checks

cache_allocation_probe.c observes the actual separately compiled product main
and root. Build-Dos16CacheProbe.ps1 substitutes only allocator, preflight and
root-step symbols in that test executable; its startup hooks, device lifetime,
resource bindings and remaining optimized product objects are retained.
No production C file is included in the test and no diagnostic EXE is published.

Configure the named mysmb_dos16_cache_integration target with
MYSMB_CACHE_PRODUCT_DIR (an existing optimized DOS build),
MYSMB_DOSBOX_EXECUTABLE and MYSMB_DOSBOX_CONFIG. The target builds/links the
probe, invokes DOSBox and validates the receipt. The owner's configuration is
read unchanged; the supplemental configuration contains mounting/commands only.
Both output directories must be below ignored build. The original compiler
requires a short build/tmp16 path; LINK needs its existing qualified execution
environment. Run long commands in continuable sessions.

Fault modes are0natural,1denyD,2deny both near/farA,3denyB,4denyC,
5deny nearA only,6denyDpreflight,7denyBpreflight and8denyCpreflight.
Each run stops after the first actual cache allocation/presentation and records
the root's exit decision before the probe requests a bounded diagnostic exit.
It checks all root-owned successful allocations are freed with matching heap
provenance. Standard CRT pools may retain freed DOS blocks until process exit;
the after-shutdown MCB census is not a leak assertion by itself.

Invoke-Dos16CacheProbe.ps1 additionally supports ConventionalPressureKiB64.
It creates a local, project-authored DOS COM helper, frees that helper's copied
environment and retains64KiB including its PSP (plus the DOS MCB). Run the same
probe without allocation denial; an actual smaller largest-free block must
leave ABD running. VerifyDos16CacheReceipt.py --pressure verifies this route.
The helper disappears with that private DOSBox process. No TSR is installed
on the user's system and no emulator CPU/memory/device option is changed.

test_cache_receipt.py owns malformed/incomplete/contradictory receipt rejection
using invented neutral records. The real matrix owns allocator fallback,
required-cache exit, optional-cache retention, and cleanup boundaries. Neither
proves ROM semantics, exact PPU pixels or performance; those have separate
owners. Report the diagnostic PSP separately from the original MZ loader bound
and from root-owned live allocation bytes. Never equate EXE size to DOS usage.

cache_factorial_probe.c is a separate diagnostic composition root, linked to
the original optimized game/PPU/device objects. It requests exactly the selected
A/B/C/D buffers; C requires B. The production ABD-required/C-optional policy
is unchanged. Without D it submits bounded16-row bands; with D it uses the
current full RAM compositor and screen publication. Thus a D comparison
measures these two complete output paths, not an isolated passive allocation.

The named mysmb_dos16_cache_matrix_integration target uses the same host
configuration variables above. Equivalent manual commands are
Build-Dos16CacheProbe.ps1 -Benchmark, then -Benchmark -LinkOnly, followed by
MeasureDos16CacheMatrix.py --probe <diagnostic-exe> --dosbox <installed-exe>
--configuration <owner-config> --output <ignored-build-directory>.
The diagnostic and matrix tools never publish product executables.

The full matrix runs12valid profiles three times. Each run warms8title and
8gameplay frames and measures the next8of each phase. Preparation, composition
and publication are timed with the original PIT clock; file dumping, startup,
logical game/audio ticks and pacing are outside the measured kernels.
Full palette/original RAM/final VGA streams must match byte-for-byte across
all36runs. Protected streams stay below build, with a48MiB total matrix budget
and180second per-run timeout. This finite route is not a ROM certificate or
an end-to-end playable-frame-rate measurement.

Clock reads have measurable cost. Reports retain both raw and calibrated
totals; band submission has more timer boundaries than full-screen submission.
Small D margins within that difference cannot establish a real speedup.
test_cache_matrix.py owns the valid-pair universe, signed marginal arithmetic,
paired-repeat aggregation and neutral labels; it uses invented timing records.
