# Metaworld — MetaHuman Facial Expression, Lip-Sync & Runtime Animation System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / MetaHuman-aware / layered animation / significance-scaled

## Canonical Principle

Facial animation is a modular presentation layer over the canonical character state. Expressions, blinks, speech visemes, emotion, sleep state and look-at behavior must coexist with body animation without breaking the MetaHuman face rig or forcing one fragile Construction Script configuration.

> Metaworld animates the face because gameplay/social state calls for an expression. The facial montage, Control Rig or Live Link data presents that state; it does not become character gameplay authority.

Related canon:

- `Docs/Avatar_Communication_Character_Animation_Architecture.md`
- `Docs/Animation_Authoring_Control_Rig_Root_Motion_Workflow.md`
- `Docs/NPC_MetaHuman_Fidelity_Customization_Hair_Performance_System.md`
- `Docs/Rest_Sit_Sleep_Furniture_Recovery_System.md`

---

# 1. Facial Animation Sources

Approved sources include:

- MetaHuman Facial Control Rig / Sequencer-authored clips;
- MetaHuman expression/pose library where available;
- authored Animation Sequences/Montages for reusable expressions;
- MetaHuman Animator / captured performances for important content;
- Live Link facial animation where realtime capture is intentionally used;
- procedural blink/look-at/micro-expression layers where appropriate;
- dialogue/lip-sync data from an approved dialogue/voice pipeline later.

A single project may use several sources according to context and fidelity tier.

---

# 2. Stable Facial Intent

Gameplay/social systems should request semantic facial intent rather than directly keying face controls.

Examples:

- `Face.Expression.Neutral`
- `Face.Expression.Angry`
- `Face.Expression.Fear`
- `Face.Expression.Happy`
- `Face.State.SleepingEyesClosed`
- `Face.State.Pain`
- `Face.Action.Blink`
- `Face.Speech.Active`

The facial presentation layer resolves the actual asset/control data.

---

# 3. Sleep / Blink Integration

The tutorial's closed-eye sleep animation is approved.

Canonical flow:

`Rest.Sleeping begins`
-> facial layer requests sleeping face/closed-eye profile
-> body rest layer plays sleep pose
-> on wake/interrupt, facial request clears/transitions
-> blink/normal expression logic resumes.

Do not permanently disable normal facial animation just because a sleep montage played.

---

# 4. Do Not Universally Disable MetaHuman Face Processing

The tutorial disconnects the face from Leader Pose and disables a post-process path to make its prototype facial montage work.

Metaworld treats that as a project-specific troubleshooting technique, **not** a universal UE5.8 rule.

The production setup must verify the current assembled MetaHuman's:

- facial Animation Blueprint / post-process requirements;
- MetaHuman Component facial settings;
- body/face synchronization;
- runtime Control Rig/corrective requirements;
- LOD/fidelity profile;
- custom facial animation source.

Only disable/replace a face-processing stage when the chosen runtime profile explicitly requires it and visual QA confirms correct deformation.

---

# 5. Body and Face Stay Layered

Body locomotion/combat/rest and facial expression are separate concerns.

Example:

`Walking + Holding Rifle + Talking + Angry`

can resolve as:

- locomotion/combat body layer;
- upper-body weapon layer;
- facial speech/viseme layer;
- angry expression bias;
- eye/look-at layer.

Do not require one monolithic animation asset containing the entire body and face for ordinary gameplay.

---

# 6. Speech / Visemes

MetaHuman viseme poses are approved for authored/testing workflows.

Long-form speech should eventually support a scalable lip-sync source such as:

- captured MetaHuman facial performance;
- generated/processed dialogue facial animation;
- realtime Live Link for creator/live-performance contexts;
- lower-fidelity procedural mouth/viseme approximation for distant NPCs.

Speech identity/text/voice remains owned by communication/dialogue systems.

---

# 7. Expression Blending / Priority

Facial requests can overlap, so a resolver should define priority/layering.

Possible inputs:

- baseline personality/idle;
- current emotional state;
- speech visemes;
- blink/eye motion;
- injury/pain;
- sleep/unconscious state;
- cinematic override;
- supernatural state.

Examples:

- Sleeping suppresses normal blink loops because eyes are already closed;
- speech visemes modify mouth while an anger expression remains active;
- severe pain may temporarily override a neutral social expression.

---

# 8. Multiplayer / Replication

Do not replicate every facial control value for ordinary gameplay.

Replicate compact semantic state where needed, for example:

- expression/emotion profile ID;
- speech-active state/dialogue event;
- important facial action/event;
- cinematic/performance reference.

Local clients resolve appropriate facial animation according to fidelity tier.

Realtime voice lip-sync, if implemented, gets its own bandwidth/performance policy.

---

# 9. Fidelity Scaling

Hero/player/important nearby NPC:

- full facial rig where budget allows;
- detailed expressions/lip-sync;
- look-at/blink;
- high-quality corrective behavior.

Normal nearby NPC:

- reduced facial update cost;
- simplified expressions/lip-sync.

Crowd/distant NPC:

- low-frequency or simplified face animation;
- no expensive facial solve where it is not visible.

Facial fidelity should follow the broader NPC/MetaHuman significance profile.

---

# 10. Editor Authoring / Control Rig

Control Rig + Sequencer are approved for:

- blink clips;
- sleep face;
- pain/reaction poses;
- custom emotes;
- dialogue/cinematic expressions;
- correcting captured performance;
- creating reusable expression assets.

Keep source/edit assets organized so production clips can be regenerated or adjusted later.

---

# 11. Acceptance Tests

1. Sleep closes the eyes and wake restores normal facial state.
2. Facial montage does not break body locomotion/rest animation.
3. Speech visemes can coexist with broader expression state.
4. Player/NPC face remains visually correct across supported MetaHuman LOD/fidelity profiles.
5. Project does not depend on universally disabling MetaHuman post-process/face processing without profile justification.
6. Facial presentation can be disabled/reduced on distant NPCs without changing gameplay state.
7. Replication uses compact semantic facial state rather than continuous full control spam for ordinary gameplay.
8. Captured/Live Link facial workflows can plug in later without replacing the character gameplay architecture.

## Core Rule

> Metaworld treats the MetaHuman face as a layered, scalable presentation system. Gameplay requests semantic expression/speech/rest state; UE5.8 facial rigs, Control Rig, captured performance and runtime animation resolve the visible result without becoming another source of character truth.