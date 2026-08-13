# Metaworld — Modern RPG UE5 Playlist Intake — Part 5

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part4.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

---

# Episode 28 — Equip / Unequip Dynamic Stat Changes

**Classification:** LOCKED + UPGRADE — APPROVED.

**Phase Ownership:** Stats/Attributes + Equipment + UI.

Detailed companion:

`Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

## Approved Tutorial Intent

- equipping an item should change relevant character stats;
- unequipping should remove those changes cleanly;
- character/stat UI should refresh when equipment changes;
- scalar stats such as Armor/Attack Speed should not be presented with confusing Current/Max labels.

## Metaworld Upgrades

- do not move scalar values into a fake `Max Stat` field merely to work around one prototype structure;
- Stat Definitions declare semantic type such as Resource, Scalar/Derived or Bounded Scalar;
- Health/Stamina/Mana use Current/Max semantics;
- Armor, Attack Speed, Damage, Carry Capacity and similar attributes normally display one effective/derived value;
- equip transaction registers modifier records with `SourceID = ItemInstanceID` only after authoritative equipment succeeds;
- unequip removes the modifiers belonging to that exact source;
- reject generic `value * -1` mutation as the final reversal architecture because additive/multiplicative/condition-driven modifiers need source-aware removal;
- affected derived stats recalculate once and emit change events to UI.

### Episode 28 Principle

> Do not fake Current/Max semantics to make the data structure fit. Model what the stat means, and apply/remove equipment effects by traceable modifier source.

---

# Episode 29 — Character Stats Display in Inventory

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Stats/Attributes + Phase 67 UI + Phase 68 Accessibility/Controller.

Detailed companions:

- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`

## Approved Tutorial Intent

- inventory/character UI can show Health, Mana, Stamina, Damage, Attack Speed, Armor and other important character values;
- icons/labels/tooltips help players understand the stat panel;
- equipment changes should refresh the panel.

## Metaworld Upgrades

- stat panel is data-driven rather than permanently hardcoded to six rows;
- Stat Definition controls icon, display name, units, decimal precision, Resource-vs-Scalar format, ordering and help text;
- examples: `Health 82/120`, `Armor 46`, `Attack Speed 1.15/s`, `Carry Load 31.4/42 kg`;
- do not convert every float to integer merely to remove decimals—precision is stat-specific;
- mouse hover tooltips have keyboard/controller focus equivalents;
- UI consumes presentation snapshots/change events rather than becoming stat authority.

### Episode 29 Principle

> Character UI shows each stat in the format appropriate to that stat's meaning, with the same information available to mouse and controller users.

---

# Episode 30 — Dropped Item Physics, UMG Binding Optimization & Data Table Row Handles

**Classification:** UPGRADE / MAINTENANCE — APPROVED.

**Phase Ownership:** Item World Representation + Inventory/UI performance + Item Definition authoring.

Detailed companions:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`

## Approved Tutorial Intent

- newly dropped items should not spawn embedded/overlapping and explode away physically;
- complex inventory/equipment UI should avoid unnecessary property bindings;
- designers benefit from directly selecting an Item Data Table row instead of manually typing a second item-name variable.

## Metaworld Upgrades

- server validates a safe world spawn/support point and appropriate spawn-collision behavior for dropped ItemInstances;
- physics may be disabled during initialization if required, then enabled only when the item actually needs active simulation; it is not permanently disabled for every world item;
- no global time-dilation dependency for item physics correctness;
- settled/distant world items sleep/reduce simulation cost;
- event-driven UI updates replace raw continuously evaluated bindings for icon, rarity, visibility, counts and mutable state;
- initial Construct/OnInitialized can populate static data, while mutable data still receives explicit change events;
- UE5.8 Data Table Row Handle is approved as an authoring reference (Data Table + Row Name);
- Row Handle does not replace `ItemDefinitionID` or `ItemInstanceID`;
- soft asset references remain preferred in catalog data where large meshes/textures would otherwise all load with the table;
- Python Editor validation can audit invalid handles/rows/stable IDs.

### Episode 30 Principle

> Author item definitions cleanly, spawn world items safely, and update UI only when the underlying state changes.

---

# Episode 31 — Inventory / Equipment UI Styling

**Classification:** UPGRADE — APPROVED PRESENTATION.

**Phase Ownership:** Phase 67 UI + Phase 68 Accessibility/Controller.

Detailed companion:

`Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`

## Approved Tutorial Intent

- inventory icons can use frames/padding/size constraints;
- inventory containers can use clear borders/background hierarchy;
- subtle gradient materials can improve visual separation;
- equipment slots can display semantic empty-slot placeholders;
- tooltip typography/layout should be polished and consistent.

## Metaworld Upgrades

- use reusable style assets/widgets/material instances rather than duplicating styling constants in every slot;
- hover state has equivalent controller-focus state;
- empty-slot placeholder derives from EquipmentSlotID and hides/shows from authoritative slot state;
- rarity styling remains centralized in Rarity Presentation profiles;
- gradients/material effects must not reduce icon/status readability or exceed UI performance budget;
- UI must scale cleanly across supported resolution/UI scale/accessibility settings;
- character-preview Z-order must never make equipment controls inaccessible.

### Episode 31 Principle

> Polish the UI through a reusable visual language, not by scattering one-off style and rarity logic across every widget.

---

# Episode 32 — Item Price / Sell Price / Description Tooltip

**Classification:** UPGRADE — APPROVED WITH ECONOMY CORRECTION.

**Phase Ownership:** Item DNA + Economy/Trading + Phase 67 UI.

Detailed companions:

- `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`
- `Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`
- `Docs/Banking_Currency_Custody_Future_Cashout.md`

## Approved Tutorial Intent

- item definitions can contain descriptions and valuation metadata;
- tooltip can display value/currency information;
- empty descriptions should collapse without layout gaps;
- multi-line description content is useful.

## Metaworld Economy Correction

Do not treat one static `Price` and one static `SellPrice` as universal world truth.

An Item Definition may have a reference/base value, while an actual vendor quote can depend on:

- currency type;
- item condition/quality/modifications;
- vendor/business type;
- supply/demand/scarcity;
- taxes/fees;
- legality/stolen status;
- local market conditions;
- vendor available funds/storage;
- creator/provenance/history where the market values it.

Canonical currencies remain GrimKoin/PromoKoin.

Outside a vendor context, UI may show `Reference Value` / `Estimated Value` / `Appraised Value`.

Inside a vendor context, UI shows the authoritative buy/sell quote and actual currency/fees.

## Description Rules

- Item Definition can carry localized Short/Long Description;
- description presentation can be multiline/wrapped;
- empty region collapses cleanly;
- static description remains separate from ItemInstance-specific condition, creator, upgrades, provenance and legal/evidence state.

### Episode 32 Principle

> Item descriptions are definition content; prices belong to the living economy. A vendor quote is contextual, authoritative and denominated in Metaworld's real currencies.

---

# Episode 33 — Crafting Materials: Wood, Iron & Leather

**Classification:** UPGRADE — APPROVED CONTENT / ITEM-DNA FOUNDATION.

**Phase Ownership:** Phase 9 Item DNA + Phase 11 Inventory + Crafting/Professions/Economy.

Detailed companion:

`Docs/Crafting_Recipes_Materials_Production_System.md`

## Approved Tutorial Intent

- create physical world resources such as wood, iron and leather;
- author appropriate mesh scale, materials and simple collision;
- generate inventory icons;
- register resource items in data-driven item catalog data;
- ensure stacking/tooltips/descriptions continue working after catalog expansion.

## Metaworld Upgrades

- wood/iron/leather are normal persistent `ItemDefinitionID` / `ItemInstanceID` resources, not a second craft-only counter system;
- material resources can carry mass, quantity, quality/grade, owner/possessor, provenance, theft/evidence state, value and physical presentation;
- stable material/category Gameplay Tags allow recipes to request exact definitions or approved substitutions;
- one recolored mesh does not define gameplay material truth—the Item Definition owns actual material/capability data;
- current UE5.8 content acquisition uses Fab/Megascans rather than treating deprecated Quixel Bridge as the future dependency;
- icons use the cached editor icon-generation pipeline already approved;
- ordinary material items remain usable for trading, storage, transport, construction and other systems, not only crafting.

### Episode 33 Principle

> Crafting materials are real items in the same persistent world economy, not abstract recipe numbers hidden behind the crafting screen.

---

# Episode 34 — Struct Breakage / Widget Data Contract Refactor

**Classification:** UPGRADE — APPROVED ARCHITECTURE CLEANUP.

**Phase Ownership:** Phase 67 UI + Item/Inventory/Equipment data contracts.

Detailed companion:

`Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`

## Approved Tutorial Intent

- avoid passing an oversized Item Info struct into every widget when the widget only needs a few fields;
- notifications should receive only the information they display;
- options/tooltips need reliable access to the selected item after gameplay structs evolve;
- UI data flow should be refactored when schema changes reveal excessive coupling.

## Metaworld Upgrades

- widgets receive stable IDs and purpose-built presentation snapshots rather than entire mutable authoritative gameplay structs by default;
- notification payloads contain only message-relevant data such as name/icon/quantity/category;
- `InventoryIndex` is not stable item identity and is rejected as the only target of a delayed context action;
- item options prefer `ItemInstanceID + SourceContainerID` and re-resolve current location when the action executes;
- tooltip accepts ItemInstanceID + viewing/context information and receives an authorized presentation snapshot;
- tooltip does not grow a giant `Switch` that directly reads Inventory, Equipment, Vendor, Loot, Crafting, Vehicle and every future storage array;
- schema/struct evolution is handled through stable contracts, validation and migration rather than endless manual widget pin repairs.

### Episode 34 Principle

> Widgets should point to stable item truth, not carry fragile copies or array positions that become wrong as the game changes.

---

# Episode 35 — Player Interface Navigation Tabs

**Classification:** UPGRADE — APPROVED UI SHELL.

**Phase Ownership:** Phase 67 UI + Phase 68 Controller/Accessibility.

Detailed companion:

`Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`

## Approved Tutorial Intent

- create one player-facing interface shell hosting multiple panels;
- switch between Inventory, Crafting, Skills and Stats;
- use a Widget Switcher-style single-active-panel layout;
- style selected/unselected tab controls clearly.

## Metaworld Upgrades

- conceptual `W_MW_PlayerInterface` owns local interface navigation only, not gameplay state;
- tabs use stable Tab IDs/registry data instead of scattering magic `ActiveWidgetIndex` integers throughout Blueprint graphs;
- UMG WidgetSwitcher is the approved baseline implementation;
- Common UI remains an optional validated upgrade for tab lists, input routing, controller navigation and platform prompts;
- mouse, keyboard, Xbox-style and PlayStation-style users all have full tab-switch/navigation support;
- bumpers/shoulders may cycle tabs through Enhanced Input where designed;
- active-tab status is not communicated by color alone;
- heavy hidden tabs stop/reduce preview/capture/event work and can be lazy-created where useful;
- tab switching preserves/restores predictable focus.

### Episode 35 Principle

> One interface shell can organize Metaworld's character systems, but each tab remains a presentation surface over its own authoritative gameplay system.

---

# Episode 36 — Crafting Recipe Categories & Browser

**Classification:** UPGRADE — APPROVED / NEW CRAFTING DOMAIN.

**Phase Ownership:** Crafting + Professions + Inventory + Item DNA + Phase 67/68 UI.

Detailed companion:

`Docs/Crafting_Recipes_Materials_Production_System.md`

## Approved Tutorial Intent

- recipes are data-driven entries rather than handwritten button logic;
- recipe UI can group entries into expandable categories;
- players can browse recipe requirements in a scrollable interface;
- reusable recipe-entry widgets are appropriate;
- Data Table Row Handles are useful authoring references.

## Metaworld Upgrades

- stable `RecipeDefinitionID` is the canonical recipe identity; Row Handle is an authoring reference only;
- categories use data-driven tags rather than a permanent Armor/Weapons/Other Switch;
- recipe definitions can specify outputs, ingredient definitions/tags, quantities, substitutions, tools, workstation, profession/skill, knowledge/unlock, time/work, utilities/fuel, legality and output-quality rules;
- crafting can consume from approved accessible carried/workstation/property/company containers rather than a single Player Blueprint array;
- UI displays material availability and missing reasons but never consumes ingredients or creates outputs itself;
- `RequestCraft` is server-authoritative and atomically reserves/consumes inputs and creates the legitimate persistent output ItemInstance(s);
- two players cannot spend the same final material stack simultaneously;
- long-running crafting uses jobs/timestamps/work units rather than permanent Tick;
- output can retain creator/crafter provenance and quality derived from recipe, inputs, tools/workstation and skill where designed;
- recipe browser supports search/filter/craftable-now/favorites/workstation/profession categories as scale grows;
- full keyboard/mouse, Xbox-style and PlayStation-style crafting navigation is required.

### Episode 36 Principle

> The recipe browser helps the player choose a production action. The server-authoritative crafting system owns ingredients, work, outputs and persistence.

---

# Current Modern RPG Additions From Episodes 28–36

`Equipment ItemInstance`
-> `Source-aware Stat Modifiers`
-> `Derived Character Stats`
-> `Event-driven Character Stat Panel`

`Item Definition Row Handle`
-> `Stable ItemDefinitionID`
-> `Persistent ItemInstanceID`

`Item/Equipment state changes`
-> `Event-driven UMG update`
-> `Reusable inventory/equipment style`

`Item Definition reference value + ItemInstance state + Vendor/Economy context`
-> `Authoritative Quote`
-> `GrimKoin/PromoKoin transaction`
-> `Tooltip/receipt presentation`

`Persistent Material ItemInstances`
-> `RecipeDefinitionID`
-> `Server ingredient reservation/consumption`
-> `Crafting work/station/profession rules`
-> `Persistent crafted output ItemInstance`

`Stable UI IDs / presentation snapshots`
-> `W_MW_PlayerInterface`
-> `Inventory / Crafting / Skills / Stats tabs`
-> `Controller-complete navigation`

---

# Playlist Continuation Rule

Future episodes continue in Part 5 until another safe continuation is needed. Parts 1–5 remain the canonical intake/audit trail for this Modern RPG playlist; detailed companion documents remain the implementation authority for established domains.