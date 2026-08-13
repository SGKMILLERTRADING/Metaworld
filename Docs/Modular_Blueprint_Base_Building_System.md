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

The system is inspired by modular Blueprint patterns in the supplied UE4 base-building tutorials, but adapted to Metaworld's UE5.8 Blueprint-first, multiplayer, property, profession, persistence, scalability, controller and performance architecture.

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
- `SelectedFamilyID`
- `SelectedVariantID`
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
- `CurrentSnapPointID`
- `CurrentSnapParentStructureID`

The component receives references/interfaces it needs from the owning character rather than becoming tightly coupled to a specific child Blueprint.

---

# 2. Input and Build-Mode Activation

Do not permanently hardcode construction to the `B` key or to mouse-only controls.

Use Enhanced Input with dedicated build actions, for example:

- `IA_MW_ToggleBuildMode`
- `IA_MW_BuildConfirm`
- `IA_MW_BuildCancel`
- `IA_MW_BuildNext`
- `IA_MW_BuildPrevious`
- `IA_MW_BuildVariantNext`
- `IA_MW_BuildVariantPrevious`
- `IA_MW_BuildRotateLeft`
- `IA_MW_BuildRotateRight`
- `IA_MW_ToggleSnap`
- `IA_MW_OpenBuildCatalog`

The player may rebind them.

Keyboard/mouse, Xbox-style controllers and PlayStation-style controllers must all have usable construction mappings. Mouse wheel cycling is approved as a fast keyboard/mouse default, but it is not the only interface. Gamepad shoulder buttons, D-pad/stick navigation, radial/category UI or other controller-friendly mappings can provide equivalent actions.

A proper build catalog UI is required once the buildable library grows, and it must be navigable without requiring a mouse cursor.

Build-mode flow:

`Input -> Toggle Build Mode -> Validate basic eligibility -> Resolve selected Buildable Definition/Variant -> Spawn or enable ghost -> Start placement updates`

Exiting build mode:

- destroy or hide ghost
- stop placement timer
- clear temporary selection/snap state
- restore normal interaction mode

Build mode must not keep expensive placement logic running while disabled.

Detailed controller rules: `Docs/Controller_Input_Compatibility_Architecture.md`.

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

Controller placement uses the same camera/view trace. The right stick aims the view/reticle; construction does not depend on mouse-cursor precision.

---

# 4. Ghost Preview

Every buildable definition/variant can specify a preview representation.

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

Changing the selected buildable or variant calls a centralized preview refresh function such as:

`RefreshSelectedBuildable()`

or the tutorial-style concept:

`ChangeMesh()`

The function should update:

- ghost mesh/representation
- selected family/variant
- collision/footprint/bounds preview
- allowed placement modes
- snap compatibility
- trace/query settings
- build range
- rotation rules
- opening/attachment metadata
- required resources/cost display
- profession/permit display

When a valid snap point is selected, the ghost uses the candidate snap transform for preview and updates its valid/invalid material state.

The ghost is presentation only. It never authoritatively creates ownership or a permanent structure.

The preview should use a low-cost material/material-instance strategy and avoid unnecessary high-cost effects.

The preview actor/components may be Movable where needed for responsive placement and mesh/variant changes. Permanent finished structures should not be forced to remain Movable merely because the preview system changes variants; where practical, the server resolves the final variant before authoritative structure creation.

---

# 5. Timer-Based Build Cycle

Metaworld should not run expensive construction traces on every frame by default.

When build mode is active:

`Timer -> Update Candidate Placement -> Detect Compatible Snap Points -> Resolve Best Snap -> Validate -> Move Ghost -> Update Ghost State`

The exact configurable interval is determined through profiling. Smoothness and responsiveness are canonical; a specific tutorial timer value is not.

The timer stops immediately when build mode exits.

This follows Metaworld's wider rule:

> Event/timer-driven systems are preferred over unnecessary per-frame Blueprint Tick.

---

# 6. Placement Validation Pipeline

`CanBuild` must not be only a collision boolean.

Recommended validation order:

1. Build mode active
2. Selected Buildable Definition/Variant valid
3. Candidate surface or snap target exists
4. Candidate within allowed build range
5. Candidate inside an allowed property/build volume
6. Player has build permission for that property
7. Player meets profession/qualification requirement where required
8. Required permit/license exists where applicable
9. Required resources/cost are available
10. Grid/socket/freeform placement rule passes
11. Snap type compatibility passes where snapping is used
12. Snap point is not occupied/reserved where exclusivity applies
13. Variant is allowed on that snap/support relationship
14. Collision/overlap rule passes using the selected variant's actual geometry/profile
15. Slope/ground rule passes
16. Structural/support rule passes where applicable
17. Height/air-right/subsurface rule passes
18. Utility/zoning restrictions pass where applicable
19. Server performs final authoritative re-validation

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
- Family ID
- Variant ID
- Display Name
- Category
- Subcategory
- Search tags
- Mesh/representation
- Permanent Actor Class or placement handler
- Ghost mesh/preview settings
- Nanite compatibility/default
- Footprint/bounds
- Collision profile/shape definition
- Grid size override
- Allowed rotation steps
- Snap types provided
- Snap types accepted
- Allowed placement modes
- Surface types allowed
- Slope limit
- Requires foundation/support
- Build range override
- Opening Type if applicable
- Attachment Slots if applicable
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

The Build Component should operate on stable IDs and definitions, not giant Switch-on-Integer graphs.

---

# 10. Runtime Catalog Loading

The tutorial loads its buildable Data Table into an array for easy cycling. That is acceptable for a small prototype, but Metaworld must scale to potentially thousands of buildable definitions.

Canonical scaling rule:

> Do not force the entire construction library and all heavy assets into memory merely because build mode exists.

Approved approach:

- load lightweight definition/index data
- use soft references for heavy meshes/classes where practical
- cache the active category/subcategory/family
- async/load the selected preview asset where appropriate
- release unused preview assets according to memory policy
- keep frequently used starter/building pieces hot when profiling shows value

For the first vertical slice, a small array cache is fine. The architecture must not depend on the entire future catalog fitting in one permanently loaded array.

---

# 11. Buildable Selection, Families & Cycling

Players need fast selection and large-library browsing.

## Quick Cycling

Mouse wheel / next-previous input can cycle through the active filtered list.

Use safe wrap logic:

`0 -> 1 -> 2 -> ... -> Last -> 0`

and reverse:

`0 -> Last`

The selected item is tracked by ID and/or stable catalog key, not only by a fragile array index.

Gamepad next/previous actions must offer the same functionality without requiring the mouse wheel.

## Family / Variant Cycling

Related pieces can share one family.

Example:

`Build.Family.Wall`

Variants:

- `Wall.Standard`
- `Wall.DoorOpening`
- `Wall.WindowOpening`

The player can select the Wall family, then cycle valid wall variants without leaving the wall workflow. Keyboard/mouse and controllers both require a usable variant-selection path.

## Build Catalog UI

For larger libraries provide:

- categories
- families
- variants
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

Cycling is convenience; the catalog is the scalable interface. The catalog must support controller focus/navigation as well as mouse input.

---

# 12. Snap Types Instead of Endless Trace Channels

The tutorials use separate custom Trace Channels such as foundation, floor and wall to help snapping. Metaworld may use dedicated collision/query channels where they provide a clear low-level performance or filtering advantage, but should not create one Project Settings trace channel for every future buildable category.

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

All compatible wall-family variants can consume that wall snap point unless their data explicitly restricts it.

This keeps compatibility data-driven and expandable without continually modifying global collision settings.

---

# 12A. Blueprint Interface Snap Provider

The supplied tutorial's Blueprint Interface approach is approved and upgraded into a common Metaworld snapping contract.

Recommended interface:

`BPI_MW_BuildSnapProvider`

Any buildable Actor that can provide construction snap points implements this interface.

Possible interface functions:

- `GetBuildSnapPoints()`
- `GetCompatibleSnapPoints(AcceptedSnapTypes)`
- `GetSnapPointByID(SnapPointID)`
- `IsSnapPointAvailable(SnapPointID)`

The interface returns data; it does not own the entire construction algorithm.

This avoids class-specific casting such as:

`Cast to Foundation -> Cast to Floor -> Cast to Wall -> Cast to Roof`

The Build Component can ask any compatible structure the same question.

Suggested snap-point record:

- Snap Point ID
- Local/world transform
- provided Snap Type tags
- accepted Buildable/Snap tags where needed
- orientation/facing rule
- occupancy state
- structural/support role
- query volume/bounds
- priority/weight
- optional parent Structure ID

---

# 12B. Snap Point Components / Collision Boxes

Box Collision components are approved as one practical snap-point implementation, especially for modular foundations, floors and walls.

Recommended setup:

- keep component scale at `1,1,1` where practical
- size the snap interaction area through Box Extent rather than arbitrary component scaling
- Query Only collision
- no physics simulation
- no damage/hit behavior
- no unnecessary overlap events
- custom collision profile or limited query response for construction snapping
- stable Snap Point ID metadata
- snap compatibility tags

A Scene Component/socket can represent the exact attachment transform while a small Box Collision provides the acquisition volume.

Example:

`SnapVolume_Wall_East`
- exact attachment transform at foundation edge
- Box Extent defines how easy it is for the trace/query to acquire
- provides `Build.Snap.Wall`
- stable ID `Wall_East`

The acquisition volume must be forgiving enough for controller aiming without making nearby snap points ambiguous.

---

# 12C. Detect Build Snap Points

The tutorial-style `detect build boxes` concept becomes a reusable function such as:

`DetectCompatibleSnapPoints(HitActor, HitLocation, SelectedBuildableDefinition)`

Recommended flow:

1. Camera/view trace hits a candidate Actor or nearby construction query region.
2. Check whether the Actor implements `BPI_MW_BuildSnapProvider`.
3. Request only snap points compatible with the selected Buildable Definition/Variant.
4. Reject occupied, disabled, incompatible or out-of-range points.
5. Score remaining candidates.
6. Select the best candidate.
7. Set `CurrentSnapTarget`, `CurrentSnapPointID`, `CurrentPlacementTransform` and preview state.

Possible scoring factors:

- distance from hit location/reticle ray
- snap compatibility
- orientation/facing match
- angle to player view
- structural support preference
- occupancy
- same-plane/grid preference
- user-selected snap mode

Do not loop through every snap point in the world. Query the hit/relevant nearby structure and a tightly filtered candidate set.

---

# 12D. Snap Collision Filtering

Custom collision settings from the tutorials are approved as a low-level filtering tool.

Metaworld can define a small number of general construction query profiles/channels, for example:

- Build Placement Query
- Build Snap Query
- Build Obstruction Query

Snap volumes should ignore unrelated gameplay traces where possible.

This prevents construction snap boxes from interfering with bullets, normal interaction, movement, cameras and other unrelated systems.

High-level compatibility remains data/tag driven; collision channels are only the efficient query/filter layer.

---

# 12E. Wall Family, Door-Wall & Window-Wall Variants

The wall-snapping tutorial's standard wall, door wall and window wall concepts are approved, but Metaworld treats them as **structural variants**, not merely cosmetic mesh swaps.

Canonical wall family:

`Build.Family.Wall`

Initial variants:

- `Wall.Standard`
- `Wall.DoorOpening`
- `Wall.WindowOpening`

All three can share common wall logic and the same foundation/floor wall-snap contract, but each variant may have different:

- mesh
- collision geometry
- opening dimensions
- footprint/bounds
- material requirements
- Buildable cost
- durability
- structural/support metadata
- navigation/access behavior
- attachment slots
- damage/broken states
- future door/window compatibility
- performance metadata

A door-opening wall may expose a dedicated attachment slot such as:

`Build.Attach.Door`

A window-opening wall may expose:

`Build.Attach.Window`

The opening is therefore meaningful world structure, not just a different picture on the same wall.

---

# 12F. Wall Snapping to Foundations and Floors

Foundations and floors provide wall-edge snap points.

Example:

- `Wall_North`
- `Wall_East`
- `Wall_South`
- `Wall_West`

Each provides `Build.Snap.Wall` and an exact transform/orientation.

A selected wall-family variant can snap to those edges if compatible.

Flow:

`Foundation/Floor hit`
-> `BPI_MW_BuildSnapProvider`
-> `GetCompatibleSnapPoints(Build.Snap.Wall)`
-> filter occupied/invalid points
-> score candidate edge
-> preview Standard/DoorOpening/WindowOpening variant
-> server validates and places

This lets all initial wall variants snap consistently without duplicating separate placement graphs for each wall type.

---

# 12G. Wall Collision Policy

The tutorials manually replace simple wall collision with Box Collision. Metaworld keeps the useful principle—collision must match gameplay—but does not assume one box is correct for every wall variant.

Rules:

- Standard wall collision blocks through the solid wall area.
- Door-opening wall collision must preserve the intended doorway opening.
- Window-opening wall collision must preserve the intended window opening while blocking the remaining wall.
- Collision can use multiple simple boxes or another performant approved setup where needed.
- Snap query volumes remain separate from gameplay blocking collision.
- Snap volumes are Query Only and should not become walkable/blocking geometry.
- Finished wall collision should be tested for player movement, NPC navigation, projectiles and interaction as appropriate.

The system should prefer simple performant collision over unnecessarily complex per-poly collision when simple shapes correctly represent the gameplay space.

---

# 12H. Dynamic Variant Refresh vs Permanent Structure State

A tutorial-style `Set Mesh` / `ChangeMesh` event is useful for the preview and for data-driven variant visualization.

Metaworld upgrades the rule:

- Preview ghost can switch Standard/DoorOpening/WindowOpening dynamically.
- Variant selection also refreshes collision-preview bounds, opening metadata, cost and snap rules.
- Final server request includes stable Buildable/Family/Variant identity.
- Server resolves the authoritative variant definition.
- Permanent structure is created/initialized from that resolved definition.

Do not keep every finished wall permanently movable just so players can cycle preview meshes.

If later renovation allows a placed Standard wall to become a DoorOpening wall, that is a separate authorized renovation transaction with resource/profession/collision/persistence validation—not an untracked cosmetic mesh swap.

---

# 13. Placement Modes

Metaworld supports more than one placement style.

## Grid Placement

Useful for:
- floors
- walls
- foundations
- modular structures

## Socket/Snap Placement

Useful for:
- walls to foundations/floors
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
- family/variant selection where applicable

Controls should use Enhanced Input, be rebindable, and have keyboard/mouse plus Xbox-style and PlayStation-style controller paths.

---

# 15. Final Placement / SpawnBuild

The tutorial concept `SpawnBuild()` is approved as a centralized final-placement function, but in multiplayer Metaworld it must not directly trust the client to spawn the permanent Actor.

Recommended flow:

`Build Confirm Input`
-> `RequestPlaceBuildable(SelectedBuildableID/VariantID, CandidateTransform, ParentStructureID, SnapPointID)`
-> server resolves Buildable/Variant Definition independently
-> server resolves authoritative parent Structure/Snap Point
-> server validates property/profession/resources/snap/collision/world rules
-> server consumes resources/payment atomically
-> server spawns/registers permanent structure
-> persistent Structure ID is created
-> snap/support relationship is persisted
-> clients receive replicated/streamed result

The client may run a local prediction/preview animation, but authoritative world state comes from the server.

The client cannot invent a valid snap transform by sending only raw coordinates; when snapping is used, the server resolves the referenced parent Structure ID + Snap Point ID and verifies that the requested buildable/variant is compatible.

---

# 16. Multiplayer Authority

Client:
- enters build mode
- performs responsive local preview
- cycles/selects buildables and variants
- resolves preliminary snap target
- moves ghost
- displays valid/invalid feedback

Server:
- resolves submitted Buildable/Variant ID from authoritative data
- resolves submitted Parent Structure/Snap Point IDs
- re-checks final transform
- checks property rights
- checks profession/licenses
- checks inventory/resources/currency
- checks snap compatibility/availability
- checks variant-specific collision/structural/world rules
- consumes resources/payment atomically
- spawns/registers permanent structure
- creates ownership/persistence record

Never trust a client-supplied `CanBuild = true`, Actor Class, mesh, cost, Buildable Definition, Variant Definition, raw snap compatibility or occupancy result as authoritative.

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

Variant choice can change material/resource requirements. A window-opening wall or door-opening wall does not have to cost exactly the same as a solid wall.

A build must fail safely if payment/resource consumption fails.

Do not remove resources on the client before authoritative placement succeeds.

---

# 18. Persistence

Permanent structures require persistent records.

Minimum record:

- Structure ID
- Buildable Definition ID
- Family ID / Variant ID where applicable
- Owner/organization/property ID
- World transform
- Parent/support Structure ID where relevant
- Snap Point ID/relationship metadata where relevant
- Opening/attachment state where relevant
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

`Blueprint/Permit -> Foundation -> Frame -> Walls/Openings -> Utilities -> Finish -> Inspection -> Active Building`

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
- opening-aware wall support rules where useful
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
- convert eligible wall variants through authorized renovation
- install/remove compatible doors/windows
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

Wall variants should use compatible Nanite/performance settings where appropriate, while their gameplay collision remains independently correct.

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
- locate snap candidates from the hit/relevant nearby structure rather than world-wide searches
- interface calls request filtered/compatible snap records instead of repeatedly casting through every possible buildable class
- snap collision volumes are Query Only and do not generate unnecessary physics/overlap gameplay
- wall family variants share common logic instead of duplicated placement graphs
- simple collision should be used where it correctly represents the wall/opening
- server validates only on meaningful placement requests
- permanent buildings use normal World Partition/HLOD/relevancy rules
- repeated modular pieces can use optimized instancing/rendering strategies where appropriate
- construction damage/destruction obeys physics budgets

Controller support must not be implemented through expensive per-frame polling hacks. Enhanced Input actions and contextual mappings drive controller behavior.

---

# 25. Python Editor Tooling Upgrade

Python can later assist development by:

- batch-generating Buildable Definition assets
- generating/updating Data Table rows
- validating duplicate Buildable/Family/Variant IDs
- validating missing preview assets
- validating soft references
- validating collision/query configuration
- checking wall-opening collision does not accidentally block the opening
- checking door/window attachment slot metadata
- checking Nanite settings
- checking snap sockets/tags
- checking missing `BPI_MW_BuildSnapProvider` implementation on snap-capable actors
- checking duplicate Snap Point IDs
- checking snap-volume collision profiles
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
5. Wall family offers Standard -> DoorOpening -> WindowOpening variants.
6. Selected Buildable/Variant ID survives list/filter changes correctly.
7. Changing selection/variant refreshes ghost mesh, collision preview, opening metadata, costs and rules.
8. Camera trace finds candidate surface.
9. Ghost follows candidate transform.
10. Green/red feedback reflects placement validity.
11. Foundation/floor/wall Actors implement `BPI_MW_BuildSnapProvider` where appropriate.
12. Box Collision or equivalent query volumes expose practical snap acquisition areas.
13. Foundation/floor wall-edge snap points accept all valid initial wall variants.
14. `DetectCompatibleSnapPoints` chooses a valid nearby snap point without scanning the whole world.
15. Invalid or occupied snap combinations are rejected.
16. Standard wall collision blocks solid wall space correctly.
17. DoorOpening wall leaves a usable doorway opening.
18. WindowOpening wall leaves a correct window opening.
19. Snap query volumes do not block player movement.
20. Grid rotation works.
21. Build timer stops outside build mode.
22. Property boundary prevents illegal placement.
23. Builder qualification gates a structural piece.
24. Required resources/cost are checked per variant.
25. Client preview is responsive.
26. Server resolves Buildable/Variant ID + Parent Structure ID + Snap Point ID and re-validates final placement.
27. Client cannot spoof Actor Class/mesh/cost/CanBuild/snap occupancy.
28. Successful building receives persistent Structure ID/ownership/variant state.
29. Save/load restores structure, variant, opening and snap/support relationships.
30. Another player without permission cannot modify it.
31. The entire construction flow can be completed with keyboard/mouse.
32. The entire construction flow can be completed with an Xbox-style controller.
33. The entire construction flow can be completed with a PlayStation-style controller.
34. Performance remains stable while previewing/cycling/variant-switching/snapping/building.

---

# 27. Approved Future Upgrades

- foundations/support system
- walls/floors/roofs/stairs
- standard/door-opening/window-opening wall families
- actual placeable doors and windows connected to opening attachment slots
- multiple door/window sizes and styles
- socket snapping
- snap occupancy/reservation rules
- snap-point priority/scoring profiles
- snap-tag visualization/debugger
- freeform furniture placement
- build catalog search/filter/favorites/recently used
- blueprint/house-plan presets
- copy/rotate/mirror tools
- multi-select renovation tools
- authorized wall-opening conversion/renovation
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

> Metaworld construction is modular, data-driven, catalog-driven, family/variant-aware, interface-driven, snap-aware, controller-compatible, property-aware, profession-aware, multiplayer-authoritative, persistent and performance-budgeted. Standard walls, door-opening walls and window-opening walls share one scalable wall system while retaining the collision, opening, attachment and structural differences that make each variant real gameplay geometry. The ghost helps the player decide where to build; the server and the world rules decide what actually exists.