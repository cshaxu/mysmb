# Mine core tests

core_test.c owns independent rules, boundaries, deterministic fixed-width
boards, first-safe relocation, marking/flood/chord outcomes and clock limits.
Run the same C test as x86,x64 and actual small-model DOS16; compare its board
hash. This replaces, rather than claims equivalence to, the excluded XP core.
