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
- persistent parent/child relationships are typed gameplay relationships, not one generic child Actor array; parent failure resolves according to support/attachment/utility/occupancy semantics and configured failure policies.
- Chaos/Geometry Collection fracture hierarchy is destruction presentation inside an object and never replaces Metaworld's persistent cross-buildable relationship graph.

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

## Episode Upgrade 17 — Hierarchical Destruction & Persistent Structure Relationships

**Classification:** UPGRADE — APPROVED

**Phase Ownership:** Phase 20 persistent relationship/support graph + Phase 36 destruction/collapse consequences.

Approved:

- tutorial goal of preventing floating/orphaned child buildables after a parent is destroyed is fully retained
- tutorial `BuildChildren[]` Actor array is upgraded into typed persistent structure relationships keyed by stable Structure/Object IDs
- recommended relationship record includes RelationshipID, ParentStructureID, ChildStructureID, RelationshipType, relevant Snap/Opening/Attachment IDs, support/required flags, failure policy and relationship state
- relationship types are explicitly separated rather than treating every child identically; initial types include structural support, installed attachment, surface attachment, snap occupancy, utility dependency, containment and movable group/module relationships
- physical support is distinct from ownership, placement parent, visual attachment and snap proximity
- support relationships may be many-to-one/many-to-many where a floor/roof/platform has multiple valid supports; the authoritative model is therefore a graph, not necessarily a strict tree
- destroying one support does not automatically destroy a dependent if configured alternate supports still satisfy structural requirements
- support loss triggers event-driven stability reevaluation: Stable / Degraded / Unstable / Unsupported according to configured structural rules
- installed Door/Window relationships are resolved when their wall/opening parent fails so functional floating doors/windows cannot remain after the opening no longer exists
- installed/surface children do not universally receive lethal damage; relationship failure policies may destroy, detach, drop, salvage, preserve with alternate support, transfer, disable, disconnect utility or block parent removal until resolved
- tutorial pattern `ForEach Child -> Deal massive damage -> Delay -> Destroy Parent` is rejected as permanent architecture
- synthetic maximum damage is avoided because it can create incorrect damage/crime attribution, salvage exploits, unnecessary VFX and uncontrolled deep cascades
- authoritative parent destruction resolves relationship consequences directly; actual damage is applied only when the configured failure profile calls for it
- arbitrary Blueprint `Delay` is not used as the correctness mechanism for destruction ordering
- server uses an authoritative relationship-resolution transaction/queue: terminal parent state -> load relevant relationships -> update collision/opening/support truth -> resolve attachments/utilities -> reevaluate dependents -> queue secondary failures -> clean occupancy -> persist -> broadcast presentation event
- tutorial `Avoid Adding as Child` Boolean is rejected as a universal special case
- foundations are valid roots when directly supported by terrain but can also legitimately be children/dependents of piers, footings, foundation extensions or engineered support frames; legality comes from relationship/support definitions rather than one Boolean
- door/window structural opening remains separate from installed object; wall destruction resolves the installed object's policy without confusing the two identities
- surface-mounted items such as shelves, signs, TVs, cameras and electrical boxes may detach/drop/disable rather than all being destroyed
- container/inventory state remains authoritative during parent failure; relationship destruction cannot duplicate or erase contents through local visual effects
- utility relationships can disconnect/fail service without necessarily destroying connected devices
- prefab houses keep logical relationships even when visual geometry is merged/Nanite optimized; destruction of one logical zone resolves only its relevant dependents unless authored rules require a wider failure
- demolition and renovation use the same relationship graph to preview dependents, cascade risk, attachments, utilities and blocked-removal conditions before committing changes
- relocation uses the same graph; support-bearing pieces cannot be moved while unresolved dependents exist, installed objects require compatible destination slots, and declared modules may move as groups
- destruction cascades preserve causal attribution: direct attacker/event -> directly destroyed support -> secondary structural collapse consequences; secondary failures are not falsely recorded as identical direct hits
- relationship graph validation rejects self-parenting, missing IDs, duplicate exclusive occupancy, invalid type pairings and forbidden structural-support cycles
- large cascades use visited StructureID sets, deterministic queues, deduplication, bounded transaction work and one terminal transition per structure rather than uncontrolled Blueprint recursion
- client cannot add/delete/forge relationships, claim nonexistent alternate support, protect a child from authoritative failure, invent griefing children or bypass occupancy cleanup
- relationships persist independently of Actor streaming; unloaded child state still resolves through persistent IDs when a parent is destroyed
- runtime Actor references may be cached while relevant but are not the only relationship truth
- no permanent Tick to check whether parents are alive; relationships are registered/updated on placement, installation, renovation, relocation, demolition and meaningful damage events
- no whole-world child search during destruction; query direct relationship edges and only affected support dependents
- Chaos Geometry Collection fracture hierarchy remains separate from the persistent Metaworld relationship graph; Chaos clusters/bones present one object's fracture while server relationships resolve whole-buildable consequences
- `BP_MW_Buildable_Master` may expose generic relationship lifecycle hooks but does not contain a giant family-specific destruction switch
- reusable Blueprint concepts may include `S_MW_StructureRelationship`, `BPI_MW_StructureRelationshipParticipant`, `BPC_MW_StructureRelationships` and a persistent relationship registry/service compatible with Blueprint-first architecture
- Python Editor tooling can audit relationship metadata, invalid cycles, orphaned Opening/Snap IDs, missing failure policies, legacy child-array-only logic and overly expensive dependency graphs
- controller input requires no special child-destruction path; keyboard/mouse, Xbox-style and PlayStation-style players produce the same authoritative damage/removal relationship results

Detailed companion: `Docs/Structural_Relationship_Hierarchical_Destruction_System.md`

---

# Current Phase 20 / Phase 36 Construction-Damage Stack

`BP_MW_Buildable_Master + Components / Interfaces / Data`

`-> Construction / Placement / Typed Relationship Graph / Support / Persistence`

`-> Completed or Unfinished Physical Structure`

`-> Authoritative Damage Event`

`-> Durability / Damage-State Transition`

`-> Relationship Resolution: Attachments / Utilities / Occupancy / Support`

`-> Alternate-Support Re-evaluation / Stable-Unstable-Collapse Decision`

`-> Phase 36 Chaos / Geometry Collection Presentation where appropriate`

`-> Debris Budget / Sleep / Disable / Cleanup`

`-> Stable Persistent Damaged / Breached / Destroyed / Detached State`

`-> Repair / Salvage / Crime / Insurance / Reconstruction later`

---

# Destruction Principle

> Metaworld destruction is persistent gameplay state first and physics spectacle second. Damage, ownership, collision, openings, support failure, crime, repair and persistence are server-authoritative. Chaos/Geometry Collections provide controlled fracture presentation only where they add value without violating the smoothness budget.

---

# Relationship / Hierarchical Destruction Principle

> Metaworld does not destroy a build hierarchy by blindly killing every child Actor. It maintains typed persistent relationships. When a parent fails, the server resolves support, attachments, utilities, occupancy and dependents according to explicit failure policies and alternate-support rules; Chaos then presents the physical result without becoming the source of gameplay truth.

---

# Playlist Continuation Rule

Future playlist episodes may be appended to this Part 3 continuation. Parts 1, 2 and 3 together are the canonical Phase 20 playlist intake log until final consolidation into the Master Roadmap.