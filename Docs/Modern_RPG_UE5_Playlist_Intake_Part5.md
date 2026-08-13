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

# Current Modern RPG Additions From Episodes 28–32

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

---

# Playlist Continuation Rule

Future episodes continue in Part 5 until another safe continuation is needed. Parts 1–5 remain the canonical intake/audit trail for this Modern RPG playlist; detailed companion documents remain the implementation authority for established domains.