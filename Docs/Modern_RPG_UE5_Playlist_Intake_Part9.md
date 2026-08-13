# Metaworld — Modern RPG UE5 Playlist Intake — Part 9

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part8.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

This Part contains Episodes 63–71.

---

# Episode 63 — Arrow Assets, Item Definition & Crafting Integration

**Classification:** UPGRADE — APPROVED / AMMUNITION CONTENT EXTENSION.

**Phase Ownership:** Ranged Weapons + Item DNA + Crafting + Projectile Collision.

Detailed companions:

- `Docs/Ranged_Weapons_Bow_Ammo_Quiver_Container_System.md`
- `Docs/Batch_Crafting_Stack_Output_Quantity_Transaction_System.md`
- `Docs/Crafting_Recipes_Materials_Production_System.md`

## Approved Tutorial Intent

- author arrow mesh/material/scale;
- create reusable arrow data/presentation foundation;
- generate cached inventory icon;
- define stack quantity, mass/weight and combat contribution;
- add arrow recipe using wood/iron materials;
- integrate arrows into crafting catalog.

## Metaworld Upgrades

- arrows use stable ItemDefinitionID / persistent stack/ItemInstance state rather than requiring one child Blueprint for every ordinary variant;
- `Craft.Category.Ammunition` / `Ammo.Arrow.*` replaces permanent classification under generic Other;
- arrow recipe uses RecipeDefinitionID, materials, profession/station/tool rules and batch output policy;
- output can preserve crafter/quality/provenance lot state;
- ordinary arrows do not automatically receive weapon random-affix generation unless their profile explicitly supports it;
- stored arrow/world pickup collision is separate from in-flight projectile collision;
- elongated Box Collision alone is not treated as the final high-speed collision solution;
- UE5.8 projectile implementation may use ProjectileMovement swept collision and/or appropriate CCD/collision strategy after profiling;
- in-flight projectile remains a lightweight combat representation; recoverable arrow world item follows the existing ranged-item policy.

### Episode 63 Principle

> Arrows are persistent ammunition items created by real recipes; projectile collision is authored for high-speed combat rather than assuming the inventory item's stretched collision box solves tunneling.

---

# Episode 64 — Batch Crafting / Craft Multiple Arrows

**Classification:** UPGRADE — APPROVED WITH ATOMIC-BATCH CORRECTION.

**Phase Ownership:** Crafting + Ammunition + Inventory/Containers + Notifications.

Detailed companion:

`Docs/Batch_Crafting_Stack_Output_Quantity_Transaction_System.md`

## Approved Tutorial Intent

- recipe can produce more than one output unit;
- arrow crafting should support stack/batch output;
- UI should show quantity such as `Arrows x10`;
- output must not disappear when destination inventory is full;
- crafting output rules must distinguish commodity ammo from generated equipment stats.

## Metaworld Upgrades

- recipe definition owns `OutputQuantityPerBatch` / batch-size rules;
- client does not ForLoop ten independent `PickupItem`/craft calls;
- one authoritative batch request calculates/reserves all inputs and creates the legitimate output quantity exactly once;
- output can become one compatible arrow stack/lot rather than ten separate inventory objects;
- if destination lacks capacity, recipe policy may reject, route to workstation output, split across approved containers or create a validated world-output stack;
- do not craft until inventory becomes full and then blindly spawn leftovers in front of player;
- no item loss or duplication on partial failure;
- profession XP/batch reward follows recipe progression policy rather than unlimited `single craft XP × quantity` by default;
- success notification uses the committed output count.

### Episode 64 Principle

> `Craft Arrows x10` is one authoritative production transaction with explicit overflow policy—not ten client-side item creations in a loop.

---

# Episode 65 — Shield Item / Off-Hand Equipment

**Classification:** UPGRADE — APPROVED / EXISTING EQUIPMENT ARCHITECTURE.

**Phase Ownership:** Equipment + Combat + Stats + Animation + Item DNA.

Detailed companions:

- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

## Approved Tutorial Intent

- create shield world/equipped presentation and inventory icon;
- define shield Item data;
- equip to Off Hand through authored socket/attachment profile;
- shield can modify protection/stamina/other appropriate character/combat state;
- tune mesh scale/attachment transform to animation.

## Metaworld Upgrades

- shield is a persistent ItemInstance using `BPC_MW_Equipment` Off-Hand rules;
- shield conflicts with Two-Handed weapon use through data-driven equipment rules;
- socket transform comes from reusable AttachmentProfile rather than scattered Player Blueprint values;
- `Armor`, `Stamina`, `Health Regen`, weight/value fields are interpreted through their owning systems: protection modifier, Stamina resource/max/regeneration policy, status/modifier effect, carried mass and economy valuation;
- a shield does not grant permanent baked Health regeneration by directly mutating base stats;
- equipped shield ItemInstance contributes real carried mass;
- running/combat clipping is not accepted as an indefinite production state—animation, IK, socketing, rig/mesh and authored pose QA must resolve unacceptable clipping;
- no item duplication during bow/two-handed conflict resolution.

### Episode 65 Principle

> A shield is persistent Off-Hand equipment whose protection, movement/resource effects and visuals are resolved through existing equipment/stat/animation systems—not a mesh that permanently edits Player Blueprint numbers.

---

# Episode 66 — Inventory Avatar Preview Performance Lifecycle

**Classification:** LOCKED + PERFORMANCE UPGRADE.

**Phase Ownership:** Phase 61 Performance + Phase 67 UI + Avatar/Equipment Preview.

Detailed companions:

- `Docs/Avatar_Preview_Lifecycle_Performance_System.md`
- `Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`

## Approved Tutorial Intent

- an invisible character preview should not continue costing normal gameplay performance;
- preview can be created when inventory/character screen opens and released when it closes;
- current real Equipment state rebuilds the preview after reopening;
- optional preview reference must be validated so gameplay functions do not error when preview is absent.

## Metaworld Upgrades

- no hidden always-rendering SceneCapture/preview simulation;
- spawn-on-open/destroy-on-close is approved when profiling proves it best;
- pooled/dormant reuse is also permitted when capture/animation/groom/cloth work fully stops and profiling proves lower cost/latency;
- no fixed `+20 FPS` performance guarantee is recorded from one tutorial project;
- preview destroys/releases presentation attachments only and never calls gameplay Unequip or deletes real ItemInstances;
- Equip/Use gameplay works whether preview exists or not;
- preview reconstructs from AvatarCustomizationSnapshot + EquipmentSnapshot on activation;
- avoid replacing hidden-render cost with synchronous menu-open hitching—use soft refs/async/pooling where required.

### Episode 66 Principle

> The avatar preview earns frame time only while visible. Its Actor may be destroyed or suspended, but real avatar/equipment truth always lives elsewhere and rebuilds the preview on demand.

---

# Episode 67 — Stack Quantity Slider / Partial Drop

**Classification:** UPGRADE — APPROVED / QUANTITY-TRANSACTION UI.

**Phase Ownership:** Inventory/Containers + Item Drop + UI + Controller.

Detailed companion:

`Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`

## Approved Tutorial Intent

- choose a specific quantity from a stack before dropping;
- show selected amount clearly;
- confirm or cancel;
- dropping part of a stack must preserve remaining inventory quantity;
- avoid duplication while modal is active.

## Metaworld Upgrades

- reusable `W_MW_QuantitySelector` serves Drop/Split/Transfer/Sell/Give and similar actions;
- target is ItemInstanceID/stack-lot ID + SourceContainerID, not inventory index alone;
- discrete item selector clamps/snaps to integer range `1..CurrentQuantity`;
- one server `RequestDropQuantity` transaction splits/moves the stack rather than looping DropItem N times;
- both retained/dropped portions preserve all stack-significant quality/provenance/effect/legal state;
- dropped partial stack uses safe world-output location and compact stack/bundle representation where compatible;
- underlying inventory is blocked from unintended activation while modal is active;
- shared world does not globally pause.

### Episode 67 Principle

> The quantity dialog selects part of a persistent stack; one authoritative split/drop transaction preserves the rest and cannot duplicate the item.

---

# Episode 68 — Quantity Slider Snapping / Keyboard / Focus Refinement

**Classification:** LOCKED + UPGRADE UI/ACCESSIBILITY MAINTENANCE.

**Phase Ownership:** Phase 67 UI + Phase 68 Controller/Accessibility + Inventory.

Detailed companion:

`Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`

## Approved Tutorial Intent

- quantity selector snaps to valid integers;
- prevent click-through to inventory while modal is open;
- keyboard can increment/decrement quantity;
- focus returns cleanly after closing;
- input mode is correct for active UI.

## Metaworld Upgrades

- mouse-only slider is not sufficient;
- keyboard, Xbox-style and PlayStation-style controls can increment/decrement/confirm/cancel;
- modal UI layer owns input blocking/focus rather than adding duplicated Booleans to every inventory entry;
- hardcoded close keys become UI Back/Cancel actions;
- current stack quantity is re-resolved at confirm time because another authoritative event may have changed it;
- focus returns to originating ItemInstance entry if it still exists, otherwise next valid focus target;
- repeated Confirm is debounced/transaction protected.

### Episode 68 Principle

> Quantity selection is a controller-complete modal over current item state, with integer semantics and predictable focus—not a mouse slider glued onto the inventory graph.

---

# Episode 69 — Base NPC / Trader Interaction Foundation

**Classification:** UPGRADE — APPROVED / NEW NPC INTERACTION-SERVICE DOMAIN.

**Phase Ownership:** NPCs + Interaction + Jobs/Businesses + UI + AI.

Detailed companion:

`Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`

## Approved Tutorial Intent

- reusable NPC foundation;
- NPC implements common interaction contract;
- interaction can require appropriate distance/facing;
- specialized trader/innkeeper/etc. roles expose different actions;
- dot product is useful for checking facing/interaction cone.

## Metaworld Upgrades

- conceptual `BP_MW_NPC_Master` remains shallow and role/component/data driven; avoid deep child-class trees for every job type;
- NPC uses `BPI_MW_Interactable` / common `BPC_MW_Interaction` targeting;
- Talk/Trade/Service options derive from current NPC role, job, business, relationship and world state;
- distance + view cone/dot + LOS can help validate target, but do not run a permanent 10 Hz interaction timer on every NPC;
- bounded current-candidate resolver checks facing/LOS only while relevant;
- NPC may have schedules, Needs, combat state, job/business links and can become unavailable;
- interaction prompt remains one local contextual HUD prompt with device-aware input.

### Episode 69 Principle

> NPC services are contextual capabilities on living world characters. Facing helps select a candidate, but interaction does not justify a global timer running on every NPC.

---

# Episode 70 — Generated Stats For World Drops & Trader Stock

**Classification:** LOCKED + UPGRADE — APPROVED GENERATION-LIFECYCLE CORRECTION.

**Phase Ownership:** Generated Items + Loot + Vendors + Persistence.

Detailed companions:

- `Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`
- `Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`

## Approved Tutorial Intent

- generated stats can apply to legitimate world-drop/vendor equipment, not only crafted gear;
- crafting skill influence can be enabled/disabled depending on generation source;
- material/currency-like items should not receive inappropriate random equipment stats;
- dropped/picked-up items must not reroll;
- trader restock can generate new merchandise.

## Metaworld Upgrades

- generated affixes roll **when a new persistent ItemInstance is legitimately created**, not every Actor BeginPlay;
- authoritative generation source/profile determines whether crafting proficiency, loot tier, vendor stock profile or other inputs affect quality;
- once ItemInstance generated state exists, BeginPlay/pickup/drop/load/menu-open never rerolls it;
- trader stock uses persistent ItemInstances/containers; restocking is a world/business process, not opening the Trader Widget;
- materials/commodities such as wood, iron and physical gold do not receive weapon/armor affixes unless an explicit generation profile says otherwise;
- GrimKoin/PromoKoin ledger/currency records are not generated-stat equipment;
- optional deterministic authoritative generation seed remains available for audit/debug.

### Episode 70 Principle

> Random properties are assigned once at legitimate item creation and become part of that ItemInstance's history; spawning a representation or opening a shop never rerolls it.

---

# Episode 71 — Trader Widget / Buy & Sell Interface

**Classification:** UPGRADE — APPROVED WITH CRITICAL CURRENCY / BUSINESS CORRECTION.

**Phase Ownership:** Economy/Trade + NPC Services + Inventory/Containers + Businesses + Phase 67/68 UI.

Detailed companions:

- `Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`
- `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`
- `Docs/Gold_Material_Commodity_Not_Currency_Rule.md`
- `Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`

## Approved Tutorial Intent

- trader UI can show vendor stock and player sellable inventory side by side;
- interacting with a trader opens commerce UI;
- user can inspect item stats/details;
- buy/sell quantity and pricing information belong in the transaction screen;
- input/focus should transition cleanly while trading.

## Critical Metaworld Gold Rule

**Gold is not money in Metaworld.**

- there is no tutorial `Player Gold` balance;
- there is no `Trader Gold` balance;
- goods/services are bought/sold using GrimKoin and PromoKoin where accepted;
- Gold Ore/Nuggets/Ingots/Dust/etc. are normal physical material/commodity ItemInstances;
- a trader can buy or sell Gold material as merchandise, but payment still uses GrimKoin/PromoKoin;
- Gold may be consumed by weapon/jewelry/component/magic/etc. crafting recipes as a material.

## Trader / Business Upgrade

- trader stock is real persistent business/NPC inventory, not a copied UI-only array;
- NPC trader may be an employee/owner attached to BusinessID, schedule and service profile;
- payment ability comes from business/NPC authorized ledger/wallet/cash source—not a hardcoded Gold integer;
- actual buy/sell amounts come from authoritative vendor quotes using condition, quality, generated affixes/upgrades, supply/demand, taxes, legality, vendor funds/storage and other economy context;
- opening Trader UI does not pause shared world;
- UI may restrict local movement/look while open, but NPC can become unavailable because of combat, schedule, death, shop closure, etc.;
- Buy/Sell commits ItemInstance/quantity + GrimKoin/PromoKoin atomically;
- quantity selection reuses canonical quantity selector;
- no client array swap/payment arithmetic is authoritative;
- KBM/Xbox-style/PlayStation-style users can navigate both sides, inspect quote, choose quantity and confirm/cancel.

### Episode 71 Principle

> Trader UI is a view over a living NPC/business, real stock and real currency ledgers. Gold can be valuable merchandise or crafting material, but every normal purchase/sale is paid with GrimKoin/PromoKoin.

---

# Current Modern RPG Additions From Episodes 63–71

`Arrow ItemDefinition`
-> `Ammo RecipeDefinitionID`
-> `Batch Output Quantity`
-> `Authoritative Stack/Overflow Transaction`
-> `Quiver / Ammo Consumption`

`Shield ItemInstance`
-> `Off-Hand Equipment`
-> `Protection / Resource Modifiers`
-> `Animation / Socket QA`

`Inventory Preview Visible`
-> `Activate/Spawn Preview`
-> `Bounded SceneCapture`
-> `Close Tab/Menu`
-> `Stop/Destroy/Dormancy Preview Work`

`Persistent Stack`
-> `Quantity Selector`
-> `Atomic Split/Drop/Transfer/Sell`

`Living NPC`
-> `Interaction Capability`
-> `Trader/Business Service`
-> `Persistent Vendor Stock`
-> `Authoritative Quote`
-> `GrimKoin/PromoKoin Payment`

`Physical Gold Item`
-> `Material / Commodity / Crafting Resource`
-> **NOT CURRENCY**

---

# Playlist Continuation Rule

Future episodes continue in Part 9 until another safe continuation is needed. Parts 1–9 remain the canonical intake/audit trail for this Modern RPG playlist; detailed companion documents remain implementation authority for established domains.