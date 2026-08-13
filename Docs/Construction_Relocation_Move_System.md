# Metaworld — Construction Relocation & Move System

**Status:** Canonical / Approved Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld supports relocating eligible placed objects and structures, but relocation is an authoritative construction transaction rather than unrestricted world-transform editing.

Core rule:

> An object may be movable only when its definition, ownership, structural dependencies, attachments, utilities, property rules and destination all permit relocation.

The UE4 tutorial concepts of selecting a finished buildable, entering a move state, reusing the build ghost/placement flow, resolving the original Build ID and confirming a new transform are approved. Metaworld upgrades them for data-driven relocation policy, structural dependencies, multiplayer authority, persistence, controller support, performance and world-system integration.

---

# 1. Relocation Categories

Metaworld separates relocation into practical categories.

## A. Freely Relocatable Placed Objects

Examples may include:

- furniture
- decorative objects
- some storage containers when empty or allowed
- appliances/equipment where disconnected and permitted
- signs
- light props
- non-structural fixtures
- selected creator/decor items

These can usually use the normal Move workflow after ownership, obstruction and destination checks.

## B. Restricted Installed Objects

Examples may include:

- doors
- windows
- utility fixtures
- machines
- security devices
- counters/workstations
- installed equipment

These may require:

- compatible attachment/opening/utility slot at the destination
- disconnect/reconnect rules
- empty inventory or cargo policy
- owner/business/property permission
- profession/tool requirements

## C. Structural Pieces

Examples:

- foundations
- foundation extensions/piers
- walls
- floors
- columns
- beams
- stairs
- roofs
- structural openings
- multi-story support pieces

These are **not** treated as ordinary furniture transforms.

Structural relocation may be:

- blocked when dependencies exist
- permitted only as a grouped/module move when explicitly designed
- converted into dismantle + rebuild
- performed through a Builder relocation job with tools/machinery later
- allowed only for a complete independent modular structure that can preserve a valid support graph

The system never teleports a support-bearing wall out from under a second floor simply because the player owns it.

---

# 2. Data-Driven Relocation Policy

Each Buildable Definition can provide relocation metadata such as:

- `RelocationPolicy`
- `CanMoveWhenFinished`
- `CanMoveWhenUnfinished`
- `RequiresEmptyInventory`
- `RequiresUtilityDisconnect`
- `RequiresBuilder`
- `RequiresToolTags`
- `RequiresMachineryTags`
- `RequiresPermit`
- `AllowedMoveModes`
- `AllowedDestinationSnapTypes`
- `PreserveAttachments`
- `PreserveContents`
- `MoveCost`
- `MoveWorkUnits`
- `MaximumDirectMoveMass`
- `MaximumDirectMoveSize`
- `CanGroupMove`
- `CanCrossPropertyBoundary`

Tutorial logic such as `ReturnBuildID` becomes a stable authoritative Buildable/Variant identity lookup rather than trusting an arbitrary preview mesh/class.

---

# 3. Input & Interaction

Do not permanently bind relocation to keyboard `Q` or right-click.

Recommended Enhanced Input actions can include:

- `IA_MW_BuildMoveSelect`
- `IA_MW_BuildMoveConfirm`
- `IA_MW_BuildMoveCancel`
- existing Rotate Left/Right
- existing Fine Rotate where eligible

The move workflow must have equivalent keyboard/mouse, Xbox-style controller and PlayStation-style controller paths.

Input contexts determine whether a physical control means ordinary Interact, Build Work, Rotate, Move or another action.

---

# 4. Move Selection

The player targets an existing object through the shared construction/interaction targeting path.

Local request identifies:

- persistent Structure/Object ID
- requested Move action

The server or authoritative construction service resolves:

- actual Buildable ID
- Variant ID
- owner/property
- current construction state
- relocation policy
- attachments
- contents
- support relationships
- utilities
- active jobs/contracts
- damage state

Only an eligible target enters relocation preview.

---

# 5. Preview / Ghost Workflow

Relocation reuses the placement architecture without moving the authoritative finished object around every preview update.

Recommended flow:

`Select eligible existing object`
-> server/authority grants relocation session
-> original object is reserved/locked against conflicting construction transactions
-> client creates low-cost movable relocation ghost from authoritative Buildable/Variant definition
-> candidate transform follows normal placement, rotation, snapping and controller rules
-> destination reruns overlap, support, property, snap, opening and utility checks
-> client shows valid/invalid feedback
-> player confirms or cancels

The original persistent object remains authoritative until commit succeeds.

This avoids temporarily turning a real wall/foundation into a client-controlled world object.

---

# 6. Original Location Reservation

While a relocation session is active:

- the original object still owns its current persistent identity
- its current snap/opening/support slots remain reserved until commit
- another player cannot steal the vacated slot before the move succeeds
- conflicting demolition, renovation or second relocation attempts are rejected/serialized

On cancel or failure, nothing authoritative changes.

On successful commit, old relationships are released and new relationships are created atomically.

---

# 7. Destination Validation

A relocation candidate uses the same validation stack as new construction, plus move-specific checks.

Validate:

- Buildable relocation policy
- player/role authorization
- current object state
- candidate placement footprint
- physical overlap/clearance
- snap/opening/support compatibility
- destination slot occupancy
- terrain/foundation support where applicable
- property/deed/build-volume rights
- zoning/height/subsurface rules
- destination parcel performance/build budget
- profession/tool/machinery requirements
- utility connection/disconnection requirements
- inventory/content policy
- attachments/children
- structural dependencies
- move cost/work requirements

The destination is not valid merely because the ghost is visually clear.

---

# 8. Structural Dependency Rules

Structural movement must account for both parents and dependents.

Examples:

- wall supports upper floor -> direct wall move normally blocked
- pier supports foundation -> direct pier move normally blocked
- door installed in DoorOpening -> door can move only to a compatible opening unless dismantled/stored by another approved path
- window installed in WindowOpening -> same rule
- free-standing chair -> usually direct move allowed

Possible structural responses:

1. **Direct Move Allowed** — no critical dependency and definition permits it.
2. **Move Attachment/Group** — deliberately configured linked module moves together.
3. **Disconnect First** — utility/attachment must be removed safely.
4. **Dismantle + Rebuild Required** — normal structural renovation path.
5. **Blocked** — current state cannot be safely/legally relocated.

Moving one child never silently invalidates the support graph.

---

# 9. Group / Module Relocation

Future approved direction:

Small self-contained modules may support grouped relocation when designed for it.

Examples could include:

- prefab shed
- small cabin module
- shipping-container structure
- kiosk
- portable stage
- selected temporary construction modules

A group move needs a stable Group/Module ID and validates:

- combined footprint
- combined mass/size
- internal attachment graph
- destination support
- property rights
- machinery/work requirements
- utility reconnection
- world/performance constraints

This is not an excuse to move an entire skyscraper by dragging one wall ghost.

---

# 10. Utilities & Installed Systems

Relocating an object can affect:

- electricity
- water
- heating/fuel
- HVAC
- communications
- alarms/security
- plumbing/drainage

Depending on definition, relocation may require:

`Disconnect`
-> `Move`
-> `Reconnect`
-> `Test/Inspect`

Moving an appliance or machine does not grant magical wireless utilities unless that product is actually designed that way.

---

# 11. Contents & Inventory

Containers and equipment with internal inventory need explicit policy.

Possible rules:

- lightweight furniture may move with contents
- heavy storage may require emptying first
- business machines may preserve internal state but require disconnection
- hazardous/fragile contents may block move
- moving a storage object cannot duplicate or drop persistent inventory accidentally

Contents remain server-authoritative throughout the relocation transaction.

---

# 12. Cost, Labor & Builder Integration

Not every move must be free.

Possible cost/work factors:

- size
- mass
- structural type
- utility disconnection
- required workers
- machinery
- distance/category of relocation
- permits
- damage risk

Examples:

- move chair across room -> immediate/free or trivial
- move refrigerator -> perhaps requires disconnect/reconnect
- relocate heavy machinery -> Builder/Mechanic/Engineer job
- relocate prefab structure -> crew + crane/vehicle + work units
- move structural wall -> normally renovation/dismantle/rebuild

Relocation can generate real Builder, mover, mechanic, electrician or utility duties where appropriate.

---

# 13. Mobility / Rendering Performance Policy

Metaworld does **not** permanently set every foundation, wall, floor or finished build component to engine `Movable` mobility merely to support occasional relocation.

Rules:

- finished settled structural pieces should remain in the most efficient appropriate mobility/rendering state wherever practical
- relocation preview uses a temporary low-cost movable ghost
- the authoritative finished object changes transform only during the committed transaction
- after commit, the object returns to its appropriate settled state
- relocation must not disable Nanite/HLOD/streaming/scalability benefits unnecessarily
- no permanent Move-system Tick while relocation mode is inactive

The tutorial requirement to mark all floor/foundation components Movable is therefore a prototype implementation detail, not canonical Metaworld architecture.

---

# 14. Server Authority / Anti-Cheat

Client may propose:

- Structure/Object ID
- candidate destination transform
- destination Snap/Open/Support IDs where relevant

Server independently resolves:

- authoritative Buildable/Variant definition
- relocation policy
- original persistent record
- owner/permissions
- dependencies
- footprint
- support
- property rules
- destination occupancy
- utilities
- cost/work

Only the server commits relocation.

A modified client cannot:

- move another player's object
- claim a structural wall is furniture
- shrink its footprint
- ignore dependencies
- bypass utility rules
- move outside the property
- forge a legal destination
- preserve illegal snap relationships

---

# 15. Atomic Commit

Successful relocation is one authoritative transaction.

Recommended order:

1. verify relocation session still valid
2. revalidate destination
3. reserve destination slot/support/opening
4. resolve utilities/attachments/contents
5. update persistent transform
6. update parent/support/snap/opening relationships
7. release old relationships
8. update property/build-budget state where needed
9. replicate new settled state
10. clear relocation reservation/session

If commit fails, the original object remains at the original legal location.

---

# 16. Persistence

Relocation preserves the same persistent Object/Structure ID unless a specific dismantle/rebuild workflow intentionally creates a replacement structure.

Persist/update:

- Structure/Object ID
- Buildable/Variant ID
- transform
- property/owner
- parent/support/snap/opening IDs
- utility relationships
- contents
- attachments
- condition/damage
- construction state
- relocation timestamp/history where useful
- actor/worker/contract reference where relevant

Property history can later record major renovations/relocations.

---

# 17. Multiplayer Concurrency

Only one conflicting construction transaction may control a given object at a time.

Examples of conflicting operations:

- Move
- Demolish
- Renovate
- Replace parent opening
- Repair state-changing operation
- Transfer property during critical commit

Use reservation/transaction state rather than letting two players race to move/delete the same structure.

---

# 18. UI / Feedback

Relocation UI should clearly communicate:

- selected object
- move allowed / not allowed
- reason if blocked
- destination validity
- required snap/support
- utility disconnect requirement
- contents requirement
- Builder/tool/machinery requirement
- move cost/work
- dependent structures affected
- confirm/cancel controls

A reusable hold/progress widget component may be shared where a relocation requires deliberate confirmation/work, but simple furniture movement need not force a long hold every time.

---

# 19. Controller Compatibility

Relocation must be fully operable with:

- keyboard/mouse
- Xbox-style controller
- PlayStation-style controller

Controller-capable flow includes:

- target/select object
- enter Move mode
- reposition via camera/reticle placement
- rotate
- snap/cycle candidate where applicable
- confirm
- cancel
- understand blocked-reason UI

No mouse-only transform gizmo is required for basic gameplay relocation.

---

# 20. Performance

- no relocation queries while Move mode is inactive
- one active relocation ghost per local move session by default
- reuse existing targeted placement/footprint/support queries
- do not continuously re-evaluate all placed structures for move eligibility
- structural dependency lookup uses persisted graph/index data
- server performs final checks on confirmation, not every client visual frame
- avoid full component reconstruction until transaction commit
- finished idle objects pay no Move-system Tick cost

---

# 21. Python Editor Validation

Python Editor tools can later audit:

- missing relocation policy
- objects incorrectly marked freely movable despite structural/support tags
- relocation definitions missing footprints
- incompatible utility/attachment metadata
- unsupported mobility setup
- finished structural assets unnecessarily configured as permanently Movable
- missing group/module metadata
- inconsistent snap/opening destination types

Python remains Editor automation only.

---

# 22. Initial Vertical-Slice Tests

The Phase 20 vertical slice should prove:

1. Owned free-standing furniture can enter Move mode and be repositioned.
2. Move ghost uses authoritative Buildable/Variant identity.
3. Rotation and overlap validation work during relocation.
4. Destination outside property rights is rejected.
5. Destination overlap is rejected.
6. Move to an occupied exclusive snap slot is rejected.
7. Unauthorized player cannot move another player's object.
8. Cancel returns to original state with no authoritative transform change.
9. Server rejects forged destination/footprint/permission values.
10. Successful move preserves the same Object/Structure ID.
11. Save/load restores moved location.
12. Door can relocate only to a compatible unoccupied Door opening when its policy allows.
13. A support-bearing wall with an upper-floor dependency cannot be directly moved as ordinary furniture.
14. A foundation pier supporting a structure cannot be directly moved without resolving dependencies.
15. Utility-connected object follows disconnect/reconnect policy.
16. Container contents are preserved or require emptying according to data.
17. Finished structural pieces do not remain permanently engine-Movable just because Move mode exists.
18. Keyboard/mouse completes the flow.
19. Xbox-style controller completes the flow.
20. PlayStation-style controller completes the flow.
21. Repeated move/cancel operations leave no stale reservations or snap occupancy.
22. Performance remains stable with many finished structures nearby and Move mode inactive.

---

# Core Rule

> Metaworld allows players to reorganize property without turning construction into unrestricted transform editing. Lightweight placed objects can move directly when authorized; installed and structural pieces respect attachments, support, utilities, property, labor and persistence; the client previews, but the server commits the relocation transaction.