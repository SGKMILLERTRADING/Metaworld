# Metaworld — Rest, Sitting, Sleeping, Furniture & Recovery System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / persistent world objects / interaction-integrated / animation-driven / server-authoritative state

## Canonical Principle

Sitting and sleeping are contextual character states attached to real world furniture and rest opportunities. Furniture provides authored interaction targets; gameplay owns the seated/sleeping state, recovery rules, occupancy and interruption.

> A chair or bed is not just an animation trigger. It is a world object with occupancy, access, positioning and recovery rules that integrate with the character's Needs, Vitals, property and traversal systems.

---

# 1. Furniture Interaction Contract

Suggested world capability/profile:

- `Furniture.Action.Sit`
- `Furniture.Action.Sleep`
- `Furniture.Action.Rest`

A furniture object may expose:

- WorldObjectID;
- seat/sleep slot IDs;
- authored entry/exit transforms;
- occupant limits;
- animation profile;
- access/property rules;
- comfort/recovery profile;
- condition/broken state;
- reservation/occupancy state.

---

# 2. Sitting State

Suggested semantic state:

`Rest.Sitting`

Flow:

`Request Sit`
-> validate seat exists/is free/access allowed
-> reserve seat slot
-> align/warp to entry target
-> play Sit montage
-> enter Seated idle state
-> apply movement/action restrictions
-> optional recovery modifiers
-> `Request Stand`
-> validate exit
-> play Stand montage
-> restore movement/collision
-> release seat reservation.

---

# 3. Sleeping State

Suggested semantic state:

`Rest.Sleeping`

Flow:

`Request Sleep`
-> validate bed/sleep slot/access
-> reserve slot
-> align to bed-side/entry transform
-> play lie-down transition
-> enter Sleep idle/state
-> Needs/Vitals/rest systems process recovery/time consequences
-> wake reason occurs
-> validate exit
-> play wake/stand transition
-> restore movement/action state
-> release reservation.

Sleeping is not a global world pause.

---

# 4. Animation / Alignment

Approved:

- retargeted sit/stand/lie-down/wake animations;
- Control Rig/Sequencer cleanup;
- root motion where appropriate;
- Motion Warping to authored seat/bed transforms;
- Inertialization/blending for smoother transitions;
- linked rest animation layer/profile.

Avoid long manual Player timelines that drag the character to arbitrary offsets if authored contextual targets + warping can solve the alignment more robustly.

---

# 5. Collision Policy

Do not globally disable character collision for the entire seated/sleeping state unless the specific furniture profile requires a controlled alternative.

Preferred:

- reserve seat/sleep slot;
- use authored capsule/mesh alignment;
- adjust collision only where needed and restore it explicitly;
- prevent other characters from occupying the same slot;
- validate exit space before standing.

Interruption/death must never leave the character permanently no-collision.

---

# 6. Recovery / Needs Integration

Sitting/sleeping may influence:

- Fatigue;
- Stamina recovery;
- Health recovery only under approved medical/natural rules;
- Mana/resource recovery where appropriate;
- Comfort/wellbeing;
- temperature/weather protection;
- injury recovery modifiers.

Do not universally grant Health regeneration simply because the character sits down.

A chair can provide mild rest; a bed can provide stronger Fatigue recovery; a hospital bed can have separate medical rules.

---

# 7. Sleep & World Time

In persistent multiplayer Metaworld, sleep does not automatically fast-forward the global world for everyone.

Possible behavior:

- character remains sleeping while world time continues;
- offline/abstract sleep recovery may be resolved through timestamps according to server rules;
- private/single-instance scenarios may later support controlled time-skipping only if compatible with world architecture.

---

# 8. Property / Access

Furniture may belong to:

- player home;
- rented room;
- hotel;
- prison/jail;
- hospital;
- public space;
- workplace;
- another person's property.

Access and legal consequences follow property/custody/world rules.

Being able to physically sit on a chair does not automatically grant ownership or permission to sleep in a private bed.

---

# 9. Interruption

Possible interruption reasons:

- player chooses stand/wake;
- combat/damage;
- furniture destroyed/moved;
- fire/emergency;
- arrest/custody action;
- status effect;
- server/admin/world transition;
- occupancy invalidation.

The rest state has explicit cancellation/exit cleanup.

---

# 10. NPC Compatibility

NPCs can use the same seat/bed slots for:

- schedules;
- eating/resting;
- sleep cycles;
- workplaces;
- hospitals;
- prisons;
- homes/hotels.

Smart Object/reservation-style integration may coordinate AI use without creating a unique chair Blueprint per NPC.

---

# 11. Multiplayer / Occupancy

Server owns seat/bed occupancy.

Two characters cannot reserve the same one-person seat simultaneously.

Multi-seat furniture exposes separate slot IDs.

Clients animate the committed reservation/state.

---

# 12. Controller / Accessibility

Required:

- Sit/Sleep via logical Interact action;
- Stand/Wake via mapped action;
- KBM/Xbox-style/PlayStation-style support;
- current-device prompt;
- optional reduced forced-camera movement.

---

# Acceptance Tests

1. Two players cannot occupy the same one-seat chair.
2. Character aligns correctly to chairs/beds at different rotations.
3. Sit/stand restores movement/collision safely.
4. Sleeping does not pause the persistent world globally.
5. Recovery follows Needs/Vitals policy rather than automatic free healing.
6. Access/property restrictions can block or penalize unauthorized use.
7. Furniture destruction/interruption exits state safely.
8. NPCs can use compatible furniture slots.
9. Encumbrance/action restrictions remain coherent while entering/exiting rest state.
10. KBM/controllers can enter and leave rest states.

## Core Rule

> Metaworld rest is a world interaction state. Chairs and beds provide persistent usable slots and authored transforms; animation presents the transition, while occupancy, access, Needs/Vitals recovery, interruption and multiplayer authority remain owned by gameplay systems.