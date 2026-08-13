# Metaworld — Recipe Knowledge Items, Learning & Unlock System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / data-driven

## Canonical Principle

Crafting knowledge is persistent character/world knowledge identified by stable `RecipeDefinitionID` records. Books, scrolls, manuals, blueprints and other physical items may teach that knowledge, but the knowledge and the physical teaching item are separate pieces of state.

> A recipe scroll can be found, owned, stolen, traded or destroyed as an ItemInstance. Learning it grants persistent recipe knowledge according to authoritative rules; the player does not know a recipe merely because a widget or enum says so.

Related canon:

- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Loot_Generation_Tables_Drops_Provenance_System.md`
- `Docs/HUD_Notification_Feedback_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`

---

# 1. Stable Recipe Knowledge Identity

Use:

`RecipeDefinitionID`

Examples:

- `Recipe.Weapon.Sword.Iron.Basic`
- `Recipe.Armor.Plate.Gloves`
- `Recipe.Ammo.Arrow.Iron`

Do not create a closed enum containing every recipe name as the long-term identity system.

Do not derive identity by removing spaces from display strings such as `Iron Sword`.

Display/localized names may change without invalidating persistent knowledge.

---

# 2. Recipe Teaching Item

A physical teaching item is a normal ItemDefinition / ItemInstance.

Possible categories/tags:

- `Item.Category.Knowledge`
- `Item.Knowledge.Recipe`
- `Item.Knowledge.Manual`
- `Item.Knowledge.Blueprint`
- `Item.Knowledge.Scroll`

Possible definition data:

- display name/description;
- world mesh/icon;
- `TeachesRecipeDefinitionIDs[]`;
- consume policy;
- profession/skill prerequisites where required;
- language/literacy requirement where designed;
- legal/faction restrictions;
- reusable vs single-use behavior;
- rarity/presentation profile;
- weight/value/ownership/tradability.

The exact ItemInstance still carries owner, possessor, provenance, stolen/evidence status and other persistent state.

---

# 3. Learning Request

Suggested flow:

`RequestLearnRecipe(KnowledgeItemInstanceID)`

Server validates:

- item exists and requester possesses/can legitimately use it;
- definition actually teaches one or more RecipeDefinitionIDs;
- recipe definition exists/enabled;
- prerequisite knowledge/profession/language/skill rules where applicable;
- recipe is not already known unless the item has another valid use;
- item is not reserved/locked by another transaction.

On success:

1. add RecipeDefinitionID(s) to authoritative character knowledge;
2. persist knowledge revision;
3. consume/decrement teaching item only if its policy says it is consumed;
4. update Crafting UI/event state;
5. emit local notification.

Failure does not silently destroy the teaching item.

---

# 4. Known Recipe Storage

Persist known recipes as stable IDs or an equivalent knowledge record.

Conceptual:

`CharacterRecipeKnowledge`
- CharacterID
- RecipeDefinitionID
- LearnedAt
- LearnedFromSourceID / source type where useful
- Teacher/ItemInstance/Book/Quest/Faction provenance where useful
- Revision

Do not store known recipes only as Widget children or a transient Player Blueprint array with display strings.

---

# 5. Duplicate Learning

If the character already knows the recipe, the system returns an explicit result such as:

- `AlreadyKnown`
- `NoNewKnowledge`

The UI may show:

`Recipe already known`

The physical item remains according to its consume/use policy.

A repeated use must not duplicate RecipeDefinitionIDs or repeatedly grant profession XP/rewards unless an explicit study/training system says it should.

---

# 6. One Item Can Teach Multiple Recipes

A manual or book may teach:

- one recipe;
- a recipe family;
- multiple specific recipes;
- a progression tree unlocked through study.

Example:

`Blacksmithing Basics Manual`
- Recipe.Weapon.Sword.Iron.Basic
- Recipe.Tool.Hammer.Iron
- Recipe.Armor.Shield.Iron.Basic

This is data-driven; no special hardcoded widget path is required.

---

# 7. Loot Integration

Loot profiles may legitimately create recipe teaching ItemInstances.

Examples:

- workshop chest;
- boss/container drop;
- library/manual shelf;
- trader stock;
- quest reward;
- dead specialist NPC's possessions where world rules permit.

The loot system selects the actual teaching ItemDefinition/ItemInstance once and persists it.

Opening/reloading the same persistent container must not reroll the recipe scroll indefinitely.

---

# 8. Crafting UI Integration

The crafting catalog filters against authoritative known/unlocked RecipeDefinitionIDs.

When knowledge changes:

`OnRecipeKnowledgeChanged`
-> refresh affected recipe/category entries

Do not clear/rebuild the entire Crafting Widget every frame.

Clearing dynamic children on a deliberate full rebuild is acceptable, but scalable list/virtualized/event-driven approaches are preferred as the recipe catalog grows.

Unknown recipe behavior may be configured as:

- hidden completely;
- visible silhouette/locked entry;
- show requirements/hint;
- discoverable through profession/research systems.

---

# 9. Tooltip / Knowledge Item Presentation

A recipe scroll/manual tooltip may show:

- display name;
- description;
- recipe(s) taught;
- profession/category;
- `Known` / `Not Known` state for local character;
- required profession/skill/language where relevant;
- consume/reusable behavior;
- item ownership/value/provenance according to normal item rules.

The `Already Known` warning is presentation derived from current knowledge state, not stored permanently inside the physical scroll.

---

# 10. Sharing / Trading / Theft

Because teaching items are physical items, they can follow normal world rules:

- sell/trade to another player;
- gift;
- store in chest/library;
- steal;
- recover;
- inherit;
- lose/destroy where allowed.

Learning the recipe does not automatically consume ownership of every copy unless the particular item is designed as single-use.

Likewise, selling the book after learning it does not erase learned knowledge unless a deliberately temporary-license system is being used.

---

# 11. Knowledge vs License

Recipe knowledge and legal/professional permission are separate.

A character can know how to manufacture an item yet still require:

- profession certification;
- legal license;
- restricted facility;
- workstation/tool;
- business permit;
- rare materials.

`Knows Recipe` does not mean `May legally/physically craft it right now`.

This distinction is especially important for firearms, explosives, medicine and other regulated/industrial systems.

---

# 12. Performance / Validation

- RecipeDefinitionIDs are compact data;
- no per-frame recipe-knowledge scans;
- cache known-set membership and invalidate on knowledge revision;
- UI refreshes on knowledge change/open;
- Python Editor tooling can audit teaching items that reference missing RecipeDefinitionIDs;
- detect duplicate RecipeDefinitionIDs within one teaching item where unintended;
- detect recipes with no possible unlock source if the design expects them to be learnable.

---

# 13. Acceptance Tests

1. Recipe scroll is a normal persistent ItemInstance.
2. Teaching identity uses RecipeDefinitionID rather than display-name enum/string conversion.
3. Learning adds the recipe exactly once.
4. Already-known recipe returns clear feedback and does not duplicate knowledge.
5. Single-use scroll consumes only after successful learn when configured.
6. Reusable manual remains after reading when configured.
7. Dropping/trading the manual after learning does not erase knowledge.
8. Loot container cannot reroll the same persistent recipe item on reopen.
9. Crafting UI updates when knowledge changes without per-frame polling.
10. Controller/keyboard/mouse can inspect/use recipe items.
11. Knowledge does not bypass profession/tool/station/legal requirements.
12. Save/load preserves known RecipeDefinitionIDs.

## Core Rule

> Recipe knowledge is stable persistent character knowledge. Physical scrolls, manuals and blueprints are ordinary world items that can teach that knowledge under authoritative rules, but item ownership, learned knowledge and crafting permission remain separate concepts.