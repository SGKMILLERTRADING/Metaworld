# Metaworld — Master Development Roadmap v3.0 — Phase 20 Consolidation Overlay

**Status:** Canonical / Approved

**Supersedes:** The Phase 20 base-building/construction section of `Docs/Master_Development_Roadmap.md` v2.9.

**Preserves:** Every non-Phase-20 rule and roadmap phase in v2.9 unless another later canonical document explicitly supersedes it.

**Engine:** Unreal Engine 5.8

**Runtime:** Blueprint-first

## Canonical Phase 20 Source

The completed 26-video base-building playlist is consolidated in:

`Docs/Base_Building_Playlist_Phase20_Final_Consolidation.md`

That document, together with its listed detailed companion documents, is the authoritative Phase 20 implementation direction.

The seven playlist addenda remain the historical intake/audit trail and do not need to be reread for normal implementation.

## Phase 20 Locked Scope

Phase 20 now includes:

- modular `BPC_MW_BuildComponent` + local ghost preview;
- data-driven Buildable catalog with stable Buildable/Family/Variant IDs;
- controller-complete Build Catalog UI;
- Enhanced Input construction controls;
- interface-driven snapping and contextual snap-point visualization;
- wall families and structural Door/Window openings;
- separate installed persistent Doors/Windows and runtime interaction;
- structural Floors and multi-story support;
- placement footprint/overlap validation;
- Foundation raise/lower, terrain support sampling and persistent support extensions;
- 3D property/build-zone permissions and restrictions;
- persistent Construction Sites, stages, Work Units and resource delivery/consumption;
- authorized removal/deconstruction/demolition;
- relocation preserving persistent identity;
- prefab/pre-built house construction using logical structure data;
- `BP_MW_Buildable_Master` shallow inheritance plus components/interfaces/data;
- persistent structure condition and typed structural/support/attachment relationships;
- multiplayer server authority, compact replication, relevancy and dormancy;
- stable-ID persistent save/load/world reconstruction;
- household residential access/lock permissions integration;
- construction dependency/health-check Editor tooling;
- performance-first implementation and keyboard/mouse + Xbox-style + PlayStation-style acceptance testing.

## Required Implementation Spine

`Catalog / Quick Select`
-> `Local Ghost`
-> `Rotation / Foundation Elevation`
-> `Snap + Zone + Footprint + Support Prediction`
-> `Server Validation`
-> `Persistent Construction Site / Structure`
-> `Materials + Work Units`
-> `Completed Structure`
-> `Replication + Persistence`

## Phase 20 Completion Gate

Phase 20 is not complete until one connected test environment proves:

- stable-ID catalog selection;
- all three input families;
- ghost/rotation/foundation elevation;
- property/build-zone/footprint/support validation;
- snap guides and structural snapping;
- multi-story support;
- Door/Window opening installation and runtime interaction;
- household access result;
- persistent materials + Work Units;
- multiplayer construction consistency;
- relocation and authorized removal;
- prefab construction;
- structure relationship/state updates;
- server restart/save-load reconstruction;
- late-join reconstruction;
- dormancy/relevancy and worst-case performance behavior.

## Master Roadmap Rule

All future construction tutorials, feature ideas and implementation work must be compared against this v3.0 Phase 20 consolidation. New material may extend Phase 20, upgrade another roadmap phase, or be rejected/researched, but it must not silently restore tutorial-specific UE4 patterns already superseded by the canonical UE5.8 architecture.
