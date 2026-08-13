# Metaworld — Modern RPG UE5 Playlist Intake — Part 15

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part14.md`

**Playlist Source Engine:** Unreal Engine tutorial series spanning older UE5 versions including 5.5

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

This Part contains **Episodes 123–136**.

---

# Episode 123 — Project Upgrade to Unreal Engine 5.5

**Classification:** RESEARCH + UPGRADE — PROJECT MIGRATION STANDARD.

**Phase Ownership:** Project Maintenance + Tooling + Validation + Performance.

Detailed companion:

`Docs/Engine_Version_Upgrade_Migration_Validation_Standard.md`

## Approved Tutorial Intent

- protect/copy project before engine migration;
- account for custom fonts/external assets;
- review plugin prompts;
- allow shader recompilation;
- repair migrated material/reference issues;
- smoke-test swimming, climbing, trading and other core systems;
- improve editor workflow preferences.

## Metaworld Upgrades

- tutorial's UE5.5 target does not replace Metaworld's UE5.8 target;
- migrations occur on recoverable branch/copy with known-good rollback point;
- required plugin/dependency versions are audited deliberately;
- critical Blueprint/data/material/animation/MetaHuman/Water/Nanite systems are validated;
- gameplay smoke suite includes current Metaworld critical systems and controller paths;
- representative performance is measured before/after;
- custom fonts/assets become tracked dependencies rather than remembered manual copy steps;
- editor layout/preferences remain workflow settings, not runtime dependencies.

### Episode 123 Principle

> An engine upgrade is accepted only after the upgraded Metaworld proves its data, content, gameplay and performance still work; opening the project is only the first step.

---

# Episode 124 — Underwater Audio / VFX / Water Presentation

**Classification:** UPGRADE — APPROVED SWIMMING PRESENTATION EXTENSION.

**Phase Ownership:** Swimming + Audio + Niagara/VFX + Accessibility + Performance.

Detailed companion:

`Docs/Underwater_Audio_VFX_Presentation_System.md`

## Approved Tutorial Intent

- underwater ambience loop;
- muffle/filter outside sounds while submerged;
- bubble/fish Niagara presentation;
- tune Breath duration for exploration;
- reuse/configure multiple water body types.

## Metaworld Upgrades

- audio/VFX derive from canonical water/camera/airway environment state and never own Swimming/Breath truth;
- water presentation uses per-water profiles for lake/river/ocean/etc.;
- Niagara/audio/post-process are significance/scalability controlled;
- Breath drain value such as 0.05 is prototype tuning only;
- critical UI/accessibility/emergency audio must not be unintentionally hidden by underwater filtering;
- surfacing/ladder/ledge/teleport transitions reconcile audio/VFX from current environment state;
- duplicated/converted Water Bodies are validated for actual gameplay water-query/physics behavior rather than assumed correct.

### Episode 124 Principle

> Underwater sound and visuals make the water believable, but one environment state still decides whether the character is submerged, breathing or drowning.

---

# Episode 125 — Rune Puzzle Door Assets / Pillars / Decals

**Classification:** UPGRADE — NEW PUZZLE / WORLD-LOGIC DOMAIN.

**Phase Ownership:** Interaction + World State + Puzzle Logic + Environment Art.

Detailed companion:

`Docs/Puzzle_World_State_Rune_Door_Logic_System.md`

## Approved Tutorial Intent

- Modeling Tools-built puzzle assets;
- stone pillars/base/door;
- emissive translucent rune decals/material instances;
- one master puzzle actor grouping related pieces.

## Metaworld Upgrades

- puzzle gets stable PuzzleInstanceID/Definition/Input/Output identities;
- visual runes/meshes are presentation of persistent puzzle state;
- authored hierarchy can package a puzzle without making Actor transform values the only save truth;
- asset materials/decals remain reusable/configurable and performance-budgeted.

### Episode 125 Principle

> Puzzle art defines readable inputs and outputs; persistent puzzle data defines what those objects mean.

---

# Episode 126 — Rune Pillar Rotation / Solution Logic

**Classification:** UPGRADE — APPROVED EVENT-DRIVEN PUZZLE LOGIC.

**Phase Ownership:** Puzzle + Interaction + Persistence + Multiplayer.

Detailed companion:

`Docs/Puzzle_World_State_Rune_Door_Logic_System.md`

## Approved Tutorial Intent

- rotate interaction action;
- discrete 90-degree pillar rotation;
- current pillar state;
- authored solution map;
- compare current inputs to target solution;
- open door when solved.

## Metaworld Upgrades

- stable discrete state/data replaces dependence on one global A/B/C/D enum for all puzzles;
- server commits next input state before clients animate it;
- Timeline presents committed rotation;
- puzzle evaluates only when an input changes, not on Tick;
- concurrent player interaction cannot desync pillar state;
- puzzle definition can later support sequences, timed logic, cooperative rules, randomized persistent solutions and other puzzle types.

### Episode 126 Principle

> Rotate an input, commit its state, evaluate the puzzle, then notify outputs—never let Timeline state or client order become puzzle authority.

---

# Episode 127 — Rune Door Movement / Audio / VFX / Rune Feedback

**Classification:** UPGRADE — APPROVED PUZZLE OUTPUT PRESENTATION.

**Phase Ownership:** Puzzle + Door/World Objects + Audio/VFX.

Detailed companion:

`Docs/Puzzle_World_State_Rune_Door_Logic_System.md`

## Approved Tutorial Intent

- heavy stone door Timeline;
- pillar/door audio;
- door impact/dust effects;
- door rune display reflecting puzzle state.

## Metaworld Upgrades

- door movement uses authored local/relative transforms rather than absolute world-height assumptions;
- puzzle solution requests the door/world-object state through a reusable output contract;
- runes can show state/clues but do not own the solution;
- audio/Niagara/dust are presentation;
- reversible/one-shot/reset behavior comes from PuzzleDefinition.

### Episode 127 Principle

> Puzzle completion changes authoritative world state; heavy movement, runes, dust and sound communicate that change.

---

# Episode 128 — UE5.5 Cleanup / Puzzle Relative Motion / Stack / IK / UI Fixes

**Classification:** LOCKED + UPGRADE — MAINTENANCE.

**Phase Ownership:** Puzzle + Inventory + Quickslots + Animation/IK + UI/Input.

Detailed companions:

- `Docs/Puzzle_World_State_Rune_Door_Logic_System.md`
- `Docs/Quickslot_Hotbar_Item_Action_Assignment_System.md`
- `Docs/UI_Base_Widget_Modal_Input_Lifecycle_System.md`
- `Docs/Animation_Authoring_Control_Rig_Root_Motion_Workflow.md`

## Approved / Locked Corrections

- puzzle door uses relative/local movement;
- partial-stack drop must preserve the split quantity, never the original unsplit count;
- quickslot duplicate-removal handles empty/missing targets safely;
- HUD/resource percent code guards against zero maximums;
- UI focusability is deliberately configured for controller/keyboard focus routing;
- MetaHuman IK may use project-compatible Virtual Bones/IK contracts where needed;
- UI input state returns through the shared lifecycle architecture.

## Metaworld Rule

Do not treat tutorial-specific UE5.5 focus/IK fixes as universal constants; preserve the problem/acceptance requirement and implement against UE5.8 project assets.

### Episode 128 Principle

> Maintenance fixes become system invariants: local-space world movement, exact stack identity, safe references, zero-safe resource math, compatible IK and predictable UI focus.

---

# Episode 129 — Potion Drinking Animation / Anti-Spam

**Classification:** UPGRADE — NEW CONSUMABLE ACTION PIPELINE.

**Phase Ownership:** Item Use + Status Effects + Animation + Quickslots + Movement.

Detailed companion:

`Docs/Consumable_Action_Use_Animation_Interruption_System.md`

## Approved Tutorial Intent

- authored drinking animation/montage;
- Montage Notify at the actual drink/contact phase;
- Layered Blend Per Bone so locomotion can continue where allowed;
- prevent repeated potion spam;
- temporary bottle/potion hand presentation;
- synchronized consumption sound.

## Metaworld Upgrades

- real ItemInstance is reserved/validated before the action;
- shared CharacterActionID replaces one loose `IsDrinkingPotion` Boolean;
- use profile defines movement/traversal/environment restrictions;
- notify is a commitment-phase signal, not sole inventory/effect authority;
- consume/decrement and effect application commit exactly once;
- potion effects flow through Stats/StatusEffects;
- quickslots submit the same authoritative use request;
- spawned hand prop is presentation, not a duplicate inventory item.

### Episode 129 Principle

> Drinking is a timed item-use action: validate first, animate, commit the real item/effect once at the approved phase, and cancel cleanly if the action is interrupted.

---

# Episode 130 — Upgrade Index Fix / Unified Movement Speed Function

**Classification:** LOCKED + UPGRADE — MOVEMENT-STATE ARCHITECTURE.

**Phase Ownership:** Item Upgrade + Movement + Encumbrance + Swimming + Actions.

Detailed companion:

`Docs/Character_Action_Movement_State_Resolver_System.md`

## Approved Tutorial Intent

- centralize speed changes instead of scattered direct writes;
- prevent Sprint/Potion/Encumbrance movement conflicts;
- apply comparable logic to swim speed;
- fix inventory-index targeting during upgrades.

## Metaworld Upgrades

- stable ItemInstanceID already avoids inventory-index identity bugs for ordinary upgrades;
- tutorial `Normal/Sprint/Potion/KeepCurrent` enum is a prototype, not final world state;
- one resolver derives movement from action + traversal + environment + encumbrance + injury/status + equipment;
- systems declare semantic restrictions instead of directly overwriting MaxWalkSpeed/MaxSwimSpeed;
- leaving an action recomputes current truth instead of restoring a stale default speed;
- evaluation runs on state changes, not Tick.

### Episode 130 Principle

> No gameplay feature owns character speed by itself. Metaworld derives effective movement from all active character states so one feature cannot erase another's restrictions.

---

# Episode 131 — Sitting / Chair / Recovery

**Classification:** UPGRADE — NEW REST / FURNITURE INTERACTION DOMAIN.

**Phase Ownership:** Interaction + Animation + Needs/Vitals + Furniture + NPC AI.

Detailed companion:

`Docs/Rest_Sit_Sleep_Furniture_Recovery_System.md`

## Approved Tutorial Intent

- sit/stand animation preparation;
- chair interactable with authored seat transform;
- smooth alignment/rotation;
- seated idle state;
- standing action;
- interaction prompt/facing requirement;
- potential recovery while resting.

## Metaworld Upgrades

- seat exposes stable slot/occupancy data;
- server reserves one-person seat before use;
- Motion Warping/root motion can replace long arbitrary position Timelines where appropriate;
- collision changes are bounded/restored explicitly rather than blanket no-collision;
- sitting does not universally grant free Health regeneration; recovery follows Needs/Vitals/injury/medical policy;
- NPCs can use the same furniture slots;
- property/access rules apply.

### Episode 131 Principle

> A chair is a usable world slot with occupancy and recovery policy, not only a Sit montage trigger.

---

# Episode 132 — Sleeping / Bed / Wake-Up

**Classification:** UPGRADE — APPROVED REST SYSTEM EXTENSION.

**Phase Ownership:** Rest + Needs + World Time + Property + Animation.

Detailed companion:

`Docs/Rest_Sit_Sleep_Furniture_Recovery_System.md`

## Approved Tutorial Intent

- bed asset/positioning targets;
- lie-down/sleep/wake animations;
- root-motion transitions;
- smooth character rotation/alignment;
- interface-driven interaction prompting.

## Metaworld Upgrades

- `Rest.Sleeping` is an explicit character state;
- bed slot is reserved and validated;
- sleeping never globally pauses/fast-forwards a persistent multiplayer world by default;
- Fatigue/Needs/rest recovery may resolve through active time/timestamps;
- wake can occur from player choice, danger, damage, property/world events or schedule;
- beds can belong to homes, hotels, hospitals, jail/prison and other access contexts;
- exit restores collision/movement through shared state resolver.

### Episode 132 Principle

> Sleep is persistent-world rest: the character occupies a real bed slot and recovers according to Needs/Vitals while the rest of Metaworld continues living.

---

# Episode 133 — Pushable Stone Block

**Classification:** UPGRADE — NEW PUSHABLE OBJECT / PHYSICS PUZZLE DOMAIN.

**Phase Ownership:** World Objects + Puzzle + Physics + Animation + Stamina.

Detailed companion:

`Docs/Pushable_Object_Pressure_Plate_Physics_Puzzle_System.md`

## Approved Tutorial Intent

- constrained heavy stone block;
- valid push-side collision areas;
- pushing locomotion/animation state;
- player must face block correctly;
- Control Rig/Sequencer animation cleanup.

## Metaworld Upgrades

- pushable is a reusable object capability/profile;
- server validates grounded state, push side, obstruction, action state and object availability;
- strength/Stamina/skill/team rules can affect heavy objects;
- physics owns actual block movement while animation presents effort;
- restrictions are content/profile driven rather than universal X/Y-only behavior;
- world/property/crime rules may apply to moving owned objects.

### Episode 133 Principle

> Pushing is a character-to-world-object action: validate the side and effort, then let authoritative world physics/state move the real object.

---

# Episode 134 — Ledges on Movable Blocks / Push Audio / IK Fix

**Classification:** UPGRADE — CROSS-SYSTEM PUZZLE/TRAVERSAL INTEGRATION.

**Phase Ownership:** Pushables + Ledge Traversal + Animation + Audio.

Detailed companions:

- `Docs/Pushable_Object_Pressure_Plate_Physics_Puzzle_System.md`
- `Docs/Ledge_Mantle_Climb_Traversal_System.md`

## Approved Tutorial Intent

- suppress inappropriate IK trace while on/near ledge state;
- attach ledge affordances to movable blocks;
- avoid traversal collision interfering with push physics;
- play scraping loop only while the block moves.

## Metaworld Upgrades

- traversal targets move coherently with parent WorldObject transform;
- server validates the ledge's current moved position at grab/climb time;
- no stale detached ledge Actor after the block moves;
- animation IK policies derive from current traversal/action state;
- scrape sound derives from actual movement/velocity state and shuts down cleanly;
- future surface material can affect push audio.

### Episode 134 Principle

> A movable block can also be a movable traversal surface, but its ledge, physics, animation and sound must all read the same authoritative world transform/state.

---

# Episode 135 — Block Placeholder / Pressure Plate / Door Trigger

**Classification:** UPGRADE — APPROVED PUZZLE INPUT SYSTEM.

**Phase Ownership:** Puzzle + Physics + World Objects + Interaction.

Detailed companion:

`Docs/Pushable_Object_Pressure_Plate_Physics_Puzzle_System.md`

## Approved Tutorial Intent

- visible placeholder/pressure plate;
- non-blocking overlap detection;
- reusable interface/event output;
- count placed blocks against required blocks;
- open/close door reversibly when occupancy changes.

## Metaworld Upgrades

- stable PuzzleInputID + accepted-object/weight/count profile;
- overlap is candidate signal; authoritative validation determines whether the placement counts;
- PuzzleDefinition evaluates the combined plate/input state;
- outputs use reusable puzzle/world-object contracts rather than direct casts;
- saved block transforms/world state reconstruct valid occupancy rather than persisting one stale overlap Boolean;
- same system can drive doors, ladders, lifts, bridges or traps.

### Episode 135 Principle

> Pressure plates observe real world placement; puzzle rules decide whether it counts and what world output reacts.

---

# Episode 136 — Placeholder Material/Sound Feedback / Airborne Push Fix

**Classification:** LOCKED + UPGRADE — PRESENTATION + PUSH VALIDATION.

**Phase Ownership:** Pushables + Puzzle Presentation + Audio/VFX + Movement.

Detailed companion:

`Docs/Pushable_Object_Pressure_Plate_Physics_Puzzle_System.md`

## Approved Tutorial Intent

- per-instance Dynamic Material feedback;
- smooth state color transition;
- activation/deactivation audio;
- block pushing disallowed while player is falling;
- pressure-plate puzzle can drive a ladder/world event.

## Metaworld Upgrades

- dynamic material/audio follows authoritative plate state;
- color is not the sole accessibility cue where state is important;
- airborne player cannot start ordinary grounded pushing;
- reusable puzzle output can target a Lift/Ladder/Door through stable output contract;
- activation/deactivation feedback never becomes puzzle truth.

### Episode 136 Principle

> Feedback makes puzzle state readable; the placement rule remains authoritative, and grounded pushing remains a real movement/action constraint.

---

# Part 15 Consolidated Additions

New companions introduced in this Part:

- `Docs/Engine_Version_Upgrade_Migration_Validation_Standard.md`
- `Docs/Underwater_Audio_VFX_Presentation_System.md`
- `Docs/Puzzle_World_State_Rune_Door_Logic_System.md`
- `Docs/Consumable_Action_Use_Animation_Interruption_System.md`
- `Docs/Character_Action_Movement_State_Resolver_System.md`
- `Docs/Rest_Sit_Sleep_Furniture_Recovery_System.md`
- `Docs/Pushable_Object_Pressure_Plate_Physics_Puzzle_System.md`

Core integration chains:

`Engine Upgrade Candidate`
-> `Recoverable Migration Branch`
-> `Plugin/Data/Content Validation`
-> `Gameplay Smoke Suite`
-> `Performance Comparison`
-> `Canonical Engine Approval`

`Puzzle Inputs`
-> `Persistent Puzzle State`
-> `Event-Driven Evaluation`
-> `Door/Lift/Ladder/World Outputs`
-> `Audio/VFX/Material Feedback`

`Item Use / Rest / Push / Sprint / Swim / Traversal`
-> `Semantic Character State`
-> `Movement Resolver`
-> `Effective Movement Parameters`
-> `ABP_MW_Master Presentation`.

## Part 15 Core Rule

> Metaworld keeps gameplay systems composable. Engine upgrades are validated, puzzles are world-state logic, consumables/rest/pushing declare semantic actions, and one movement resolver prevents those actions from fighting over the character's movement values.