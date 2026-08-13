# Metaworld — Batch Crafting, Stack Output & Quantity Transaction System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / batch-safe

## Canonical Principle

Recipes may create multiple units in one legitimate production action, but batch quantity, material use, output placement and resulting stack/ItemInstance state are owned by the authoritative crafting transaction.

> `Craft 10 Arrows` means one validated batch transformation that creates ten legitimate arrow units—not ten client-side pickup calls in a loop.

Related canon:

- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Ranged_Weapons_Bow_Ammo_Quiver_Container_System.md`
- `Docs/HUD_Notification_Feedback_System.md`

---

# 1. Recipe Output Quantity

Recipe definitions may specify output behavior such as:

- `OutputQuantityPerBatch`
- minimum/maximum BatchQuantity
- batch-size increments
- packaging/lot policy
- output stack policy
- byproducts/waste per batch
- time/work scaling
- profession progression scaling

Example:

`Recipe.Ammo.Arrow.Iron.Basic`

Input per batch:
- Wood x2
- Iron material x1

Output per batch:
- Iron Arrow x10

The exact tuning is design data, not hardcoded into the Crafting Widget.

---

# 2. Arrows Are an Ammunition Recipe Category

Arrows belong to a data-driven category/tag such as:

- `Craft.Category.Ammunition`
- `Ammo.Arrow`

Do not permanently classify arrows under a generic `Other` branch merely because the tutorial only has Armor/Weapons/Other.

The recipe browser already supports expandable data-driven categories.

---

# 3. Generated Stats Are Not Applied Blindly To Commodity Ammo

A recipe output does not automatically receive the weapon/armor random-affix generation path.

The output Item Definition / generation profile decides whether it receives:

- no generated affixes;
- lot/batch quality;
- material-grade properties;
- crafted provenance;
- special ammunition effects;
- authored/generated modifiers where deliberately supported.

Ordinary arrows/material stacks should not accidentally roll weapon affixes merely because the Crafting system can generate them.

---

# 4. Batch Craft Request

Use the existing conceptual request:

`RequestCraft(RecipeDefinitionID, BatchQuantity, CraftingContextID, SelectedSourceContainerIDs)`

The server resolves total requirements from the requested batch count.

Example:

1 batch -> 10 arrows
3 batches -> 30 arrows

The server verifies:

- requested BatchQuantity is legal;
- required input quantities exist;
- profession/station/tool requirements;
- output destination capacity/policy;
- reservation/concurrency;
- output definition/stack compatibility;
- work/time requirements.

The client does not loop ten times and claim each loop is a successful craft.

---

# 5. Atomic Batch Commit

For an immediate batch craft:

1. reserve all required input quantities;
2. reserve/validate the output destination policy;
3. resolve the exact output quantity;
4. consume/transform the inputs according to recipe policy;
5. create the output stack/lot/ItemInstances exactly once;
6. attach crafter/recipe/quality/provenance state;
7. place outputs into legal destination(s);
8. persist transaction;
9. emit deltas/progression/notification.

No partial loop may create 7 arrows, fail, and forget whether materials for the remaining 3 were consumed unless the recipe explicitly supports incremental production jobs.

---

# 6. Stack / Lot Output

For homogeneous stackable commodities such as ordinary arrows, the output may be represented as a compact stack/lot record rather than ten unrelated unique Actors.

The resulting record can preserve, where needed:

- ItemDefinitionID;
- quantity;
- crafter/provenance lot;
- quality/grade;
- condition where meaningful;
- poison/condition payload;
- upgrade/modification state;
- ownership/legal state.

If generated properties differ per individual unit, those units cannot be merged into one stack that destroys the differences.

---

# 7. Output Capacity / Overflow

Do not implement overflow by crafting units one-by-one into inventory until full and then blindly spawning the rest in front of the player.

The recipe/output policy chooses what happens before commit.

Possible policies:

- require enough destination capacity for the full batch;
- split output across approved containers;
- use workstation output storage;
- create a validated world-output stack at the workstation;
- queue/hold completed output until storage is available;
- reject the batch size and suggest a smaller quantity.

Any world-output location must use the canonical safe-spawn/support validation.

Nothing is silently deleted.

---

# 8. Craft Quantity UI

Crafting UI may allow:

- one batch;
- multiple batches;
- `Craft Max` according to materials/capacity/work limits;
- preset quantities;
- numeric/slider selection where useful.

UI displays resulting output clearly:

- `Iron Arrows x10`
- `3 batches -> 30 arrows`

The UI may calculate a local preview from authoritative recipe snapshots but the server recalculates on submission.

---

# 9. Profession / XP Scaling

Batch production does not automatically grant full single-craft progression reward multiplied without limit.

Recipe/profession policy can define:

- per-unit reward;
- per-batch reward;
- diminishing reward for trivial repetition;
- work-unit-based reward;
- quality bonus;
- company/machine production rules.

Progression occurs only after legitimate committed work/output.

---

# 10. Arrow Asset / Collision Authoring

Arrow world/drop presentation may use an authored mesh, icon, mass, simple collision and Item Definition data.

For actual high-speed projectile flight, do not rely only on making the Box Collision longer.

UE5.8 projectile movement supports swept collision checks, and physics components can use Continuous Collision Detection (CCD) where appropriate. Projectile collision strategy should be selected/profiled for the combat implementation.

The stored arrow ItemInstance/stack and the in-flight projectile presentation remain separate states as defined in the ranged-weapon architecture.

---

# 11. Notifications

After successful batch commit, notification may say:

- `Crafted Iron Arrows x10`
- `Crafted 3 batches — Iron Arrows x30`

If output is routed to workstation/world storage, notification should identify that result when useful.

No success message before commit.

---

# 12. Persistence / Concurrency

Batch transaction records must prevent:

- duplicate outputs after reconnect/retry;
- two players spending the same final ingredient stack;
- repeating a completed batch after server restart;
- output quantity mismatch between UI and persistent state.

Use transaction/job revision/ID where needed.

---

# 13. Acceptance Tests

1. Recipe can output 10 arrows from one batch without ten independent client craft calls.
2. Batch quantity multiplies authoritative input requirements correctly.
3. Commodity arrows do not receive inappropriate weapon random affixes.
4. Full output is committed exactly once.
5. Two concurrent batch crafts cannot spend the same ingredient quantity.
6. Output stack preserves all stack-significant quality/provenance/effect state.
7. Insufficient capacity follows the configured output policy without item loss.
8. World overflow output spawns at a validated location if that policy is enabled.
9. `Craft Max` is revalidated server-side.
10. Notification displays committed output quantity.
11. Save/reconnect cannot duplicate a completed batch.
12. Arrow projectile collision uses the chosen swept/CCD/high-speed strategy rather than depending only on elongated pickup collision.

## Core Rule

> Batch crafting is one authoritative production transaction with explicit quantity and output policy. Stackable results stay compact when their state is compatible, and high-speed projectile behavior is handled by the combat projectile system rather than by stretching the inventory item's collision box.