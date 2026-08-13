# Metaworld — Combat Hit Reaction, Directional Impact & Animation System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / result-driven / anatomy-aware / action-state integrated / server-authoritative combat

## Canonical Principle

Hit reactions are presentation/action consequences of an already validated combat result. Direction, body zone, impact strength, current action, stance and damage profile select an appropriate reaction; the montage never decides whether damage occurred.

> The server commits the hit. Metaworld derives an impact reaction from that result. Animation communicates the consequence without becoming damage authority.

Related canon:

- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Combat_Feedback_Audio_Blood_VFX_System.md`
- `Docs/Combat_Parry_Perfect_Block_Stagger_System.md`
- `Docs/Avatar_Communication_Character_Animation_Architecture.md`

---

# 1. Reaction Event

Recommended conceptual event/snapshot:

`S_MW_HitReactionRequest`

Possible fields:

- DamageEventID;
- TargetCharacterID;
- AttackerCharacterID / source identity;
- hit location/normal;
- semantic body zone;
- relative impact direction;
- impact strength/severity;
- DamageProfileID / damage channel tags;
- blocked/parried/absorbed/health-damaged result;
- target action/stance/traversal state;
- suggested reaction profile;
- interruption/stagger/knockdown result where authoritative.

The reaction request is created from the committed combat result.

---

# 2. Direction Calculation

Tutorial Front/Back/Left/Right direction is approved, but derive it from target-local impact geometry rather than a fragile branch tree based only on attacker rotation.

Preferred inputs can include:

- target transform;
- hit/impact location;
- attacker/source location;
- impact normal/velocity where meaningful.

Conceptually:

`DirectionToSource in target local space`
-> compare Forward/Right dot products or signed relative yaw
-> map to semantic sector.

Initial sectors may be:

- `Impact.Front`
- `Impact.Back`
- `Impact.Left`
- `Impact.Right`

Future profiles can support diagonals/high/low without redesign.

Do not assume the attacker is facing the target; projectile/explosion impacts may come from a different physical direction.

---

# 3. Body Zone Integration

Reaction selection may also use semantic body zones:

- Head;
- Torso;
- Arm.Left/Right;
- Leg.Left/Right;
- other anatomy profiles.

Raw skeleton bone names map through the canonical anatomy profile so MetaHumans and other supported characters do not need identical bone naming.

Example:

`Impact.Left + BodyZone.Torso + LightSlash`
-> left torso flinch profile.

---

# 4. Reaction Severity

Not every hit should play the same full-body interruption.

Possible reaction classes:

- cosmetic/light flinch;
- upper-body reaction;
- heavy reaction;
- stagger;
- guard break;
- knockback;
- knockdown;
- incapacitation/death.

Severity can derive from authoritative combat result, poise/Guard/stability, target state and AttackDefinition.

A light hit reaction may coexist with locomotion. A committed Stagger/Knockdown is a gameplay action/state and can interrupt incompatible actions.

---

# 5. Upper-Body Reactions

Upper-body montage slots are approved for light reactions that should not stop locomotion.

Rules:

- use the shared animation-layer/slot architecture;
- do not allow a cosmetic reaction montage to clear authoritative combat actions;
- suppress/modify reactions when the current animation/action cannot accept them;
- use handling/stance-specific variants when weapon pose would otherwise clip badly.

---

# 6. Reaction Priority / Interruption

Reaction selection checks current state.

Examples:

- dead character does not play ordinary flinch;
- active knockdown overrides light hit react;
- parried attacker may enter Stagger instead of generic hit react;
- successful ordinary Block may play block reaction rather than flesh-hit reaction;
- dodge iframe result produces no damage reaction if the hit was avoided;
- ladder/ledge/swim contexts can use compatible reactions or transition to a fall/interrupt state where designed.

Gameplay interruption is committed by the action/state systems, not by whatever montage happens to play.

---

# 7. Reaction Profile Data

Suggested `HitReactionProfileID` can define:

- directional montage/animation map;
- body-zone variants;
- severity variants;
- handling/stance variants;
- playback-rate limits;
- movement/rotation restrictions;
- root-motion policy;
- camera/haptic feedback hooks;
- minimum significance tier.

Avoid one closed forever Direction enum as the entire reaction architecture.

---

# 8. Root Motion / Displacement

Light reactions normally should not create large authoritative displacement.

Heavy stagger/knockback/knockdown may have gameplay movement policies and root-motion presentation where validated.

Do not let a client reaction montage teleport a target or move them through world collision.

---

# 9. Multiplayer

Server owns the underlying combat result and gameplay interruption state.

Clients can select/reconstruct the correct local animation from compact result/reaction data.

A client cannot avoid damage by refusing to play the reaction, nor create damage by playing one.

---

# 10. Performance

- reaction evaluation occurs only on committed combat results;
- no Tick required;
- distant NPCs can use reduced/suppressed reaction detail while gameplay consequence remains;
- reuse animation profiles and Linked Animation Layers;
- avoid spawning separate helper Actors for every reaction.

---

# Acceptance Tests

1. Front/Back/Left/Right reaction follows physical impact direction in target-local space.
2. Attacker facing away does not invert projectile impact direction incorrectly.
3. Light upper-body reaction can coexist with allowed locomotion.
4. Successful Block uses block reaction instead of ordinary flesh flinch where configured.
5. Parry Stagger overrides generic reaction.
6. Dead/incapacitated target does not restart ordinary hit reactions.
7. Reaction montage cannot create or cancel damage authority.
8. Body-zone mapping works across supported character skeleton profiles.
9. Multiplayer observers reconstruct the same reaction class.
10. Distant NPC reaction presentation can scale down without changing Health/state.

## Core Rule

> Metaworld hit reactions are contextual presentation and action consequences derived from committed combat results. Direction, anatomy, severity and current state select the reaction; damage, stagger and interruption remain authoritative gameplay state.