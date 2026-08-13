# Metaworld — Animation Authoring, Control Rig & Root Motion Workflow

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first runtime / Control Rig + Sequencer + Python editor tooling / data-driven animation architecture

## Canonical Principle

Metaworld can create, repair and adapt animation directly in Unreal Engine using Control Rig, Sequencer and animation tools, while runtime animation remains integrated with the canonical `ABP_MW_Master`, Motion Matching/Pose Search, Linked Animation Layers, Montages, IK and Motion Warping architecture.

> In-engine animation authoring is a production tool. It improves reusable animation assets; it does not justify bypassing the shared animation contract with one-off Player Blueprint movement hacks.

Related canon:

- `Docs/Avatar_Communication_Character_Animation_Architecture.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`
- `Docs/Movement_Sprint_Stamina_Regeneration_Exertion_System.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`

---

# 1. Control Rig / Sequencer Authoring Is Approved

Use Control Rig + Sequencer for:

- creating custom animation from keyframes;
- correcting clipping;
- hand/foot alignment fixes;
- weapon/tool pose cleanup;
- interaction animation edits;
- ladder/vehicle/seat alignment;
- root trajectory fixes;
- imported-animation cleanup;
- animation prototyping;
- creator/profession animation adjustments.

Animation assets authored/fixed in Unreal should still follow shared skeleton/socket/retarget contracts.

---

# 2. Bake Existing Animation To Control Rig

Existing Animation Sequences can be baked to an appropriate Control Rig for editing, then baked/exported back to reusable animation assets according to the production workflow.

This is preferred over permanently running complex Sequencer authoring data for ordinary runtime locomotion/actions.

Keep source/edit history where practical so animation changes remain reproducible.

---

# 3. Animation Corrections Must Solve The Actual Problem

Examples:

Shield clips through body while running:
- inspect attachment profile/socket;
- inspect animation pose;
- inspect body/armor proportions;
- use IK/Control Rig correction where appropriate.

Ladder exit misses platform:
- inspect target alignment;
- root trajectory;
- Motion Warping target;
- montage timing/collision transition.

Do not globally distort unrelated animations to fix one contextual interaction.

---

# 4. Root Motion Policy

Root Motion is approved for discrete authored actions when the animation's root trajectory should contribute to character movement.

Good candidates can include:

- melee lunges/committed attacks;
- ladder top/bottom entry/exit;
- vault/mantle segments;
- vehicle entry/exit;
- arrests/grapples;
- contextual workstation/door actions;
- selected special movement abilities.

Normal open locomotion remains driven through the locomotion/movement architecture rather than converting every walk/run/sprint animation into an authoritative root-motion sequence.

---

# 5. Root Motion Does Not Bypass Gameplay Authority

Animation can provide motion, but gameplay still owns:

- whether action is allowed;
- target/context validation;
- stamina/cost;
- collision/world legality;
- damage/interaction result;
- interruption/cancel rules;
- replication/persistence consequences.

Client animation root movement cannot create authoritative teleportation, damage or interaction success.

---

# 6. Motion Warping For Context Targets

For contextual animation, prefer target-aware alignment over manually teleporting the player to magic offsets.

Examples:

- ladder entry point;
- ladder top exit;
- chair/bed;
- vehicle seat/door;
- workstation;
- contextual melee target.

Gameplay defines a valid target transform; Motion Warping/interaction animation aligns the authored root motion to it where appropriate.

---

# 7. Sprint Animation Integration

The tutorial's Blend Space sprint extension is an approved prototype/content lesson.

Metaworld's canonical locomotion direction remains:

- `ABP_MW_Master`;
- Motion Matching / Pose Search for high-fidelity locomotion where appropriate;
- locomotion profiles/layers;
- Sync Markers/contact timing;
- IK/procedural contacts;
- significance-scaled NPC alternatives.

Sprint gameplay state comes from the Movement/Stamina/Encumbrance system.

Animation reads:

- desired velocity/speed;
- sprint state;
- movement direction;
- stance/injury/carry/equipment context.

Animation does not decide whether the player has enough stamina to sprint.

---

# 8. Sync Markers / Foot Timing

Foot-phase synchronization is approved for movement blending where the asset set supports it.

Use markers/groups consistently across compatible cycles so transitions reduce foot sliding/pop.

Naming/marker conventions should be standardized and validated across the locomotion library.

---

# 9. Imported Animation Sources

External animation assets such as Mixamo or marketplace/Fab animation can be used only after:

- license/source provenance is recorded;
- skeleton/retarget setup is correct;
- scale/orientation is validated;
- root motion policy is understood;
- contacts/clipping are reviewed;
- animation is retargeted/edited into canonical production assets where appropriate.

Do not preserve bad root orientation just because the source asset imported that way.

---

# 10. Quickslot/UI Bug From Discarded Widgets

The tutorial reports double-triggered item use caused by stale/discarded UI elements.

That is a UI lifecycle bug, not an animation problem.

Canonical fix lives in:

`Docs/UI_Base_Widget_Modal_Input_Lifecycle_System.md`

- unbind stale delegates;
- deactivate/remove transient widgets;
- clear references;
- avoid duplicate listeners;
- no forced GC as routine cleanup.

Do not couple gameplay input dispatch to dead Quickslot Widget instances.

---

# 11. Python Editor Automation

Python editor tooling may assist with:

- animation naming/folder audits;
- marker/notifies consistency checks;
- skeleton compatibility reports;
- root motion metadata audits;
- batch asset metadata operations;
- export/bake workflow helpers where supported;
- identifying animations missing expected profile/tags.

Python remains editor/content tooling, not packaged runtime animation logic.

---

# 12. Performance

- baked reusable Animation Sequences preferred for ordinary repeated runtime content;
- do not run Sequencer unnecessarily for routine locomotion;
- animation layers activate by context;
- crowd/distant NPCs use lower-cost animation profiles;
- Control Rig at runtime is used only where the feature justifies its cost;
- IK/procedural solve complexity scales by significance;
- no per-frame Blueprint graph polling just to choose a simple known animation state.

---

# 13. Acceptance Tests

1. Existing animation can be edited without breaking canonical skeleton contract.
2. Corrected animation no longer clips unacceptably in target action/body profiles.
3. Root-motion action cannot bypass server/gameplay validation.
4. Sprint animation reads authoritative sprint state rather than deciding stamina eligibility.
5. Ladder/vehicle/context actions align correctly through authored targets/warping policy.
6. Foot markers synchronize compatible locomotion transitions.
7. Imported animation records license/provenance and retarget status.
8. Reusable production animation is not left as an unnecessary live Sequencer dependency.
9. Quickslot duplicate-trigger bug is fixed through UI lifecycle, not animation input hacks.
10. Animation authoring workflow remains compatible with KBM/controller gameplay because input intent is separate from animation assets.

## Core Rule

> Metaworld uses Unreal's in-engine animation tools aggressively for creation and repair, but every finished asset plugs back into one scalable character-animation architecture. Root motion, Control Rig and Sequencer serve the gameplay contract; they do not replace it.