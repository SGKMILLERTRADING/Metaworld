# Metaworld — Modular Blueprint Base-Building System

**Status:** Canonical / Approved Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld's construction system uses a reusable Blueprint Actor Component rather than placing all build logic directly inside the master character Blueprint.

Recommended component:

`BPC_MW_BuildComponent`

Attached to:

`BP_MW_Character_Master`

Core rule:

> The character requests construction; the Build Component manages preview and placement; property/profession/economy/world systems decide whether construction is actually legal and possible.

The system is inspired by modular Blueprint patterns in the supplied UE4 base-building tutorials, but adapted to Metaworld's UE5.8 Blueprint-first, multiplayer, property, profession, persistence, scalability and performance architecture.

---

# 1. Build Component

`BPC_MW_BuildComponent` should own build-mode state and construction flow.

Suggested state:

- `BuildModeOn`
- `CanBuild`
- `SelectedBuildableID`
- `SelectedBuildableDefinition`
- `SelectedCategory`
- `SelectedIndex`
- `GhostActor`
- `CurrentPlacementTransform`
- `CurrentPlacementReason`
- `BuildRange`
- `GridSize`
- `RotationStep`
- `PlacementUpdateInterval`
- `CurrentPropertyID`
- `CurrentBuildPermissionState`
- `CurrentSnapTarget`
- `CurrentSnapType`

The component receives references/interfaces it needs from the owning character rather than becoming tightly coupled to a specific child Blueprint.

---

# 2. Input and Build-Mode Activation

Do not permanently hardcode construction to the `B` key.

Use Enhanced Input with dedicated build actions, for example:

- `IA_MW_ToggleBuildMode`
- `IA_MW_BuildConfirm`
- `IA_MW_BuildCancel`
- `IA_MW_BuildNext`
- `IA_MW_BuildPrevious`
- `IA_MW_BuildRotateLeft`
- `IA_MW_BuildRotateRight`
- `IA_MW_ToggleSnap`

The player may rebind them.

Mouse wheel cycling is approved as a fast default for next/previous buildable, but it is not the only interface. A proper build catalog UI is required once the buildable library grows.

Build-mode flow:

`Input -> Toggle Build Mode -> Validate basic eligibility -> Resolve selected Buildable Definition -> Spawn/enable ghost -> Start placement updates`

Exiting build mode:

- destroy or hide ghost
- stop placement timer
- clear temporary selection/snap state
- restore normal interaction mode

Build mode must not keep expensive placement logic running while disabled.

---

# 3. Camera-Based Placement Trace

The player's active camera/view provides the placement trace origin/direction.

The original tutorial used a fixed forward range. Metaworld should make this data-driven.

Example:

`Camera Location -> Camera Forward Vector -> BuildRange -> Line/Sphere Trace`

Build range may vary by:

- buildable category
- profession/tool
- construction mode
- accessibility settings where appropriate
- special machinery

Do not bake one fixed `350–1000` distance into the whole system.

The trace produces a candidate surface/location, then the placement validator resolves the final transform and optional snap target.

---

# 4. Ghost Preview

Every buildable definition can specify a preview representation.

Ghost states:

- Valid placement
- Invalid placement
- Warning/conditional placement
- No surface / out of range

Minimum visual language:

- Green = valid
- Red = blocked/invalid

Optional later state:

- Yellow/amber = valid but warning, cost issue, permit issue, or pending requirement

Changing the selected buildable calls a centralized preview refresh function, for example:

`RefreshSelectedBuildable()`

or the tutorial-style concept:

`ChangeMesh()`

The function should update:

- ghost mesh/representation
- footprint/bounds
- allowed placement modes
- snap compatibility
- trace/query settings
- build range
- rotation rules
- required resources/cost display
- profession/permit display

The ghost is presentation only. It never authoritatively creates ownership or a permanent structure.

The preview should use a low-cost material/material-instance strategy and avoid unnecessary high-cost effects.

---

# 5. Timer-Based Build Cycle

Metaworld should not run expensive construction traces on every frame by default.

When build mode is active:

`Timer -> Update Candidate Placement -> Resolve Snap -> Validate -> Move Ghost -> Update Ghost State`

Suggested configurable interval can be tuned during profiling, for example a small fraction of a second rather than unconditional Event Tick.

The exact interval is not canonical; smoothness and responsiveness are.

The timer stops immediately when build mode exits.

This follows Metaworld's wider rule:

> Event/timer-driven systems are preferred over unnecessary per-frame Blueprint Tick.

---

# 6. Placement Validation Pipeline

`CanBuild` must not be only a collision boolean.

Recommended validation order:

1. Build mode active
2. Selected Buildable Definition valid
3. Candidate surface or snap target exists
4. Candidate within allowed build range
5. Candidate inside an allowed property/build volume
6. Player has build permission for that property
7. Player meets profession/qualification requirement where required
8. Required permit/license exists where applicable
9. Required resources/cost are available
10. Grid/socket/freeform placement rule passes
11. Snap type compatibility passes where snapping is used
12. Collision/overlap rule passes
13. Slope/ground rule passes
14. Structural/support rule passes where applicable
15. Height/air-right/subsurface rule passes
16. Utility/zoning restrictions pass where applicable
17. Server performs final authoritative re-validation

Only then can permanent construction be created.

---

# 7. Property Integration

Construction must obey Metaworld's 3D property system.

The Build Component should query property/build rights rather than deciding ownership itself.

Possible checks:

- owner
- tenant build permission
- family/group permission
- business permission
- public contract permission
- faction/war-control permission where relevant
- deed footprint
- vertical air rights
- subsurface rights
- zoning/building restrictions
- parcel build/performance budget

A player cannot simply point at somebody else's home and build there without legitimate permission/world-rule authority.

---

# 8. Builder Profession Integration

Basic placement of small personal objects may be generally available where approved.

Real building construction can require the Builder profession and possibly legal permits.

Examples:

General:
- place owned furniture
- place simple camp object if world rules allow

Builder-skilled/profession:
- structural walls
- foundations
- houses
- commercial buildings
- apartments
- major renovations

Advanced/licensed:
- larger public/commercial structures
- regulated electrical/plumbing/HVAC work
- inspected construction

Animation never grants the profession; the profession system authorizes the action.

---

# 9. Data-Driven Buildable Catalog

Do not create separate hardcoded logic graphs for every foundation, floor, wall, roof, stair, door, fixture or furniture piece.

Metaworld uses a canonical buildable data definition backed by one or more of:

- Blueprint Struct, for example `S_MW_BuildableDefinition`
- Data Table for large editable catalogs
- Primary Data Asset / Data Asset for richer per-item definitions
- soft references to heavy meshes/classes/assets so the full library does not have to load at once

A buildable catalog entry can include:

- Buildable ID
- Display Name
- Category
- Subcategory
- Search tags
- Mesh/representation
- Permanent Actor Class or placement handler
- Ghost mesh/preview settings
- Nanite compatibility/default
- Footprint/bounds
- Grid size override
- Allowed rotation steps
- Snap types provided
- Snap types accepted
- Allowed placement modes
- Surface types allowed
- Slope limit
- Requires foundation/support
- Build range override
- Required profession
- Required skill/certification
- Required permit
- Required resources
- GrimKoin cost where applicable
- Build time where applicable
- Health/durability
- Repair recipe
- Demolition/salvage rules
- Utility connection requirements
- Persistence class/state schema
- Performance/build-budget cost
- Unlock/research requirement if later used
- icon/thumbnail/UI description

The Build Component should operate on `Buildable ID -> Buildable Definition`, not on giant Switch-on-Integer graphs.

---

# 10. Runtime Catalog Loading

The tutorial loads its buildable Data Table into an array for easy cycling. That is acceptable for a small prototype, but Metaworld must scale to potentially thousands of buildable definitions.

Canonical scaling rule:

> Do not force the entire construction library and all heavy assets into memory merely because build mode exists.

Approved approach:

- load lightweight definition/index data
- use soft references for heavy meshes/classes where practical
- cache the active category/subcategory
- async/load the selected preview asset where appropriate
- release unused preview assets according to memory policy
- keep frequently used starter/building pieces hot when profiling shows value

For the first vertical slice, a small array cache is fine. The architecture must not depend on the entire future catalog fitting in one permanently loaded array.

---

# 11. Buildable Selection & Cycling

Players need fast selection and large-library browsing.

Approved controls:

## Quick Cycling

Mouse wheel / next-previous input can cycle through the active filtered list.

Use safe wrap logic rather than relying only on clamp behavior:

`0 -> 1 -> 2 -> ... -> Last -> 0`

and reverse:

`0 -> Last`

The selected item is tracked by ID and/or stable catalog key, not only by a fragile array index.

## Build Catalog UI

For larger libraries provide:

- categories
- search
- filters
- favorites
- recently used
- required profession/permit indicators
- resource cost
- GrimKoin cost
- locked/unavailable reason
- thumbnail
- structural type

Possible categories:

- Foundations
- Floors
- Walls
- Roofs
- Stairs
- Doors
- Windows
- Furniture
- Utilities
- Security
- Farming
- Business
- Decoration
- Public Works

Cycling is convenience; the catalog is the scalable interface.

---

# 12. Snap Types Instead of Endless Trace Channels

The tutorial uses separate custom Trace Channels such as foundation, floor and wall to help snapping. Metaworld may use dedicated collision/query channels where they provide a clear low-level performance or filtering advantage, but should not create one Project Settings trace channel for every future buildable category.

Preferred high-level snapping architecture:

- socket components / snap points
- Gameplay Tags or names describing snap compatibility
- lightweight query collision for locating candidate snap points
- Buildable Definition rules declaring accepted/provided snap types

Example tags:

- `Build.Snap.Foundation`
- `Build.Snap.Floor`
- `Build.Snap.Wall`
- `Build.Snap.Roof`
- `Build.Snap.Stair`
- `Build.Snap.Door`
- `Build.Snap.Window`
- `Build.Snap.Utility.Power`
- `Build.Snap.Utility.Water`

Example:

Foundation edge exposes `Build.Snap.Wall`.

Wall definition accepts `Build.Snap.Wall` and may expose `Build.Snap.Roof`, `Build.Snap.Door`, and `Build.Snap.Window` points.

This keeps compatibility data-driven and expandable without continually modifying global collision settings.

---

# 13. Placement Modes

Metaworld should support more than one placement style.

## Grid Placement

Useful for:
- floors
- walls
- foundations
- modular structures

## Socket/Snap Placement

Useful for:
- walls to foundations
- roofs
- stairs
- doors/windows
- utility connections

## Free Placement

Useful for:
- furniture
- decorations
- some outdoor props

## Surface-Aligned Placement

Useful for:
- wall signs
- lights
- fixtures
- road/terrain props where allowed

The Buildable Definition chooses which modes are valid.

---

# 14. Rotation and Adjustment

Construction controls should support:

- rotate left/right
- configurable rotation increment
- snap on/off where permitted
- fine placement mode where permitted
- vertical adjustment only within legitimate rules
- cancel
- confirm

Controls should use Enhanced Input and be rebindable.

---

# 15. Final Placement / SpawnBuild

The tutorial concept `SpawnBuild()` is approved as a centralized final-placement function, but in multiplayer Metaworld it must not directly trust the client to spawn the permanent Actor.

Recommended flow:

`Build Confirm Input`
-> `RequestPlaceBuildable(SelectedBuildableID, CandidateTransform, SnapTarget)`
-> server resolves Buildable Definition independently
-> server validates property/profession/resources/snap/collision/world rules
-> server consumes resources/payment atomically
-> server spawns/registers permanent structure
-> persistent Structure ID is created
-> clients receive replicated/streamed result

The client may run a local prediction/preview animation, but authoritative world state comes from the server.

---

# 16. Multiplayer Authority

Client:
- enters build mode
- performs responsive local preview
- cycles/selects buildables
- resolves preliminary snap target
- moves ghost
- displays valid/invalid feedback

Server:
- resolves submitted Buildable ID from authoritative data
- re-checks final transform
- checks property rights
- checks profession/licenses
- checks inventory/resources/currency
- checks snap compatibility
- checks collision/structural/world rules
- consumes resources/payment atomically
- spawns/registers permanent structure
- creates ownership/persistence record

Never trust a client-supplied `CanBuild = true`, Actor Class, cost, or Buildable Definition as authoritative.

---

# 17. Economy and Resource Integration

Construction can consume:

- physical materials
- crafted components
- GrimKoin fees
- labor costs
- permits
- utility connection fees
- taxes where configured

A build must fail safely if payment/resource consumption fails.

Do not remove resources on the client before authoritative placement succeeds.

---

# 18. Persistence

Permanent structures require persistent records.

Minimum record:

- Structure ID
- Buildable Definition ID
- Owner/organization/property ID
- World transform
- Parent/support Structure ID where relevant
- Snap Point/relationship metadata where relevant
- Condition/health
- Construction state
- Permissions
- Utility connections
- Damage state
- Creator texture/product entitlement where relevant
- Timestamp built
- Builder/contract reference where relevant

Logging out does not remove structures.

---

# 19. Construction Stages

Metaworld can later upgrade instant placement into staged construction for larger structures.

Example:

`Blueprint/Permit -> Foundation -> Frame -> Walls -> Utilities -> Finish -> Inspection -> Active Building`

Small objects can still place quickly where appropriate.

Large structures may require:

- resources
- Builder labor
- time
- machinery
- permits
- inspections
- utility hookups

This creates construction jobs/businesses without forcing every decorative placement into a long process.

---

# 20. Structural Rules

Future upgrade:

- foundations
- support graph
- load/support checks
- stairs/accessibility
- roof attachment
- invalid floating structure prevention
- damage-driven structural failure where appropriate

Do not over-simulate engineering if it harms fun/performance, but large buildings should not be able to ignore all support rules.

---

# 21. Utilities

Construction later connects to:

- electricity
- water
- heating/cooling
- fuel/gas where applicable
- communications
- security systems
- fire suppression

Building a wall is different from installing regulated electrical service.

Professional/licensing requirements can differ by utility.

---

# 22. Repair, Renovation and Demolition

The same construction framework should later support:

- repair
- replace damaged module
- repaint/retexture through approved systems
- renovate
- move eligible furniture
- demolish
- salvage materials
- inspect

Ownership, tenant rights, city rules, war/conquest state and court orders can affect who is authorized to demolish or modify structures.

---

# 23. Nanite and Rendering

Use Nanite for compatible permanent construction meshes where it benefits Metaworld and does not break required functionality.

The build system should not need separate gameplay rules because a mesh uses Nanite.

Preview/ghost representation may use a simpler presentation path if that is cheaper and more reliable.

---

# 24. Performance Rules

Construction must obey Metaworld's smoothness policy.

Rules:

- no placement trace when build mode is off
- prefer timer/event updates over unconditional Tick
- ghost is one temporary preview representation, not repeated permanent spawning
- cache selected/lightweight Buildable Definition data
- do not permanently load every heavy buildable asset
- avoid scanning all nearby structures every update
- use targeted traces/overlaps/query volumes
- locate nearby snap points through filtered queries rather than broad searches
- server validates only on meaningful placement requests
- permanent buildings use normal World Partition/HLOD/relevancy rules
- repeated modular pieces can use optimized instancing/rendering strategies where appropriate
- construction damage/destruction obeys physics budgets

---

# 25. Python Editor Tooling Upgrade

Python can later assist development by:

- batch-generating Buildable Definition assets
- generating/updating Data Table rows
- validating duplicate Buildable IDs
- validating missing preview assets
- validating soft references
- validating collision/query configuration
- checking Nanite settings
- checking snap sockets/tags
- checking invalid accepted/provided snap combinations
- checking material/texture requirements
- checking footprint/bounds metadata
- reporting missing profession/permit/resource fields
- auditing performance-cost metadata
- generating build-catalog reports

Python remains editor tooling, not packaged runtime construction logic.

---

# 26. Initial Vertical-Slice Construction Test

The first town should prove:

1. Player toggles build mode through Enhanced Input.
2. `BPC_MW_BuildComponent` activates.
3. Buildable catalog provides multiple pieces.
4. Player cycles Foundation -> Floor -> Wall using next/previous input.
5. Selected Buildable ID survives list/filter changes correctly.
6. Changing selection refreshes ghost mesh and rules.
7. Camera trace finds candidate surface.
8. Ghost follows candidate transform.
9. Green/red feedback reflects placement validity.
10. Foundation/floor/wall snap compatibility works through snap metadata.
11. Invalid snap combinations are rejected.
12. Grid rotation works.
13. Build timer stops outside build mode.
14. Property boundary prevents illegal placement.
15. Builder qualification gates a structural piece.
16. Required resources/cost are checked.
17. Client preview is responsive.
18. Server resolves Buildable ID and re-validates final placement.
19. Client cannot spoof Actor Class/cost/CanBuild.
20. Successful building receives persistent Structure ID/ownership.
21. Save/load restores structure and snap/support relationships.
22. Another player without permission cannot modify it.
23. Performance remains stable while previewing/cycling/building.

---

# 27. Approved Future Upgrades

- foundations/support system
- walls/floors/roofs/stairs
- doors/windows
- socket snapping
- snap-tag visualization/debugger
- freeform furniture placement
- build catalog search/filter/favorites/recently used
- blueprint/house-plan presets
- copy/rotate/mirror tools
- multi-select renovation tools
- construction contracts
- Builder company jobs
- material delivery/logistics
- staged construction
- inspections
- zoning
- electrical/plumbing/HVAC
- repair
- structural damage
- demolition/salvage
- shared/family/business build permissions
- faction/public construction projects
- city infrastructure contracts
- construction history in property records

---

# Core Rule

> Metaworld construction is modular, data-driven, catalog-driven, snap-aware, property-aware, profession-aware, multiplayer-authoritative, persistent and performance-budgeted. The ghost helps the player decide where to build; the server and the world rules decide what actually exists.