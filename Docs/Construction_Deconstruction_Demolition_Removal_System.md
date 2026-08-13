# Metaworld — Construction Deconstruction, Demolition & Removal System

**Status:** Canonical / Approved Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld separates **cancelling unfinished construction**, **authorized demolition of completed structures**, and **world damage/destruction** into different systems.

Core rule:

> A construction removal tool is an authorized building-management action, not a universal `Destroy Actor` command.

The UE4 tutorial concepts of hold-to-remove input, radial progress feedback, interface checks and reset/cleanup logic are approved. Metaworld upgrades them for persistent construction state, ownership, Builder work, structural dependencies, salvage, multiplayer authority, crime/evidence, controller support and performance.

---

# 1. Three Different Removal Paths

## A. Cancel / Dismantle Unfinished Construction

Used for a construction site or partially built piece.

Possible results:

- cancel planned-but-unbuilt work
- remove partially constructed geometry
- release reserved snap/placement slots after authoritative completion of removal
- return eligible unused materials
- salvage a configurable portion of already-installed materials
- lose consumed labor/time
- record the cancellation in construction/property history where useful

Unfinished does **not** mean anybody can delete it. Ownership, property rights, contract permissions and organization authority still apply.

## B. Authorized Demolition / Deconstruction of Completed Structures

Used when an owner or otherwise authorized party intentionally removes a finished structure.

Possible requirements:

- property/ownership authority
- tenant/organization permissions
- Builder or demolition profession/skill for structural work
- permit where configured
- utilities disconnected or made safe
- dependent pieces checked
- occupants/critical inventory handled
- demolition/salvage resources and work
- neighboring/public-space restrictions

Finished structures are therefore removable, but not by the tutorial's instant delete mechanic.

## C. Damage / Destruction Through World Gameplay

Combat, fire, vehicle impact, explosions, storms, supernatural attacks, war, crime and other world events use the damage/destruction system.

This path may:

- damage condition/durability
- break doors/windows
- destroy structural pieces
- create debris/salvage
- create evidence/crime records
- trigger insurance/repair/emergency duties later
- invalidate structural support and cause instability where configured

It is **not** the construction-management remove action.

---

# 2. Input Architecture

Do not permanently bind demolition logic to the keyboard `1` key.

Recommended Enhanced Input action concepts:

- `IA_MW_BuildRemoveHold`
- `IA_MW_BuildCancelRemoval`
- optional contextual `IA_MW_DemolitionConfirm`

The action exists inside the relevant Build/Edit/Demolition input context.

Keyboard/mouse, Xbox-style controllers and PlayStation-style controllers require equivalent bindings and prompts.

The same physical button may be rebound by the player, but the logical action remains stable.

---

# 3. Hold-to-Confirm Safety

The tutorial's hold-to-delete idea is retained as a useful safety pattern.

A removal action can require continuous intentional hold for a definition-driven duration.

Recommended data:

- `RemovalHoldDuration`
- `RemovalMode`
- `RequiresSecondConfirmation`
- `RequiresTool`
- `RequiresBuilderQualification`
- `RequiresPermit`
- `RefundPolicyID`
- `SalvagePolicyID`

The timer must cancel if:

- player releases the action
- target changes
- target becomes invalid
- permission changes
- player leaves allowed range
- character becomes unable to continue
- server rejects the request

No stale progress may carry from one target to another.

---

# 4. Radial / Progress UI

The tutorial radial progress indicator is approved.

Metaworld can show:

- circular/radial hold progress
- target name/type
- action text such as `Cancel Construction`, `Dismantle`, `Demolish`, or `Remove Fixture`
- estimated salvage/refund
- dependency warning
- permission/qualification warning
- irreversible-action warning

The widget stays hidden/collapsed when no removal action is active.

Progress presentation is client-side UI. The server remains authoritative over whether removal is allowed and when it completes.

---

# 5. Common Interface / Capability Direction

Do not create one cast chain per buildable class.

Existing common interaction/capability architecture should expose removal-related queries/actions.

Possible interface/capability calls:

- `GetConstructionState()`
- `CanRequestRemoval(RequesterContext)`
- `GetRemovalMode()`
- `GetRemovalRequirements()`
- `GetDependentStructures()`
- `GetSalvagePreview()`

Possible Gameplay Tags:

- `Build.Removal.CancelUnfinished`
- `Build.Removal.Deconstruct`
- `Build.Removal.Demolish`
- `Build.Removal.NonRemovable`
- `Build.Removal.RequiresBuilder`
- `Build.Removal.RequiresPermit`

A narrow `IsBuildFinished` boolean can still exist as convenience data, but final behavior comes from richer construction state and removal policy.

---

# 6. Construction State Integration

The removal system integrates with `Docs/Construction_Progress_Build_To_Completion_System.md`.

Possible states:

- Planned
- Reserved
- Foundation/Support stage
- Framing
- Rough Build
- Finishing
- Completed
- Damaged
- Under Repair
- Demolition Pending
- Being Deconstructed
- Removed/Destroyed

Removal policy may differ by state.

Example:

`Planned` -> cancel with near-full return of unconsumed reserved materials.

`50% built wall` -> dismantle with partial salvage; consumed labor is not refunded.

`Completed wall` -> authorized demolition workflow.

`Destroyed wall` -> cleanup/salvage workflow rather than normal demolition.

---

# 7. Salvage & Refund Rules

Removing a structure must not become a duplication exploit.

Server-authoritative policy determines:

- unused reserved material return
- installed material salvage percentage
- damaged-material loss
- demolition waste
- tool/machinery costs
- labor cost
- GrimKoin fees where applicable
- creator-item entitlement behavior where relevant

Possible rule:

`Returned + Salvaged <= legitimately committed material quantity`

No removal path may mint resources.

Different materials and states can have different salvage rates.

---

# 8. Structural Dependency Validation

Before removing a structural piece, the server checks what depends on it.

Examples:

- wall supporting upper floor
- pier supporting foundation
- column supporting floor/roof
- floor supporting second-story walls
- opening wall containing installed door/window
- utility-bearing wall/shaft later

Possible outcomes:

1. **Safe removal** — no critical dependency.
2. **Cascade removal preview** — authorized operation includes dependent pieces.
3. **Blocked** — dependencies must be removed/reconfigured first.
4. **Unsafe demolition permitted** — special demolition path intentionally creates instability/collapse/damage where the world rules allow it.

The player must see a clear warning before an authorized action removes more than the directly targeted object.

---

# 9. Door / Window / Attachment Rules

A wall with an installed door/window cannot silently delete the child object without resolving the relationship.

Depending on operation:

- remove installed door first
- include door/window in deconstruction set
- salvage them separately
- destroy them during destructive demolition where explicitly allowed

Opening occupancy and parent relationships must be cleaned up atomically.

---

# 10. Foundation / Support Rules

Removing a foundation, pier or support extension requires structural dependency validation.

A support cannot simply disappear while supported upper structures remain treated as valid.

After an approved structural removal:

- support graph updates
- dependent structures revalidate
- affected pieces may become unsupported/unstable
- repair/demolition/emergency duties can be generated later

Recalculation is event-driven, not permanent Tick.

---

# 11. Property & Permission Rules

Server authorization can consider:

- property owner
- co-owner
- tenant modification rights
- spouse/family permission
- business role
- Builder/demolition contract
- faction/government/public-project authority
- court/legal order where deliberately supported
- war/occupation rules where applicable

Being able to aim at a structure never grants removal permission.

---

# 12. Unauthorized Destruction & Crime

A player without management permission does not get a hidden construction-delete shortcut.

If world gameplay allows them to damage the object, they must use legitimate damage/destruction mechanics.

That may create:

- property damage crime
- trespass/burglary evidence
- camera/witness evidence
- repair costs
- police duties
- insurance claims later
- owner notifications where appropriate

The construction removal UI must not bypass law/evidence/durability.

---

# 13. Server Authority

Client may submit:

- target Structure/Object ID
- requested removal mode
- held-input start/cancel events or final request according to implementation

Server independently checks:

- target exists
- authoritative construction state
- ownership/permission
- distance/range
- required tool/profession/permit
- dependency graph
- installed attachments
- active occupants/critical contents where relevant
- salvage/refund policy
- current world state
- whether the required hold/work condition is satisfied

Only the server removes/persists the object and grants salvage/refunds.

A modified client cannot:

- delete arbitrary actors
- pretend a finished structure is unfinished
- shorten hold duration authoritatively
- fake ownership
- fake salvage amount
- omit dependent pieces

---

# 14. Persistent Transaction / Atomic Cleanup

Removal is a state transaction, not only a visual Actor destroy.

Successful removal must update atomically where relevant:

- structure/object record
- parent/child relationships
- snap-point occupancy
- opening occupancy
- support graph
- construction-site reservation
- property/build budget
- utility links later
- inventory/salvage outputs
- contract/job state
- event/property history where appropriate

Only after authoritative state is committed should the runtime representation disappear or transition to debris/demolition presentation.

---

# 15. Builder Profession & Role Duties

Authorized removal creates real Builder/demolition gameplay.

Possible duties/jobs:

- cancel abandoned construction
- dismantle temporary structure
- remove damaged wall
- replace door/window
- demolish unsafe building
- remove failed support
- salvage materials
- clear debris
- renovate structure

Larger demolition can require workers, tools/machinery, permits, safety preparation and contracts.

NPC Builders may perform legitimate scheduled deconstruction when assigned and supplied, using the same persistent job rules as construction.

---

# 16. Tools, Work & Time

A tiny unfinished decorative piece may use only a short hold confirmation.

A structural wall or completed building should not vanish merely because a button was held for two seconds.

Authorized removal can have two layers:

1. **Hold to confirm/start** — protects against accidental actions.
2. **Actual deconstruction/demolition work** — Construction/Demolition Work Units, tools, machinery, NPC labor and stages where appropriate.

This preserves the tutorial's good UX without turning demolition into instant magic.

---

# 17. Performance

- no removal targeting/hold UI when removal mode is inactive
- one relevant target at a time for player hold interaction
- radial UI updates only while active
- dependency graph checks happen on request/state change, not every frame
- support graph recalculation is event-driven
- completed idle structures do not Tick for removal eligibility
- server validates only relevant structures/dependencies

---

# 18. Controller Compatibility

The complete removal flow must work with:

- keyboard/mouse
- Xbox-style controllers
- PlayStation-style controllers

Required gamepad-capable behavior:

- enter build/edit/demolition mode where required
- target structure using camera/reticle
- hold remove/cancel action
- see radial progress
- cancel cleanly
- navigate warnings/confirmation UI
- choose removal/cascade option where exposed

No mouse-only critical confirmation path is allowed.

---

# 19. UI Reset / Error Handling

The tutorial's reset logic is retained and expanded.

On success, cancellation, target loss, mode exit, death/incapacitation, server rejection or context switch:

- hold progress resets to zero
- radial widget hides
- target reference clears
- local timers/gates stop
- pending local preview state clears

No previous target's progress may carry into a new structure.

---

# 20. Initial Vertical-Slice Tests

The construction vertical slice should prove:

1. Target unfinished construction site.
2. Authorized player holds Remove and sees radial progress.
3. Releasing early cancels and resets UI.
4. Looking away cancels and resets UI.
5. Unauthorized player cannot remove it through construction tools.
6. Server determines legitimate refund/salvage.
7. Cancelled site releases its reserved snap/placement slot only after authoritative removal.
8. Completed wall is not handled as simple unfinished cancellation.
9. Owner/authorized Builder can start an approved demolition/deconstruction path for completed wall.
10. Wall supporting an upper floor reports dependency and cannot silently disappear.
11. Door/window child relationship is handled correctly when parent wall is removed.
12. Removing a support triggers structural support revalidation.
13. Modified client cannot delete arbitrary finished structures or fake unfinished state.
14. No material duplication occurs through repeated build/remove cycles.
15. Save/load does not resurrect removed structures or lose surviving dependencies.
16. Keyboard/mouse flow works.
17. Xbox-style controller flow works.
18. PlayStation-style controller flow works.
19. Idle structures have no permanent removal Tick cost.
20. Unauthorized physical damage still routes through normal damage/crime/evidence systems instead of build removal.

---

# Core Rule

> Metaworld never treats construction removal as a universal delete key. Unfinished construction can be cancelled or dismantled under real permissions and salvage rules; completed structures use authorized deconstruction/demolition; hostile or accidental destruction uses the world damage/crime system. Every path is server-authoritative, persistent, controller-compatible and structurally aware.
