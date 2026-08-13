# Metaworld — Quickslot / Hotbar Item & Action Assignment System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / controller-complete / persistent / event-driven / server-authoritative activation

## Canonical Principle

Quickslots are saved shortcuts to gameplay intents and item references. They do not own inventory, duplicate items, bypass equipment/container rules or become a second source of item truth.

> A quickslot remembers what the player wants quick access to. When activated, the authoritative gameplay system resolves whether the referenced item/action is currently available and legal.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Ranged_Weapons_Bow_Ammo_Quiver_Container_System.md`
- `Docs/Item_Upgrade_Reinforcement_Enhancement_System.md`
- `Docs/Player_HUD_Vitals_Resources_System.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`

---

# 1. Quickslot Is Not Inventory

Assigning an item to a quickslot does **not**:

- move the item out of its ContainerID;
- create another ItemInstance;
- reserve the item permanently;
- make the item weightless;
- protect it from theft/drop/destruction;
- duplicate stack quantity;
- bypass equip/use restrictions.

The quickslot stores a stable reference/action descriptor and presents it on HUD.

---

# 2. Quickslot Identity

Suggested stable identity:

`QuickslotID`

Examples:

- `Quickslot.1`
- `Quickslot.2`
- `Quickslot.3`
- `Quickslot.Left`
- profile-defined slots for controller radial/hotbar layouts.

The tutorial's six slots are a valid prototype layout, not a permanent hard cap.

A profile may define:

- number of visible slots;
- layout/order;
- input action mapping;
- combat vs social/context profiles;
- controller/radial alternative;
- user-rebindable presentation.

---

# 3. Assignment Target Types

Quickslots may reference different target semantics.

## Unique Item Instance

Use exact `ItemInstanceID` when the player means one specific persistent object.

Examples:

- custom upgraded sword;
- exact firearm;
- unique tool;
- specific magical artifact.

## Item Definition / Use Profile

Use `ItemDefinitionID` / capability/use profile where any compatible current stack may satisfy the action.

Examples:

- health potion;
- food item type;
- bandage;
- standard throwable where design allows.

The resolver finds an authorized compatible ItemInstance/stack at activation time according to container/access policy.

## Ammunition / Ammo Preference

A quickslot can select an ammunition type/profile rather than point to one physical arrow stack.

Example:

`Ammo.Arrow.Poison`

The ranged system resolves available compatible ammunition from the quiver/approved containers.

## Gameplay Action / Ability

The architecture can later support stable action/capability IDs for non-item shortcuts, but those remain actions resolved by their owning systems.

---

# 4. Suggested Assignment Record

Conceptual:

`S_MW_QuickslotAssignment`

Possible fields:

- QuickslotID
- AssignmentType
- TargetItemInstanceID optional
- TargetItemDefinitionID optional
- TargetActionID / UseProfileID optional
- PreferredContainerID optional
- Ammo/Profile Tag optional
- display override only where legitimate
- created/updated timestamp
- revision

The HUD derives icon/count/availability from current gameplay state rather than persisting stale item structs inside widgets.

---

# 5. Assigning From Inventory

Suggested flow:

`RequestAssignQuickslot(QuickslotID, ItemInstanceID / UseTarget)`

Validation/presentation checks can ensure:

- source item exists;
- it exposes a quickslot-compatible action/capability;
- assignment type is resolved correctly;
- duplicate policy is respected;
- assignment persists to the current character/loadout profile.

Assignment itself is primarily character/UI preference state and does not transfer item ownership.

---

# 6. Activation

Physical input maps to an Enhanced Input action, not hardcoded keys such as `1`, `X`, `C`, `V` in gameplay logic.

Flow:

`IA_MW_Quickslot_1`
-> local quickslot manager resolves assignment
-> resolve current item/action availability
-> submit the appropriate authoritative gameplay request

Examples:

Potion:
`Quickslot -> Resolve compatible potion -> RequestUseItem(ItemInstanceID)`

Sword:
`Quickslot -> exact Sword ItemInstanceID -> RequestEquip/Use according to state`

Arrow type:
`Quickslot -> Set selected ammo preference -> ranged system validates/resolves actual stack on shot`

The widget/event dispatcher does not directly consume items or equip weapons as authoritative truth.

---

# 7. Stack Counts

For stackable assignment by ItemDefinition/use profile, HUD count may aggregate compatible accessible quantities.

Example:

`Health Potion`
- Backpack stack x3
- Belt pouch stack x2

Quickslot may show `5` if both are allowed quick-access sources.

Count updates from container deltas.

Do not count Widget children or cache one stale stack count permanently.

For arrows, the count comes from compatible accessible ammunition across the allowed quick-access ammo source policy, not merely one stack.

---

# 8. Unique Item Upgrades

Canonical ordinary upgrades preserve the same ItemInstanceID.

Therefore:

`Sword #84721 +2`
-> upgrade
-> `Sword #84721 +3`

The quickslot referencing `ItemInstanceID #84721` remains valid automatically.

Do not delete/recreate quickslot assignments merely because the item's UpgradeLevel or presentation name changed.

If a true transformation intentionally consumes an old ItemInstance and creates a new one, the transformation transaction may optionally migrate the quickslot reference only according to explicit policy/provenance—not by guessing from display name.

---

# 9. Missing / Unavailable Item State

If the referenced item is:

- dropped;
- sold;
- stolen;
- destroyed;
- moved to inaccessible storage;
- consumed;
- reserved by another transaction;
- unequippable in current state;

then the quickslot becomes unavailable/empty according to assignment semantics.

Possible UI presentation:

- dim icon;
- `0` count;
- unavailable badge;
- cleared assignment only when policy says the reference should be removed.

A quickslot cannot resurrect or duplicate an item that no longer exists.

---

# 10. Duplicate Assignment Policy

The tutorial removes duplicate items from other slots. That is a valid default, but not universal law.

Profiles may define:

- UniqueTargetOnly: the same exact ItemInstance/action can occupy only one quickslot;
- AllowDuplicates: useful where multiple physical inputs should trigger the same action;
- DefinitionUnique: same ItemDefinition shortcut only once;
- ContextDependent.

Default player HUD may prefer unique assignments to reduce confusion, but the architecture remains data-driven.

When reassignment moves a unique shortcut from Slot 1 to Slot 3, both UI entries update from one assignment-state change transaction.

---

# 11. UI / HUD

Suggested presentation:

`W_MW_QuickslotBar`
-> reusable slot entries

Each slot may show:

- icon;
- current input glyph/action label;
- quantity/count;
- equipped/active state;
- unavailable state;
- cooldown/condition where relevant;
- selection/focus highlight when editing.

Quickslot HUD is event-driven.

Refresh on:

- assignment changed;
- item/container quantity delta;
- exact ItemInstance changed/upgraded;
- equipment state changed;
- input device/rebinding changed;
- character possession/loadout changed.

No per-frame full-inventory search is required.

---

# 12. Quickslot Editing UI

Opening `Set Quickslot` can use a modal overlay, but it follows the existing modal/focus architecture.

Required behavior:

- inventory selection remains known;
- choose a slot with mouse/keyboard/controller;
- confirm/cancel;
- prevent click-through while modal is active;
- restore focus predictably;
- close/deactivate transient widgets cleanly without forced garbage collection hacks.

The tutorial's black-screen widget can become a reusable modal dim/background layer rather than a unique gameplay system.

---

# 13. Controller Compatibility

Quickslots must not depend on six keyboard keys as the only interface.

Support:

- keyboard/mouse mapped actions;
- Xbox-style controller;
- PlayStation-style controller;
- remapping;
- contextual radial/menu alternative when controller button budget requires it;
- on-screen glyphs that reflect the current device/binding.

Possible layouts can use D-pad, bumper modifiers, radial selection or other validated control schemes.

The `QuickslotID` is separate from the physical key/button.

---

# 14. Persistence

Persist quickslot assignments per character/loadout/profile as compact stable references.

Save/load/reconnect must restore:

- QuickslotID -> assignment mapping;
- selected ammo/use preference where designed;
- revision.

Do not persist transient Widget references, Actor pointers or copied ItemInfo structs.

If a referenced ItemInstance no longer exists after loading, resolve the unavailable state safely.

---

# 15. Multiplayer / Authority

Quickslot layout itself is generally private local/character preference state.

Actual actions remain server-authoritative:

- use item;
- equip item;
- consume potion;
- fire ammunition;
- activate gameplay capability.

A modified client cannot activate a non-existent potion or inaccessible weapon merely because a quickslot record points to it.

---

# 16. Performance

- quickslot assignments are compact records;
- no `Get All Widgets Of Class` or full inventory scans every frame;
- maintain container/item indexes/aggregates where useful;
- refresh count only when relevant inventory/container deltas occur;
- slot widgets listen to quickslot manager/presentation events;
- hidden edit UI stops work;
- icons use existing cached presentation assets.

---

# 17. Acceptance Tests

1. Assigning an item to quickslot does not move/duplicate the ItemInstance.
2. Unique sword quickslot references exact ItemInstanceID.
3. Upgrading the same sword preserves its quickslot automatically.
4. Potion quickslot can resolve compatible stack(s) and show current aggregate quantity.
5. Consuming the last potion makes slot unavailable/zero without duplication.
6. Arrow quickslot selects ammo type/preference and displays authoritative accessible count.
7. Dropping/selling/stealing referenced item updates availability correctly.
8. Same quickslot layout survives close/reopen/save/load.
9. Duplicate-assignment policy behaves according to profile.
10. Quickslot activation is validated by gameplay system/server.
11. KBM/Xbox-style/PlayStation-style activation/editing works.
12. Input glyph changes when active binding/device changes.
13. Editing modal prevents click-through and restores focus.
14. No per-frame inventory scanning is required for count updates.
15. Quickslot cannot resurrect a deleted/consumed ItemInstance.

## Core Rule

> Metaworld quickslots are persistent shortcuts, not pockets. They reference stable items, definitions, ammo preferences or actions; the live inventory/equipment/combat systems decide what is actually available and perform every real gameplay action.