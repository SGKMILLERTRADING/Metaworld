# Metaworld — Structural Relationship & Hierarchical Destruction System

**Status:** Canonical / Approved Phase 20 + Phase 36 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld tracks persistent relationships between buildables so destruction, demolition, relocation, renovation, support failure and attachment removal can resolve dependents without leaving floating or orphaned world objects.

Core rule:

> A parent object being destroyed does not blindly apply lethal damage to every child. The server resolves each authoritative relationship according to its relationship type, dependency rules, alternate support and configured failure policy.

The UE4 tutorial concepts of registering child buildables when they are attached, maintaining a parent/child hierarchy and preventing floating doors/windows after parent destruction are approved. The tutorial implementation of one `Build Children` array, an `Avoid Adding as Child` Boolean and looping through every child with massive damage is upgraded into a typed, persistent, server-authoritative relationship graph.

---

# 1. Phase Ownership

This system extends two existing roadmap areas without creating a duplicate destruction system.

## Phase 20 — Construction / Persistent Relationships

Phase 20 owns:

- persistent parent/child and support relationships
- stable Structure/Object IDs
- relationship creation/removal
- snap/opening/support occupancy
- attachment compatibility
- relocation/demolition dependency checks
- save/load of structural relationships
- authoritative orphan prevention

## Phase 36 — Damage / Collapse Consequences

Phase 36 owns:

- destruction-driven relationship failure
- structural collapse consequences
- Chaos/Geometry Collection presentation where appropriate
- debris/collapse effects
- damage propagation where explicitly configured

The relationship graph is persistent gameplay data. Chaos fracture hierarchy is visual/physics presentation inside a destructible representation and does not replace the gameplay relationship graph.

---

# 2. Relationship Graph Instead of One Child Array

A simple `BuildChildren[]` Actor array is useful for a prototype but is not sufficient for Metaworld.

Metaworld should track relationships as explicit records.

Suggested structure:

`S_MW_StructureRelationship`

Possible fields:

- `RelationshipID`
- `ParentStructureID`
- `ChildStructureID`
- `RelationshipType`
- `ParentSnapPointID`
- `ChildSnapPointID`
- `OpeningID` where relevant
- `AttachmentSlotID` where relevant
- `SupportRole`
- `IsRequiredForStability`
- `FailurePolicy`
- `DetachPolicy`
- `TransferPolicy`
- `OccupancyPolicy`
- `CreatedTimestamp`
- `RelationshipState`
- optional local transform / attachment metadata

Persistent IDs are authoritative. Runtime Actor references may be cached while streamed/relevant but are not the only truth.

---

# 3. Canonical Relationship Types

Do not treat every parent/child link as the same kind of dependency.

Initial relationship types can include:

## `Structure.Support`

Examples:

- terrain/footing -> foundation extension
- foundation extension -> foundation
- foundation -> wall/column
- wall/column/beam -> upper floor
- structural frame -> roof

Loss may trigger stability reevaluation rather than immediate child destruction.

## `Structure.Attachment.Installed`

Examples:

- DoorOpening wall -> installed door
- WindowOpening wall -> installed window
- utility mounting point -> device
- security mounting point -> camera/alarm

Loss of parent normally requires detach, destruction, salvage/drop or another explicit policy.

## `Structure.Attachment.Surface`

Examples:

- wall -> sign
- wall -> shelf
- ceiling -> light fixture
- exterior wall -> decorative object

These are physically mounted but not necessarily structural.

## `Structure.SnapOccupancy`

Represents exclusive structural/catalog slot use.

Examples:

- foundation edge -> wall
- opening -> door
- opening -> window
- stair opening -> stair

It prevents duplicate placement even when physical meshes do not overlap.

## `Structure.Utility`

Examples:

- building service point -> breaker/panel
- water connection -> appliance/fixture
- electrical device -> powered parent circuit

Failure normally disconnects service rather than automatically destroying the child.

## `Structure.Containment`

Examples:

- prefab root -> logical section
- cabinet -> installed shelf/component
- equipment enclosure -> module

Containment does not automatically imply structural support.

## `Structure.Group / Module`

Used by deliberately movable prefabs/modules that can relocate as an authored group.

Additional relationship types may be added only when they express genuinely different world semantics.

---

# 4. Failure Policies

Each relationship can define what happens when the parent becomes Destroyed, Collapsed, Removed or otherwise invalid.

Possible policies:

- `ReevaluateSupport`
- `BecomeUnstable`
- `DestroyWithParent`
- `DetachAsWorldObject`
- `DetachAsDebris`
- `DropToGround`
- `UninstallAndSalvage`
- `RemoveWithParent`
- `PreserveIfAlternateSupport`
- `TransferToAlternateParent`
- `DisableOnly`
- `DisconnectUtility`
- `BlockParentRemovalUntilResolved`
- `CustomFamilyPolicy`

The policy is authoritative data, not hardcoded by one giant Blueprint switch whenever possible.

---

# 5. No Universal Massive-Damage Cascade

The tutorial's pattern:

`Parent destroyed -> ForEach BuildChild -> Deal huge damage -> Delay -> Destroy Parent`

is rejected as permanent Metaworld architecture.

Reasons:

- not every child should be destroyed
- some children may have alternate support
- some attachments should detach or drop
- utility connections should disconnect
- containers may preserve contents
- doors/windows may have salvage/damage rules
- support failure may propagate differently from direct damage
- artificial massive damage can create false crime/damage attribution
- artificial damage can create salvage/loot exploits
- arbitrary delay ordering can race with multiplayer persistence
- deep chains can cause uncontrolled cascades

Metaworld resolves relationship consequences directly through authoritative policies.

Damage is applied only when the relationship/failure profile says actual damage should occur.

---

# 6. Destruction Resolution Transaction

Recommended server flow when a persistent buildable reaches terminal destruction:

`Structure reaches Destroyed / Collapsed`
-> lock structure relationship transaction
-> load authoritative outgoing/incoming relationships
-> change parent gameplay collision/opening/support state
-> resolve installed/surface/utility children by relationship policy
-> reevaluate structural dependents and alternate supports
-> queue secondary failures only where required
-> clean or transfer snap/opening occupancy
-> update property/build-budget records
-> persist relationship changes
-> publish compact destruction/collapse events
-> clients play Chaos/visual presentation where relevant
-> release transaction lock

The server must not depend on a short Blueprint Delay to make relationship ordering correct.

---

# 7. Structural Support Is Not Simple Ownership

A support relationship answers:

`What is physically keeping this structure valid?`

It is separate from:

- owner
- property
- construction creator
- snap parent
- visual attachment

Example:

A second-floor panel may touch four walls/columns.

It may have multiple support relationships:

- Wall A -> Floor
- Wall B -> Floor
- Column C -> Floor

Destroying Wall A does not automatically destroy the floor if Wall B + Column C still satisfy the floor's configured support requirements.

Flow:

`Support lost`
-> reevaluate remaining valid supports
-> Stable / Degraded / Unstable / Unsupported
-> only trigger structural failure when configured requirements are no longer met

This prevents crude one-parent destruction cascades.

---

# 8. Multiple Parents / Alternate Support

The persistent relationship model is a graph, not necessarily a strict tree.

A buildable may legitimately have:

- one installation parent
- multiple structural supports
- one utility parent
- one property owner
- several neighboring snap relationships

Therefore a single `ParentActor` variable is not sufficient as the entire world model.

The runtime can still cache a primary placement parent for convenience, but authoritative stability/attachment rules come from typed relationships.

---

# 9. Foundations Do Not Need `Avoid Adding as Child`

The tutorial's `Avoid Adding as Child` Boolean is replaced by relationship rules.

A Foundation is not globally forbidden from being a child.

Examples:

- a ground foundation may terminate directly in approved terrain support
- an elevated foundation may depend on piers/footings/extensions
- a prefab foundation may be supported by an engineered frame

The system asks:

- what relationship is being created?
- is that relationship valid for this Buildable Definition?
- what does the child require for support?

No universal `AvoidAddingAsChild` special-case is required.

---

# 10. Door / Window Parent Failure

Canonical rule remains:

`DoorOpening wall != installed door`

`WindowOpening wall != installed window`

If the wall is destroyed, the installed object relationship must resolve.

Possible door outcomes by definition/world state:

- door destroyed with collapsing wall
- door detaches as damaged debris
- door becomes salvageable world object
- door already destroyed, relationship simply cleaned

Possible window outcomes:

- glass/frame destroyed
- window detaches/breaks
- lightweight debris only

The chosen outcome must not leave a functional floating door/window occupying an OpeningID whose wall no longer exists.

---

# 11. Surface-Mounted Objects

A wall may hold:

- shelf
- painting
- TV
- security camera
- alarm
- electrical box
- sign

When the wall is destroyed, these do not all need to receive lethal damage.

Their relationship policies may say:

- drop intact
- detach damaged
- destroy
- disconnect utility then fall
- become collectible/salvage

This creates more believable world behavior and prevents unnecessary destruction cascades.

---

# 12. Containers & Inventory

When a mounted/container object loses its parent, inventory state must remain authoritative.

Examples:

- cabinet falls but keeps contents
- fragile shelf breaks and contents drop through the inventory/world-item system
- installed safe detaches only under specific rules

Relationship destruction cannot duplicate or erase inventory through client-side visual effects.

---

# 13. Utility Consequences

Structural parent loss can affect utilities without destroying every connected device.

Examples:

- wall containing an electrical run is destroyed -> circuit segment fails/disconnects
- utility panel support destroyed -> panel may detach/shut down
- pipe support fails -> pipe may break/leak later

Utility failure state belongs to the utility system and relationship policy, not a generic damage loop.

---

# 14. Prefab Relationships

Prefab houses may use optimized merged visual shells but still expose logical relationships.

A prefab instance can own relationships for:

- support points
- logical wall/roof sections
- Door/Window openings
- installed objects
- utility service points
- expansion modules
- damage zones

Destroying one logical section resolves only the relationships tied to that section unless the prefab's authored failure rules require larger failure.

A prefab root is not a reason to destroy every child object whenever one section fails.

---

# 15. Demolition / Renovation Integration

Authorized demolition uses the same relationship graph before removal.

Before removing a wall/foundation/support, the server can report:

- direct installed children
- structural dependents
- utility dependents
- objects that will detach
- objects that will be destroyed
- objects blocking removal
- cascade-risk structures

The player can therefore receive a clear demolition preview rather than discovering after confirmation that half the building vanished.

Renovation similarly resolves relationships when replacing:

- Standard Wall -> DoorOpening Wall
- DoorOpening -> WindowOpening
- Floor.Standard -> Floor.Opening.Stair

Valid child/slot relationships must transfer, detach or block the renovation according to policy.

---

# 16. Relocation Integration

Move/relocation sessions query the relationship graph.

Examples:

- chair: no structural dependents -> direct move permitted
- installed door: must move to a compatible opening and resolve old/new OpeningIDs
- support wall: move blocked while upper floor depends on it
- portable prefab module: grouped move allowed only if its internal relationships are declared movable together

Relocation cannot bypass destruction/demolition dependency rules.

---

# 17. Damage Attribution & Crime

Failure cascades must preserve cause attribution without pretending every dependent object received the same direct attack.

Example:

`Player illegally destroys support column`
-> column direct damage attributed to player
-> floor becomes unsupported and collapses
-> dependent objects are damaged/destroyed by structural-collapse consequence

The Event Ledger can preserve causal linkage:

- root damaging actor/event
- direct target
- secondary structural failures
- resulting property damage

This supports crime, evidence, insurance and repair calculations more accurately than applying synthetic maximum damage to every child.

---

# 18. Cycle Prevention & Graph Validation

Persistent structure relationships must not create invalid dependency cycles.

The server and Editor tooling should reject or flag relationships such as:

- A requires B as sole support
- B requires A as sole support

Graph validation can check:

- duplicate RelationshipIDs
- duplicate exclusive occupancy
- invalid parent/child type
- self-parenting
- forbidden cycles for support dependencies
- missing referenced Structure IDs
- orphaned OpeningIDs
- invalid alternate support references
- illegal cross-property relationships

Not every graph edge type needs to be acyclic; structural dependency edges do.

---

# 19. Cascade Guardrails

Large destruction events must not recurse without limits.

Use a controlled failure queue rather than uncontrolled Blueprint recursion.

Possible safeguards:

- visited StructureID set
- deterministic queue/order
- maximum transaction work budget per server step
- batching of large collapse graphs
- cause/event ID carried through the cascade
- one terminal transition per structure
- deduplicate repeated dependency notifications
- defer purely visual effects independently from authoritative state

A skyscraper-scale collapse should resolve deterministically without a Blueprint stack explosion or hundreds of duplicate damage events.

---

# 20. Multiplayer Authority

Client may:

- display attached/dependent preview information
- visualize demolition/collapse risk
- play local destruction presentation

Server owns:

- relationship creation
- relationship deletion
- relationship type
- occupancy
- support requirements
- parent failure policies
- structural stability result
- detach/destroy/remove results
- persistence

A modified client cannot:

- remove itself from a parent relationship
- claim alternate support that does not exist
- protect an attached object from parent failure
- invent children to grief another player
- force another player's children to destroy
- bypass occupancy cleanup

---

# 21. Persistence / Streaming

Relationships persist independently of current Actor streaming.

Store at minimum:

- RelationshipID
- ParentStructureID
- ChildStructureID
- RelationshipType
- relevant Snap/Opening/Attachment IDs
- required/support flags
- failure policy
- relationship state

When actors stream in, runtime references can be rebuilt from persistent IDs.

When a parent is destroyed while a dependent is unloaded, the server/data layer still updates that dependent's authoritative state or queues its required resolution. It does not rely on finding a currently loaded Actor pointer.

---

# 22. Performance Rules

- no permanent Tick to check whether parents are alive
- no whole-world child search on destruction
- relationships are registered when placement/install/renovation/relocation occurs
- destruction queries only directly related edges then affected support dependents
- support reevaluation is event-driven
- use stable IDs and compact records
- cache relevant runtime references only while useful
- batch large cascades
- separate server relationship resolution from client Chaos presentation
- visual rubble does not become the source of relationship truth

---

# 23. Chaos Hierarchy vs Metaworld Relationship Graph

These are separate layers.

## Chaos Geometry Collection Hierarchy

Used for:

- fracture bones
- clusters
- connection graph
- strain thresholds
- progressive physical breakup
- local destruction presentation

## Metaworld Relationship Graph

Used for:

- wall -> door
- wall/column -> floor support
- opening -> installed window
- foundation extension -> foundation
- prefab section -> attached object
- structure -> utility dependency
- persistent parent/child consequences

A Chaos cluster breaking does not automatically define which separate persistent world objects must be destroyed.

The server translates meaningful damage/destruction state into relationship consequences; Chaos presents the result where appropriate.

---

# 24. Blueprint Architecture

Recommended reusable concepts:

- `S_MW_StructureRelationship`
- relationship Gameplay Tags / enums
- relationship failure policy data
- `BPI_MW_StructureRelationshipParticipant` where a capability contract is useful
- `BPC_MW_StructureRelationships` where per-buildable relationship caching/queries are useful
- centralized/persistent relationship registry/service compatible with Blueprint-first architecture

`BP_MW_Buildable_Master` may expose generic relationship lifecycle hooks, but it must not contain a giant family-specific destruction switch for every Buildable type.

Example hooks:

- `OnRelationshipAdded`
- `OnRelationshipRemoved`
- `OnParentStateInvalidated`
- `OnDependentStateChanged`
- `RequestRelationshipResolution`

---

# 25. Python Editor Tooling

Python Editor automation can later audit:

- invalid parent/child relationship metadata
- duplicate Snap/Opening/Attachment IDs
- support cycles
- unsupported roots
- doors/windows without failure policies
- foundations with invalid support definitions
- structural Buildables incorrectly configured as simple attachments
- orphaned prefab slots
- destruction profiles lacking relationship consequences
- overly deep/costly dependency graphs
- families still using legacy `BuildChildren[]`-only logic

Python remains editor/tooling automation, not runtime relationship authority.

---

# 26. Initial Vertical-Slice Tests

The relationship/destruction vertical slice should prove:

1. Door installed into DoorOpening creates persistent typed relationship.
2. Window installed into WindowOpening creates persistent typed relationship.
3. Second-floor piece stores all configured structural support relationships.
4. Destroying a wall resolves its installed door/window without leaving a floating functional object.
5. Destroying one of several supports does not destroy a floor when valid alternate support remains.
6. Destroying the final required support marks the floor unstable/unsupported and triggers configured failure.
7. Support failure uses relationship consequences rather than applying fake maximum direct damage to every dependent.
8. Surface-mounted object can detach/drop without being automatically destroyed when policy allows.
9. Utility relationship disconnects correctly when supporting structure is lost.
10. Foundation/root behavior works without a universal `AvoidAddingAsChild` Boolean.
11. Elevated foundation can legally depend on foundation extensions/piers.
12. Demolition preview reports dependent structures/attachments before confirmation.
13. Relocation of a structural support is blocked while unresolved dependents exist.
14. Parent destruction and child resolution occur authoritatively without arbitrary Blueprint Delay ordering.
15. Save/load restores all relationships.
16. Destroying a parent while a child Actor is unloaded still resolves persistent child state.
17. Modified client cannot forge/delete dependency relationships.
18. Relationship cycles are rejected/flagged.
19. Large cascade uses bounded queue/visited-set logic without duplicate terminal processing.
20. Chaos fracture presentation can run locally while persistent relationship results remain identical across clients.
21. Late joiner sees correct parent/child destroyed/detached states without historical physics replay.
22. Performance remains stable during a multi-piece structural collapse event.

---

# Core Rule

> Metaworld does not destroy a building hierarchy by blindly killing every child Actor. It maintains a typed persistent relationship graph. When a parent fails, the server resolves support, attachments, utilities, occupancy and dependents according to explicit world rules, then Chaos/visual systems present the physical result without becoming the source of gameplay truth.