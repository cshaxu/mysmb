# Architecture Rules

The concrete MySMB component map is [System Architecture](../design/ARCHITECTURE.md).

## Non-Negotiable Invariants

- Dependencies point toward neutral declared capabilities; no hidden reverse or cyclic dependency may pass through a helper, callback, global, or test.
- Each mutable state, original-ROM data region, validation trace, resource route, and platform capability has one explicit owner and production path.
- The portable translated game layer exposes no host API, host-sized pointer assumption, mutable platform layout, or implicit global state.
- Only a declared composition root connects game logic, validation adapters, renderers, input, timing, and audio.
- `app-mario/src/platform/` contains exactly `dos16/` and `win32/` through T43 S2.
  Host execution and platform-specific declarations belong to their host component.
  Shared formats/services belong to neutral components and cannot import a host.
  Later T43 extraction tasks replace these app-local owners with the declared
  `lib/dos16/` and `lib/win32/` owners; they do not fork game behavior.
- T44 S2 explicitly admits a Win16 host under `lib/win16` and a Mario-specific
  Win16 composition adapter. The later T44 layout move places that adapter
  under `src/app-mario/kvm`; USER/GDI mechanics remain shared host ownership.
  Original game/PPU semantics remain common and contain no Win16 API.
- The translation preserves source-address provenance and original state semantics. A visually similar replacement cannot silently substitute for a translated original routine.

## Source And Research Admission

ROMs, disassemblies, translations, assets, traces, and third-party material require the [source and research policy](../etc/operations/policy/source-policy.md) before entry. Research never becomes an implementation dependency by default.

## KVM boundary

lib/kvm owns portable contracts and algorithms only. It must not include host APIs, reference a named application, or assign keyboard/mouse/game/menu semantics. Applications map raw physical events locally.
