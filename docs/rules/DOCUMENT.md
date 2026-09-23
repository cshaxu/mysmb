# Documentation Rules

`docs/README.md` is the sole documentation entry point. Its direct directories are exactly `rules/`, `design/`, `history/`, `states/`, `proposals/`, and `etc/`.

## Authority Boundaries

| Location | Owns |
| --- | --- |
| `states/CURRENT.md` | One active packet, current technical baseline, and compact closure status. |
| `states/QUEUE.md` | Ordered, unnumbered candidates linked to proposals. |
| `states/TODO.md` | Open debt with priority and an admission path. |
| `proposals/` | Candidate rationale and bounded approach before admission. |
| `rules/` | Mandatory process, architecture, coding, and documentation constraints. |
| `design/` | Goals, concrete architecture, source map, product UX, and milestone order. |
| `history/` | Closed numeric-task records and retained proposals. |
| `etc/` | Indexed supporting detail only. |

One topic has one current authority. Link to it instead of duplicating it. Historical records preserve closure-time facts. `CURRENT.md` retains only one active packet and at most eight compact closure summaries.
