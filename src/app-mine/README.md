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
