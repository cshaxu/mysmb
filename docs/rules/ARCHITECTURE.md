# Architecture Rules

The concrete MySMB component map is [System Architecture](../design/ARCHITECTURE.md).

## Non-Negotiable Invariants

- Dependencies point toward neutral declared capabilities; no hidden reverse or cyclic dependency may pass through a helper, callback, global, or test.
- Each mutable state, original-ROM data region, validation trace, resource route, and platform capability has one explicit owner and production path.
- The portable translated game layer exposes no host API, host-sized pointer assumption, mutable platform layout, or implicit global state.
- Only a declared composition root connects game logic, validation adapters, renderers, input, timing, and audio.
- `src/lib/{dos16,win16,win32}` owns reusable host mechanisms. Mario-specific
  composition adapters live at `src/app-mario/kvm/platform/{dos16,win16,win32}`.
  Shared formats/services belong to neutral components and cannot import a host.
  Original game and PPU semantics remain common and contain no host API.
- The translation preserves source-address provenance and original state semantics. A visually similar replacement cannot silently substitute for a translated original routine.

## Source And Research Admission

ROMs, disassemblies, translations, assets, traces, and third-party material require the [source and research policy](../etc/operations/policy/source-policy.md) before entry. Research never becomes an implementation dependency by default.

## KVM boundary

src/lib/kvm owns portable contracts and algorithms only. It must not include host APIs, reference a named application, or assign keyboard/mouse/game/menu semantics. Applications map raw physical events locally.
