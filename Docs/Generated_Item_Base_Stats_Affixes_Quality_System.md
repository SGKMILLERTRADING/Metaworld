# Metaworld — Generated Item Base Stats, Affixes & Quality System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / deterministic-capable generation

## Canonical Principle

Crafted/equipment items can combine mandatory base functionality with generated secondary traits, but all generated results belong to the exact persistent `ItemInstanceID` and are rolled authoritatively once.

> Base stats make the item what it is. Generated affixes make this exact copy special. Rarity may shape the generation budget, but rarity alone does not define power, value or quality.

Related canon:

- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Item_Valuation_Vendor_Pricing_Trade_System.md`

---

# 1. Base Functional Stats

An Item Definition may define mandatory base functional properties that every legitimate instance of that definition needs.

Examples:

Weapon:
- base damage profile;
- attack/use speed envelope;
- reach/range class;
- weight/mass;
- durability rules;
- allowed damage types/capabilities.

Armor:
- base coverage;
- base protection profile;
- weight/mass;
- durability rules;
- mobility/thermal properties.

Tool:
- tool capability tags;
- work efficiency baseline;
- durability;
- weight.

These are not `random bonus stats` and should not disappear because an item rolled Common rarity.

---

# 2. Definition Base vs Instance Generated State

Canonical separation:

`ItemDefinitionID`
-> mandatory base stat templates / legal ranges / affix pools

`ItemInstanceID`
-> condition
-> quality score/tier
-> generated affix records
-> crafted provenance
-> modifications/upgrades
-> seed/generation record where retained

Two swords with the same ItemDefinitionID may therefore share the same basic function while having different generated secondary traits.

---

# 3. Generated Affix Record

Suggested conceptual record:

`S_MW_ItemGeneratedModifier`

Possible fields:

- AffixDefinitionID
- TargetStatID / capability
- Operation = Add / Multiply / special rule
- RolledValue
- Tier/grade
- Source = CraftGeneration / LootGeneration / Upgrade etc.
- generation seed/reference where retained
- visible/revealed state if identification systems exist later

Stable affix IDs / Gameplay Tags are preferred over one permanently closed enum.

Examples:

- `Affix.Weapon.CriticalChance`
- `Affix.Weapon.AttackSpeed`
- `Affix.Armor.PhysicalResistance`
- `Affix.Armor.FireResistance`
- `Affix.Tool.WorkEfficiency`

---

# 4. Context-Specific Affix Pools

Weapons, armor, tools and other item families use compatible affix pools.

Do not let every item roll every numeric stat merely because the generic Stats system contains it.

Example pool rules:

Weapon may roll:
- critical chance;
- handling/attack speed;
- damage-type modifier;
- durability efficiency;
- accuracy/recoil-related property where relevant.

Armor may roll:
- physical resistance;
- elemental resistance;
- mobility penalty reduction;
- durability bonus;
- thermal/weather protection.

Tool may roll:
- work efficiency;
- durability;
- precision/quality contribution.

Affix eligibility is data-driven through item-family/category/capability tags.

---

# 5. Rarity and Affix Budget

The tutorial ties rarities to a fixed number of random stats. That pattern is approved only as a configurable presentation/generation rule, not universal law.

Possible profile examples:

- Common: usually no optional affix or very small budget;
- Uncommon: small optional budget;
- Rare: larger budget;
- Epic: larger/stronger combination budget;
- Legendary: high budget or special authored possibilities.

But Metaworld may use:

- affix count range;
- total affix budget;
- tier ceiling;
- special-pool access;
- guaranteed/optional slots;
- handcrafted unique definitions.

Rarity does not overwrite base stats and does not automatically equal higher market value, better condition or creator prestige.

---

# 6. Crafting Skill / Quality Influence

Crafting proficiency can improve the **quality envelope** of a generated result, but it does not simply force every roll to maximum.

Possible inputs:

- recipe difficulty;
- crafter profession/skill proficiency;
- input material quality;
- workstation quality;
- tool quality/condition;
- workmanship outcome;
- recipe-specific limits;
- special training/specialization.

Recommended approach:

1. determine legal quality/affix envelope from recipe + definition;
2. calculate crafter/context quality influence;
3. roll/select the final result inside that envelope;
4. persist the exact result on the new ItemInstance.

A novice with exceptional materials may still produce something usable; a master using poor inputs is still limited by those inputs where the recipe says they matter.

---

# 7. Authoritative Random Generation

Generated stats are rolled by the server/authoritative crafting or loot service.

The client never submits the final random values.

For reproducibility/audit/debugging, Metaworld may retain a generation seed or use an authoritative `RandomStream`/equivalent deterministic stream when appropriate.

UE5.8 Random Streams can generate repeatable Blueprint random values from a seed, which is useful when deterministic regeneration/auditing is desired. The seed remains authoritative; clients do not choose it.

The output is rolled once and stored. Opening a tooltip, dropping the item, loading a save or re-equipping it must not reroll its affixes.

---

# 8. Duplicate Affix / Conflict Rules

Generation data defines whether affixes can:

- repeat;
- stack;
- conflict;
- require another affix;
- exclude a family;
- share a total budget.

Example:

Do not accidentally roll `Affix.AttackSpeed` four times unless the profile explicitly permits stacking duplicates.

Use weighted pools/selection policies where desired, but every final combination must pass the configured compatibility rules.

---

# 9. Base Stats in UI

Base/mandatory stats can be visually distinguished from generated bonuses, but **blue color alone is not sufficient**.

Possible presentation:

`BASE`
- Damage 25
- Weight 3.0 kg

`GENERATED`
- +4% Critical Chance
- +6 Durability

Use label/icon/grouping plus optional color.

The tooltip/crafting preview consumes presentation snapshots; widgets do not recalculate generation.

---

# 10. Crafting Preview vs Final Result

Before crafting, the UI may show:

- guaranteed base stats;
- possible affix pool;
- possible quality range;
- rarity/quality expectations;
- material/tool/proficiency influences.

It must not claim a random final value before the server has generated the actual output.

After success, the created ItemInstance receives and displays the actual persisted generated result.

---

# 11. Economy / Provenance

Generated quality and affixes may influence vendor/player valuation, but actual price still belongs to the contextual economy quote system.

The ItemInstance keeps:

- crafter identity where appropriate;
- recipe/source;
- generated quality/affixes;
- material provenance where retained;
- condition/durability.

This allows player-crafted signature items without losing the stable definition/instance architecture.

---

# 12. Multiplayer / Persistence

Persist generated modifier records on the ItemInstance or an authoritative compact generation record sufficient to reconstruct them exactly.

Replication sends the generated stats needed by authorized viewers/equipment/combat systems.

No client can reroll by reconnecting, reopening inventory or transferring the item.

Item transfer, trade, loot, death, evidence and save/load preserve the same generated stats.

---

# 13. Performance

- generation happens when a new instance is legitimately created/modified, not every frame;
- effective item stats are cached/recalculated only when base/condition/modifiers change;
- unloaded items store data only;
- tooltip builds from snapshots on focus/change;
- weighted pools/affix definitions are data assets/tables, not live Actors.

---

# 14. Python / Editor Validation

Future validation can detect:

- affix IDs targeting undefined stats;
- impossible min/max ranges;
- incompatible item-family pools;
- duplicate affixes when duplicates are forbidden;
- rarity profiles with impossible budgets;
- generated ranges exceeding hard gameplay caps;
- item definitions missing mandatory base functional stats;
- base and random modifiers accidentally double-counting the same intended property.

---

# 15. Acceptance Tests

1. Every weapon/armor instance retains mandatory base functionality regardless of rarity.
2. Generated affixes are stored on the exact ItemInstance and survive save/load/drop/trade.
3. Tooltip open/close never rerolls an item.
4. Client cannot choose final generated values.
5. Weapon cannot roll an armor-only affix unless explicitly permitted.
6. Rarity profile can alter affix budget without rewriting generation logic.
7. Crafting proficiency influences legal result quality according to data, but never bypasses recipe/material caps.
8. Duplicate/conflicting affixes follow configured policies.
9. Base and generated stats are both accessible without color-only distinction.
10. Vendor valuation may react to generated quality but remains contextual.
11. Deterministic seed/stream, if used, reproduces the same authoritative result for audit/debug purposes.
12. Repeated equip/unequip applies the generated ItemInstance modifiers exactly once through the existing source-aware modifier system.

## Core Rule

> A Metaworld item has stable base identity and function, while this exact persistent copy may gain authored or generated individuality. Randomness happens once under server authority and becomes part of the item's history—not a UI reroll.