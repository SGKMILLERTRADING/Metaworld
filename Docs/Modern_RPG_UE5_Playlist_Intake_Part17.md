# Metaworld — Modern RPG UE5 Playlist Intake — Part 17

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part16.md`

**Playlist Source:** Unreal Engine RPG tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

This Part contains **Episodes 152–164**.

---

# Episode 152 — Combat Sounds

**Classification:** UPGRADE — COMBAT FEEDBACK AUDIO.

Detailed companion:

`Docs/Combat_Feedback_Audio_Blood_VFX_System.md`

Approved intent:

- AnimNotify-triggered swing sounds;
- reusable player/NPC combat sound contract;
- weapon-specific audio;
- bounded pitch/volume variation;
- impact sounds on successful hits;
- reduce overlapping swoosh/impact clutter.

Metaworld upgrades:

- swing audio follows attack/weapon profile but never implies a hit;
- impact audio comes from validated combat result + surface/material response;
- Attack Speed to pitch mapping is clamped/presentation-only;
- one multi-channel hit does not spam duplicate identical sounds;
- stop/duck/fade swing sound on impact is audio-profile policy.

Principle:

> Combat sounds follow action and contact state; they never create combat state.

---

# Episode 153 — Blood Burst / Gash Decal

**Classification:** UPGRADE — COMBAT VFX PRESENTATION.

Detailed companion:

`Docs/Combat_Feedback_Audio_Blood_VFX_System.md`

Approved intent:

- Niagara blood burst at hit location;
- attached wound/gash decal using hit bone;
- fade/cleanup;
- prevent inappropriate decals on weapons.

Metaworld upgrades:

- anatomy/content profile determines whether blood is valid;
- temporary decal is not persistent injury truth;
- decal count/lifetime scales by significance;
- equipment/material surfaces can opt out;
- VFX is spawned only from validated hit/result events.

Principle:

> Blood makes a valid hit readable; hit validation and injury state remain gameplay authority.

---

# Episode 154 — Basic Enemy AI / Combat / Death

**Classification:** UPGRADE — NEW NPC COMBAT AI DOMAIN.

Detailed companion:

`Docs/NPC_Combat_AI_Engagement_Death_System.md`

Approved intent:

- bounded perception;
- navigation to hostile target;
- randomized attacks;
- enemy weapon/loadout;
- shared damage/blood;
- death handling;
- prevent death from triggering repeatedly.

Metaworld upgrades:

- StateTree/AI decision layer chooses actions while shared `BPC_MW_Combat` executes them;
- hostility is faction/world-state driven, not one Player tag;
- NPC equipment is legitimate ItemInstance/loadout state;
- death is authoritative/idempotent and transitions equipment/loot through persistent systems;
- corpse collision remains compatible with looting/drag/evidence gameplay;
- distant NPC perception/combat fidelity scales by significance.

Principle:

> NPC AI decides; shared combat systems execute.

---

# Episode 155 — Blocking Foundation

**Classification:** UPGRADE — DEFENSE SYSTEM FOUNDATION.

Detailed companion:

`Docs/Combat_Defense_Block_Dodge_Guard_Stamina_Input_Buffer_System.md`

Approved intent:

- block animation/stance;
- Enhanced Input block action;
- strafing while blocking;
- incoming-hit block check;
- block reaction.

Metaworld upgrades:

- directional block arc/coverage;
- equipment/handling-specific BlockProfile;
- movement changes go through Movement Resolver;
- block does not universally zero every damage source;
- block resolution can affect Health, Guard, Stamina and equipment durability separately.

Principle:

> Blocking is a defensive action with direction, equipment, resources and timing—not a global damage-off Boolean.

---

# Episode 156 — Blocking Strafing / Sound / Sparks

**Classification:** UPGRADE — DEFENSE PRESENTATION + MOVEMENT.

Detailed companions:

- `Docs/Combat_Defense_Block_Dodge_Guard_Stamina_Input_Buffer_System.md`
- `Docs/Combat_Feedback_Audio_Blood_VFX_System.md`

Approved intent:

- combat-strafe locomotion while guarding;
- metal/wood-specific block audio;
- impact sparks;
- combat feedback tied to block result.

Metaworld upgrades:

- guard locomotion is a semantic movement profile;
- impact surface/equipment profile chooses sound/VFX;
- sparks/audio are presentation of a validated block;
- color/sound alone does not determine combat result.

Principle:

> Guard movement and feedback derive from the same committed defense state.

---

# Episode 157 — Blocking Clipping Fix / Combat Input Buffer

**Classification:** PARTIAL REJECT + UPGRADE — INPUT RESPONSIVENESS.

Detailed companion:

`Docs/Combat_Defense_Block_Dodge_Guard_Stamina_Input_Buffer_System.md`

Approved intent:

- prevent combat action overlap/clipping;
- remember player action intent during recovery;
- execute buffered action when legal;
- held Block must still be held when executed.

Rejected/Corrected:

- universal capsule radius 35 -> 80 while blocking is not canonical;
- buffer identity is logical InputAction/ActionDefinition, not a closed `LMB/RMB/Dodge/Toggle` enum forever;
- AnimNotify opens candidate windows but does not pre-authorize buffered action.

Principle:

> Buffer intent, then revalidate it; do not fix spacing by globally mutating the character capsule.

---

# Episode 158 — Dodge / Iframes

**Classification:** UPGRADE — DODGE DEFENSE ACTION.

Detailed companion:

`Docs/Combat_Defense_Block_Dodge_Guard_Stamina_Input_Buffer_System.md`

Approved intent:

- directional dodge;
- buffered dodge;
- animation-defined invulnerability window;
- damage system respects valid dodge window.

Metaworld upgrades:

- dodge does not permanently replace Jump as a world rule;
- iframe is tied to exact Dodge CombatActionInstance and server timing;
- invulnerability applies only to configured damage families;
- environmental hazards can remain valid damage sources;
- client-added tags cannot create immunity.

Principle:

> Dodge immunity, if used, exists only inside one authored and authoritative defense window.

---

# Episode 159 — Guard / Blocking Power / Stagger + Combat Stamina

**Classification:** UPGRADE — RESOURCE-AWARE DEFENSE/COMBAT.

Detailed companion:

`Docs/Combat_Defense_Block_Dodge_Guard_Stamina_Input_Buffer_System.md`

Approved intent:

- blocking stability resource;
- block-break/stagger when depleted;
- guard UI;
- attacks/dodges cost Stamina;
- equipment affects action cost.

Metaworld upgrades:

- Guard and Stamina remain distinct resources;
- guard damage, Health mitigation and Stamina cost can all occur on one block;
- guard recovery is event/timer driven;
- attack/dodge cost derives from profile + weapon mass/handling + character state, not simply `weight = cost`;
- Guard break is authoritative state/action, not only a montage.

Principle:

> Stamina limits exertion; Guard limits defensive stability.

---

# Episode 160 — Target Lock

**Classification:** UPGRADE — NEW TARGET-LOCK DOMAIN.

Detailed companion:

`Docs/Combat_Target_Lock_Aim_Camera_System.md`

Approved intent:

- bounded target query from camera direction;
- target indicator;
- character/camera facing assistance;
- drop lock on death/out-of-range.

Metaworld upgrades:

- target candidates validate hostility/targetability/LOS/state;
- acquisition/maintain ranges are profile data, not universal 12m;
- active lock may use bounded local per-frame camera work while active;
- movement/facing integrates with resolver;
- target lock never guarantees a hit or bypasses obstruction.

Principle:

> Lock-on helps orientation; it is not hit authority.

---

# Episode 161 — Aim Offset / Target Indicator Fix / Camera Shake / Hit Sound Fix

**Classification:** LOCKED + UPGRADE — COMBAT PRESENTATION MAINTENANCE.

Detailed companions:

- `Docs/Combat_Target_Lock_Aim_Camera_System.md`
- `Docs/Combat_Feedback_Audio_Blood_VFX_System.md`

Approved intent:

- aim/look offset;
- correctly clear dead/out-of-range target marker;
- camera shake on heavy combat feedback;
- prevent duplicate hit sounds.

Metaworld upgrades:

- aim/look offsets clamp anatomically and blend by handling profile;
- Legacy Camera Shake is tutorial implementation detail, not project requirement;
- shake/haptics respect accessibility;
- one physical contact with multiple damage channels does not repeat identical audio.

Principle:

> Combat camera/aim/audio feedback follows target and damage state without duplicating gameplay truth.

---

# Episode 162 — Perfect Block / Parry Foundation

**Classification:** UPGRADE — NEW PARRY / COUNTER DOMAIN.

Detailed companion:

`Docs/Combat_Parry_Perfect_Block_Stagger_System.md`

Approved intent:

- short perfect-block timing window;
- successful parry staggers attacker;
- parry-specific sound/VFX;
- defender gains tactical opening.

Metaworld upgrades:

- tutorial `0.1s` is prototype tuning;
- parry window belongs to exact defensive CombatActionInstance;
- incoming attack must be eligible by attack/equipment/direction profile;
- server commits ParryResult;
- attacker stagger is authoritative combat state.

Principle:

> Parry is a validated timing result between one defense action and one incoming attack.

---

# Episode 163 — Parry VFX / Stagger Polish

**Classification:** UPGRADE — PARRY FEEDBACK + STAGGER.

Detailed companions:

- `Docs/Combat_Parry_Perfect_Block_Stagger_System.md`
- `Docs/Combat_Feedback_Audio_Blood_VFX_System.md`

Approved intent:

- Niagara flash/parry effect;
- parry impact sound;
- extended stagger/stun presentation.

Metaworld upgrades:

- VFX/audio triggers from committed parry result;
- stagger duration/action restrictions are gameplay data;
- animation length does not independently define authoritative stun duration;
- NPC/player use same stagger contracts where applicable.

Principle:

> Parry feedback celebrates the result; stagger state defines the tactical consequence.

---

# Episode 164 — Parry Animation Profiles / Slow-Motion Correction

**Classification:** UPGRADE + PARTIAL REJECT — PARRY PRESENTATION FINALIZATION.

Detailed companion:

`Docs/Combat_Parry_Perfect_Block_Stagger_System.md`

Approved intent:

- handling-specific parry montages;
- root motion where appropriate;
- camera shake/impact emphasis;
- trim animation startup for responsiveness;
- upper-body layering where compatible.

Rejected/Corrected:

- global `0.1x for 2 seconds` time dilation is not canonical persistent-multiplayer behavior;
- dramatic impact uses local camera/animation/audio/haptic emphasis or specifically-authorized instance mechanics;
- montage selection comes from equipment/handling profile, not closed tutorial CombatType enum.

Principle:

> Parry can feel dramatic without slowing the entire persistent world.

---

# Part 17 Cross-System Locks

1. Combat feedback never owns hit/damage truth.
2. NPC combat uses the same Combat/Damage/Equipment systems as players.
3. Guard and Stamina are distinct.
4. Blocking is directional/profile-dependent, not universal immunity.
5. Dodge iframes are bounded server-authoritative action windows.
6. Input buffer stores intent, not permission.
7. Target lock assists facing/camera but cannot auto-hit.
8. Parry is an authoritative window/result, not a permanent tag.
9. Global time dilation is rejected as routine multiplayer parry feedback.
10. Combat presentation scales for large fights/NPC populations.

## Part 17 Principle

> Metaworld defense and combat feedback stay responsive because actions have authored windows, buffering and rich presentation—but every block, dodge, hit, parry, stagger and AI decision remains grounded in the same authoritative combat state and persistent world rules.