# M2 T27 S1: Screen initialization and palette chain

S1 completed 20 leaf/data nodes in ROM lines 1408--1513. `ScreenRoutines` transfers to T27 S3 because its complete table needs every target chain; no partial table credit is claimed. The owner C now updates ScreenRoutineTask before the GetPlayerColors fallthrough. Focused smoke, title/local-area regressions, platform purity, x86/x64 product self-tests, DOS16 MZ link and a one-Start 200-frame ROM/x86/x64 comparison passed with zero output differences in the recorded groups.
