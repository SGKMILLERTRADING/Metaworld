# Metaworld — Crafting UI: Recipe Selection, Details & Progress System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / event-driven / controller-complete / presentation-only

## Canonical Principle

The crafting interface selects and explains a stable recipe and mirrors authoritative crafting state. It never identifies recipes only by transient widget index and never decides that an output exists because a local progress bar reached 100%.

> Selection is UI state. Craft completion is world state.

Related canon:

- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`
- `Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`

---

# 1. Stable Recipe Selection

Each recipe button/entry receives or exposes:

- `RecipeDefinitionID`
- compact recipe presentation snapshot
- optional category/context data

A visual list index may exist for layout/navigation, but it is not the recipe's gameplay identity.

Canonical selection state belongs to the parent crafting screen/controller:

`SelectedRecipeDefinitionID`

When the player selects a recipe:

1. parent validates/resolves the RecipeDefinitionID;
2. previous selected entry receives deselected presentation state;
3. new entry receives selected presentation state;
4. details panel updates from the selected recipe snapshot;
5. craftability/material state is recalculated from relevant authoritative sources.

Do not query `Get All Widgets of Class` every time a recipe is pressed merely to deactivate all buttons.

---

# 2. Recipe Entry State

Suggested entry states:

- Normal
- Focused
- Selected
- Disabled/Unavailable
- Craftable
- MissingRequirements
- Queued/InProgress where relevant

Focus and selection are different:

- controller/mouse focus = what the user is currently navigating;
- selected recipe = what the details panel/craft action currently targets.

The visual language must not rely only on color.

---

# 3. Parent/Child Widget Communication

A recipe entry may hold a lightweight interface/reference to its owning crafting view, but gameplay logic remains below the UI.

Preferred flow:

`Recipe Entry`
-> emits `OnRecipeSelected(RecipeDefinitionID)`
-> `W_MW_Crafting` / presentation controller updates selection
-> requests/receives recipe presentation/craftability snapshot

Do not make each button directly read Player Blueprint inventory/stats and mutate the main widget through brittle hard references.

---

# 4. Details Panel

The selected recipe details panel may display:

- item/output icon;
- output name/category;
- rarity/quality expectation where appropriate;
- guaranteed base stats;
- possible generated affix/quality range;
- description;
- profession/skill requirement;
- current profession/skill state;
- progression reward estimate where allowed;
- workstation/tool requirements;
- ingredient list;
- available / required amounts;
- expected time/work;
- output quantity;
- destination/capacity warning;
- unavailable reason;
- Craft / Queue / Cancel action.

The UI distinguishes guaranteed output data from possible/random result ranges.

---

# 5. Material Requirement Rows

Reusable material-row widgets are approved.

Each row receives a compact requirement/availability snapshot such as:

- required ItemDefinitionID/material tag;
- display icon/name;
- RequiredQuantity;
- AvailableQuantity from approved source scope;
- missing quantity;
- quality/substitution state;
- source summary where exposed.

Display example:

`Iron Bar  6 / 10`

The count is calculated by the inventory/container/crafting source resolver, not by a widget manually searching only one Player Blueprint array.

When relevant inventory/container state changes, only affected requirement rows/craftability state need refresh.

---

# 6. Item Stats / Base Stats / Generated Possibilities

The crafting details screen may reuse the canonical stat presentation system.

Before craft:

- show guaranteed base functional stats;
- show possible generated-affix pool/range where design permits preview;
- show quality envelope rather than falsely displaying an unrolled exact bonus.

After craft:

- the new ItemInstance displays its exact persisted generated result through the normal item tooltip/details architecture.

Do not duplicate the Stats Widget's gameplay logic into a separate Crafting Stats widget. Share presentation models/styles.

---

# 7. Craftability State

Suggested presentation snapshot:

`S_MW_CraftabilityPresentation`

Possible data:

- RecipeDefinitionID
- CanCraft
- FailureReason(s)
- ingredient availability
- station/tool state
- profession/skill requirement state
- knowledge/unlock state
- output capacity state
- expected duration/work

The Craft button may enable/disable from this snapshot for UX, but server validation still runs when the request is submitted.

A locally enabled Craft button is never authority.

---

# 8. Craft Action

Pressing/holding Craft submits the appropriate request to the authoritative crafting system.

For immediate recipes:

`Craft Action`
-> `RequestCraft(...)`
-> server validates/reserves/consumes/creates output
-> result event updates UI/notification.

Do not call the ordinary `PickupItem` function as the meaning of crafting. Pickup transfers an existing item; crafting creates a new ItemInstance only after legitimate input transformation.

---

# 9. Hold-to-Craft / Progress Bar

Hold-to-craft is an approved interaction pattern for recipes designed to require a held action, but the progress bar is presentation.

Possible flow:

1. player presses/holds craft action;
2. client sends start/request for recipe/job;
3. server validates and creates/reserves an authoritative crafting job or accepted work action;
4. client receives accepted start timestamp/duration/work target;
5. progress bar interpolates/displays local presentation;
6. player releases/cancels -> cancellation request sent where recipe policy allows;
7. server decides Completed / Cancelled / Failed;
8. only Completed creates/commits the output.

UE5.8 Blueprint timers remain valid for local periodic UI updates; `Set Timer by Event` returns a Timer Handle and supports looping behavior. A timer can update presentation without using Widget Tick. The timer reaching its local end does not itself mint the item.

---

# 10. Timed Craft vs Work-Based Craft

The UI must support more than one progress model.

Possible job modes:

- fixed duration;
- hold duration;
- Work Units;
- machine batch timer;
- queued production;
- NPC/company process.

Progress representation can be:

`Elapsed / Duration`

or:

`CompletedWorkUnits / RequiredWorkUnits`

according to the authoritative job type.

---

# 11. Release / Cancellation

Releasing a held craft early may:

- cancel with no input consumed;
- pause and preserve partial work;
- lose some consumed inputs;
- keep reserved materials;
- follow another recipe-specific policy.

Do not universally reset everything to zero client-side and assume the server agrees.

Cancellation/refund policy belongs to the recipe/job definition.

---

# 12. Inventory Capacity

Output capacity is checked before commit according to the recipe/output policy.

Possible outcomes:

- place in selected destination container;
- place in workstation output storage;
- spawn at a validated workstation/world output point;
- reject/hold completion until output destination is available where designed.

Do not simply call `PickupItem` after the progress bar completes and hope the inventory has room.

---

# 13. Crafting Progression UI

The details screen may show:

- required profession/skill proficiency;
- player's current relevant proficiency;
- progress bar to next profession threshold;
- expected/base practice reward;
- unlocked/locked state.

The actual XP/proficiency value comes from `Docs/Crafting_Profession_Skill_Progression_System.md`.

The UI never awards progression itself.

---

# 14. Controller / Input

Required support:

- mouse click/press;
- keyboard selection;
- Xbox-style controller;
- PlayStation-style controller;
- D-pad/stick recipe navigation;
- confirm/select;
- hold craft action where used;
- release/cancel;
- category switching;
- details scrolling;
- predictable focus restoration.

`OnPressed` can provide immediate button feedback, but action behavior must also support keyboard/controller confirm/hold semantics through the input/navigation system.

---

# 15. Performance

- no `Get All Widgets of Class` per selection;
- parent directly tracks recipe entry instances or selected ID;
- no per-frame full recipe/material scan;
- material availability refreshes on relevant container deltas;
- stats/details rebuild when selection/source changes;
- timers may update visible progress at a bounded cadence;
- hidden crafting tab stops progress presentation work unless a visible background job indicator is deliberately needed;
- large recipe lists use scalable list/virtualization where appropriate.

---

# 16. Acceptance Tests

1. Recipe selection remains correct after list sorting/filtering.
2. Selection uses RecipeDefinitionID rather than transient button index as authority.
3. Selecting one entry deselects prior entry without `Get All Widgets of Class` scan.
4. Controller focus and selected-recipe state remain distinct and predictable.
5. Details panel shows correct recipe after category/filter changes.
6. Material counts reflect approved crafting source containers, not only one inventory array.
7. Craft button disabled reason matches the presentation snapshot but server still revalidates.
8. Crafting never calls Pickup as the authoritative item-creation operation.
9. Hold progress reaching 100% locally cannot create an item if server job failed/cancelled.
10. Early release follows recipe cancellation policy.
11. Output capacity is handled before/at authoritative commit.
12. Profession XP display mirrors server-owned progression.
13. Base stats and possible generated affix ranges are clearly distinguished before craft.
14. Keyboard/mouse, Xbox-style and PlayStation-style navigation/craft hold all work.
15. No permanent Widget Tick or global widget-class scan is required.

## Core Rule

> The crafting screen owns selection and presentation. The authoritative crafting service owns requirements, materials, time/work, progression reward and the creation of the persistent output item.