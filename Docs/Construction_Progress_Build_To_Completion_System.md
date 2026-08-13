# Metaworld — Construction Progress & Build-To-Completion System

**Status:** Canonical / Approved Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld supports construction that can exist in an **unfinished state** before becoming a completed usable structure.

Core rule:

> Placement decides where a structure is allowed to exist. Construction work and resources decide when that structure is actually finished.

The UE4 tutorial concept of spawning a gray/transparent buildable and pressing Interact a fixed number of times is approved as a prototype pattern, but Metaworld upgrades it into a persistent, data-driven construction-progress system tied to Builder work, tools, materials, multiplayer authority, NPC labor, property, persistence and performance.

---

# 1. Placement vs Construction

Metaworld separates two events:

1. **Placement approval** — the server validates property, snap/support, profession, permit, resources/reservations and location.
2. **Construction completion** — approved labor/material work advances the persistent structure through its required construction stages.

A successful placement can therefore create a persistent construction site rather than instantly creating a fully finished building.

Small/simple objects may still complete immediately when their definition allows it. Large or structural pieces can require staged work.

---

# 2. Construction States

Recommended high-level states:

- `Planned`
- `MaterialsPending`
- `ReadyForWork`
- `UnderConstruction`
- `StageComplete`
- `Completed`
- `Paused`
- `Blocked`
- `DamagedDuringConstruction`
- `Cancelled`

For large structures, a buildable can contain multiple stages.

Example house flow:

`Plan/Permit -> Foundation -> Frame -> Floors -> Walls/Openings -> Roof -> Utilities -> Finish -> Inspection -> Completed`

A single modular wall may use fewer stages:

`Placed Construction Site -> Materials Ready -> Build Work -> Completed Wall`

---

# 3. Work Units Instead of Repeated Button Counts

The tutorial stores a number of interactions required to complete an object. Metaworld generalizes that into **Construction Work Units**.

Suggested data:

- `RequiredWorkUnits`
- `CurrentWorkUnits`
- `WorkUnitType`
- `MinimumToolTag`
- `RequiredProfessionTag`
- `MinimumSkill/Certification`
- `StageID`
- `StageRequiredMaterials`
- `StageCompletionThreshold`

Example:

A simple interior object may require `5` work units.

A structural wall may require `40` work units.

A large commercial stage may require thousands of work units supplied by multiple qualified workers and equipment.

The system must not depend on literal button spam such as `press E 40 times`.

Approved player interaction patterns can include:

- hold/interact to perform a work action
- timed construction animation
- repeated deliberate work cycles where appropriate
- using a required tool
- using construction machinery
- team/crew work
- NPC worker labor

Each completed authoritative work action contributes a defined amount of work units.

---

# 4. Builder Skill, Tools & Efficiency

Work contribution can be affected by legitimate world state.

Possible factors:

- Builder profession qualification
- skill/mastery
- certification/license
- correct tool
- tool quality/condition
- machinery
- number of workers
- fatigue/stamina
- injury
- weather/site conditions
- stage complexity

Important rule:

> Skill and equipment can improve efficiency, but they do not bypass required property rights, materials, permits or server validation.

A player cannot buy a rank or toggle a client variable to instantly complete construction.

---

# 5. Material Requirements

Construction progress can be gated by actual required materials.

Examples:

- lumber
- concrete
- steel
- glass
- wiring
- pipes
- fasteners
- doors/windows
- fixtures
- specialty components

Material requirements are stored in the authoritative Buildable/Stage definition.

Recommended stage behavior:

1. materials delivered/reserved
2. server validates quantity/ownership
3. stage begins
4. materials are consumed according to the approved transaction policy
5. labor advances work units
6. stage completes

Large projects can require material deliveries over time rather than consuming the entire future building inventory at the first click.

Construction companies, drivers, warehouses and suppliers can therefore participate in the same economy.

---

# 6. Construction-Site Visual State

The tutorial's gray/transparent blueprint material is approved as a useful presentation baseline.

Metaworld should use a dedicated **construction-site visual state**, not overwrite and forget the original materials.

Possible presentation stages:

- `Planned`: translucent/ghosted blueprint or site markers
- `Foundation`: visible foundation work
- `Frame`: structural frame/scaffolding
- `RoughBuild`: partial wall/floor/roof representation
- `Finish`: near-final materials
- `Completed`: canonical finished material/texture state

Small modular pieces can use a simplified gray/transparent temporary representation if creating full staged art is unnecessary.

The canonical finished material/creator texture entitlement is stored in data/persistent state and restored when completion is reached.

Do not rely on reading the current material at runtime as the only record of what the finished object should look like.

---

# 7. Material / Creator Texture Preservation

A buildable can have:

- canonical base material set
- approved creator texture entitlement
- owner-selected legal finish/texture
- temporary construction material/state

Construction presentation must never destroy the authoritative finished material choice.

Completion resolves the correct final material/texture state from authoritative data.

This preserves Metaworld's creator rule: creators texture approved locked inputs only; construction state does not alter mesh/material-slot ownership rules.

---

# 8. Collision by Construction Stage

The tutorial disables most collision during construction and restores `Block All` when complete. Metaworld keeps the principle that unfinished geometry should not behave like a fully finished object, but collision is **stage-specific**.

## Planned / Blueprint Stage

Usually:

- Query Only / construction interaction
- no invisible full-size walk blocker unless specifically required for safety/site rules
- can reserve the placement/snap slot so another structure cannot occupy it

## Physical Construction Stages

When visible physical structure exists, collision should represent what actually exists.

Examples:

- finished foundation can become walkable before the whole house is complete
- visible frame posts can block movement where appropriate
- incomplete floor should not pretend the full finished floor exists if there is physically a hole
- partial wall collision should correspond to the current stage/representation

## Completed

The object receives its normal final gameplay collision profile.

Core rule:

> Do not use invisible finished collision for a structure that visually does not exist yet, and do not let players walk through physical construction that visibly exists unless the design intentionally allows it.

Snap/query collision remains separate from gameplay blocking collision.

---

# 9. Construction-Site Occupancy & Reservation

Once the server accepts a construction site, its structural slot/location can be reserved.

This prevents another player from placing a conflicting wall/floor/door/etc. into the same authoritative location while the first object is unfinished.

Reservation records can include:

- Construction Site ID
- planned Buildable/Variant ID
- property
- owner/contract
- parent/support Structure ID
- Snap Point/Openings ID where relevant
- occupied/reserved bounds
- stage
- progress

Cancelling or legally demolishing an unfinished site releases the reservation according to world rules.

---

# 10. Common Interaction Contract

Construction work should use Metaworld's shared interaction architecture.

Recommended path:

`BPC_MW_Interaction -> BPI_MW_Interactable -> Construction Site -> Available Work Action`

Possible actions:

- Build
- Deliver Materials
- Inspect
- Pause Work
- Resume Work
- Repair Construction Damage
- Cancel/Demolish where authorized

The player character does not need a special one-off `InteractWithBuild` implementation for every buildable Blueprint.

---

# 11. Input & Controller Support

Construction work must work with:

- keyboard/mouse
- Xbox-style controllers
- PlayStation-style controllers

Use Enhanced Input actions rather than a mandatory physical `E` key.

Possible action:

`IA_MW_Interact`

or a context-specific construction action exposed through the common interaction system.

A hold-to-work interaction must provide controller-equivalent hold/cancel/progress feedback.

---

# 12. Player Construction Animation

Actual construction work can trigger appropriate animations.

Examples:

- hammering
- fastening
- sawing
- drilling
- welding
- laying material
- installing panels
- fitting doors/windows
- wiring/plumbing work
- operating construction equipment

Animation is presentation and work cadence; the server remains authoritative for whether the action contributes valid work units.

The same animation system should use the master humanoid animation architecture rather than a one-off character Blueprint animation hack.

---

# 13. NPC & Crew Construction

NPC Builders and hired construction crews can contribute valid work units.

NPC workers still obey:

- profession/skill
- schedule
- wages/contracts
- hunger/food
- fatigue/rest where relevant
- tools/equipment
- access permissions
- site safety/world events

A construction company can therefore accept a contract and assign workers to a site.

Nearby workers can perform visible actions.

Distant/unloaded legitimate construction crews can use scheduled/timestamp work simulation rather than remaining as full Actors continuously.

No work progresses merely because the site exists; progress requires an approved source of labor/time/resources according to its contract/state.

---

# 14. Multiplayer Authority

The server owns:

- Construction Site ID
- authoritative Buildable/Variant definition
- stage
- required/available materials
- CurrentWorkUnits
- RequiredWorkUnits
- worker authorization
- profession/skill/tool validation
- structural/support state
- property/contract permissions
- completion transition

Client can request:

`PerformConstructionWork(ConstructionSiteID, RequestedAction/ToolContext)`

Server checks:

- site exists
- player/NPC is allowed to work there
- stage is ready
- correct profession/skill if required
- correct tool/equipment if required
- materials are available
- player/NPC is in valid range/state
- work action is not rate-spammed beyond allowed cadence

Only then does authoritative work progress increase.

The client cannot submit `CurrentWorkUnits = RequiredWorkUnits` or set `Completed = true`.

---

# 15. Anti-Spam & Exploit Rules

Do not equate fast input spam with construction skill.

Server can enforce:

- work-action cadence
- animation/action duration
- stamina/tool constraints
- valid interaction distance
- line-of-sight/site access where relevant
- tool possession
- work stage readiness
- duplicate request rejection

This prevents macros or network spam from completing a building instantly.

---

# 16. Stage Completion

When a stage reaches its authoritative completion threshold:

1. validate all stage requirements still pass
2. finalize stage resource transaction/state
3. update physical representation/collision
4. expose new snap/support/opening points if that stage creates them
5. unlock the next construction stage
6. persist progress
7. optionally generate Builder/payment/contract records

At final completion:

- construction state becomes `Completed`
- finished mesh/material/texture state is applied
- final gameplay collision activates
- normal door/window/interactions become available
- utilities/inspection activation occurs where required
- building becomes fully usable according to world rules

---

# 17. Partial Structural Availability

A partially built structure should only provide capabilities that physically exist at that stage.

Examples:

- an unfinished wall may not yet provide a valid finished Door attachment slot
- an unfinished support wall may not support an upper floor until its structural stage is complete
- a completed foundation may allow the next wall stage
- wiring sockets do not become powered merely because the wall mesh exists

Construction stages can expose or withhold snap/support/utility capabilities through data.

This prevents players from exploiting half-built structures as fully functional finished buildings.

---

# 18. Damage During Construction

Unfinished structures can later be vulnerable to:

- weather
- attacks
- accidents
- fire
- war
- sabotage
- theft of exposed site materials where world rules allow

Damage can:

- reduce condition
- pause construction
- require repair work
- destroy a stage/site
- consume replacement materials
- create Builder/security/police/insurance tasks

Construction sites are not magical safe zones.

---

# 19. Persistence & Offline World

Construction progress is persistent.

Recommended record:

- Construction Site ID
- Buildable/Family/Variant ID
- Property ID
- Owner/Contract ID
- Parent/support/snap/opening relationships
- Current Stage ID
- CurrentWorkUnits
- RequiredWorkUnits
- reserved/consumed materials
- site condition/damage
- assigned workers/crew contract
- timestamps
- pause/block reason
- finished material/texture entitlement

Logging out does not delete the site.

If legitimate NPC/company labor is assigned, distant/unloaded progress can be calculated from work schedules/timestamps and available resources. If no legitimate labor/resources exist, the site does not magically finish while offline.

---

# 20. Builder Profession & Role Duties

Construction progress creates real profession gameplay.

Possible Builder duties:

- deliver/verify materials
- foundation work
- framing
- wall/floor/roof installation
- door/window fitting
- repair
- renovation
- utility prep
- finishing
- inspection preparation
- structural emergency work

Higher Builder skill can unlock harder stages/contracts rather than simply multiplying rewards with no world basis.

Construction companies can hire players/NPCs and pay wages from contract revenue.

---

# 21. Economy & Contracts

A construction contract can separate:

- material budget
- labor budget
- permit/inspection fees
- equipment rental
- company profit
- taxes
- completion milestones

Payments can occur by approved milestones rather than all money transferring before any work occurs.

Failed/cancelled projects can follow contract/refund/legal rules defined later.

This gives builders, suppliers, drivers, inspectors and business owners connected economic roles.

---

# 22. Large Building Stages

The system must scale beyond a single wall.

Large building projects can use hierarchical construction:

`Project -> Building Stage -> Structural Module -> Work Units`

Example:

- Project: Apartment Building
  - Stage: Foundation
  - Stage: Structural Frame
  - Stage: Floors
  - Stage: Exterior Walls
  - Stage: Utilities
  - Stage: Interior Finish
  - Stage: Inspection

The server does not need every worker to modify one giant global float every frame. Work is applied through meaningful actions/scheduled updates to the relevant stage/module.

---

# 23. Performance Rules

- unfinished sites do not Tick just to own progress
- progress changes on work/material/stage events
- distant NPC construction uses scheduled/timestamp simulation
- construction visuals use appropriate LOD/HLOD/relevancy
- do not continuously swap/material-scan every slot
- store canonical finished material references in data
- collision changes only when stage/state changes
- avoid full physics simulation for all construction sites
- structural recalculation occurs on meaningful stage/damage/demolition events
- replicate compact stage/progress state, not every hammer animation event globally
- nearby visible worker animations are presentation; distant work can be data-only

---

# 24. UI Feedback

Construction UI can show:

- buildable/site name
- current stage
- progress percentage/work units
- required materials
- missing materials
- required profession/tool
- assigned workers
- blocked reason
- estimated in-world work requirement (not a promise of real-world completion time)
- next stage

Controller focus/navigation must work without mouse dependence.

The UI should communicate *why* work cannot continue instead of simply doing nothing.

---

# 25. Python Editor Tooling

Python editor tooling can later validate:

- missing Construction Stage definitions
- impossible/zero work requirements
- missing final materials
- missing temporary construction material
- collision profiles per stage
- unsupported snap/support exposure
- missing resource recipes
- missing profession/tool tags
- invalid stage order
- duplicate Stage IDs
- missing finished material/texture restoration data
- performance metadata

Python remains editor automation, not packaged runtime work logic.

---

# 26. Initial Vertical-Slice Test

The first construction vertical slice should prove:

1. Place a structural wall in a valid property location.
2. Server creates persistent Construction Site ID instead of instantly finished wall.
3. Site shows an approved unfinished/blueprint presentation.
4. Site reserves the wall snap slot so another wall cannot overlap it.
5. Site exposes a common Interact/Build action.
6. Player cannot advance work without required materials where configured.
7. Authorized Builder with required tool can contribute work units.
8. Repeated input spam cannot bypass action cadence.
9. Progress is server-authoritative.
10. Keyboard/mouse can perform construction work.
11. Xbox-style controller can perform construction work.
12. PlayStation-style controller can perform construction work.
13. Work progress persists through save/load/reconnect.
14. Unfinished representation/collision matches its physical stage.
15. No invisible finished wall collision exists during pure blueprint stage.
16. Physical partial stage blocks/walks only where geometry exists.
17. Stage completion updates representation/collision once, not every frame.
18. Final completion restores correct approved finished material/creator texture state.
19. Completed wall exposes its normal snap/support/opening capabilities.
20. NPC Builder can contribute valid work.
21. Assigned distant NPC crew can progress through scheduled/timestamp simulation only when labor/resources/contract permit.
22. Unassigned construction does not magically finish while offline.
23. Multiplayer clients see consistent stage/progress/completion state.
24. Unauthorized player cannot complete/cancel another player's site.
25. Performance remains stable with many idle unfinished sites because they do not run continuous Tick work.

---

# Core Rule

> Metaworld construction is work, not button spam. Placement creates an authorized persistent construction site; materials, qualified labor, tools and world rules advance it through meaningful stages; the server decides progress and completion; collision and visuals reflect what physically exists; players and NPC Builders can contribute through the same persistent economy without turning every unfinished structure into a per-frame simulation.