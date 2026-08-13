# Metaworld — Status Effects, Conditions, Buffs & Debuffs System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / data-driven / event-driven

## Canonical Principle

A condition is an authoritative gameplay effect applied to a character or other valid target for a defined duration/state. Conditions modify existing systems through traceable effect records; they do not each become isolated mini-gameplay components running permanent Tick.

> One status-effect manager owns active effect state. Individual conditions are data/records with explicit stacking, duration, modifier and gameplay rules.

Related canon:

- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Player_HUD_Vitals_Resources_System.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`

---

# 1. Status Effect Manager

Recommended component:

`BPC_MW_StatusEffects`

Possible targets:

- player character;
- NPC/enemy;
- creature;
- other Actors only where the effect contract genuinely applies.

Responsibilities:

- validate/apply/remove effects;
- own active-effect records;
- enforce stacking/refresh policies;
- schedule periodic effect pulses/timers;
- register/remove source-aware stat modifiers;
- persist long-lived effects where required;
- replicate relevant effect state;
- emit UI/presentation events.

Do not spawn one full Actor Component per condition as the default scalable runtime architecture.

---

# 2. Stable Condition Definition

Recommended identity:

`ConditionDefinitionID` / Gameplay Tag

Examples:

- `Condition.Buff.HealthRegeneration`
- `Condition.Debuff.Burning`
- `Condition.Buff.FortifyArmor`
- `Condition.Debuff.Poison`
- `Condition.Debuff.Bleeding`
- `Condition.State.Stunned`

A Data Table Row Handle or Data Asset may author the definition, but stable ConditionDefinitionID remains the gameplay identity.

Do not depend on `Enum -> String -> RowName` conversion as the permanent lookup contract.

---

# 3. Condition Definition Data

Possible fields:

- ConditionDefinitionID
- display name / localized description
- icon/style profile
- category/tags
- duration policy
- default duration
- periodic interval where applicable
- stacking policy
- maximum stacks
- refresh policy
- stat modifier templates
- periodic resource/damage/heal actions
- movement/action restrictions
- dispel/cure tags
- immunity/resistance requirements
- source requirements
- persistence policy
- visibility/knowledge policy
- audiovisual presentation references

Definitions are data-driven rather than hardcoded Switch graphs.

---

# 4. Active Condition Instance

Suggested record:

`S_MW_ActiveCondition`

Possible fields:

- ActiveConditionID
- ConditionDefinitionID
- TargetCharacterID / target identity
- SourceType
- SourceID / ItemInstanceID / CharacterID / EnvironmentID
- AppliedAt
- ExpiresAt or remaining-duration state
- StackCount
- potency/rolled magnitude where required
- periodic-next-pulse timestamp
- revision
- dispel/removed reason

This lets multiple sources of the same effect be resolved deliberately instead of relying on whether one dynamically spawned component exists.

---

# 5. Stacking / Duplicate Policies

Do not universally say `if already active, reset timer`.

Each Condition Definition chooses a policy such as:

- RejectDuplicate
- RefreshDuration
- ExtendDuration
- IncreaseStacks
- ReplaceIfStronger
- KeepStrongest
- IndependentBySource
- IndependentInstances

Examples:

- a simple Fortify potion may refresh duration;
- Burning may stack intensity up to a cap;
- two different poison sources may remain independently attributable;
- a stronger medical buff may replace a weaker version.

The manager applies the configured policy authoritatively.

---

# 6. Duration / Timers

Condition duration uses explicit timer/timestamp state.

No condition needs permanent Tick only to ask `has my duration ended?`.

Possible flow:

`ApplyCondition`
-> compute expiration / pulse schedule
-> register modifiers/effects
-> schedule only required expiration/pulse work
-> on expiration revalidate/remove

Periodic effects such as Burning can use bounded scheduled pulses rather than per-frame damage.

Long/persistent effects may store timestamps so save/load/reconnect can reconstruct remaining duration correctly.

---

# 7. Stat Modifiers

Conditions use the existing source-aware modifier architecture.

Example Fortify:

`Source = ActiveConditionID #C184`
-> `Stat.Combat.ArmorPhysical +20`

On removal:

remove modifiers whose SourceID = ActiveConditionID #C184.

Do not bake temporary condition bonuses permanently into BaseValue.

---

# 8. Periodic Effects

Examples:

Health Regeneration:
- periodic heal or resource-regeneration modifier according to definition;
- clamps to legal Max Health.

Burning:
- periodic authoritative damage;
- can interact with armor/resistance/environment rules;
- may produce evidence/fire/world effects where appropriate.

Poison/Bleeding:
- periodic damage or other effects according to definition.

Periodic scheduling stops immediately when the condition ends/is cured/target dies according to policy.

---

# 9. Resource Clamp Safety

Conditions cannot push bounded Current resources outside legal range unless the specific system deliberately supports an overflow mechanic.

Normal Health rule:

`0 <= CurrentHealth <= EffectiveMaxHealth`

A regeneration effect at full Health cannot set Health above Max and accidentally make later Burning/Damage appear ineffective.

---

# 10. Item / Potion Integration

Consumable Item Definitions may reference one or more condition-application entries.

Suggested conceptual entry:

- ConditionDefinitionID
- application chance where intentionally designed
- magnitude/potency profile
- duration override where allowed
- target rules

Item use flow:

`RequestUseItem(ItemInstanceID)`
-> server validates item/target/use legality
-> consume/decrement item according to Item Definition policy
-> apply approved conditions through `BPC_MW_StatusEffects`
-> persist/replicate result
-> update inventory/HUD/tooltip.

The Item Info struct does not need to duplicate entire mutable condition definitions.

---

# 11. Item Tooltip Presentation

A potion tooltip can display:

- effect name;
- description;
- duration;
- magnitude where player knowledge permits;
- positive/negative/neutral category;
- stacking/usage notes where useful.

Tooltip gets condition presentation snapshots from definitions/current item data.

Do not build gameplay effect logic inside Rich Text widgets.

---

# 12. Condition Data Table / Authoring

A Data Table is an approved Blueprint-first authoring source for condition definitions.

Rules:

- stable ConditionDefinitionID is explicit data;
- Row Name may match the stable ID by convention but gameplay does not depend only on converting an enum string;
- display names use localized Text and may contain spaces;
- Python Editor validation can detect missing IDs, duplicate IDs, invalid modifier targets, impossible durations, missing icons and broken soft references.

A future migration to Data Assets/Data Registry/database-backed definitions can preserve stable ConditionDefinitionIDs.

---

# 13. Condition HUD / UI

Suggested local module:

`W_MW_ConditionsBox`

with entries such as:

`W_MW_ConditionIcon`

Possible presentation:

- icon;
- stack count;
- remaining-duration visualization;
- tooltip/details;
- positive/negative/neutral classification;
- source/context where appropriate.

Radial progress material is approved as presentation.

The UI does not own effect duration or remove the condition when its local radial meter reaches zero.

Authoritative condition expiration/removal updates the UI.

---

# 14. Remaining-Time Presentation

For a timed condition, the client can derive:

`Remaining = ExpiresAt - CurrentAuthoritative/AlignedTime`

and animate locally.

Bounded timers/animation may update the radial fill while the icon is visible.

No permanent UI Tick is required for all hidden effects.

If timing drifts/reconnect occurs, the UI resynchronizes from the authoritative condition record.

---

# 15. Accessibility

Do not communicate condition meaning only through green/red color.

Also use:

- unique icon;
- condition name;
- Buff/Debuff/State text or symbol where useful;
- stack count;
- optional remaining time;
- reduced-motion option for radial/pulsing animations.

---

# 16. Persistence / Death / Removal

Each Condition Definition declares whether it:

- ends on logout;
- persists by timestamp;
- ends on character death;
- transfers to a transformed/supernatural state;
- remains on a corpse/body for forensic/world reasons;
- is cleared by medical treatment/cure/dispel.

Do not silently persist or remove every effect with one global rule.

Permanent death remains governed by the character/death system.

---

# 17. Multiplayer / Authority

The server owns gameplay-relevant condition application, stacks, potency, pulses and expiration.

Clients can request use/ability actions but cannot directly grant themselves Fortify or remove Burning.

Replication sends relevant compact effect state to authorized clients for local presentation/combat prediction needs.

---

# 18. Performance

- one manager/component per target rather than one live component per effect by default;
- no per-condition Tick for duration;
- periodic effects schedule only at required cadence;
- UI updates on add/remove/stack/refresh events;
- hidden/distant NPC effect presentation can be omitted while gameplay state remains data;
- definition assets use soft references where appropriate.

---

# 19. Acceptance Tests

1. Applying Health Regeneration registers the intended effect once.
2. Reapplying follows its configured Refresh/Stack policy.
3. Burning pulses at the configured cadence without Event Tick.
4. Condition expires/removes exactly once.
5. Temporary stat modifiers remove by exact ActiveConditionID source.
6. Health regeneration cannot exceed Max Health.
7. Burning can damage a character immediately after they were fully regenerated.
8. Potion use applies conditions only after authoritative item-use success.
9. Stackable potions preserve condition/application metadata during stacking.
10. Condition lookup does not depend on fragile enum-string-row conversion.
11. Tooltip shows condition data without owning condition logic.
12. Radial timer reflects authoritative expiration and resyncs after reconnect.
13. UI conveys condition meaning without color alone.
14. Player and NPC use the same status-effect rules where applicable.
15. Client cannot self-apply/remove authoritative effects illegally.

## Core Rule

> Metaworld conditions are authoritative, traceable effect records managed centrally. Data defines what an effect means, the manager owns duration/stacking/application, existing systems own the stats/resources being changed, and the HUD simply presents the active state.