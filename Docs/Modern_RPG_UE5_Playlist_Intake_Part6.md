# Metaworld — Modern RPG UE5 Playlist Intake — Part 6

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part5.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

---

# Episode 37 — Crafting Recipe Buttons, Selection & Navigation

**Classification:** UPGRADE — APPROVED UI ARCHITECTURE.

**Phase Ownership:** Crafting UI + Phase 67/68 UI/Controller.

Detailed companion:

`Docs/Crafting_UI_Recipe_Selection_Details_Progress_System.md`

## Approved Tutorial Intent

- recipe entries/buttons display output icon/name/type/rarity presentation;
- one recipe can be selected and highlighted;
- selection opens/updates a details panel;
- pressed interaction can feel more responsive than waiting for a click release.

## Metaworld Upgrades

- recipe entry uses stable `RecipeDefinitionID`; list/button index is layout/navigation state only;
- parent crafting view owns `SelectedRecipeDefinitionID`;
- selecting one entry directly deselects the previous selected entry instead of `Get All Widgets of Class` + loop;
- recipe entry emits selection intent to parent rather than directly reading/mutating Player Blueprint gameplay state;
- Focused and Selected are separate UI states;
- mouse, keyboard, Xbox-style and PlayStation-style navigation have equivalent selection/highlight behavior;
- selection presentation is not color-only.

### Episode 37 Principle

> A recipe button points to a stable recipe; the parent crafting interface owns selection. Do not discover/deactivate every recipe widget globally just to change one selection.

---

# Episode 38 — Crafting Details Layout, Materials, Level & Stats

**Classification:** UPGRADE — APPROVED PRESENTATION.

**Phase Ownership:** Crafting UI + Profession/Skill Progression + Item Stats.

Detailed companions:

- `Docs/Crafting_UI_Recipe_Selection_Details_Progress_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`
- `Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`

## Approved Tutorial Intent

- selected recipe details show output name/icon/category/rarity;
- display material requirements through reusable material-row widgets;
- show crafting/progression requirement information;
- show item stats/expected result information;
- maintain an organized details layout with reusable containers.

## Metaworld Upgrades

- details panel consumes `S_MW_RecipePresentation` / craftability snapshots rather than owning recipe truth;
- generic `Crafting Level` becomes relevant Profession/Skill requirement(s);
- UI may show profession progress and recipe difficulty, but profession state remains authoritative outside the widget;
- material rows display required/available/missing amounts from approved crafting source containers;
- details distinguish guaranteed base stats from possible generated affix/quality ranges;
- before craft, random exact bonuses are not falsely shown as guaranteed;
- controller/keyboard focus can inspect every material/stat requirement.

### Episode 38 Principle

> The crafting details screen explains the recipe, requirements and possible result; it does not become the recipe, inventory or profession system.

---

# Episode 39 — Active Recipe Details, Material Rows & Crafting XP Estimate

**Classification:** UPGRADE — APPROVED WITH PROGRESSION CORRECTION.

**Phase Ownership:** Crafting UI + Profession Progression.

Detailed companions:

- `Docs/Crafting_UI_Recipe_Selection_Details_Progress_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`

## Approved Tutorial Intent

- selecting a recipe updates the active details panel;
- old material widgets are cleared/replaced when selected recipe changes;
- recipe can advertise progression/experience reward;
- one Craft action operates on the selected recipe.

## Metaworld Upgrades

- active recipe identity is `SelectedRecipeDefinitionID`, not a mutable whole `ItemInfo` copy;
- update only affected material/details widgets from the selected recipe snapshot;
- XP/practice reward is not derived universally from total ingredient quantity;
- recipe/profession data defines base practice reward/difficulty, with server-side adjustment policies;
- crafting UI can display an estimate/expected reward but never awards XP itself;
- selected recipe change cancels/replaces stale presentation safely without touching active server jobs unless the player explicitly cancels them.

### Episode 39 Principle

> Recipe selection drives details; recipe/profession metadata drives meaningful progression reward. Ingredient count alone is not difficulty.

---

# Episode 40 — Material Availability, Item Stats & Prototype Craft Action

**Classification:** PARTIAL APPROVE + REJECT TUTORIAL CRAFT SHORTCUT.

**Phase Ownership:** Crafting Sources + UI + Item Creation.

Detailed companions:

- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Crafting_UI_Recipe_Selection_Details_Progress_System.md`

## Approved Tutorial Intent

- crafting UI needs available/required material counts such as `0 / 10`;
- recipe details can display output item stats;
- selected Craft action should attempt to produce the recipe output.

## Rejected Tutorial Direction

- do **not** use the normal `PickupItem` function as the authoritative meaning of crafting;
- do not count materials only by searching one Player Blueprint inventory array;
- do not duplicate the Stats widget's gameplay logic into a separate craft-only stat system.

## Metaworld Upgrade

- source resolver totals only approved accessible crafting sources (carried inventory, workstation input, authorized nearby/property/company storage according to context);
- recipe UI gets availability snapshots from the resolver;
- stats use shared canonical presentation models;
- Craft submits `RequestCraft(...)` to the authoritative crafting system;
- crafting creates a new ItemInstance only after valid input transformation/commit;
- pickup remains a transfer of an already-existing world item, not item creation.

### Episode 40 Principle

> Count real accessible materials through the crafting source resolver and create outputs through the craft transaction—not through the pickup system.

---

# Episode 41 — Material Validation, Removal & Craft Completion

**Classification:** LOCKED + UPGRADE — APPROVED TRANSACTIONAL INTENT.

**Phase Ownership:** Crafting Core + Inventory/Containers + Notifications.

Detailed companion:

`Docs/Crafting_Recipes_Materials_Production_System.md`

## Approved Tutorial Intent

- verify required material quantities before crafting;
- reject with clear feedback when requirements are missing;
- consume the correct stacks/quantities;
- add the legitimate output after valid material consumption;
- refresh UI and notify the player after success.

## Metaworld Upgrades

- material check/removal is one server-authoritative reservation/consumption transaction;
- sources may span multiple approved stacks/containers and are serialized against concurrent crafting;
- no partial state may consume input without creating the legitimate output or create output without consuming input;
- notification fires only after committed result;
- inventory/crafting UI updates from resulting deltas/events;
- two players cannot spend the same final material stack simultaneously;
- cancellation/refund follows recipe consume policy rather than ad-hoc array restoration.

### Episode 41 Principle

> Material validation, consumption and output creation are one authoritative craft transaction, not a chain of unrelated client array edits.

---

# Episode 42 — Hold-to-Craft Progress Bar / Timed Crafting

**Classification:** UPGRADE — APPROVED INTERACTION / JOB PRESENTATION.

**Phase Ownership:** Crafting Jobs + UI + Controller.

Detailed companion:

`Docs/Crafting_UI_Recipe_Selection_Details_Progress_System.md`

## Approved Tutorial Intent

- some crafts may require holding the Craft action;
- progress can be shown with a bar;
- release before completion can cancel/reset according to design;
- timer handles are preferable to per-frame craft Tick for simple timed presentation.

## Metaworld Upgrades

- progress bar is local presentation of an accepted authoritative crafting job/work state;
- server validates and starts/reserves the craft before progress is considered legitimate;
- client reaching 100% never mints the output by itself;
- fixed-duration, hold-duration, Work Units, queued machine and company production can share the same presentation contract;
- early release sends cancel/pause request according to recipe/job policy;
- consumed/reserved materials follow configured cancellation/refund policy;
- output destination/capacity is validated rather than simply calling Pickup at completion;
- timers may update visible UI at bounded cadence without Widget Tick;
- full hold/release interaction works KBM, Xbox-style and PlayStation-style.

### Episode 42 Principle

> The progress bar tells the player how the craft is progressing; the server-owned crafting job decides whether the craft completed.

---

# Episode 43 — Crafting Level / Experience / Profession Progression

**Classification:** UPGRADE — APPROVED AS PROFESSION/SKILL PROGRESSION.

**Phase Ownership:** Professions/Skills + Crafting + UI.

Detailed companion:

`Docs/Crafting_Profession_Skill_Progression_System.md`

## Approved Tutorial Intent

- successful crafting can grant experience/practice;
- progress carries toward future proficiency thresholds;
- crossing a threshold can increase proficiency;
- UI can show current progress and next requirement;
- later thresholds can require progressively more experience.

## Metaworld Upgrades

- no one universal `Crafting Level` controls every trade;
- progression is attached to relevant profession/skill IDs such as Smithing, Carpentry, Leatherworking, Gunsmithing, etc.;
- recipe requirements reference relevant profession/skills independently;
- XP/practice reward is server-awarded only after legitimate work/result milestones;
- excess XP carries across thresholds and multi-threshold gains are handled safely;
- tutorial's fixed `+20% requirement` becomes one possible prototype curve; final curves are data-driven per profession/skill family;
- trivial repeat spam can be balanced through recipe difficulty/repetition policies rather than becoming optimal mastery;
- progression may improve efficiency/quality envelope/advanced recipe eligibility without replacing materials/tools/stations/licenses/knowledge.

### Episode 43 Principle

> Characters improve by practicing the profession they are actually performing; there is no single generic crafting number that replaces Metaworld's profession system.

---

# Episode 44 — Mandatory Base Item Stats

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Item DNA + Equipment/Combat + Generated Item System.

Detailed companion:

`Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`

## Approved Tutorial Intent

- functional equipment needs mandatory baseline properties regardless of random secondary bonuses;
- base stats should be visible distinctly from generated/random stats;
- the character receives appropriate item effects when equipped;
- randomized future item generation should not erase fundamental weapon/armor behavior.

## Metaworld Upgrades

- mandatory base functional stat templates belong primarily to ItemDefinitionID;
- exact ItemInstance may modify effective base result through condition/quality/upgrades while preserving definition identity;
- examples: weapon base damage/use-speed/reach/weight; armor base coverage/protection/weight/durability;
- generated affixes are separate ItemInstance modifier records;
- base-vs-generated presentation uses label/icon/grouping plus optional color—never blue color alone;
- equipping applies all effective ItemInstance modifiers through the existing source-aware Equipment/Stats architecture;
- do not double-count a property as both base and random bonus accidentally.

### Episode 44 Principle

> Base stats make the item function as its intended item type; optional generated traits add individuality without replacing that foundation.

---

# Episode 45 — Randomized Crafted Item Stats / Affix Quality

**Classification:** UPGRADE — APPROVED WITH AUTHORITY / BALANCE CORRECTIONS.

**Phase Ownership:** Generated Items + Crafting + Professions + Item DNA + Economy.

Detailed companion:

`Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`

## Approved Tutorial Intent

- generated items can roll secondary stats from min/max ranges;
- item families can have different compatible random-stat pools;
- rarity can influence how many/what tier of optional traits appear;
- crafting proficiency can influence result quality;
- decimal rounding/presentation should be controlled.

## Metaworld Upgrades

- generated result is rolled by the server once when the ItemInstance is legitimately created;
- exact generated affixes/values persist on that ItemInstance through drop/trade/save/load/equip;
- opening a tooltip or reloading does not reroll;
- stable affix IDs/Gameplay Tags + data-driven compatible pools replace one unrestricted all-stat pool;
- weapons cannot receive armor-only bonuses unless explicitly allowed;
- rarity may control an affix count/budget/tier ceiling/special pool, but does not overwrite mandatory base stats or automatically determine value/power;
- profession proficiency influences the legal quality envelope rather than simply forcing rolls toward maximum independent of recipe/material/tool limits;
- input quality, workstation/tool quality, recipe limits and workmanship can all constrain output;
- duplicate/conflicting affixes obey explicit pool rules;
- optional authoritative seed / UE5.8 RandomStream can make generation reproducible for audit/debug, but the client never chooses the final seed/result;
- vendor price may react to quality/affixes through the normal contextual valuation system.

### Episode 45 Principle

> Random generation creates persistent individuality on the exact item once, under server authority and within recipe/material/profession limits. It is not a UI reroll and rarity is not the whole item.

---

# Current Modern RPG Additions From Episodes 37–45

`RecipeDefinitionID`
-> `Parent-owned recipe selection`
-> `Details / requirements snapshot`
-> `Craftability presentation`

`Authoritative craft request`
-> `Input reservation`
-> `Crafting job / work / timer state`
-> `Committed output ItemInstance`

`Successful meaningful craft/work`
-> `Profession/Skill progression reward`
-> `Data-driven progression curve`
-> `Advanced capability / quality envelope`

`ItemDefinition mandatory base stats`
+
`Recipe + materials + tools + profession context`
-> `Authoritative generated affix/quality roll`
-> `Persistent exact ItemInstance`
-> `Equipment / Tooltip / Economy`

---

# Playlist Continuation Rule

Future episodes continue in Part 6 until another safe continuation is needed. Parts 1–6 remain the canonical intake/audit trail for this Modern RPG playlist; detailed companion documents remain implementation authority for established domains.