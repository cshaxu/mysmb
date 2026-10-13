# Mine receiving boundary

This directory reserves the application boundary. It contains no Mine game
source, assets or imported Git history yet.

After the owner approves the import revision and provenance/redistribution
receipt, import history below this directory and add its own CMakeLists.txt.
Enable `MYGAMES_BUILD_MINE` to include that application from the root build.
An enabled but absent CMakeLists.txt fails configuration explicitly.

Mine owns its game rules, board/art, input bindings, composition roots, product
targets and app tests. It may consume `mygames_kvm`, `mygames_win32` and the
DOS16 host services; it must not import Mario sources. Win16 integration will consume `mygames_win16_contract` and the existing
shared Win16 host after app-specific qualification. Target names must carry the app prefix.

The import gate requires an exact revision, ownership/distribution record,
history-preserving import, dependency audit and the app's actual-width native
and DOS/Win16 target matrix. This receiving seam proves none of those later
runtime claims by itself.

T44 shared-host readiness is closed; see the [capability matrix](../../docs/history/M3-T44-library-readiness-correction.md#final-bounded-capability-and-evidence-matrix).
The library accepts physical mouse/keyboard events, variable boards and
app-directed dirty/wakeup scheduling. Mine must supply its own bindings,
renderers and entry composition; no Mario rendering or save codec is shared.
Win16 window text is available; real DOS-prompt handoff is outside this seam.
