# Metaworld — Phase 20 Base-Building Playlist Final Consolidation

**Status:** Canonical / Playlist Complete
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first
**Episodes Reviewed:** 26

## Canonical Rule

Future construction work starts from this consolidated Phase 20 architecture and the linked companion documents. The seven playlist addenda remain the historical intake/audit trail; tutorial-specific UE4 patterns do not override the approved Metaworld architecture.

## Locked Capability Set

1. Modular Build Component + local ghost preview
2. Data-driven stable-ID Buildable catalog
3. Interface-driven snapping
4. Wall family + structural Door/Window openings
5. Separate persistent Door/Window installation
6. Floors + supported multi-story building
7. Runtime Door/Window interaction
8. Persistent Construction Sites + Work Units
9. Rotation/orientation controls
10. Placement footprint / overlap validation
11. Foundation terrain support + extensions
12. Authorized deconstruction/demolition
13. Relocation preserving persistent identity
14. Prefab/pre-built houses with logical structure data
15. Shallow Buildable Master inheritance + components/interfaces/data
16. Persistent structure condition + UE5.8 Chaos presentation where justified
17. Typed support/attachment relationships
18. Smart News significance filtering for major world changes
19. Construction dependency/health-check tooling
20. Material delivery/resource consumption
21. Multiplayer authority + compact replication/dormancy
22. Stable-ID world persistence/save-load reconstruction
23. Foundation raise/lower + household home-access permissions
24. Contextual snap-point visualization
25. 3D build-zone permissions/restrictions
26. Controller-complete Build Catalog UI

## Implementation Spine

`Catalog -> Ghost -> Rotation/Elevation -> Snap/Zone/Footprint/Support Preview -> Server Validation -> Persistent Construction Site -> Materials + Work -> Completed Structure -> Replication + Persistence`

## Required Global Rules

- Blueprint-first runtime; Python editor tooling only.
- Stable IDs are authoritative identity, not mesh references or temporary Actor pointers.
- Server decides permanent placement and persistent state.
- Keyboard/mouse, Xbox-style and PlayStation-style controls are required.
- Stable frame time comes before visual excess.
- No idle Buildable Tick, world-wide snap scans, permanent terrain polling, or continuous movement replication for settled structures.
- New construction families should be data-driven and reuse common interfaces/components.
- Property/build-zone, support, footprint, resources, profession/permit and permissions remain integrated checks.
- Save/load restores stable IDs and explicit relationships rather than guessing hierarchy from fresh traces.

## Canonical Companion Index

Use the relevant detailed companion in `Docs/`, including the construction progress, rotation, overlap, foundation support, demolition, relocation, prefab, Buildable Master, structure condition, structural relationships, dependency health check, materials, multiplayer, persistence, household access, snap visualization, build-zone and Build Catalog UI documents.

The playlist audit trail is Parts 1–7 of `Base_Building_Playlist_Phase20_Roadmap_Addendum`.

## Acceptance Gate

Phase 20 is not complete until a connected test environment proves catalog selection, all three input families, placement/rotation/elevation, property/build-zone rejection, overlap/support validation, snapping and snap guides, multi-story construction, Door/Window installation/interaction, household access, material delivery + Work Units, relocation, authorized removal, prefab placement, multiplayer consistency, save/load/server restart reconstruction, late joining and acceptable worst-case performance.

## Final Rule

> The playlist is closed. Future base-building research extends this architecture; it does not reset Metaworld back to tutorial-specific UE4 implementation patterns.