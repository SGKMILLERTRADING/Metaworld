# Metaworld — RPG Interface Shell, Widget Data Contracts & Navigation System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / controller-complete / event-driven

## Canonical Principle

Metaworld UI receives stable presentation data or stable gameplay IDs and asks authoritative systems for current truth. Widgets do not pass giant mutable gameplay structs around as if those structs were durable contracts.

> UI should survive gameplay-struct growth, inventory sorting and equipment movement without losing track of which item or system state it is showing.

Related canon:

- `Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`

---

# 1. Do Not Pass Whole Mutable Gameplay Structs By Default

The tutorial correctly identifies a Blueprint maintenance problem: expanding a heavily reused gameplay struct can break widget pins/defaults and produce stale or incorrect presentation.

Metaworld's solution is to reduce coupling.

A widget receives only what it needs, preferably through:

- stable IDs such as `ItemInstanceID`, `RecipeDefinitionID`, `EquipmentSlotID`;
- compact immutable/presentation snapshots;
- explicit widget ViewModel-style structs dedicated to presentation;
- event-driven updates from the owning gameplay system.

Do not make `S_MW_ItemInstance`, Inventory state, Equipment state, Currency state or other large authoritative structs the direct constructor contract for every widget.

---

# 2. Stable ID Beats Inventory Array Index

An inventory array index is not durable identity.

An index may change when the player:

- sorts;
- filters;
- stacks/splits;
- picks up/drops another item;
- equips/unequips;
- moves an item between containers;
- receives a replicated inventory update.

Therefore an options menu should prefer:

`ItemInstanceID`
+
`SourceContainerID`

rather than `InventoryIndex` as the only identity.

The container system resolves the current valid location/entry at action time.

This prevents a delayed context menu from accidentally acting on a different item after the list changed.

---

# 3. Widget Presentation Snapshots

Suggested examples:

`S_MW_ItemEntryPresentation`
- ItemInstanceID
- display name
- icon
- quantity
- rarity profile
- condition summary
- equipped/status flags known to viewer

`S_MW_NotificationPresentation`
- title/text
- icon
- quantity/amount
- category/priority

`S_MW_ItemTooltipPresentation`
- ItemInstanceID
- definition text
- stats
- weight/value context
- description
- allowed visible status data

`S_MW_RecipePresentation`
- RecipeDefinitionID
- name/icon
- category
- ingredient availability
- requirements
- craftability/reason

These are presentation contracts, not authoritative persistent state.

They may be regenerated when the source state changes.

---

# 4. Tooltip Source Context

The tutorial adds a `Tool Tip Type` enum to choose Inventory versus Equipment arrays.

That is acceptable for a tiny prototype, but Metaworld should not require the tooltip to know every possible storage system.

A tooltip should receive the ItemInstanceID plus a viewing/context descriptor and request/receive the authorized item presentation snapshot.

The same tooltip can then work for:

- inventory;
- equipment;
- container/chest;
- vendor stock;
- trade window;
- corpse/loot inventory;
- construction storage;
- prison property storage;
- vehicle cargo;
- crafting source/result.

The tooltip does not Switch across all those gameplay arrays itself.

---

# 5. Main RPG Interface Shell

A unified interface shell is approved for major character/player panels.

Suggested conceptual widget:

`W_MW_PlayerInterface`

Possible top-level sections:

- Inventory
- Equipment / Character
- Crafting
- Skills / Professions
- Stats
- Journal / Quests where implemented
- Reputation / Relationships where appropriate
- other future modules

Not every module must be loaded/constructed permanently if performance benefits from lazy creation.

---

# 6. Widget Switcher / Tab Architecture

UE5.8 UMG `WidgetSwitcher` is an approved baseline: it displays one child widget at a time and can be controlled by active widget/index.

Metaworld should address tabs through stable Tab IDs rather than relying everywhere on magic integer indexes.

Example:

- `UI.Tab.Inventory`
- `UI.Tab.Crafting`
- `UI.Tab.Skills`
- `UI.Tab.Stats`

A tab registry can map TabID -> child widget/switcher slot/presentation.

This allows ordering or future tabs to change without scattering `SetActiveWidgetIndex(3)` assumptions throughout Blueprints.

---

# 7. Common UI Optional Path

UMG + Enhanced Input remains the baseline architecture.

UE5.8 Common UI may be adopted after project validation where it provides value for:

- tab lists linked to switchers;
- controller/cardinal navigation;
- input routing;
- back actions;
- platform/device-specific prompts;
- shared style assets.

Do not make Common UI mandatory merely because it exists; validate plugin behavior and project fit first.

---

# 8. Controller Navigation

The interface shell must support:

- mouse clicking tabs;
- keyboard navigation;
- Xbox-style bumper/shoulder tab cycling where mapped;
- PlayStation-style bumper/shoulder tab cycling where mapped;
- D-pad/stick cardinal navigation;
- confirm/back actions;
- predictable focus restoration when switching tabs;
- no mouse-only hover requirement.

The active tab presentation must be obvious through more than color alone.

---

# 9. Tab Lifecycle / Performance

Possible policies:

- create core tabs once and reuse;
- lazy-create heavy tabs on first opening;
- suspend/stop expensive preview capture when tab is hidden;
- unsubscribe or reduce nonessential UI listeners when inactive;
- refresh tab presentation on activation if underlying state changed;
- do not run hidden-tab Tick logic unless explicitly required.

Switching tabs does not duplicate gameplay components or authoritative data.

---

# 10. UI State vs World State

Local interface state may remember:

- current selected tab;
- focused recipe/item;
- sort/filter selection;
- expanded category state;
- scroll position where useful.

These are presentation preferences, not authoritative Item/Skill/Crafting state.

If a selected item disappears/moves while a menu is open, the UI resolves the stable ID again and safely updates/closes the affected context menu instead of acting on stale data.

---

# 11. Notifications / Menus

Notification widgets should receive the exact presentation payload required for the message (for example ItemName/Icon/Quantity) rather than an entire ItemInstance gameplay struct.

Context/action menus receive stable target/action references and ask the gameplay system to execute the action.

The menu does not cache a mutable copy of the item and then write that copy back.

---

# 12. Struct / Schema Evolution

When gameplay schemas evolve:

- authoritative structs can add/version fields according to system needs;
- presentation snapshots are updated deliberately;
- widgets depending only on stable IDs/minimal view data are less likely to break;
- Python/Editor validation can identify stale Blueprint dependencies where practical;
- save-data schema migration remains separate from widget layout changes.

Do not solve every Blueprint struct edit by manually refreshing hundreds of unrelated widget pins forever; reduce coupling at the architecture level.

---

# 13. Acceptance Tests

1. Adding a new field to ItemInstance gameplay state does not require every notification widget constructor to change.
2. Item options menu still targets the correct ItemInstance after inventory sorting.
3. Dropping/equipping an item while its tooltip is open updates or closes the tooltip safely.
4. Same tooltip works for inventory and equipment without reading two arrays directly.
5. Same tooltip architecture can extend to vendors/loot/crafting without redesign.
6. Inventory/Crafting/Skills/Stats tabs switch correctly by stable Tab ID.
7. Keyboard/mouse, Xbox-style and PlayStation-style users can switch tabs.
8. Tab switch restores a sensible focus target.
9. Hidden character-preview/crafting tabs do not continue unnecessary expensive UI work.
10. UI state changes do not mutate gameplay state directly.
11. Notification payloads remain small and purpose-specific.
12. Struct/schema changes have an explicit validation/migration path rather than silent `None` data.

## Core Rule

> Metaworld UI points to stable world truth; it does not carry copies of the world around inside widgets. Stable IDs, purpose-built presentation snapshots and event-driven navigation keep the interface resilient as the game grows.