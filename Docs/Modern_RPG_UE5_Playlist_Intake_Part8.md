# Metaworld — Modern RPG UE5 Playlist Intake — Part 8

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part7.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

**Counting Note:** The Sprint/Stamina/Regeneration tutorial was supplied twice in the intake message and is counted once. This Part contains 10 unique episodes, Episodes 53–62.

---

# Episode 53 — Sprint, Stamina Drain, Regeneration & HUD Events

**Classification:** UPGRADE — APPROVED / MOVEMENT-EXERTION FOUNDATION.

**Phase Ownership:** Movement + Stats/Vitals + Encumbrance + HUD + Controller.

Detailed companion:

`Docs/Movement_Sprint_Stamina_Regeneration_Exertion_System.md`

## Approved Tutorial Intent

- use event-driven communication between Stats/Vitals and HUD;
- Sprint requires movement, sufficient Stamina and valid movement state;
- Sprint consumes Stamina while active;
- Stamina can regenerate after a configurable delay;
- Stamina HUD can appear while relevant and fade after recovery;
- timers are preferred over permanent Tick for bounded drain/regen behavior.

## Metaworld Upgrades

- hardcoded Shift becomes Enhanced Input `IA_MW_Sprint` with KBM/Xbox-style/PlayStation-style mappings;
- Sprint input is intent; authoritative movement/Stamina state decides eligibility;
- eligibility includes Encumbrance tier, injuries/status effects, Needs/Fatigue, equipment/action/world restrictions and future supernatural movement rules where relevant;
- Sprint speed is part of a derived movement profile, not one direct `Set Max Walk Speed` shortcut;
- releasing Sprint recomputes the correct non-sprint movement state rather than resetting to one tutorial default speed;
- Stamina drain/regeneration are bounded timer/timestamp/event processes, not permanent Tick;
- each resource owns its regeneration policy—Health/Mana do not automatically copy Stamina rules;
- HUD receives resource-change events and never owns the Stamina calculation;
- Stamina visibility/fade is contextual presentation with accessibility option to keep visible.

### Episode 53 Principle

> Sprint is a state of the whole character. Stamina, load, injuries and other modifiers decide whether it can continue; the HUD only presents the authoritative result.

---

# Episode 54 — Delayed / Double Health Bar

**Classification:** UPGRADE — APPROVED PRESENTATION.

**Phase Ownership:** Player HUD + Health presentation + Performance.

Detailed companions:

- `Docs/Movement_Sprint_Stamina_Regeneration_Exertion_System.md`
- `Docs/Player_HUD_Vitals_Resources_System.md`

## Approved Tutorial Intent

- primary Health bar updates immediately;
- a trailing/white Health bar follows after a short delay to visualize recent damage/healing;
- use bounded timer/animation behavior rather than permanent Event Tick;
- account for Max Health changes from equipment/stat modifiers.

## Metaworld Upgrades

- trailing Health is strictly local presentation, not a second gameplay Health value;
- authoritative Health remains one Current/Max resource;
- trailing bar cannot absorb damage, heal or replicate as gameplay truth;
- on Health change, primary updates immediately and trailing presentation converges to the current normalized Health;
- Max Health changes safely rebase both visual percentages;
- timer/animation runs only while convergence is required;
- accessibility/reduced-motion settings may simplify or disable trailing animation.

### Episode 54 Principle

> The delayed Health bar visualizes what just happened to Health; it never becomes another Health resource.

---

# Episode 55 — Regeneration Efficiency, Encumbrance Movement & HUD Indicator Fixes

**Classification:** LOCKED + UPGRADE MAINTENANCE.

**Phase Ownership:** Movement/Exertion + Stats/Vitals + Encumbrance + HUD.

Detailed companion:

`Docs/Movement_Sprint_Stamina_Regeneration_Exertion_System.md`

## Approved Tutorial Intent

- only resources with active/nonzero regeneration should schedule regeneration work;
- Stamina/HUD updates should use reusable event logic;
- Sprint ending while overweight/encumbered must not restore normal unrestricted movement;
- HUD can show an overweight/encumbrance indicator.

## Metaworld Upgrades

- no BeginPlay loop starts meaningless regeneration timers for every stat;
- each Resource Definition schedules work only when RegenEnabled/rate/blocker rules justify it;
- Encumbrance remains tier/data-driven, not a single overweight Boolean;
- Sprint stop recomputes the derived movement profile including Encumbrance, injuries, Needs, status effects and equipment;
- HUD reads the canonical carried-load/Encumbrance presentation state rather than recalculating weight itself;
- encumbrance presentation uses icon/text/tier information, not color alone.

### Episode 55 Principle

> Regeneration and movement only do work when their state requires it, and movement never forgets the character's actual load when Sprint ends.

---

# Episode 56 — Buff / Debuff / Condition Component

**Classification:** UPGRADE — APPROVED / NEW STATUS-EFFECT DOMAIN.

**Phase Ownership:** Status Effects + Stats/Vitals + Combat + NPCs + Persistence.

Detailed companion:

`Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`

## Approved Tutorial Intent

- reusable modular condition system can affect players and enemies;
- conditions can have duration, icon and gameplay behavior;
- examples include Health Regeneration, Burning and Fortify;
- duplicate applications need explicit handling;
- temporary conditions must cleanly remove their effects when finished.

## Metaworld Upgrades

- recommended manager `BPC_MW_StatusEffects` owns active effect records;
- do not spawn one independent Actor Component per condition as the default scalable design;
- stable `ConditionDefinitionID`/Gameplay Tag replaces a permanently closed condition enum;
- active `S_MW_ActiveCondition` records keep source, target, stack, potency, timestamps and revision;
- duplicate behavior is data-driven: Reject, Refresh, Extend, Stack, ReplaceIfStronger, IndependentBySource, etc.;
- duration/periodic pulses use timers/timestamps rather than per-condition Event Tick;
- temporary stat effects use source-aware modifiers and remove by ActiveConditionID;
- server owns gameplay-relevant application/stack/pulse/expiration.

### Episode 56 Principle

> Conditions are managed effect records with explicit stacking and lifetime rules, not a collection of mini-components independently ticking themselves to death.

---

# Episode 57 — Buff / Debuff HUD, Interfaces & Radial Duration UI

**Classification:** UPGRADE — APPROVED PRESENTATION.

**Phase Ownership:** Status Effects + HUD + Accessibility.

Detailed companion:

`Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`

## Approved Tutorial Intent

- HUD can show active condition icons;
- one conditions box can organize many effect entries;
- remaining duration can use a radial progress presentation;
- positive/negative effects can be visually distinguished;
- reusable interface/event communication is appropriate.

## Metaworld Upgrades

- suggested `W_MW_ConditionsBox` + `W_MW_ConditionIcon` are presentation only;
- UI receives add/remove/refresh/stack/expiration events from status-effect state;
- radial meter derives from authoritative ExpiresAt/remaining duration and resynchronizes after reconnect/drift;
- UI does not remove an effect merely because its local radial animation reaches zero;
- condition meaning is not color-only—icon/name/type/stack/time are available;
- timers/animation run only for visible timed effects;
- player/NPC status-effect gameplay can share one system while local HUD remains viewer-specific.

### Episode 57 Principle

> The condition HUD visualizes authoritative active effects and their remaining time; it does not own their duration or gameplay consequence.

---

# Episode 58 — Potions / Items Applying Conditions

**Classification:** UPGRADE — APPROVED ITEM / STATUS-EFFECT INTEGRATION.

**Phase Ownership:** Item DNA + Consumables + Status Effects + Tooltips.

Detailed companions:

- `Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`

## Approved Tutorial Intent

- consumables can apply one or more conditions;
- item tooltip can explain those effects;
- examples include Health Regeneration, Burning and Fortify;
- condition data should be encapsulated/refactored rather than exposed as brittle mutable maps.

## Metaworld Upgrades

- Item Definition references condition-application entries by stable ConditionDefinitionID;
- item-use transaction is authoritative: validate -> consume/decrement item -> apply approved effect(s) -> persist/replicate;
- tooltip receives presentation data (effect name/description/duration/magnitude where known) and does not own condition logic;
- an ItemInstance/stack preserves any effect-relevant metadata required for stack compatibility/provenance;
- different potion potency/conditions cannot merge if stacking would erase meaningful state;
- conditions can target stats/resources through canonical source-aware/status-effect contracts.

### Episode 58 Principle

> A potion is a persistent item whose successful use requests defined effects; the status-effect system applies them, and the tooltip only explains what the item can do.

---

# Episode 59 — Condition Data Table Migration

**Classification:** UPGRADE — APPROVED DATA AUTHORING CLEANUP.

**Phase Ownership:** Status Effects + Blueprint-first data architecture + UI contracts.

Detailed companion:

`Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`

## Approved Tutorial Intent

- move condition definitions from a fragile Blueprint Map into data-driven table entries;
- add localized display names/descriptions;
- reuse the same definition data for gameplay and tooltip presentation;
- consistent IDs prevent lookup mistakes.

## Metaworld Upgrades

- Data Table is an approved Blueprint-first authoring source;
- stable `ConditionDefinitionID` remains explicit canonical identity;
- do not rely permanently on `Enum -> String -> Name -> DataTable Row` conversion;
- Row Name may mirror stable ID by convention, but display name uses localized Text independently;
- gameplay/UI resolve definitions through stable IDs/handles and cache safe presentation snapshots;
- Python Editor validation can audit missing/duplicate condition IDs, invalid modifier targets, durations and assets;
- future Data Asset/Data Registry/database migration can preserve ConditionDefinitionID.

### Episode 59 Principle

> Condition definitions belong in stable data. Row names and enums may help authoring, but gameplay identity must survive schema and UI changes.

---

# Episode 60 — Health Regeneration Clamp + Condition-Aware Stacking Fix

**Classification:** LOCKED / BUGFIX — APPROVED CANONICAL SAFETY RULES.

**Phase Ownership:** Stats/Vitals + Status Effects + Item Stacking.

Detailed companions:

- `Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`

## Approved Tutorial Intent

- Current Health must never exceed Max Health through normal regeneration;
- new item fields such as condition/effect data must not disappear when stacks merge/split/pickup/remove;
- schema expansion should not silently corrupt item state.

## Metaworld Upgrades

- normal bounded resource rule remains `0 <= Current <= EffectiveMax`;
- Health Regeneration at full Health cannot create an over-max value that makes later Burning/Damage appear ineffective;
- stack compatibility checks all persistent/effect-relevant state, not merely ItemDefinitionID/class;
- potions with different condition payload, potency, expiry/quality/provenance or other meaningful state do not merge if information would be lost;
- item transfers/stack operations use stable ItemInstance/lot data and purpose-built transaction code, avoiding manual struct-pin omissions;
- Python/editor/schema validation should catch newly added stack-significant fields that are not included in compatibility/serialization policies.

### Episode 60 Principle

> Resource clamps preserve combat correctness, and stacking may never erase gameplay state just because a new struct field was added later.

---

# Episode 61 — Bow Item / Two-Handed Ranged Equipment

**Classification:** UPGRADE — APPROVED / RANGED-WEAPON FOUNDATION.

**Phase Ownership:** Equipment + Combat + Animation + Item DNA + Stats.

Detailed companion:

`Docs/Ranged_Weapons_Bow_Ammo_Quiver_Container_System.md`

## Approved Tutorial Intent

- create a persistent bow item with mesh/icon/stats;
- treat bow as Two-Handed equipment;
- resolve Off-Hand conflicts;
- attach bow through an authored character socket/profile;
- expose ranged-weapon-specific damage/attack/critical data.

## Metaworld Upgrades

- bow remains an ItemDefinition/ItemInstance using the canonical Equipment system;
- Two-Handed conflict is data-driven and never silently destroys Off-Hand equipment;
- attachment uses semantic socket/AttachmentProfile data rather than scattered Player Blueprint transforms;
- bow's effective combat contribution combines Definition + exact ItemInstance condition/quality/upgrades/affixes + character skill + ammunition + target/world rules;
- avoid double-counting damage where both bow and arrow contribute;
- hardcoded unique child Blueprint is optional only for genuinely unique bow behavior;
- all equip/unequip/attachment actions support KBM/Xbox-style/PlayStation-style controls.

### Episode 61 Principle

> A bow is persistent two-handed equipment whose combat result comes from the full weapon/ammunition/character state—not merely a mesh with three numbers in a table.

---

# Episode 62 — Quiver / Arrow Container System

**Classification:** UPGRADE — APPROVED WITH CONTAINER-ARCHITECTURE CORRECTION.

**Phase Ownership:** Inventory/Containers + Ammunition + Ranged Combat + UI.

Detailed companion:

`Docs/Ranged_Weapons_Bow_Ammo_Quiver_Container_System.md`

## Approved Tutorial Intent

- separate arrow organization from the general backpack UI;
- manage arrow quantities clearly;
- route compatible arrow items to the appropriate storage;
- pickup/remove/drop/tooltip flows must all understand ammunition storage;
- Widget Switcher/tab presentation is acceptable.

## Metaworld Upgrades

- a Quiver is a specialized persistent `ContainerID`, often itself owned by an equipable Quiver ItemInstance;
- allowed tags/capacity define what ammunition it can store;
- arrows remain normal persistent ItemInstances/stacks with mass, ownership, provenance, condition/quality and effect metadata;
- switching Backpack/Quiver tabs changes only presentation, not item authority;
- reject duplicated `IsArrow` macros throughout every inventory function;
- centralized item tags + container compatibility/auto-route policy resolve legal destination;
- arrow pickup can route Quiver -> other ammo container -> general inventory -> reject according to capacity/policy;
- moving arrows between backpack/quiver does not remove their weight from Carried Load;
- firing consumes compatible ammunition server-authoritatively;
- in-flight projectile is lightweight combat representation; recoverable arrow world item is created only according to definition/result policy;
- special arrows can apply canonical Conditions on valid impact through the status-effect system;
- no global inventory scan every frame for ammo; update cached accessible ammo state from container deltas.

### Episode 62 Principle

> The quiver organizes and quick-accesses real arrow items; it is a specialized container, not a second inventory system, and firing consumes those arrows under the same authoritative item rules as the rest of Metaworld.

---

# Current Modern RPG Additions From Episodes 53–62

`IA_MW_Sprint`
-> `Derived Movement Eligibility/Profile`
-> `Authoritative Stamina Drain`
-> `Regen Delay / Policy`
-> `Resource Events`
-> `Contextual HUD + Trailing Health Presentation`

`ConditionDefinitionID`
-> `BPC_MW_StatusEffects`
-> `ActiveCondition Records`
-> `Stack/Refresh/Duration Policies`
-> `Stats/Vitals/Movement Effects`
-> `Condition HUD / Tooltips`

`Bow ItemInstance`
-> `Two-Handed Equipment`
-> `Quiver ContainerID`
-> `Arrow ItemInstances/Stacks`
-> `Authoritative Ammo Resolution/Consumption`
-> `Projectile / Recoverable Arrow Result`

---

# Playlist Continuation Rule

Future episodes continue in Part 8 until another safe continuation is needed. Parts 1–8 remain the canonical intake/audit trail for this Modern RPG playlist; detailed companion documents remain implementation authority for established domains.