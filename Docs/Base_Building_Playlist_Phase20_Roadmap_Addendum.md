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
- Buildable orientation is data-driven and snap-aware; snapping constrains legal rotation instead of automatically disabling rotation.
- Physical overlap validation uses explicit placement footprints plus logical slot occupancy; render-mesh bounds, Visibility traces and one universal shrink multiplier are not authoritative placement rules.
- Structural support must terminate through valid terrain or an approved support chain. Elevated structures are allowed when their definition and real supports permit them; arbitrary unsupported floating structures are not.

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

## Episode Upgrade 9 — Buildable Rotation & Orientation

**Classification:** UPGRADE — APPROVED

Approved:
- rotation input only operates while Build Mode and a valid rotatable placement/ghost are active
- Enhanced Input actions replace permanently hardcoded Q/E rotation keys
- left/right rotation both supported
- structural pieces use deterministic step rotation where appropriate
- eligible free-placement objects can use smooth held/fine rotation
- tutorial gate + `0.01` delay loop is not a permanent architecture requirement
- rotation step, axis, speed, range and allowed orientations are Buildable Definition data
- snap-aware rotation replaces the tutorial limitation where snapping simply disables rotation
- snap relationships may lock rotation, allow 180° flip, allow quarter-turns, expose approved variants or allow special free-yaw cases
- resolved orientation uses base/snap rotation + validated user rotation offset rather than uncontrolled rotator accumulation
- rotating a ghost reruns footprint/collision/property/snap validation and can change valid/invalid preview state
- Build Mode input context takes priority so rotation does not accidentally trigger Interact/Build Work on the same physical control
- client gets responsive local rotation preview; server independently validates legal orientation before permanent placement
- forged illegal rotation from a modified client is rejected
- final orientation persists across save/load
- keyboard/mouse, Xbox-style controller and PlayStation-style controller rotation paths are required
- no permanent high-frequency rotation polling while Build Mode is inactive/idle

Detailed companion: `Docs/Construction_Rotation_Orientation_Control_System.md`

## Episode Upgrade 10 — No-Overlap / Placement Collision Validation

**Classification:** UPGRADE — APPROVED

Approved:
- green/red ghost feedback reflects local obstruction validation
- selected Buildable/Variant carries explicit authoritative placement footprint data rather than relying only on render-mesh bounds
- footprint may use one or more simple Box/Capsule/convex-style volumes with local transform/tolerance metadata
- tutorial `Get Component Bounds + Box Trace` remains a useful prototype but is not the final universal footprint architecture
- Visibility is not the permanent construction-overlap channel; use a small dedicated Build Obstruction query family where practical
- tutorial bounds multipliers such as `0.2` are kit-specific examples, not global rules
- per-buildable clearance/contact/snap tolerances replace magic shrink values
- simple collision / explicit lightweight footprints are preferred for predictable performance and placement behavior
- complex/per-poly collision is not allowed to accidentally make tiny decorative triangles decide construction validity
- logical snap/opening/support occupancy is checked separately from physical world-space overlap
- valid intentional contact such as wall-to-foundation, upper-floor-to-support and door-to-opening is permitted through authoritative snap relationships
- duplicate occupancy of an exclusive wall edge/opening/floor slot is rejected even when raw geometry might appear clear
- rotating a ghost reruns obstruction validation using the rotated footprint
- bad pivots/origins are treated as asset-authoring/QA issues instead of permanently patching runtime logic with one multiplier
- Build Mode / valid selection / ghost checks prevent cycling or preview operations from dereferencing missing build references while Build Mode is inactive
- client obstruction result is advisory; server independently resolves authoritative footprint and reruns obstruction validation before consuming resources/creating the structure
- modified clients cannot fake `CanBuild`, footprint size, collision response or green ghost state
- construction sites retain logical location/slot reservation while unfinished
- door/window runtime motion clearance can later be modeled separately from installation footprint
- no overlap queries when Build Mode is inactive; targeted shape queries replace broad scans
- Python Editor tooling can audit pivots, simple collision, footprint alignment and missing placement metadata
- keyboard/mouse, Xbox-style controller and PlayStation-style controller placement/rotation paths all receive the same valid/blocked result

Detailed companion: `Docs/Construction_Overlap_Collision_Validation_System.md`

## Episode Upgrade 11 — Foundation Height, Terrain Support & Extensions

**Classification:** UPGRADE — APPROVED

Approved:
- foundations check for valid support below authored support sample points rather than permitting arbitrary floating placement
- tutorial four-corner Arrow Components are generalized into data-driven `SupportSamplePoints[]`; small foundations may still use four corners while larger/irregular pieces can use more appropriate authored patterns
- support queries measure direct-ground/support distance and classify direct support, extension-required support or invalid support
- single fixed floating-height limits become per-buildable `MaximumUnsupportedDistance`, support query range, slope/normal and support-type rules
- a downward trace hit is not automatically valid ground; accepted terrain/structural support is defined through tags/data
- vehicles, characters, loose props and other non-structural objects cannot become fake foundation support merely because a trace hits them
- uneven terrain may automatically preview pier/post/footing/foundation-extension pieces beneath required sample points
- extension segment family/type, height, stack count, maximum depth, allowed surfaces, collision, durability and support metadata are data-driven
- required support extensions add real material/resource cost and Construction Work Units; auto-generated support is not free
- required extension cost/work is shown before confirmation where practical
- missing materials, excessive depth, invalid support surface, collision, zoning/property/depth-right violations or unsupported slope can block placement
- elevated/stilt/deck-style structures remain possible when their Buildable Definition explicitly allows the support pattern and a valid structural chain exists
- extension ghosts are transient/non-blocking during preview and use construction/ghost presentation rather than finished physical collision
- successful support extensions become real persistent structural elements with Structure IDs and parent/support relationships
- foundation support connects into the existing structural graph: approved ground/base -> extension/pier -> foundation -> walls/columns -> upper floors
- support-extension placement uses the canonical overlap footprint system and allows only intentional structural contact
- unfinished support pieces participate in the build-to-completion system rather than magically becoming completed if their construction definition requires labor/stages
- support state can later participate in damage, repair, inspection, collapse/instability and emergency Builder duties when critical supports are lost
- no permanent per-frame ground tracing after placement; support validation/recalculation is event-driven
- client support calculations are advisory; server independently resolves sample points, support hits, extension counts, total cost and legal depth before creating the construction site
- modified clients cannot fake ground height, omit required extensions or bypass extension resource/depth rules
- property footprint, 3D build volume, subsurface/depth rights, zoning, protected/public space and future underground-utility restrictions can apply
- keyboard/mouse, Xbox-style controller and PlayStation-style controller users receive the same support/height feedback and confirmation flow
- Python Editor tooling can audit support sample points, extension definitions, pivots, collision/footprints and suspicious support metadata

Detailed companion: `Docs/Foundation_Terrain_Support_Extension_System.md`

---

# Current Phase 20 Construction Stack

`Build Catalog / Selection`

`-> Ghost Placement / Rotation / Orientation`

`-> Placement Footprint / Overlap / Slot-Occupancy Validation`

`-> Terrain / Foundation Support Sampling & Required Extensions`

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

# Rotation Principle

> Rotation is part of the placement rules, not a free transform cheat. Structural pieces favor deterministic orientation steps; free-placement pieces may support fine rotation; snap points define legal orientation choices; the server validates the final transform.

---

# Overlap Validation Principle

> Metaworld separates what an asset looks like from the space it is allowed to occupy. Explicit placement footprints, snap-slot occupancy and authoritative server obstruction checks decide whether a structure fits; tutorial trace channels, mesh bounds and shrink constants are implementation aids, not world truth.

---

# Foundation Support Principle

> Metaworld does not require every foundation to touch flat terrain, but every structural load path must end in valid support. Uneven/elevated construction uses real authored support rules and persistent extension pieces with real cost and labor; unsupported floating construction is rejected.

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