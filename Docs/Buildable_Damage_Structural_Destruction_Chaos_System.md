# Metaworld — Buildable Damage, Structural Destruction & Chaos System

**Status:** Canonical / Approved Phase 20 + Phase 36 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld buildables can receive persistent world damage and transition into damaged, breached, destroyed or collapsed states, while Unreal Engine 5.8 Chaos Destruction provides fracture presentation where it is appropriate and performance-safe.

Core rule:

> The server owns damage, durability, destruction state and structural consequences. Chaos owns the relevant local fracture presentation; debris becomes authoritative only when gameplay explicitly requires it.

The UE4 tutorial concepts of per-buildable health, a common damage interface, one-time death handling, destructible visual replacement and multi-part window handling are approved. The tutorial's APEX Destruction implementation is not adopted for new Metaworld content; new destruction content uses UE5.8 Chaos Destruction / Geometry Collections where real-time fracture is justified.

---

# 1. Phase Ownership

This system crosses two roadmap phases without creating a duplicate system.

## Phase 20 — Construction / Persistent Buildable State

Phase 20 owns:

- buildable durability/condition data
- persistent damage state
- structure/object identity
- ownership/property relationship
- repair eligibility
- opening/support/snap consequences
- save/load state
- server-authoritative transition to Destroyed / Breached / Removed
- integration with `BP_MW_Buildable_Master`

## Phase 36 — Destruction / Collapse Presentation & Damage Consequences

Phase 36 owns:

- Chaos Geometry Collection fracture presentation
- controlled debris
- impact/explosion/weapon destruction presentation
- structural-collapse presentation
- fracture/field tuning
- debris cleanup/significance budgets
- destruction effects, particles, dust, sound and related world presentation

Damage therefore begins as ordinary persistent world state and only escalates into Chaos simulation when the object's definition says that visual destruction is justified.

---

# 2. Canonical Damage Capability

Recommended shared capability:

`BPI_MW_Damageable`

or equivalent reusable damage contract.

Possible Blueprint-facing functions/events:

- `CanReceiveDamage`
- `RequestApplyDamage`
- `GetDamageState`
- `GetDurability`
- `GetMaxDurability`
- `OnDamageStateChanged`
- `OnDestroyedAuthoritatively`

A reusable Actor Component such as:

`BPC_MW_Damageable`

may own generic durability/state behavior when many unrelated world objects need the same logic.

`BP_MW_Buildable_Master` may host the component or common hooks, but the master should not absorb every family-specific destruction implementation.

---

# 3. Buildable Definition Damage Data

A Buildable / Variant Definition can include damage/destruction metadata such as:

- `MaxDurability`
- `DamageProfileID`
- `ResistanceTags`
- `VulnerabilityTags`
- `Armor / MaterialClass`
- `DamageStateThresholds`
- `RepairProfileID`
- `DestructionPresentationMode`
- `GeometryCollectionAsset` where applicable
- `DestroyedStaticRepresentation` where cheaper than Chaos
- `DestroyedCollisionProfile`
- `DebrisProfileID`
- `StructuralFailurePolicy`
- `OpeningFailurePolicy`
- `UtilityFailurePolicy`
- `CanBeBreached`
- `CanBeRepaired`
- `CanBeSalvagedAfterDestruction`
- `DamageZoneDefinitions[]` for prefab/logical sections where needed

The tutorial's simple `Health` and `Destructible Mesh` fields are therefore retained as the seed of a richer data-driven definition rather than copied literally as two universal variables.

---

# 4. Damage State Model

Do not rely on one `isDead` Boolean as the complete world state.

Recommended high-level states can include:

- `Intact`
- `Damaged`
- `Critical`
- `Breached`
- `Destroyed`
- `Collapsed`
- `Removed`

Not every object uses every state.

Examples:

### Standard Wall

`Intact -> Damaged -> Critical -> Breached/Destroyed`

### Window

`Intact -> Cracked/Damaged -> Broken/Breached`

### Door

`Intact -> Damaged -> Breached/Destroyed`

### Support Pier

`Intact -> Damaged -> Critical -> StructuralFailure`

A lightweight guard such as `HasProcessedDestruction` can still prevent duplicate terminal handling, but it is an implementation guard rather than the canonical gameplay state.

---

# 5. Damage Inputs

Possible legitimate damage sources include:

- melee
- firearms
- explosives
- vehicle impact
- fire
- weather/disaster
- structural collapse
- supernatural/magic damage
- authorized demolition tools
- construction accident
- scripted/world-event damage

Damage uses typed data/tags so materials and structures can respond differently.

Examples:

- reinforced concrete resists small-caliber damage
- glass is vulnerable to impact
- wooden structures are vulnerable to fire
- security doors resist ordinary melee
- supernatural damage may use configured resistances

The client never decides final damage or durability reduction for authoritative multiplayer state.

---

# 6. Server-Authoritative Damage Flow

Recommended flow:

`Damage Source`
-> submit/resolve hit or damage event
-> server validates source, target, range/context and applicable rules
-> server resolves authoritative damage profile
-> server applies resistance/material/armor rules
-> server changes durability/state
-> server evaluates breach/destruction/support consequences
-> server persists significant state
-> relevant clients receive compact state/destruction event
-> clients play appropriate visual/audio/Chaos presentation

The client cannot set `Health = 0`, mark `Destroyed = true`, substitute a weaker damage profile or spawn authoritative destruction by itself.

---

# 7. Chaos Destruction / Geometry Collections

For new UE5.8 content, Metaworld's real-time fracturing path is Chaos Destruction using Geometry Collections when justified.

A buildable can normally exist as an efficient finished representation.

When terminal destruction occurs, its destruction profile may:

1. hide/replace the intact visual representation;
2. update authoritative gameplay collision/state;
3. activate/spawn a prepared Geometry Collection or other destruction representation;
4. apply strain/impulse/Physics Field behavior appropriate to the damage event;
5. run fracture/debris simulation only while relevant;
6. sleep/disable/clean up fragments according to budget;
7. transition to a cheap persistent destroyed representation once active simulation is no longer needed.

Not every buildable needs a Geometry Collection.

Cheap alternatives are approved for ordinary/low-significance objects:

- destroyed static mesh
- pre-broken mesh variant
- decals/material damage
- hidden section + debris Niagara
- lightweight debris actors
- state-only destruction when offscreen/unloaded

Chaos is a presentation tool, not a requirement that every object becomes a persistent physics simulation.

---

# 8. Fracture Hierarchy & Structural Tuning

Geometry Collections can use authored fracture hierarchy/clustering so a structure does not always explode into tiny fragments immediately.

Destruction profiles can define:

- fracture levels
- cluster thresholds
- strain thresholds
- impact behavior
- anchored/world-supported sections
- debris size classes
- sleep/disable thresholds
- cleanup time/policy
- maximum active fragments
- significance distance
- whether the object may crumble progressively or fail as a larger section

Large buildings should not be authored as one unbounded Geometry Collection containing the entire property unless profiling proves that design safe.

Prefer logical zones/sections so destruction can be localized and budgeted.

---

# 9. Gameplay Collision vs Chaos Shards

Authoritative gameplay state must not depend on every client simulating identical individual fragments.

When a wall becomes destroyed, the server decides the real gameplay consequence, for example:

- solid wall collision removed
- breach opening created
- traversal allowed
- cover value reduced
- room/weather/security boundary changed
- support relationship invalidated

Nearby clients can simulate visual rubble with Chaos.

If specific debris must have gameplay authority, such as a large collapsed beam blocking a doorway, create or promote a small number of authoritative debris/blockage objects.

Do not replicate every shard as a critical persistent network object by default.

---

# 10. Structural Support Consequences

Destroyed support-bearing buildables integrate with the existing support graph.

Examples:

- foundation extension destroyed
- structural column destroyed
- load-bearing wall destroyed
- upper-floor support destroyed
- stair support destroyed

Flow:

`Support object reaches structural-failure state`
-> update support graph
-> reevaluate dependents on meaningful event
-> mark stable / unstable / unsupported according to configured rules
-> trigger repair/evacuation/collapse behavior where required

The game does not need finite-element engineering, but it must not allow a multi-story structure to remain logically supported after every required support is gone.

Support reevaluation is event-driven, not a permanent per-frame graph scan.

---

# 11. Window / Door Multi-Part Handling

The tutorial's special handling for two window child parts is generalized into explicit part/zone definitions.

A window or door can contain:

- one panel
- two panels
- glass + frame
- shutters
- multiple panes
- sliding sections
- reinforced security components

Damage can target logical parts/zones such as:

- Frame
- PanelLeft
- PanelRight
- GlassPaneA
- GlassPaneB
- Lock
- Hinge

The object definition decides whether damage is shared, per-part or hybrid.

A two-panel window does not require a hardcoded special case in `BP_MW_Buildable_Master`.

---

# 12. Openings, Security & Breach State

Door/window destruction connects to the existing opening/attachment architecture.

Examples:

- broken window makes the opening traversable according to dimensions
- breached door may no longer lock
- destroyed door can remain attached as damaged debris or detach visually
- reinforced door may transition to Breached before Destroyed

The structural wall opening remains separate from the installed door/window object.

Destroying the installed door does not automatically destroy the wall.

Destroying the wall resolves the installed object/opening relationship according to authoritative parent-child rules.

---

# 13. Prefab Damage Zones

A prefab house may use optimized merged visual geometry while still exposing logical damage zones.

Example zones:

- FrontWall_A
- RearWall_B
- RoofSection_01
- PorchSupport_A
- GarageWall
- UtilityRoomExterior

Damage to one zone should not automatically reduce an entire house to one universal health bar unless that prefab deliberately uses a simplified arcade profile.

Prefab damage state remains compatible with merged/Nanite visual shells because rendering representation and authoritative logical damage data are separate.

---

# 14. Construction Stage Damage

Unfinished structures can also receive damage.

A construction site may have stage-specific durability/collision/damage behavior:

- Blueprint/plan: normally no physical durability
- footing/frame: exposed and easier to damage
- partially completed wall: partial collision/durability
- completed structure: final profile

Destroyed unfinished work can lose consumed materials, require repair/rework or be dismantled/salvaged according to the construction-progress rules.

Damage never becomes a free refund mechanism.

---

# 15. Repair Integration

Damage is persistent enough to support real repair gameplay.

Repair can require:

- owner/authorized access
- Builder or appropriate profession
- tools
- materials
- Construction/Repair Work Units
- utility isolation where relevant
- inspection for critical structures where configured

Repair can restore condition in stages rather than instantly setting `Health = MaxHealth`.

Future repair jobs can be generated from actual damaged structures and feed Builder/company role duties.

---

# 16. Crime, Evidence & Insurance Integration

Unauthorized property destruction is not construction-management removal.

When world rules classify the action as illegal, it can create:

- property-damage crime event
- witnesses
- camera evidence
- weapon/tool/impact evidence where supported
- repair cost
- owner notification
- police/security duties
- insurance claim data later
- Event Ledger/news significance for major destruction

Authorized demolition uses the construction/demolition system instead.

---

# 17. Persistence

Persist compact gameplay state, not active fragment simulation.

Store as appropriate:

- Structure/Object ID
- Buildable/Variant ID
- durability/condition
- damage state
- damaged zone/part states
- breach state
- support status
- installed/opening relationship changes
- utility consequences
- destroyed/collapsed timestamp
- repair state
- relevant cause/event reference

On load/unstream:

- intact objects load intact representation
- damaged objects load damaged representation/state
- destroyed objects load a stable destroyed representation
- active Chaos simulation is only recreated when specifically useful, not replayed forever by default

---

# 18. Multiplayer Replication

Replicate compact meaningful state such as:

- durability/state changes where relevant
- damage zone changes
- breach state
- authoritative destruction event
- destruction seed/profile/event parameters where useful for presentation
- support-failure result
- authoritative blocked/open collision state

Do not replicate full transform updates for hundreds of Chaos shards by default.

Clients reconstruct local fracture presentation where safe.

Late-joining clients receive the persistent settled damage/destroyed state rather than replaying every historical fragment trajectory.

---

# 19. Performance / Smoothness Rules

Metaworld's smoothness requirement is mandatory.

Rules:

- no permanent Tick just to check buildable health
- damage is event-driven
- no Geometry Collection simulation for every intact buildable
- fracture only when relevant and supported by the object's destruction profile
- cap active fragments/debris by significance and quality tier
- use sleep/disable/cleanup behavior
- use cheap destroyed representations after active fracture has served its purpose
- use distance/significance to reduce or skip expensive destruction presentation
- unloaded/distant destruction resolves as persistent data/state without requiring full local physics simulation
- avoid whole-building Geometry Collections when sectional destruction is more scalable
- use Niagara/audio/dust selectively
- profile destruction-heavy scenes with Unreal Insights/GPU/physics tools

Worst-case tests should include multiple nearby walls/windows/doors failing during combat while NPCs, replication, weather and building-support updates are also active.

---

# 20. Nanite / Rendering Rules

Intact and settled construction meshes remain Nanite-first where compatible.

Destruction representation is chosen according to UE5.8 feature compatibility and profiling rather than forcing one rendering path.

A buildable can use:

- Nanite-compatible intact representation
- Chaos Geometry Collection destruction representation when appropriate
- alternate damaged/destroyed representation where cheaper or more reliable

The existence of a destruction path does not justify keeping every intact structure in an expensive physics-ready state.

---

# 21. Python Editor Tooling

Python Editor automation can later audit:

- missing durability/damage profiles
- missing destruction presentation assets
- invalid Geometry Collection references
- excessive fracture piece counts
- missing/invalid damage zones
- damageable structural pieces without support-failure policy
- windows/doors lacking part definitions
- prefabs missing logical damage zones
- destroyed collision setup
- heavy assets loaded directly instead of soft-referenced where appropriate
- naming/folder rules
- performance metadata

Python remains Editor tooling, not runtime damage logic.

---

# 22. Initial Vertical-Slice Tests

The construction/destruction vertical slice should prove:

1. Standard wall receives server-authoritative damage.
2. Client cannot directly set wall durability/destruction state.
3. Wall transitions through configured damage states.
4. Terminal destruction happens once; repeated hits do not duplicate destruction actors/effects.
5. Destroyed wall updates authoritative collision/traversal.
6. Nearby client sees Chaos or approved fracture presentation.
7. Late-joining client sees correct settled destroyed state without requiring historical shard replay.
8. Window can damage/break independently from its wall opening.
9. Two-panel/multi-part window uses data-driven part handling rather than one hardcoded second-part special case.
10. Door can become breached while wall remains intact.
11. Destroying a support-bearing piece triggers event-driven support revalidation.
12. Unsupported dependent floor becomes unstable/fails according to configured rules.
13. Unauthorized property damage feeds crime/evidence hooks.
14. Authorized demolition still uses the demolition workflow rather than combat damage hacks.
15. Repair can restore an eligible damaged structure using real materials/work.
16. Destroyed construction site cannot mint/refund extra resources.
17. Multiple simultaneous nearby destruction events remain inside frame/physics/network budgets.
18. Distant/unloaded destruction can resolve to state without running full Chaos simulation.
19. Keyboard/mouse, Xbox-style and PlayStation-style combat/interaction paths produce the same authoritative damage results.
20. Save/load restores damaged/breached/destroyed state and structural relationships correctly.

---

# Core Rule

> Metaworld destruction is persistent gameplay state first and physics spectacle second. Damage, ownership, collision, openings, support failure, crime, repair and persistence are server-authoritative. UE5.8 Chaos/Geometry Collections provide controlled fracture presentation only where they add value without violating the smoothness budget.