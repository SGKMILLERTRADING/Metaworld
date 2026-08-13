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

The system is inspired by the modular Blueprint pattern in the supplied UE4 base-building tutorial, but adapted to Metaworld's UE5.8 Blueprint-first, multiplayer, property, profession, persistence and performance architecture.

---

# 1. Build Component

`BPC_MW_BuildComponent` should own build-mode state and construction flow.

Suggested state:

- `BuildModeOn`
- `CanBuild`
- `SelectedBuildableDefinition`
- `GhostActor`
- `CurrentPlacementTransform`
- `CurrentPlacementReason`
- `BuildRange`
- `GridSize`
- `RotationStep`
- `PlacementUpdateInterval`
- `CurrentPropertyID`
- `CurrentBuildPermissionState`

The component receives references/interfaces it needs from the owning character rather than becoming tightly coupled to a specific child Blueprint.

---

# 2. Input and Build-Mode Activation

Do not permanently hardcode construction to the `B` key.

Use Enhanced Input with a dedicated build action, for example:

`IA_MW_ToggleBuildMode`

The player may later rebind it.

Build-mode flow:

`Input -> Toggle Build Mode -> Validate basic eligibility -> Spawn/enable ghost -> Start placement updates`

Exiting build mode:

- destroy or hide ghost
- stop placement timer
- clear temporary selection state
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

The trace produces a candidate surface/location, then the placement validator resolves the final transform.

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

The ghost is presentation only. It never authoritatively creates ownership or a permanent structure.

The preview should use a low-cost material/material-instance strategy and avoid unnecessary high-cost effects.

---

# 5. Timer-Based Build Cycle

Metaworld should not run expensive construction traces on every frame by default.

When build mode is active:

`Timer -> Update Candidate Placement -> Validate -> Move Ghost -> Update Ghost State`

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
3. Candidate surface exists
4. Candidate within allowed build range
5. Candidate inside an allowed property/build volume
6. Player has build permission for that property
7. Player meets profession/qualification requirement where required
8. Required permit/license exists where applicable
9. Required resources/cost are available
10. Grid/socket/freeform placement rule passes
11. Collision/overlap rule passes
12. Slope/ground rule passes
13. Structural/support rule passes where applicable
14. Height/air-right/subsurface rule passes
15. Utility/zoning restrictions pass where applicable
16. Server performs final authoritative re-validation

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

# 9. Data-Driven Buildable Definitions

Do not create separate hardcoded logic graphs for every wall, floor or furniture piece.

Use a Buildable Definition Data Asset/structure.

Suggested fields:

- Buildable ID
- Display Name
- Category
- Mesh/representation
- Ghost mesh/preview settings
- Nanite compatibility/default
- Footprint/bounds
- Grid size override
- Allowed rotation steps
- Socket types
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

---

# 10. Placement Modes

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

# 11. Rotation and Adjustment

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

# 12. Multiplayer Authority

Client:
- enters build mode
- performs responsive local preview
- moves ghost
- displays valid/invalid feedback

Server:
- re-checks final transform
- checks property rights
- checks profession/licenses
- checks inventory/resources/currency
- checks collision/structural/world rules
- consumes resources/payment atomically
- spawns/registers permanent structure
- creates ownership/persistence record

Never trust a client-supplied `CanBuild = true` as authoritative.

---

# 13. Economy and Resource Integration

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

# 14. Persistence

Permanent structures require persistent records.

Minimum record:

- Structure ID
- Buildable Definition ID
- Owner/organization/property ID
- World transform
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

# 15. Construction Stages

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

# 16. Structural Rules

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

# 17. Utilities

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

# 18. Repair, Renovation and Demolition

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

# 19. Nanite and Rendering

Use Nanite for compatible permanent construction meshes where it benefits Metaworld and does not break required functionality.

The build system should not need separate gameplay rules because a mesh uses Nanite.

Preview/ghost representation may use a simpler presentation path if that is cheaper and more reliable.

---

# 20. Performance Rules

Construction must obey Metaworld's smoothness policy.

Rules:

- no placement trace when build mode is off
- prefer timer/event updates over unconditional Tick
- ghost is one temporary preview representation, not repeated permanent spawning
- cache selected Buildable Definition
- avoid scanning all nearby structures every update
- use targeted traces/overlaps/query volumes
- server validates only on meaningful placement requests
- persistent buildings use normal World Partition/HLOD/relevancy rules
- repeated modular pieces can use optimized instancing/rendering strategies where appropriate
- construction damage/destruction obeys physics budgets

---

# 21. Python Editor Tooling Upgrade

Python can later assist development by:

- batch-generating Buildable Definition assets
- validating missing preview assets
- validating collision
- checking Nanite settings
- checking sockets
- checking material/texture requirements
- checking footprint/bounds metadata
- reporting missing profession/permit/resource fields
- auditing performance-cost metadata

Python remains editor tooling, not packaged runtime construction logic.

---

# 22. Initial Vertical-Slice Construction Test

The first town should prove:

1. Player toggles build mode through Enhanced Input.
2. `BPC_MW_BuildComponent` activates.
3. Camera trace finds candidate surface.
4. Ghost follows candidate transform.
5. Green/red feedback reflects placement validity.
6. Grid rotation works.
7. Build timer stops outside build mode.
8. Property boundary prevents illegal placement.
9. Builder qualification gates a structural piece.
10. Required resources/cost are checked.
11. Client preview is responsive.
12. Server re-validates final placement.
13. Successful building receives persistent Structure ID/ownership.
14. Save/load restores structure.
15. Another player without permission cannot modify it.
16. Performance remains stable while previewing/building.

---

# 23. Approved Future Upgrades

- foundations/support system
- walls/floors/roofs/stairs
- doors/windows
- socket snapping
- freeform furniture placement
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

> Metaworld construction is modular, data-driven, property-aware, profession-aware, multiplayer-authoritative, persistent and performance-budgeted. The ghost helps the player decide where to build; it never overrides the rules of the world.
