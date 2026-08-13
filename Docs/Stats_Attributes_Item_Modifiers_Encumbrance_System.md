# Metaworld — Stats, Attributes, Item Modifiers & Encumbrance System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / modular / server-authoritative where gameplay-relevant

## Canonical Principle

Metaworld needs reusable numeric-stat infrastructure, but it does **not** collapse every progression, need, profession, reputation, public rank and currency value into one generic RPG stat map.

> Shared math is reusable; world meaning stays in the correct system.

Related canon:

- Master Roadmap Core Player Resources
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`

---

# 1. Layered Stat Model

A reusable stat/attribute component is approved where multiple Actors genuinely share the same numeric behavior.

Recommended concepts:

`BPC_MW_Attributes` / `BPC_MW_Stats` for reusable attribute math

Possible stat record:

- `StatID` / Gameplay Tag
- BaseValue
- CurrentValue where the stat is consumable/current-state based
- BaseMaxValue where applicable
- AdditiveModifiers
- MultiplicativeModifiers
- Final/DerivedValue
- Min/Max clamps
- revision/timestamp
- source references for active modifiers

Examples of suitable reusable stats:

- Health Max
- Stamina Max
- Mana Max
- Carry Capacity
- movement-related derived attributes where appropriate
- combat damage/protection modifiers
- attack speed / use speed where explicitly supported
- temporary resistance/bonus values

But dedicated systems remain authoritative for their own meanings:

- Hunger/Thirst/Fatigue live in Needs;
- skills/professions live in progression/profession systems;
- police/civic rank lives in career/governance systems;
- reputation/relationships live in reputation systems;
- GrimKoin/PromoKoin live in currency ledger/wallet/banking;
- item condition/durability lives on the ItemInstance;
- ownership/evidence/legal status stays in item/world-law systems.

A common math helper may be reused, but those systems are not reduced to anonymous numbers in one character Map.

---

# 2. Stable Stat IDs, Not Closed Forever Enum

A small enum is acceptable for a tiny fixed prototype, but Metaworld should use stable IDs/Gameplay Tags or Data Assets for a growing stat catalog.

Examples:

- `Stat.Vitals.Health.Max`
- `Stat.Vitals.Stamina.Max`
- `Stat.Vitals.Mana.Max`
- `Stat.Carry.CapacityMass`
- `Stat.Combat.MeleeDamage`
- `Stat.Combat.ArmorPhysical`
- `Stat.Combat.AttackSpeed`
- `Stat.Resistance.Fire`

Central stat definitions may carry:

- display name/localization;
- units;
- formatting/precision;
- minimum/maximum policy;
- whether current/max semantics apply;
- tooltip/category grouping;
- comparison direction (`higher is better`, `lower is better`, neutral/contextual);
- presentation icon/style.

---

# 3. Current vs Maximum / Clamp Rules

For resources such as Health/Stamina/Mana:

- Current is clamped to allowed range;
- Max derives from base + approved modifiers;
- if Max falls below Current, Current is reduced to valid Max unless a system explicitly defines another transition rule;
- increasing Max does not automatically heal/refill Current unless the source effect explicitly says so.

Example:

Health Current = 80
Health Max = 100
Equipment bonus +20 Max Health
-> Max becomes 120
-> Current remains 80 unless that modifier also grants healing.

Removing the item later:

Current = 110
Old Max = 120
New Max = 100
-> Current clamps to 100.

This avoids hidden free healing and stat duplication.

---

# 4. Modifier Sources

Stats may be affected by sources such as:

- equipped ItemInstance;
- armor/weapon definition + instance condition;
- injuries/status effects;
- temporary buffs/debuffs;
- supernatural abilities;
- profession/skill bonuses where the profession system explicitly grants them;
- environmental conditions;
- drugs/food/consumables where implemented;
- difficulty/world-event effects only when designed.

Each active modifier should retain a source identity when practical.

Example modifier record:

- ModifierID
- SourceType
- SourceID / ItemInstanceID / EffectID
- TargetStatID
- Operation = Add / Multiply / Override where explicitly permitted
- Value
- duration/expiry if temporary
- stacking policy

Do not repeatedly bake bonuses directly into BaseValue, because equip/unequip and temporary effects then become impossible to reverse safely.

---

# 5. Item Stats / Modifiers

Item Definitions may define base modifier templates; ItemInstances may add condition/quality/customization state that changes the effective result.

Examples:

Weapon definition:

- base damage
- attack/use speed
- reach/range category
- weight/mass
- durability rules

Armor definition:

- physical protection
- damage-type resistances
- mobility/encumbrance influence
- thermal/weather properties
- mass

ItemInstance modifies this through:

- condition/durability;
- quality;
- upgrade/modification state;
- creator-crafted properties where allowed;
- magical/supernatural effects;
- damage state.

Rarity alone does not automatically determine the numeric stats.

---

# 6. Item Stat UI / Comparison

The tutorial's dynamic stat-line widget is approved as presentation.

Recommended flow:

`Focused ItemInstanceID`
-> resolve authorized effective item-stat snapshot
-> compare against current equipped/reference item where applicable
-> create/update only relevant stat rows

Display may include:

- stat display name;
- value + units;
- optional current/equipped comparison delta;
- source/condition notes when useful;
- positive/negative indicator;
- accessibility icon/text.

Do not rely only on green/red color.

A comparison can use:

- `+5 Armor`
- `-0.2 Attack Speed`
- arrows/icons
- text labels

with color as a secondary cue.

Also note that positive/negative depends on the stat's comparison direction. Lower item weight may be beneficial even though its numerical delta is negative; slower cooldown may be worse even if a raw number is larger. The Stat Definition should tell UI how to interpret the delta.

Avoid constructing rich-text strings every frame. Build/update presentation when item/stat state changes.

---

# 7. Carry Mass / Capacity / Encumbrance

The tutorial's weight concept is approved but corrected substantially.

Metaworld separates:

## Container Capacity
What physically fits inside a specific inventory/container.

Possible constraints:

- slots;
- mass capacity;
- volume;
- dimensions;
- compartments;
- allowed item types.

## Character Carried Load
The mass the character is physically carrying/wearing.

Possible sources:

- items in carried pockets/inventory;
- backpack contents;
- equipped weapons;
- equipped armor/clothing where meaningful;
- carried containers and their contents;
- hand-carried world object/person where applicable.

## Carry Capacity
The character's supported physical load threshold, derived from approved character/skill/equipment effects.

## Encumbrance
The gameplay consequences of carried load relative to capacity.

### Critical Rule

> Equipping an item does not remove its mass from carried load.

A 12 kg armor chest still weighs 12 kg when worn.

Equipping may move the item between container/equipment locations, but the character's total carried mass still includes it.

---

# 8. Encumbrance Tiers

Do not use one universal `over capacity -> Max Walk Speed / 2` rule.

Use data-driven thresholds/curves so penalties grow predictably.

Possible example tiers (final values tuned by playtest):

- Comfortable: below normal capacity threshold
- Loaded: modest stamina/mobility cost
- Encumbered: stronger sprint/acceleration/stamina penalties
- Heavily Encumbered: severe movement/interaction restrictions
- Immobile/Unsafe Load: cannot normally move with the load; must drop, drag, use vehicle/cart/team lift, etc.

Potential effects:

- walk/run/sprint speed;
- acceleration/deceleration;
- stamina drain/recovery;
- jump/vault/climb capability;
- fall/landing risk;
- combat dodge/attack recovery where appropriate;
- swimming risk;
- carry/drag animation profile.

Do not abruptly halve movement at one invisible threshold unless playtesting specifically proves that feel is better.

---

# 9. Encumbrance Recalculation

Carried load should update from authoritative inventory/equipment state changes, not from permanent Tick.

Recalculate when:

- pickup succeeds;
- drop succeeds;
- transfer between carried/non-carried containers succeeds;
- equip/unequip succeeds;
- stack quantity changes;
- item mass changes due to crafting/consumption/damage where supported;
- character capacity modifier changes;
- backpack/container is equipped/removed;
- carried character/object state changes.

Cache the aggregate carried mass and update incrementally where practical.

---

# 10. Items / Enemies / Other Actors Using Stats

Reusable stat math may be attached to enemies or destructible/useable objects where it is genuinely appropriate.

Examples:

- player/NPC Health;
- vehicle/object durability if the object's own damage model maps cleanly;
- shield energy;
- mana-like supernatural resource.

But do not add a generic StatsComponent to every item merely because the tutorial can. Most ItemInstance data such as weight, condition, value, rarity and ownership belongs directly to Item Definition/Instance systems, not a constantly active Actor Component on every inventory item.

Unloaded inventory items are data records and do not need live Actor Components.

---

# 11. Multiplayer / Persistence

Authoritative gameplay stats and modifiers are server-owned where they affect shared gameplay.

Persist compact base/permanent state and persistent modifier sources.

Temporary effects persist only according to their system rules/timestamps.

Clients receive only the stat state needed for local UI/prediction/presentation.

Do not trust client-submitted final Health, damage, Carry Capacity or item modifier totals.

Derived totals should be reproducible from authoritative base data + modifier sources.

---

# 12. Performance

- event-driven stat recalculation;
- no per-stat Tick;
- cache derived totals until a source changes;
- batch recomputation after multiple equipment changes when useful;
- use data records for unloaded items/NPCs;
- UI updates only when focused stat/item or underlying value changes;
- avoid hard-reference chains from generic stat definitions to large assets.

---

# 13. Stat Semantic Types

Do not force every numeric stat into a `Current / Max` pair.

Recommended semantic types include:

## Resource
Examples: Health, Stamina, Mana.

Presentation:

`Current / Max`

Example:

`Health 82 / 120`

## Scalar / Derived Attribute
Examples: Armor, Attack Speed, Damage, Carry Capacity, Resistance.

Presentation:

one effective/derived value with units where appropriate.

Examples:

- `Armor 46`
- `Attack Speed 1.15 /s`
- `Carry Capacity 42 kg`

A scalar stat does not use a fake `Max` merely because the tutorial structure only has Current/Max fields.

The Stat Definition declares its semantic/display mode, so UI does not need name-based exceptions such as `if Armor then hide Max`.

## Bounded Scalar
Some stats may have a designed clamp/range without being a consumable Current/Max resource.

Example:

`Resistance.Fire = 25%` constrained by the system's legal range.

The clamp is implementation policy, not a second visible Max resource.

---

# 14. Equip / Unequip Modifier Transaction

The tutorial's `Change Stats(Add/Remove)` intent is approved, but Metaworld does not implement reversal by multiplying the same arbitrary value by `-1` and mutating final stats.

Canonical flow:

`RequestEquip(ItemInstanceID)`
-> authoritative equipment transaction succeeds
-> register modifier records whose `SourceID = ItemInstanceID`
-> recalculate affected derived stats once
-> emit `OnStatsChanged(AffectedStatIDs)`
-> UI refreshes relevant rows

Unequip:

`RequestUnequip(ItemInstanceID)`
-> authoritative equipment transaction succeeds
-> remove modifiers whose `SourceID = ItemInstanceID`
-> recalculate affected derived stats once
-> emit stat-change event

This is safer because:

- the exact source is traceable;
- repeated equip/unequip cannot drift base values;
- condition or item upgrades can change effective modifiers cleanly;
- different operations (add/multiply/override) remain reversible;
- one item can affect several stats without baking permanent changes.

---

# 15. Character Stats Display

A character stat panel inside inventory/character UI is approved.

Possible initial display:

- Health Current / Max
- Mana Current / Max
- Stamina Current / Max
- Damage / active combat profile summary
- Attack Speed
- Armor / protection summary
- Carry Load / Carry Capacity
- Encumbrance state

But the panel is data-driven rather than permanently hardcoded to exactly six fields.

Recommended flow:

`BPC_MW_Stats / relevant dedicated systems`
-> build authorized CharacterStatsPresentationSnapshot
-> UI updates on open + `OnStatsChanged` / equipment / resource-change events

Formatting comes from the Stat Definition:

- display name;
- icon;
- units;
- decimal precision;
- Resource vs Scalar presentation;
- comparison direction;
- category/order.

Do not blindly convert all floats to integers. Health may display as whole numbers while Attack Speed, movement multipliers, percentages or other values may require decimals.

Icons may have tooltips/detail labels, but core stat identification must also work with keyboard/controller focus and accessibility settings.

---

# 16. Acceptance Tests

1. Current Health clamps when Max Health decreases.
2. Increasing Max Health does not automatically heal unless defined.
3. Equip bonus applies once and removes cleanly on unequip.
4. Repeated equip/unequip never permanently modifies BaseValue.
5. Two modifier sources stack according to configured policy.
6. Item condition can alter effective item stats where designed.
7. Rarity does not automatically overwrite item stats.
8. Tooltip shows only non-zero/relevant stats.
9. Controller and mouse receive identical stat detail/comparison information.
10. Positive/negative comparison does not rely on color alone.
11. Equipped armor remains included in carried mass.
12. Moving an item from backpack to equipped slot does not falsely reduce total carried load.
13. Dropping an item reduces carried load only after server transaction succeeds.
14. Encumbrance updates after pickup/drop/equip without Tick.
15. Encumbrance penalties are data-driven and restore correctly when load decreases.
16. Unloaded inventory items require no live StatsComponent.
17. Multiplayer clients cannot set authoritative final stat totals.
18. Save/load reconstructs persistent base stats/modifier sources correctly.
19. Scalar Armor displays one derived value rather than fake Current/Max semantics.
20. Health/Stamina/Mana display Current/Max correctly.
21. Equipping one ItemInstance registers its modifiers once; unequip removes exactly those source modifiers.
22. Attack Speed preserves configured decimal precision.
23. Character stat UI updates from change events rather than per-frame binding.

## Core Rule

> Metaworld reuses stat mathematics without turning the whole living world into one anonymous RPG stat map. Meaning stays with the owning system; modifiers are traceable; scalar stats are not forced into fake Current/Max semantics; encumbrance respects actual carried mass.