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
