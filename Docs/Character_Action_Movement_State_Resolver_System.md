# Metaworld — Character Action & Movement State Resolver System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / data-driven / server-authoritative movement state / event-driven

## Canonical Principle

Character speed and locomotion parameters are derived from current movement, traversal, action, encumbrance, environment and status state. No feature owns a permanent hardcoded `Set Max Walk Speed` branch that can overwrite every other system.

> Sprinting, drinking, swimming, pushing, climbing, injuries and encumbrance all contribute to one effective movement result instead of fighting over the Character Movement component.

---

# 1. Inputs

The resolver may consume:

- Base Movement Profile;
- semantic locomotion state;
- Sprint/FastSwim exertion;
- active CharacterActionID;
- traversal state;
- water/environment state;
- Encumbrance tier;
- injuries/status effects;
- equipment/loadout;
- carrying/pushing state;
- stance;
- temporary buffs/debuffs;
- supernatural modifiers where valid.

---

# 2. Outputs

Possible derived outputs:

- Max Walk Speed;
- Max Swim Speed;
- acceleration;
- braking/deceleration;
- rotation response;
- jump permission/strength;
- Sprint eligibility;
- climb/mantle permission;
- stamina-cost multiplier;
- movement-input scaling;
- animation movement profile/tag.

The resolver writes the current effective parameters when relevant state changes.

---

# 3. Do Not Use One Closed Movement Enum As World Truth

The tutorial's `Normal / Sprint / Potion / Keep Current` enum is a useful refactor from scattered speed assignments, but it cannot scale to Metaworld.

It would quickly become:

- Normal;
- Sprint;
- Potion;
- Encumbered;
- Swimming;
- FastSwimming;
- Ladder;
- Ledge;
- Pushing;
- Carrying;
- Injured;
- Crouching;
- PrisonRestraint;
- etc.

Instead separate orthogonal state dimensions and derive the result.

---

# 4. Priority / Restriction Rules

Some states constrain others.

Examples:

- Ladder traversal overrides ground locomotion;
- Sleeping blocks normal movement;
- Sitting blocks ground translation until standing;
- Heavy Encumbrance can prohibit Sprint;
- Drinking may allow Walk but prohibit Sprint;
- Ledge Hanging prohibits normal movement;
- Swimming uses water movement outputs rather than ground Max Walk Speed;
- Stun/incapacitation can override most actions.

Rules are data/contract-driven rather than execution-order accidents.

---

# 5. State Change Evaluation

Recompute when relevant state changes, for example:

- Sprint starts/stops;
- Encumbrance tier changes;
- equipment changes;
- condition applied/removed;
- action begins/ends;
- water state changes;
- ladder/ledge traversal begins/ends;
- injury changes;
- push/carry state changes.

Do not recalculate every frame without a reason.

---

# 6. 'Keep Current' Is Not Persistent State

A tutorial `Keep Current` branch can avoid overwriting speed temporarily, but canonical state should always be derivable from current facts.

If a system needs to preserve an existing movement modifier, it remains one of the resolver's active inputs rather than relying on whatever numeric value happened to be set previously.

---

# 7. Encumbrance

The resolver consumes the canonical Encumbrance tier.

It does not directly recompute inventory weight.

Example:

- Comfortable: normal movement;
- Loaded: reduced acceleration/stamina efficiency;
- Encumbered: lower speed, reduced Sprint;
- Heavy: Sprint blocked;
- Unsafe/Immobile: severe restriction.

Final values are data-driven.

---

# 8. Swimming

Ground and water speed are resolved under the same character-state architecture, but different movement profiles can supply different outputs.

Fast Swim is an exertion modifier, not simply `MaxSwimSpeed = X` permanently.

Leaving water causes a recompute from current land/traversal state.

---

# 9. Action Integration

A consumable action may add:

`Action.Restriction.NoSprint`

A heavy push may add:

`Movement.Profile.PushingHeavy`

A chair may add:

`Traversal.Seated`

The resolver translates active semantic state into movement parameters. Gameplay systems should not reach across ownership boundaries and set unrelated movement values directly.

---

# 10. Multiplayer / Prediction

Server owns gameplay-relevant restrictions and canonical movement state.

Client prediction/presentation can respond promptly using replicated/predicted state, but modified clients cannot discard Encumbrance/Stun/Traversal restrictions by setting local speed values.

---

# 11. Acceptance Tests

1. Ending Sprint while Encumbered returns to the correct Encumbered profile.
2. Drinking while walking reduces/limits movement only according to action policy.
3. Ending drinking recomputes current movement instead of restoring a stale default.
4. Entering water switches to correct Swim outputs.
5. Leaving water restores the correct land/encumbrance/action state.
6. Ladder/ledge traversal cannot be overridden by Sprint speed changes.
7. Sitting/sleeping block normal movement until their exit action completes.
8. Status effects modify movement without permanently mutating Base speed.
9. Resolver runs on state changes rather than permanent Tick.
10. Server authority prevents local speed-cheat overrides.

## Core Rule

> Metaworld has one derived character movement result built from many independent gameplay states. Systems declare what state/restriction they own; the resolver computes the movement parameters, preventing Sprint, potions, swimming, encumbrance, traversal and future systems from overwriting each other.