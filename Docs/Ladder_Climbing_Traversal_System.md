# Metaworld — Ladder Climbing & Vertical Traversal System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative traversal state / animation-integrated / controller-complete

## Canonical Principle

A ladder is a contextual traversal object that provides valid entry/exit targets and a constrained climb path. The character enters a dedicated climbing/traversal state; animation and movement present that state; the player does not become a semantically "flying" character merely because `MOVE_Flying` can be useful as an implementation tool.

> Ladder climbing is a controlled interaction along an authored traversal path with explicit entry, climb, exit, cancellation and authority rules.

Related canon:

- `Docs/Avatar_Communication_Character_Animation_Architecture.md`
- `Docs/Animation_Authoring_Control_Rig_Root_Motion_Workflow.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`
- `Docs/Movement_Sprint_Stamina_Regeneration_Exertion_System.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`

---

# 1. Ladder Object Contract

Suggested world object:

`BP_MW_Ladder` or a general traversal-object implementation with Ladder profile.

Possible stable data:

- `TraversalObjectID`
- `TraversalType = Ladder`
- bottom entry transform
- top entry/exit transform
- ladder forward direction
- climb axis/path
- rung spacing / nominal climb rate
- usable height
- bottom/top clearance volumes
- animation profile ID
- permitted directions
- access/condition state
- damage/broken state where supported
- interaction/action IDs.

The ladder mesh can be modular and resized, but traversal data must remain valid for the actual physical dimensions.

---

# 2. Interaction Eligibility

The tutorial's "player must be in front" check is useful, but Metaworld uses the common interaction resolver.

Eligibility can consider:

- distance/reach;
- facing/dot-product cone;
- line of sight;
- valid bottom/top entry side;
- required clearance;
- ladder occupied/reserved state where necessary;
- character state;
- encumbrance/carrying restrictions where designed;
- injury/status restrictions;
- access/security rules for restricted ladders.

Do not run permanent ladder checks when no relevant character is near/interacting.

---

# 3. Traversal State

Suggested semantic state:

- `NotClimbing`
- `EnteringLadder`
- `Climbing`
- `ExitingTop`
- `ExitingBottom`
- `Interrupted/Falling` where required.

The gameplay/character traversal component owns this state.

Implementation may temporarily use Character Movement `MOVE_Flying` during the climb because it ignores gravity and supports controlled movement, but `Flying` is an engine movement mode—not the gameplay meaning of the action.

The Metaworld state remains `Climbing.Ladder` or equivalent.

---

# 4. Entry Alignment

Do not instantly snap/teleport from an arbitrary position into the ladder if a smoother contextual alignment is practical.

Preferred flow:

`Request Use Ladder`
-> validate entry
-> reserve traversal context if needed
-> align to authored entry target
-> play entry animation/montage
-> transition into constrained climb state.

Motion Warping/root-motion entry animation may align the character to the ladder target.

The entry target derives from ladder data, not hardcoded world offsets in the Player Blueprint.

---

# 5. Climb Movement

While climbing:

- normal ground locomotion is suspended;
- movement input is projected onto the ladder climb axis;
- lateral drift away from the ladder is constrained;
- gravity behavior follows climb policy;
- climb speed is data/stat/context driven;
- collision remains valid;
- animation reads signed climb velocity/progress.

Up/down input works through logical movement/traversal actions, not hardcoded keyboard-only controls.

Possible modifiers:

- Stamina;
- carried load/Encumbrance;
- injury;
- wet/icy condition;
- ladder condition;
- climbing skill/equipment where later designed.

---

# 6. Animation

The tutorial's 1D Blend Space for climb up / idle / climb down is an approved prototype/content pattern.

Metaworld can use:

- dedicated ladder animation layer/profile;
- climb idle/up/down cycles;
- Sync Markers for hand/foot/rung phase where useful;
- procedural IK/contact correction;
- Motion Warping/root-motion montages for entry/top exit/bottom exit;
- body-profile retargeting through canonical skeleton/IK contracts.

The animation system presents climb velocity/state. It does not own ladder authority.

---

# 7. Top Exit

Top exit is a contextual traversal action, not simply turning Walking back on when the capsule crosses a box.

Server/gameplay validates:

- top exit target still exists;
- landing space is clear;
- ladder/path is still valid;
- character is allowed to complete exit.

Then:

- align/warp to exit target;
- play exit montage/root trajectory;
- restore normal capsule/collision/movement state at the correct phase;
- release ladder traversal context.

Root motion may be used for the authored exit, but the gameplay system validates target/collision before completion.

---

# 8. Bottom Exit / Drop Off

Player can climb down and leave at the bottom through a defined exit flow.

Optional action to intentionally let go/drop may exist later, but it must transition to Falling with appropriate velocity/damage rules rather than silently teleporting to ground.

---

# 9. Collision / Capsule State

Any collision changes made during entry/exit are explicit state transitions.

Rules:

- do not leave the capsule in a disabled/incorrect collision state after cancellation;
- interruption/death/status effect restores a safe movement/collision state;
- other players/NPCs cannot exploit temporary no-collision state to pass through restricted geometry;
- ladder accessory meshes do not create irrelevant interaction overlaps.

---

# 10. Multiplayer / Authority

Client:

- selects ladder;
- sends use/movement intent;
- renders animation responsively.

Server:

- validates ladder/context;
- owns traversal state;
- validates entry/exit;
- resolves interruptions;
- replicates meaningful traversal state/position through normal character movement/networking architecture.

Client cannot declare itself at the top of a ladder or bypass locked/restricted traversal solely by playing an animation.

---

# 11. Multiple Characters / Occupancy

Not every ladder needs a one-user global lock.

Profiles can define:

- multiple climbers allowed with spacing rules;
- one climber only for narrow/special ladders;
- direction conflict handling;
- NPC reservation/Smart Object style usage where helpful.

Do not make one universal `IsOccupied` Boolean prevent realistic multi-user ladders unless that ladder truly requires exclusivity.

---

# 12. NPC Compatibility

NPCs can use the same traversal object/profile where pathing/AI rules support it.

NPC flow can include:

- path reaches ladder entry;
- reserve/use interaction;
- enter climb traversal;
- climb;
- exit;
- resume navigation/behavior.

Distant NPC simulation may resolve traversal abstractly rather than evaluating full ladder animation when not visible/relevant.

---

# 13. Stamina / Encumbrance

Climbing can consume Stamina according to traversal profile.

Heavy carried load can:

- slow climb;
- increase Stamina drain;
- block ladder use at extreme load;
- require dropping/carrying differently.

Do not let moving from Walking to `MOVE_Flying` accidentally bypass Encumbrance or resource rules.

---

# 14. Performance

- ladder Actors do not Tick just because they exist;
- interaction/facing checks occur only for relevant candidates;
- climb update exists only while a character is climbing;
- entry/exit volumes are simple/bounded;
- animation/IK fidelity scales with character significance;
- unloaded ladders remain data/world geometry without active traversal work.

---

# 15. Controller / Accessibility

Required:

- enter ladder with logical Interact/Use action;
- climb up/down with movement input;
- exit/cancel/drop where supported;
- KBM/Xbox-style/PlayStation-style support;
- prompts use active binding/device family;
- no mouse-only ladder action.

Optional accessibility settings can reduce repeated hold requirements or support toggle-style traversal where compatible with gameplay design.

---

# 16. Authoring Validation

Editor/Python validation can later audit:

- missing entry/exit transforms;
- wrong ladder forward direction;
- invalid usable height;
- top exit inside blocking geometry;
- missing animation profile;
- interaction volume too large/small;
- mismatched mesh/traversal height;
- missing controller test metadata.

---

# 17. Acceptance Tests

1. Player can interact only from valid ladder approach/context.
2. Entry aligns smoothly to ladder without arbitrary teleport from invalid positions.
3. Climb input moves only along the ladder path.
4. Releasing movement holds stable climb position when appropriate.
5. Climb down works.
6. Top exit lands on valid platform and restores Walking/collision cleanly.
7. Bottom exit restores Walking/collision cleanly.
8. Interruption cannot leave character stuck in Flying/no-collision state.
9. Encumbrance/Stamina rules still apply while climbing.
10. Multiplayer client cannot teleport to ladder top by faking animation state.
11. NPC can use authored ladder where supported.
12. Idle ladders incur no unnecessary Tick cost.
13. KBM/Xbox-style/PlayStation-style ladder controls all work.
14. Different ladder heights reuse the same traversal architecture through authored data.
15. Imported/edited climb animations remain compatible with the master animation contract.

## Core Rule

> A Metaworld ladder is a reusable traversal path, not a special-case Flying hack. Gameplay owns a real climbing state and valid entry/exit targets; movement, root motion, Motion Warping and animation cooperate to present that state safely across player, NPC and multiplayer use.