# Architecture Rules

The concrete MySMB component map is [System Architecture](../design/ARCHITECTURE.md).

## Non-Negotiable Invariants

- Dependencies point toward neutral declared capabilities; no hidden reverse or cyclic dependency may pass through a helper, callback, global, or test.
- Each mutable state, original-ROM data region, validation trace, resource route, and platform capability has one explicit owner and production path.
- The portable translated game layer exposes no host API, host-sized pointer assumption, mutable platform layout, or implicit global state.
- Only a declared composition root connects game logic, validation adapters, renderers, input, timing, and audio.
- `src/platform/` contains exactly `dos16/` and `win32/`. Host execution and
  platform-specific declarations belong to their host component. Shared
  formats/services belong to neutral components and cannot import a host.
- The translation preserves source-address provenance and original state semantics. A visually similar replacement cannot silently substitute for a translated original routine.

## Source And Research Admission

ROMs, disassemblies, translations, assets, traces, and third-party material require the [source and research policy](../etc/operations/policy/source-policy.md) before entry. Research never becomes an implementation dependency by default.
