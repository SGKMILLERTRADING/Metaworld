# Metaworld — Base-Building Playlist Phase 20 Roadmap Addendum

**Status:** Canonical / Approved Phase 20 Intake Log

**Base Master Roadmap:** `Docs/Master_Development_Roadmap.md` v2.9

**Purpose:** Track approved features from the current UE4 base-building tutorial playlist one episode at a time without risking loss of the larger canonical Master Roadmap during frequent micro-updates. This addendum is part of Phase 20 canon and should be consolidated into the Master Roadmap after the playlist review is complete.

## Permanent Rules

- Blueprint-first runtime architecture.
- `BPC_MW_BuildComponent` owns build-mode flow.
- `BP_MW_Character_Master` remains the canonical humanoid parent.
- Keyboard/mouse, Xbox-style controllers and PlayStation-style controllers must all have valid player-facing control paths.
- Enhanced Input is used instead of permanently hardcoded physical keys.
- Construction preview is client-responsive but permanent construction is server-authoritative.
- Stable Buildable/Family/Variant IDs and data-driven definitions replace giant hardcoded Blueprint selection graphs.
- Snapping uses `BPI_MW_BuildSnapProvider`, stable Snap Point IDs, tags/metadata and lightweight query volumes rather than endless class casts or one trace channel per buildable type.
- Construction must obey property, profession, permits, resources, support, collision, persistence and performance rules.
- Tutorial-specific constants are examples, not universal Metaworld rules.
- Construction systems should integrate with Builder jobs, NPC workers, contracts, economy and role duties rather than remain isolated minigames.

---

# Playlist Intake Status

## Episode Upgrade 1 — Modular Build Component, Ghost Preview & Build Cycle

**Classification:** UPGRADE — APPROVED

Approved:
- reusable `BPC_MW_BuildComponent`
- build-mode state
- camera/view placement trace
- green/red ghost preview
- timer/event-driven placement updates
- data-driven build range
- server-authoritative final placement
- property/profession/resource validation
- controller-compatible build mode

## Episode Upgrade 2 — Buildable Database & Piece Cycling

**Classification:** UPGRADE — APPROVED

Approved:
- Struct + Data Table/Data Asset buildable definitions
- stable Buildable IDs
- build categories/families/variants
- next/previous cycling
- scalable Build Catalog UI
- soft references / active-category loading at scale
- server resolves authoritative definition rather than trusting client mesh/class/cost

## Episode Upgrade 3 — General Snap-Point System

**Classification:** UPGRADE — APPROVED

Approved:
- `BPI_MW_BuildSnapProvider`
- Query-Only Box Collision or equivalent acquisition volumes
- Scene Component/socket exact transforms
- stable Snap Point IDs
- tag/data-driven compatibility
- targeted snap query against relevant structure instead of scanning the world
- snap scoring/filtering
- small general build/snap/obstruction query set

## Episode Upgrade 4 — Wall Snapping & Wall Variants

**Classification:** UPGRADE — APPROVED

Approved:
- `Build.Family.Wall`
- `Wall.Standard`
- `Wall.DoorOpening`
- `Wall.WindowOpening`
- common foundation/floor wall-edge snap contract
- variant-specific collision/openings/cost/durability/metadata
- real doorway/window openings rather than cosmetic mesh swaps
- authorized renovation path for changing existing wall type

## Episode Upgrade 5 — Doors, Windows & Opening Attachment

**Classification:** UPGRADE — APPROVED

Approved:
- structural opening is separate from installed door/window
- `Build.Family.Door`
- `Build.Family.Window`
- stable Opening/Attachment Slot IDs
- opening dimensions/facing/compatibility/occupancy
- server-authoritative Door/Window installation
- obstruction validation
- pivot/orientation asset standards
- future locks/keys/security/breakable windows

Detailed companion: `Docs/Doors_Windows_Openings_Construction_System.md`

## Episode Upgrade 6 — Floors & Multi-Story Building

**Classification:** UPGRADE — APPROVED

Approved:
- `Build.Family.Floor`
- structural walkable floor pieces
- wall/support top snap points for upper floors
- second-story and continued vertical construction
- valid support chain required
- no arbitrary floating floors
- property height/air-right/zoning/build-budget validation
- persistent support/snap relationships
- future stair/ladder/elevator/utility floor openings

Detailed companion: `Docs/Flooring_Multi_Story_Structural_Construction_System.md`

## Episode Upgrade 7 — Interactive Doors & Windows

**Classification:** UPGRADE — APPROVED

Approved:
- common `BPI_MW_Interactable` runtime interaction contract
- shared player interaction component/trace
- authoritative state machine: Closed / Opening / Open / Closing
- lock/jam/damage/security restrictions separate from motion state
- Timeline motion approved for simple movement
- data-driven angle/distance/duration/curve
- generalized movable-part arrays for double doors/windows/shutters/sliders/etc.
- compact state replication; clients animate presentation locally
- no idle permanent Tick
- NPC-compatible interaction

Detailed companion: `Docs/Interactive_Doors_Windows_Runtime_System.md`

## Episode Upgrade 8 — Construction Progress / Build-To-Completion

**Classification:** UPGRADE — APPROVED

Approved:
- placement may create a persistent unfinished Construction Site instead of an instantly completed structure
- tutorial gray/transparent blueprint appearance retained as a simple early construction presentation option
- authoritative finished material/creator texture state stored separately and restored on completion
- fixed repeated `Interact` counts upgraded to data-driven Construction Work Units
- no button-spam architecture
- work can come from deliberate player work actions, tools, machinery, teams and qualified NPC Builders
- work contribution can consider profession, skill, tool quality, fatigue and stage complexity
- required materials/resources can gate each construction stage
- staged construction supported for larger structures
- construction-site location/snap slot is reserved while unfinished
- collision changes by physical construction stage rather than blindly `No Collision -> Block All`
- pure blueprint stage normally has query/reservation behavior without invisible finished-wall collision
- physical foundation/frame/partial stages use collision representing what physically exists
- final completion applies normal finished collision and capabilities
- partial structures expose only capabilities physically completed at the current stage
- server owns progress, work cadence, materials, stage and completion
- client cannot submit fake progress or set Completed
- save/load/reconnect preserves unfinished progress
- legitimate assigned NPC crews may progress through scheduled/timestamp simulation while unloaded only when labor/resources/contracts actually allow it
- unattended sites do not magically finish offline
- unfinished sites remain vulnerable to world events/damage under normal rules
- Builder profession duties, construction companies, suppliers, drivers and contracts connect into the system
- controller-compatible work/interact flow required
- no continuous Tick for idle construction progress

Detailed companion: `Docs/Construction_Progress_Build_To_Completion_System.md`

---

# Current Phase 20 Construction Stack

`Build Catalog / Selection`

`-> Ghost Placement`

`-> Property / Profession / Resource Validation`

`-> Foundation / Floor / Wall Snap Architecture`

`-> Wall Families & Structural Openings`

`-> Door / Window Installation`

`-> Supported Multi-Story Construction`

`-> Persistent Construction Site / Work Stages`

`-> Completed Structure`

`-> Interactive Door / Window Runtime`

`-> Repair / Renovation / Damage / Utilities / Contracts later`

---

# Construction Completion Principle

> Metaworld construction is not instant magic and it is not mindless button spam. Placement creates an authorized structure/site; physical resources, labor, tools, Builder skills and world rules determine how construction progresses; partial geometry behaves like what physically exists; final completion unlocks the finished structure and its normal collision, materials, snapping, utilities and interactions.

---

# Playlist Consolidation Rule

For each remaining playlist episode:

1. classify as LOCKED / UPGRADE / FUTURE / RESEARCH / REJECT
2. keep useful implementation ideas
3. upgrade UE4/tutorial-specific patterns for UE5.8 Blueprint-first Metaworld architecture
4. preserve controller support
5. preserve multiplayer authority
6. preserve persistent-world/economy/property/profession integration
7. preserve performance rules
8. avoid duplicate systems
9. add approved details to the relevant companion document or create a focused companion if needed
10. record the approved episode in this addendum

After the playlist is complete, consolidate all approved Phase 20 changes into the main Master Development Roadmap in one controlled update.