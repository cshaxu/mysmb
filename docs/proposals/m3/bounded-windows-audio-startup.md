# Bounded Windows Audio Device Startup

Unnumbered candidate found during T15 S2 host regression. A transient private
desktop product startup created and painted its GUI,then blocked inside the
unchanged Win32 audio open call before entering the message loop. Both product
widths exceeded the existing8-second host budget. A diagnostic baseline using
the retained T14 compositor stalled at the same before-audio marker;there was
no after-audio marker. Both Windows audio services report Running;the cause
inside the device/driver/session route is not established. Subsequent unchanged
products passed all six launch/close routes on each width. No audio repair is
claimed. No service restart,
global input or user-window operation was attempted.

Proposed bounded S:inspect WinMM device acquisition under current local/remote
conditions;keep root startup,close and input responsive if acquisition stalls.
Give device acquisition/cancellation/lifetime one platform owner. Preserve
audio renderer and game semantics,normal sound,snapshot/focus/exit cleanup.
Test both normal device and deliberately stalled acquisition routes;repeat
actual product private-desktop launch/close checks after repair. Neither a
longer test timeout nor silently disabling all audio is an accepted repair.

T14's historical accepted startup receipts remain within their original host
conditions. Final current host routes passed;they do not prove acquisition is
always bounded. Receipts remain beneath build/m3-t15-s2. No node
credit,external import,original game change or DOS audio requirement.
