# Metaworld — Combat Target Lock, Aim, Camera & Target Presentation System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / local-presentation responsive / authoritative target validity / movement-resolver integrated

## Canonical Principle

Target lock is a combat-assistance state that selects and tracks a valid combat target for camera, facing, locomotion and UI presentation. It does not grant visibility through walls, guarantee hits, or replace server hit validation.

> Lock-on helps the player orient toward a target. The combat system still decides whether attacks, projectiles and damage actually connect.

Related canon:

- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Combat_Locomotion_Facing_Root_Motion_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Character_Action_Movement_State_Resolver_System.md`
- `Docs/Player_HUD_Vitals_Resources_System.md`

---

# 1. Target Lock State

Suggested local/replicated context:

- LockedTargetCharacterID / TargetActor reference where loaded;
- acquisition timestamp;
- target lock profile;
- current validity reason/state;
- local UI indicator state.

Gameplay tags may describe `State.Combat.TargetLocked`, but the target identity is explicit data.

---

# 2. Target Acquisition

A candidate query can use bounded sphere/cone/trace checks based on:

- camera/view direction;
- distance;
- targetability;
- line of sight;
- hostility/combat context;
- screen-space proximity/priority;
- alive/incapacitated state;
- occlusion;
- target significance.

The tutorial's Sphere Trace by `Enemy` channel is an acceptable prototype broad-phase, not the only authorization rule.

---

# 3. Target Validity

Lock breaks or changes when appropriate, for example:

- target dies;
- target becomes non-targetable;
- distance exceeds profile limit;
- sustained occlusion exceeds grace period;
- target unloads/becomes irrelevant;
- combat/world state forbids lock;
- player manually unlocks/switches.

UI indicator must clear from the same state transition.

---

# 4. Lock Range

Tutorial distance such as 12 meters is prototype tuning only.

TargetLockProfile may define:

- acquire range;
- maintain range;
- field-of-view cone;
- occlusion grace time;
- target switching radius;
- weapon-specific range preferences.

Bow/rifle/magic/melee may use different targeting profiles.

---

# 5. Camera / Controller Rotation

While locked, local camera/character rotation assistance can be updated at bounded frame/presentation cadence because camera response is inherently continuous while the player is actively using target lock.

Rules:

- yaw/facing assistance can track target;
- vertical camera remains player-controlled or profile-driven;
- smoothing/rotation speed is configurable;
- player input can influence/break lock according to profile;
- camera cannot reveal hidden server information.

This is one of the few systems where per-frame local presentation work can be appropriate while active; it is disabled immediately when lock ends.

---

# 6. Character Facing / Movement

Target lock can request a semantic movement/facing profile such as:

`Movement.Profile.CombatLocked`

The Movement Resolver can derive:

- orient-to-target/strafe policy;
- speed/acceleration changes where designed;
- backward/side movement handling;
- dodge directions;
- combat locomotion animation profile.

Do not directly overwrite unrelated movement parameters without resolver ownership.

---

# 7. Aim Offset / Look Direction

Aim/look offsets are presentation driven by local relative yaw/pitch toward camera/target.

They can control:

- head/neck look;
- torso/upper-body aim where appropriate;
- weapon aiming profile later.

Rules:

- clamp to anatomical/animation limits;
- blend out cleanly;
- do not twist full body beyond movement/facing policy;
- body/weapon profile chooses which bones/layers participate.

A 1D yaw-only tutorial Aim Offset is a valid starting point, not a universal final aiming solution.

---

# 8. Target Indicator

Target UI can be:

- world-space widget;
- HUD marker;
- outline/reticle;
- accessibility profile.

It displays only while the target remains valid and visible according to UI policy.

The indicator does not make the target targetable.

---

# 9. Target Switching

Future target cycling can score nearby valid candidates by:

- direction from current target;
- screen position;
- distance;
- hostility/threat;
- visibility;
- player input direction.

Controller support must allow deterministic left/right target switching without mouse-only selection.

---

# 10. Camera Collision / Death

Target lock must release before/when target death/ragdoll invalidates the normal tracking profile.

Camera collision settings should prevent the camera from being trapped inside character/ragdoll/accessory meshes without globally disabling useful world collision.

---

# 11. Camera Shake

Block/parry/hit camera shakes are feedback events, not part of target lock authority.

Use modern project-compatible camera shake assets/profiles; tutorial Legacy Camera Shake is research/prototype material, not a requirement.

Shake intensity obeys accessibility settings and local significance.

---

# 12. Performance

- candidate acquisition uses bounded queries when requested;
- active lock can perform local camera/facing updates only while active;
- dead/invalid target clears immediately;
- distant/unloaded targets cannot retain expensive target UI;
- no world-wide scan of all enemies each frame;
- target switching queries a bounded candidate set.

---

# 13. Multiplayer / Authority

Client may select/request a target for responsive camera/UI, but server gameplay does not trust target lock as proof of a valid hit.

Attacks still validate:

- current weapon/action;
- range/contact/projectile;
- obstruction;
- target state;
- damage rules.

A modified client locking through a wall cannot cause damage through that wall.

---

# 14. Acceptance Tests

1. Lock acquisition chooses only valid bounded candidates.
2. Target death clears lock and indicator exactly once.
3. Leaving maintain range clears lock according to profile.
4. Occluded target follows configured grace/break behavior.
5. Target lock does not make attacks auto-hit.
6. Character strafing/facing is applied through Movement Resolver.
7. Aim offset clamps and blends without extreme twisting.
8. Controller can acquire/release/switch targets.
9. Active-lock camera work stops when unlocked.
10. Client cannot use lock-on to bypass server obstruction/hit validation.

## Core Rule

> Metaworld target lock assists orientation and combat readability. It selects a valid target for camera, facing, locomotion and UI, while the authoritative combat system still requires real range, contact, projectiles and damage validation.