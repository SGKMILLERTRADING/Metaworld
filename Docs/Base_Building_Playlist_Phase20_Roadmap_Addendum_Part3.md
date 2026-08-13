# Metaworld — Base-Building Playlist Phase 20 Roadmap Addendum — Part 3

**Status:** Canonical / Approved Phase 20 Intake Log Continuation

**Continues:** `Docs/Base_Building_Playlist_Phase20_Roadmap_Addendum_Part2.md`

**Base Master Roadmap:** `Docs/Master_Development_Roadmap.md` v2.9

**Purpose:** Continue recording approved tutorial-playlist upgrades without repeatedly replacing the increasingly large Part 2 addendum. Parts 1, 2 and 3 are equally canonical Phase 20 intake material and will be consolidated into the Master Roadmap after the playlist review is complete.

## Permanent Rules Carried Forward

All permanent rules from Parts 1 and 2 remain active, including:

- Blueprint-first runtime architecture.
- `BP_MW_Buildable_Master` owns only common persistent buildable lifecycle; capabilities remain interface/component/data driven.
- stable Buildable/Family/Variant IDs and authoritative Buildable Definitions.
- server-authoritative placement, ownership, construction state, relocation, demolition and persistent world state.
- keyboard/mouse, Xbox-style controllers and PlayStation-style controllers remain first-class player-facing input paths.
- Nanite-first rendering wherever compatible.
- stable frame time takes priority over spectacle.
- damage/destruction must integrate with support, property, crime/evidence, repair, persistence and performance rather than exist as an isolated effect.

---

# Playlist Intake Status — Continued

## Episode Upgrade 16 — Buildable Damage & Destructible Structures

**Classification:** UPGRADE — APPROVED

**Phase Ownership:** Phase 20 persistent buildable damage state + Phase 36 destruction/collapse presentation.

Approved:

- tutorial per-buildable Health concept retained as durability/condition data in authoritative Buildable/Variant Definitions
- tutorial destructible-mesh reference retained conceptually as a data-driven destruction presentation profile
- new Metaworld destruction content does not depend on the UE4 APEX Destruction workflow; UE5.8 Chaos Destruction / Geometry Collections are the approved real-time fracture path when appropriate
- damage remains Blueprint-first and can use a common `BPI_MW_Damageable` capability plus reusable `BPC_MW_Damageable` component where useful
- `BP_MW_Buildable_Master` may host shared damage hooks/component references but does not absorb every family-specific fracture graph
- Buildable Definition damage data can include MaxDurability, material/armor class, resistance/vulnerability tags, state thresholds, repair profile, destruction presentation mode, Geometry Collection reference where applicable, destroyed representation, debris profile, support/opening/utility failure policies and logical damage zones
- tutorial `isDead` Boolean is upgraded into explicit world states such as Intact, Damaged, Critical, Breached, Destroyed, Collapsed and Removed according to object type
- a local one-time guard such as `HasProcessedDestruction` may prevent duplicate terminal processing but is not the authoritative gameplay state
- damage sources can include melee, firearms, explosives, vehicles, fire, weather/disasters, structural collapse, supernatural/magic damage, demolition tools and other world-event damage
- server validates damage source/context/profile and applies authoritative durability/state changes; clients cannot directly set Health to zero or mark an object destroyed
- authoritative destruction updates real gameplay collision, opening/traversal state, cover/security state, support relationships and persistence before/alongside local visual fracture
- Chaos Geometry Collections are used selectively for high-value fracture presentation rather than keeping every intact buildable in active destruction simulation
- prepared Geometry Collections may activate/spawn only when terminal destruction occurs, then sleep/disable/clean up according to significance and budget
- cheaper destruction representations are approved for ordinary/distant objects: destroyed static meshes, pre-broken variants, material damage, Niagara/debris effects or state-only resolution when unloaded
- Geometry Collection fracture hierarchy/clustering, strain thresholds, anchor/world-support behavior and Physics Fields may be used to control fracture presentation
- active debris/fragment count is budgeted; Metaworld does not network every Chaos shard as an authoritative persistent object
- server owns destroyed/breached world state; nearby clients may reconstruct Chaos fracture presentation locally from compact destruction events/state
- when specific rubble must affect gameplay, spawn/promote a small number of authoritative blockage/debris proxies rather than making every shard network-critical
- late-joining clients load the settled persistent damaged/destroyed state and do not need every historical fragment trajectory replayed
- destroyed support-bearing walls, columns, piers, foundation extensions and other structural pieces trigger event-driven support-graph reevaluation
- multi-story structures cannot remain logically supported after required supports are destroyed merely because visual rubble still exists
- tutorial special handling for a two-part window is generalized into data-driven logical part/damage-zone definitions for glass panes, frames, panels, locks, hinges, shutters and other multi-part doors/windows
- installed Door/Window destruction remains separate from structural wall-opening destruction: breaking a door does not automatically destroy its wall
- broken/breached Door/Window state can change locking, security, traversal, weather exposure and future crime/evidence behavior
- prefab houses can keep optimized merged/Nanite visual shells while storing logical damage zones so one damaged section does not automatically become one whole-house health bar unless deliberately simplified
- unfinished construction stages can receive stage-appropriate damage; damage never becomes a free material-refund exploit
- repair integrates with real materials, Builder/appropriate profession, tools, Repair/Construction Work Units and authorization
- unauthorized property destruction routes into crime/evidence/police/security/insurance hooks rather than construction-management deletion
- persist compact durability/state/zone/breach/support/repair data, not long-lived active fragment physics
- no permanent Tick for buildable health; damage is event-driven
- no active Geometry Collection for every intact wall/floor/window
- use significance/distance/quality-tier limits, sleep/disable/cleanup and cheap settled destroyed representations
- intact/settled construction remains Nanite-first where compatible; destruction representation is chosen separately according to UE5.8 feature support and profiling
- Python Editor tooling can audit damage profiles, Geometry Collection references, fracture complexity, missing damage zones, support-failure policies, destroyed collision and performance metadata
- controller input remains consistent: keyboard/mouse, Xbox-style and PlayStation-style combat/interactions all resolve through the same authoritative damage rules

Detailed companion: `Docs/Buildable_Damage_Structural_Destruction_Chaos_System.md`

---

# Current Phase 20 / Phase 36 Construction-Damage Stack

`BP_MW_Buildable_Master + Components / Interfaces / Data`

`-> Construction / Placement / Support / Persistence`

`-> Completed or Unfinished Physical Structure`

`-> Authoritative Damage Event`

`-> Durability / Damage-State Transition`

`-> Opening / Security / Support / Collision Consequences`

`-> Phase 36 Chaos / Geometry Collection Presentation where appropriate`

`-> Debris Budget / Sleep / Disable / Cleanup`

`-> Stable Persistent Damaged / Breached / Destroyed State`

`-> Repair / Salvage / Crime / Insurance / Reconstruction later`

---

# Destruction Principle

> Metaworld destruction is persistent gameplay state first and physics spectacle second. Damage, ownership, collision, openings, support failure, crime, repair and persistence are server-authoritative. Chaos/Geometry Collections provide controlled fracture presentation only where they add value without violating the smoothness budget.

---

# Playlist Continuation Rule

Future playlist episodes may be appended to this Part 3 continuation. Parts 1, 2 and 3 together are the canonical Phase 20 playlist intake log until final consolidation into the Master Roadmap.