# Metaworld — Crafting, Recipes, Materials & Production System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / data-driven

## Canonical Principle

Crafting transforms authoritative persistent inputs into authoritative persistent outputs according to a stable recipe definition, world requirements and a committed transaction/work process.

> The crafting widget shows what can be made. It does not own recipes, consume materials or create items by itself.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`
- `Docs/HUD_Notification_Feedback_System.md`

---

# 1. Crafting Materials Are Normal Persistent Items

Wood, iron, leather and other resources use the same Item Definition / Item Instance architecture as every other physical item.

Example stable definitions:

- `Item.Material.Wood.Firewood`
- `Item.Material.Wood.Plank`
- `Item.Material.Iron.Ingot`
- `Item.Material.Iron.Bar`
- `Item.Material.Leather.Hide`
- `Item.Material.Leather.Tanned`

Possible tags:

- `Item.Category.Material`
- `Material.Wood`
- `Material.Metal.Iron`
- `Material.Leather`
- `Craft.Resource.Structural`
- `Craft.Resource.Textile`

A crafting material may still carry normal item state such as:

- quantity;
- mass/volume;
- quality/grade;
- condition where meaningful;
- creator/provenance;
- legal owner/current possessor;
- stolen/evidence history;
- market value;
- physical world mesh/material;
- inventory icon;
- stack policy.

Do not create a second invisible `Crafting Materials` currency/count system that bypasses ItemInstances and containers.

---

# 2. Asset Authoring

Tutorial asset-editing lessons are approved as content-production techniques:

- scale assets to real gameplay dimensions;
- author simple collision appropriate to pickup/drop;
- adjust material instances to represent the intended material;
- create/customize meshes in a DCC when marketplace assets do not fit;
- generate cached inventory icons through the approved icon pipeline;
- register the resulting Item Definition in stable catalog data.

Current UE5.8 content sourcing should use Fab/Megascans rather than treating deprecated Quixel Bridge as a permanent dependency.

Do not assume a visually recolored stone automatically becomes valid iron gameplay data. The mesh/material presentation and the Item Definition's actual material/physical properties are separate authoring responsibilities.

---

# 3. Recipe Identity

Recommended stable identity:

`RecipeDefinitionID`

Example:

- `Recipe.Weapon.Sword.Iron.Basic`
- `Recipe.Armor.Leather.Chest.Basic`
- `Recipe.Material.Leather.Tanned`

A Data Table Row Handle may be used as an editor authoring reference, but the stable RecipeDefinitionID remains the gameplay identity.

Possible recipe definition fields:

- `RecipeDefinitionID`
- display name / localized description
- category/subcategory tags
- output ItemDefinitionID(s)
- output quantity
- ingredient requirements
- accepted substitution tags
- required tools
- required workstation/station tags
- profession/skill/certification requirements
- minimum quality/grade requirements where relevant
- batch-size rules
- work/time requirements
- fuel/power/utility requirements where relevant
- unlock/knowledge requirements
- legal/license requirements where relevant
- byproducts/waste
- output quality rules
- recipe icon/presentation metadata
- soft asset references where needed

---

# 4. Ingredient Requirement Record

Suggested conceptual record:

`S_MW_CraftingIngredientRequirement`

Fields may include:

- RequiredItemDefinitionID, or
- RequiredMaterial/Capability Tags
- RequiredQuantity
- Unit policy
- MinimumQuality/Grade
- AcceptedSubstitutionTags
- ConsumePolicy
- Optional/Required flag

Examples:

`Iron Sword`
- 2 x `Material.Metal.Iron`
- 1 x `Material.Wood` for grip/core where recipe requires it
- Smithing tool
- Forge/Anvil workstation

A recipe may accept exact ingredients or compatible substitutions according to explicit data.

Do not use hardcoded item-name Switch graphs as the recipe engine.

---

# 5. Crafting Sources / Containers

Crafting can draw from approved accessible sources according to the recipe/station/context policy.

Possible sources:

- carried inventory;
- backpack;
- workstation input storage;
- nearby authorized chest/container;
- property workshop storage;
- business warehouse;
- vehicle/trailer cargo where explicitly allowed;
- company inventory/logistics.

The source resolver respects ownership, access, locks, reservations and world distance/context.

Do not silently consume materials from every container the player owns anywhere in the world.

The UI should show which sources are being used or why materials are unavailable.

---

# 6. Craft Request / Server Validation

Suggested request:

`RequestCraft(RecipeDefinitionID, BatchQuantity, CraftingContextID, SelectedSourceContainerIDs)`

Server validates:

- recipe exists and is enabled;
- requester knows/is allowed to use the recipe;
- required profession/skills/licenses are satisfied;
- workstation/tool/context requirements are satisfied;
- requester can access the selected material sources;
- exact required quantities/qualities/substitutions exist;
- source items are not reserved by another transaction;
- destination/output container has capacity or a valid world-output policy exists;
- utilities/fuel/power are available where required;
- character/world state allows crafting;
- batch quantity is legal.

The client never says `I have enough wood, create the sword` as authoritative truth.

---

# 7. Atomic Material Reservation / Consumption / Output

For immediate crafts:

1. server reserves required input ItemInstances/quantities;
2. validates output destination;
3. consumes or transforms approved inputs according to recipe policy;
4. creates the authoritative output ItemInstance(s);
5. applies quality/creator/provenance/crafted metadata;
6. places output in destination container/world state;
7. creates byproducts/waste where defined;
8. persists the transaction;
9. replicates inventory deltas;
10. emits notification/XP/profession events where appropriate.

Failure before commit leaves the inputs unchanged.

No partial state should consume materials without creating the legitimate output, or create output without consuming/reserving the inputs.

---

# 8. Crafting Time / Work

Not every craft should be instant.

Recipes may define:

- Instant/short interaction;
- timed workstation process;
- player Work Units;
- NPC/company Work Units;
- machine process;
- scheduled batch production.

Long-running production uses authoritative state/timestamps/work units rather than permanent per-recipe Tick.

Possible states:

- Ready
- MissingMaterials
- MissingTool
- MissingStation
- Queued
- MaterialsReserved
- InProgress
- Paused
- Completed
- Failed
- Cancelled

Cancellation/refund behavior follows recipe/material-consumption policy; consumed inputs are not magically restored unless explicitly defined.

---

# 9. Output Quality / Crafted Identity

Crafting can produce an exact persistent ItemInstance with metadata derived from:

- recipe;
- crafter CharacterID/creator identity;
- profession/skill level;
- tool/workstation quality;
- input material quality;
- workmanship/result roll where approved;
- modifiers/upgrades;
- supernatural/magic crafting systems later.

This supports creator provenance and a real player economy without making rarity alone determine item power/value.

The output's `ItemInstanceID` is new because crafting legitimately creates a new physical item.

---

# 10. Recipe Categories / Browser

The tutorial's category browser is approved, but categories are data-driven tags rather than a permanent three-way hardcoded Switch.

Possible categories:

- Armor
- Weapons
- Tools
- Food
- Medicine
- Building/Construction
- Furniture
- Clothing
- Ammunition
- Components
- Materials/Processing
- Magic/Supernatural
- Other

The catalog can grow without redesigning the widget graph.

Recommended filters:

- category/subcategory;
- craftable now;
- known/unlocked;
- profession;
- workstation;
- missing materials;
- favorites;
- recently crafted;
- search text.

Expandable sections, ScrollBox/ListView/TileView presentation or other scalable layouts are implementation choices.

---

# 11. Recipe UI Data

Each recipe entry may display:

- name/icon;
- output quantity;
- ingredient list;
- available/required quantities;
- missing requirements;
- workstation/tool requirement;
- profession/skill requirement;
- expected time/work;
- resulting weight/value summary where useful;
- craftability state/reason;
- controller action prompt.

The widget receives a recipe presentation snapshot and refreshes when relevant inventory/station/skill state changes.

Do not rebuild the entire crafting catalog every frame.

---

# 12. Recipe Knowledge / Unlocks

Recipe availability can be separate from general item existence.

Possible unlock sources:

- profession training;
- books/manuals/blueprints;
- apprenticeship;
- discovery/research;
- faction/company access;
- quest/event reward;
- purchased license/recipe;
- supernatural knowledge.

Metaworld does not require a generic character `Level` gate if profession/skill/world requirements better express the recipe.

---

# 13. Multiplayer / Concurrency

Multiple players may interact with one workshop/storage system.

Server serializes reservations/consumption so two players cannot consume the same final iron bar and both receive an output.

Craft station queues, shared storage and company production remain authoritative/persistent.

Other clients receive only the state necessary to display relevant station/world results.

---

# 14. Persistence

Persist according to process type:

- known/unlocked RecipeDefinitionIDs where character-specific;
- active crafting jobs;
- reserved inputs;
- workstation/queue identity;
- progress/work units/timestamps;
- crafter/company identity;
- output destination;
- byproduct policy;
- transaction/result records.

Server restart must not duplicate reserved inputs or repeat a completed output transaction.

---

# 15. Performance

- recipe definitions are data, not live Actors;
- no global scans for all materials every frame;
- resolve/calculate craftability on UI open and relevant inventory/station changes;
- cache aggregate ingredient availability where useful;
- use soft references for heavy presentation assets;
- long jobs use timestamps/work events;
- large recipe lists use scalable/virtualized UI when needed;
- distant production exists as data/state rather than fully simulated Actors.

---

# 16. Controller Compatibility

Required with keyboard/mouse, Xbox-style and PlayStation-style controllers:

- open crafting tab;
- switch recipe categories/tabs;
- navigate recipe list/grid;
- expand/collapse category/details;
- inspect ingredients;
- choose quantity/batch;
- choose allowed source container where exposed;
- craft/queue/cancel;
- confirm/cancel dialogs;
- return focus predictably.

No essential recipe action may depend on mouse hover/click alone.

---

# 17. Python / Editor Validation

Future editor tooling can audit:

- duplicate/missing RecipeDefinitionIDs;
- missing output ItemDefinitionIDs;
- impossible ingredient IDs/tags;
- zero/negative quantities;
- impossible substitutions;
- missing station/tool tags;
- recipes whose outputs have no icon/presentation;
- orphan/unobtainable material requirements;
- invalid soft references;
- category/profile errors;
- circular processing recipes where unintended.

---

# 18. Acceptance Tests

1. Wood/iron/leather are normal persistent items usable outside crafting.
2. Recipe uses stable RecipeDefinitionID rather than item-name Switch logic.
3. UI can show Armor/Weapons/Other plus new categories without architecture changes.
4. Missing materials show exact reason/quantity.
5. Server rejects craft when client only claims to possess inputs.
6. Two simultaneous crafts cannot spend the same ingredient quantity twice.
7. Successful craft consumes/reserves correct inputs and creates output exactly once.
8. Output receives creator/provenance metadata where designed.
9. Recipe can require station/tool/profession/skill independently.
10. Crafting from shared storage obeys access rights.
11. Cancel policy does not duplicate consumed/reserved materials.
12. Save/load restores active craft job without duplicating output.
13. Recipe UI updates from inventory/station changes without Tick.
14. Keyboard/mouse, Xbox-style and PlayStation-style crafting flows all work.
15. Large recipe catalog remains within UI/frame-time budget.

## Core Rule

> Metaworld crafting is an authoritative transformation of persistent world resources through data-driven recipes, tools, skills, work and stations. The UI helps the player choose and understand the craft; it never becomes the factory.