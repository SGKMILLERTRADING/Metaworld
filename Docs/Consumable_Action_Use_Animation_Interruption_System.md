# Metaworld — Consumable Action, Use Animation & Interruption System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative item use / animation-integrated / event-driven

## Canonical Principle

Using a consumable is an authoritative item action with a defined start, commitment point, completion/interruption policy and presentation. The montage may determine when the use commits visually, but it cannot create effects or remove items without gameplay validation.

> The player does not receive a potion effect because an animation played. The validated ItemInstance is consumed at the action's committed use phase, then its effects are applied through the owning gameplay systems.

---

# 1. Consumable Action Definition

A consumable/use profile may define:

- UseActionID;
- target rules;
- montage/animation profile;
- expected duration;
- commitment point / animation notify tag;
- movement restrictions;
- allowed traversal/environment states;
- interruption policy;
- consume-on-start / consume-on-commit / consume-on-complete policy;
- spawned hand-held presentation;
- sound/VFX profile;
- applied ConditionDefinitionIDs / resource changes;
- cooldown/reuse restrictions.

Different consumables can use different action profiles.

---

# 2. Request Flow

`RequestUseItem(ItemInstanceID)`
-> server validates possession/access/use capability
-> validate character action state
-> reserve ItemInstance/quantity for the use action
-> enter `Action.Consumable.*`
-> play presentation/montage
-> at approved commitment phase, server revalidates and commits consumption/effect
-> finish/cancel action
-> release reservation.

The client cannot consume a non-existent potion by forcing a Montage Notify.

---

# 3. Montage Notify / Commitment Point

The tutorial's notify-timed consumption is approved as a presentation/action synchronization pattern.

Rules:

- notify identifies an expected phase, not sole authority;
- server action instance must still be active and valid;
- commit happens at most once;
- duplicate/missed notify cannot duplicate or permanently lose the item;
- network correction can reconcile presentation if the authoritative commit fails.

---

# 4. Spam / Concurrency Prevention

Do not rely only on a loose `IsDrinkingPotion` Boolean.

The shared character action state tracks an active use/action instance.

Policies can define:

- only one consumable use at a time;
- whether weapon attacks interrupt drinking;
- whether drinking interrupts Sprint;
- whether damage/stun cancels use;
- whether movement is allowed;
- whether a second quickslot use queues, rejects or replaces the first action.

---

# 5. Movement While Using

Layered Blend Per Bone or linked animation layers are approved so lower-body locomotion can continue while upper-body drinking plays where the action profile permits it.

Gameplay movement policy can be:

- full movement;
- reduced movement;
- walking only;
- stationary;
- contextual.

Animation blending presents the decision; it does not decide movement authority.

---

# 6. Traversal / Water Restrictions

UseAction profiles can explicitly allow/deny:

- Walking;
- Sprinting;
- Swimming.Surface;
- Swimming.Underwater;
- Ladder;
- Ledge.Hanging;
- Sitting;
- Sleeping;
- Driving;
- combat states.

Example: ordinary drinkable potion may be disallowed underwater or while hanging from a ledge, but specialized consumables may have different policies later.

Do not scatter `if climbing? if swimming? if ladder?` branches through every potion Blueprint.

---

# 7. Hand-Held Presentation

A temporary potion/bottle actor may be spawned/attached to a hand socket as local/replicated presentation.

It represents the exact authorized ItemInstance/use profile.

Destroying the presentation actor does not itself consume the inventory item; item consumption is the authoritative transaction.

---

# 8. Effects

On successful commitment:

- decrement/remove ItemInstance quantity;
- apply resource change and/or ConditionDefinitionIDs through Stats/StatusEffects;
- emit sound/VFX/presentation;
- update inventory/quickslots/HUD through deltas/events.

A healing potion can therefore apply a Health-regeneration condition rather than directly editing widget bars.

---

# 9. Quickslot Integration

Quickslot activation resolves the current compatible item/stack, then submits the same `RequestUseItem` action.

Quickslot does not bypass:

- possession/access;
- current action restrictions;
- cooldowns;
- environmental restrictions;
- authoritative consumption.

---

# 10. Persistence / Disconnect

Short consumable-use actions normally do not need long-term persistence, but disconnect/cancel policy must not duplicate the item/effect.

If the authoritative commit already occurred, reconnect reflects the consumed item/effect.

If it did not, the reservation/action is safely canceled/recovered according to transaction state.

---

# 11. Acceptance Tests

1. Potion cannot be consumed twice from one montage/notify.
2. Missing client animation does not block authoritative inventory truth forever.
3. Quickslot spam cannot start overlapping illegal drink actions.
4. Movement policy matches the active use profile.
5. Underwater/ladder/ledge restrictions are enforced by shared action state.
6. Item is removed/decremented exactly once at configured commit phase.
7. Effect applies through Stats/StatusEffects exactly once.
8. Hand prop disappears cleanly after completion/cancel.
9. Interruption returns character to valid movement/action state.
10. KBM/controller quick-use actions use the same gameplay request.

## Core Rule

> Consumables are timed gameplay actions, not instant UI calls. Metaworld reserves the real ItemInstance, validates character/environment state, synchronizes animation to one authoritative commitment point, applies the effect once, and cleans up correctly if the action is interrupted.