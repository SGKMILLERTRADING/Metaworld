# Metaworld — Crafting Profession & Skill Progression System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / profession-driven

## Canonical Principle

Crafting progression belongs to the character's profession/skill development, not to one generic global RPG level.

> Successful meaningful work can improve the relevant profession or skill, but progression does not replace tools, knowledge, licenses, materials, workstations or world consequences.

Related canon:

- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`

---

# 1. No Universal Crafting Level Requirement

The tutorial's `Crafting Level` and `Crafting Experience` are useful prototype concepts, but Metaworld does not require one universal Crafting Level for every production profession.

Possible profession/skill tracks include:

- Smithing / Gunsmithing
- Tailoring / Leatherworking
- Carpentry
- Cooking
- Medicine / Pharmacy
- Mechanics
- Electronics / Engineering
- Construction / Building
- Alchemy / Magic crafting where applicable
- other learned trades

A recipe may require one or more relevant profession/skill IDs rather than `PlayerLevel >= X`.

Suggested stable IDs / Gameplay Tags:

- `Profession.Smithing`
- `Profession.Gunsmith`
- `Profession.Carpentry`
- `Skill.Crafting.Metalwork`
- `Skill.Crafting.Leatherwork`
- `Skill.Crafting.PrecisionAssembly`

Gameplay Tags remain an appropriate UE5.8 data vocabulary for hierarchical categories and requirements.

---

# 2. Progression Record

Suggested conceptual record:

`S_MW_ProfessionProgress`

Possible fields:

- ProfessionID / SkillID
- Rank/ProficiencyTier where the design uses named tiers
- Experience / PracticePoints
- ExperienceToNextThreshold
- unlocked RecipeDefinitionIDs / knowledge refs where applicable
- certification/license refs where applicable
- specialization tags
- lifetime successful-work counters for analytics/achievements where desired
- revision/timestamp

Profession progression is persistent character state.

Public career rank, political authority and reputation remain separate systems.

---

# 3. XP / Practice Award Is Server-Owned

Experience is awarded only after an authoritative work/crafting result qualifies.

Canonical flow:

`Craft job succeeds or approved work milestone completes`
-> server resolves progression reward
-> applies reward to relevant profession/skill record
-> processes any threshold/rank changes
-> persists
-> emits local UI notification/progression event

The client does not submit `Give me 50 Crafting XP` as truth.

Failed/cancelled attempts do not automatically earn full success XP.

---

# 4. Recipe-Defined Progression Reward

Do not calculate all XP purely from total ingredient count.

Recipe progression metadata may include:

- BasePracticeReward
- Profession/Skill target(s)
- difficulty rating
- first-time-learning bonus where desired
- quality/workmanship contribution
- completion milestones
- batch scaling policy
- diminishing-repeat policy if needed
- apprentice/training modifiers

A complex watch using five tiny components may be harder than a crate requiring twenty pieces of wood. Material quantity alone is not a reliable difficulty metric.

---

# 5. Progression Curves

The tutorial's fixed `+20% XP required each level` is acceptable as a prototype curve, not a universal canonical formula.

Metaworld uses data-driven progression curves/tables per profession or skill family.

Possible behavior:

- early learning is fast;
- intermediate competence takes sustained practice;
- mastery takes significantly longer;
- some certifications/roles require training/exams/reputation in addition to numeric proficiency.

Changing the progression curve must not require rewriting every crafting Blueprint.

---

# 6. Carrying Remainder XP / Multi-Level Gain

When a reward crosses a threshold, excess progress is preserved.

Example:

Current XP = 90
Threshold = 100
Reward = 35

Result:

- threshold crossed;
- 25 XP continues into the next threshold calculation.

If one legitimate reward crosses multiple thresholds, the system processes all applicable thresholds safely rather than discarding excess XP.

---

# 7. Anti-Spam / Meaningful Practice

Repeatedly mass-producing a trivial zero-value recipe must not become the best universal path to mastery merely because it can be automated fastest.

Possible balancing inputs:

- recipe difficulty relative to current proficiency;
- first/recent repetition weighting;
- batch-production rules;
- required work/time;
- successful quality;
- material/tool cost;
- training context;
- profession-specific diminishing returns on trivial tasks.

This is balancing policy, not a requirement to punish normal production.

---

# 8. Proficiency Effects

Progression may influence, where appropriate:

- recipe eligibility;
- craft speed/work efficiency;
- error/failure risk;
- output quality envelope;
- number/strength of optional generated affixes within recipe limits;
- material efficiency/waste within reasonable bounds;
- repair quality;
- ability to use advanced tools/workstations;
- professional service reputation indirectly through successful work.

Progression never allows the client to skip server validation or create impossible outputs.

---

# 9. UI

Crafting/skills UI may show:

- profession/skill name;
- current proficiency/tier;
- progress toward next threshold;
- learned/unlocked recipes;
- recipe requirement comparison;
- recent XP/practice gain;
- specialization/certification status where relevant.

Progress bars are presentation only.

The profession system owns the actual progress values.

Keyboard/mouse, Xbox-style and PlayStation-style controller users receive equivalent navigation/details.

---

# 10. Persistence / Multiplayer

Persist profession/skill progress by stable character + profession/skill ID.

The server owns authoritative progression in shared multiplayer.

Character death/legacy behavior follows Metaworld's character/permanent-death rules and must be explicitly defined per progression domain; progression is not silently copied to a successor unless a legacy system specifically permits some knowledge transfer.

---

# 11. Performance

- progression changes on completed work/reward events, not Tick;
- curves/definitions are data-driven;
- UI updates on progression events;
- no global scans of all skills every frame;
- batch production can award aggregate progression according to policy.

---

# 12. Acceptance Tests

1. Successful qualifying craft awards the intended profession/skill progress once.
2. Failed/cancelled craft cannot claim full success reward.
3. Client cannot set its own XP/proficiency.
4. Excess XP carries across thresholds.
5. One large reward can process multiple thresholds safely.
6. Smithing progression does not automatically increase unrelated professions.
7. Recipe requirement can reference profession/skill independently of generic player level.
8. Progression curve can change through data without rewriting craft logic.
9. Ingredient quantity alone does not determine all XP rewards.
10. Crafting UI mirrors authoritative progression state and controller navigation works.
11. Save/load restores progression without duplicate reward.

## Core Rule

> Metaworld progression rewards meaningful practice in the profession being performed. Skill can improve what a character is capable of producing, but it never replaces real materials, tools, stations, knowledge, permissions or authoritative world rules.