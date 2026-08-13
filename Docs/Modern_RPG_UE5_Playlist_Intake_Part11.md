# Metaworld — Modern RPG UE5 Playlist Intake — Part 11

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part10.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

This Part contains Episodes 86–97.

A new owner-directed cross-system rule was added during this intake: gunpowder/propellant ammunition is finite and can become effectively unavailable over the world's lifetime. See `Docs/Gunpowder_Ammunition_Scarcity_Weapon_Resilience_System.md`.

---

# Episode 86 — Customizable Interactive Door

**Classification:** LOCKED + UPGRADE — EXISTING DOOR ARCHITECTURE.

**Phase Ownership:** Interactive Doors/Windows + Interaction + Property/Access + Performance.

Detailed companion:

`Docs/Interactive_Doors_Windows_Runtime_System.md`

## Approved Tutorial Intent

- separate frame/door meshes;
- correct scale/material/collision/pivot authoring;
- common interact interface;
- smooth Timeline-based open/close motion;
- contextual prompt.

## Metaworld Upgrades

- `DoorObjectID` / persistent state remain authoritative;
- pivot/hinge correctness is an authoring requirement;
- Timeline is approved only while moving;
- FlipFlop is not the authoritative state machine because doors can be Locked/Jammed/Broken/Breached/Opening/Closing;
- common `BPC_MW_Interaction` / `BPI_MW_Interactable` handles input rather than a door-specific key;
- server validates lock/property/credential/security state before transition;
- replicate compact state/start-time rather than Timeline transform every frame;
- no idle Tick.

### Episode 86 Principle

> Door mesh/pivot/Timeline presentation is useful, but the persistent lock/access/state machine decides whether the door may move.

---

# Episode 87 — Infinite Inventory / Dynamic Scrollable Slots

**Classification:** PARTIAL REJECT + UPGRADE — SCALABLE UI, FINITE PHYSICAL CAPACITY.

**Phase Ownership:** Inventory/Containers + Encumbrance + UI/Controller.

Detailed companion:

`Docs/Scalable_Inventory_UI_Finite_Physical_Capacity_System.md`

## Approved Tutorial Intent

- ScrollBox/dynamic rows can display inventories larger than 36 entries;
- inventory/quiver labels improve context;
- visual grid length can grow in clean row increments;
- fixed 36-slot UI ceiling should not limit large containers.

## Rejected Tutorial Interpretation

Metaworld does **not** gain infinite physical player inventory.

Authoritative pickup/crafting/trading can still fail for slot, mass, volume, dimensions, compartment, permission or Encumbrance reasons.

Success/failure transaction results remain necessary.

### Episode 87 Principle

> The UI may scroll indefinitely; the body/backpack/container cannot carry indefinitely.

---

# Episode 88 — Trader Scalable Inventory + Quiver Selling

**Classification:** UPGRADE — APPROVED WITH CONTAINER/COMMERCE CORRECTION.

**Phase Ownership:** Commerce + Inventory/Containers + Quiver/Ammunition + UI.

Detailed companions:

- `Docs/Scalable_Inventory_UI_Finite_Physical_Capacity_System.md`
- `Docs/Commerce_Buy_Sell_Quantity_Quote_UI_System.md`
- `Docs/Ranged_Weapons_Bow_Ammo_Quiver_Container_System.md`

## Approved Tutorial Intent

- trader/player lists can scroll beyond visual 36-slot layouts;
- Quiver can be presented as another sell-source tab;
- arrows can be selected/sold from the quiver;
- shared layout logic should be cleaned/refactored.

## Metaworld Upgrades

- trader stock capacity remains finite/business-backed even if UI is scalable;
- Quiver is one real ContainerID, not a second authority;
- selling arrows transfers exact stack/quantity from Quiver through authoritative quote/commerce transaction;
- carried load changes only because arrows leave the player, not because the UI tab changed;
- currency remains GrimKoin/PromoKoin, never Gold money;
- transaction success/failure is not deleted because UI is visually `infinite`.

### Episode 88 Principle

> Large trader/quiver screens are scalable views over real finite containers and atomic commerce.

---

# Episode 89 — Keys & Door Unlocking

**Classification:** UPGRADE — APPROVED / NEW PHYSICAL-CREDENTIAL DOMAIN.

**Phase Ownership:** Items + Doors/Locks + Property Access + Crime/Evidence + UI.

Detailed companion:

`Docs/Physical_Keys_Locks_Doors_Access_Credentials_System.md`

## Approved Tutorial Intent

- keys have stable data, icon/name/description;
- keys can exist as interactable world items;
- lock checks compatible key identity;
- key inventory/category UI can help players inspect collected keys;
- door can remain locked until compatible credential is used.

## Metaworld Upgrades

- exact physical key is a normal persistent ItemInstance;
- stable LockID/CredentialID replaces one fragile integer KeyID as permanent architecture;
- Key tab is a filter/view, not separate inventory authority;
- server validates key possession/accessibility and lock compatibility;
- possessing a stolen key may physically unlock while entry remains legally unauthorized;
- rekeying can invalidate old credentials without deleting old physical keys;
- common interaction and property-access systems remain authority.

### Episode 89 Principle

> A key is a real physical credential that can operate a lock; it is not a Boolean the player permanently absorbs.

---

# Episode 90 — Locked Chests + Hold Prompt Indicator

**Classification:** UPGRADE — APPROVED / SHARED LOCK + HOLD INTERACTION.

**Phase Ownership:** Locks/Credentials + Loot Containers + Interaction UI.

Detailed companions:

- `Docs/Physical_Keys_Locks_Doors_Access_Credentials_System.md`
- `Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`

## Approved Tutorial Intent

- chest can use the same key/lock concept as doors;
- prompt should communicate Hold interaction clearly;
- interaction feedback should distinguish locked/unlocked states.

## Metaworld Upgrades

- chest references common LockID/credential contract rather than cloned door KeyID logic;
- hold/tap presentation comes from ActionDefinition/interaction snapshot, not chest-specific permanent arrow logic;
- prompt uses current device binding/glyph;
- server validates lock + hold completion + container permission before opening;
- unauthorized use can feed crime/evidence/security systems.

### Episode 90 Principle

> Doors and chests share one lock/credential contract, and Hold is an interaction property—not a separate chest input system.

---

# Episode 91 — Keys In Loot Containers / Enemy Drops

**Classification:** UPGRADE — APPROVED ITEM/LOOT INTEGRATION.

**Phase Ownership:** Loot + Keys/Credentials + Containers + Persistence.

Detailed companions:

- `Docs/Physical_Keys_Locks_Doors_Access_Credentials_System.md`
- `Docs/Loot_Generation_Tables_Drops_Provenance_System.md`
- `Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`

## Approved Tutorial Intent

- keys can be carried by enemies/containers;
- key loot displays appropriately;
- Take / Take All must transfer keys correctly;
- boss/specific keys can gate future world access.

## Metaworld Upgrades

- Loot profile creates/transfers real key ItemInstance/CredentialID state;
- no separate `LootComponent KeyID` side-channel is required as authority;
- Take/Take All uses normal Container transactions;
- a key removed from loot container cannot be looted infinitely after commit;
- quest/boss importance is item policy/provenance, not a new inventory universe;
- door/portal/chest resolves credential from the actual possessed item/access state.

### Episode 91 Principle

> Keys can be loot because they are ordinary persistent world items with credential capability.

---

# Episode 92 — Infinite Loot Fix + Event-Driven Key/Item Tooltips

**Classification:** LOCKED / BUGFIX + UPGRADE UI CLEANUP.

**Phase Ownership:** Loot Containers + UI Data Contracts + Keys.

Detailed companions:

- `Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`
- `Docs/Physical_Keys_Locks_Doors_Access_Credentials_System.md`

## Approved Tutorial Intent

- successful loot must clear/remove source item state so it cannot be collected repeatedly;
- remove expensive tooltip bindings;
- key tooltips can use an appropriate presentation profile;
- fix rarity/upgrade-level presentation inconsistencies.

## Metaworld Upgrades

- infinite-loot prevention comes from authoritative Container transaction/revision, not manually clearing one widget struct;
- tooltip receives stable ItemInstanceID/presentation snapshot;
- item vs key display differences are presentation profiles/tags rather than fragile permanent `isKey` branching everywhere;
- key UI may hide irrelevant combat/value fields without deleting underlying physical state;
- event-driven updates remain canonical.

### Episode 92 Principle

> Loot disappears from the source because ownership/location committed once; the UI merely reflects that truth.

---

# Episode 93 — Key ID / Widget Cleanup / Craft-Upgrade Requirement Fixes

**Classification:** LOCKED + PARTIAL REJECT MAINTENANCE.

**Phase Ownership:** Keys + UI Lifecycle + Crafting/Upgrade + Currency/Professions.

Detailed companions:

- `Docs/Physical_Keys_Locks_Doors_Access_Credentials_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`
- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Item_Upgrade_Reinforcement_Enhancement_System.md`
- `Docs/Gold_Material_Commodity_Not_Currency_Rule.md`

## Approved Tutorial Intent

- pass the actual key identity rather than accepting a default zero value;
- close UI/input state cleanly;
- crafting/upgrade requirements must all be validated before commit;
- progression requirement must be checked correctly.

## Rejections / Upgrades

- do not use forced `Collect Garbage` on normal widget close as gameplay cleanup;
- release/unbind widget references/timers/input contexts normally and let engine lifecycle handle GC;
- tutorial `Gold` requirement becomes GrimKoin/PromoKoin service fee **or** physical Gold material only when the specific recipe requires Gold as material;
- generic `Crafting Level` becomes relevant Profession/Skill requirement;
- no universal requirement-check order is authoritative: server validates all requirements and returns useful prioritized failure reasons;
- physical materials and currency fees remain separate resource types.

### Episode 93 Principle

> Fix the data/lifecycle contract, not the symptom: real credential identity, normal UI cleanup, profession-aware crafting and no Gold-as-money regression.

---

# Episode 94 — Inventory Options Widget Redesign

**Classification:** UPGRADE — APPROVED PRESENTATION / MODAL ACTION CLEANUP.

**Phase Ownership:** UI + Item Context Actions + Controller/Accessibility.

Detailed companions:

- `Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`

## Approved Tutorial Intent

- consistent sizing/rounded styling;
- modal background overlay;
- close when clicking outside/canceling;
- Drop/Destroy/Cancel actions cleanly close the menu.

## Metaworld Upgrades

- action menu consumes `ItemInstanceID + ActionContext`;
- menu position-at-cursor is mouse presentation only; controller opens/focuses same actions predictably;
- do not close on literally any key if that would break controller navigation/accessibility;
- UI Back/Cancel and explicit outside-click behavior are routed through modal layer;
- actions exposed depend on item capabilities/legal/context policy;
- Destroy is not universally available for keys/evidence/leased/critical property.

### Episode 94 Principle

> The options menu is a reusable controller-complete context-action modal, not a right-click-only delete/drop popup.

---

# Episode 95 — Key Item Drop / Destroy Options

**Classification:** UPGRADE — APPROVED THROUGH GENERIC ITEM TRANSACTIONS.

**Phase Ownership:** Keys + Item Drop/Disposal + UI.

Detailed companions:

- `Docs/Physical_Keys_Locks_Doors_Access_Credentials_System.md`
- `Docs/Item_Drop_Disposal_Physical_Currency_Transaction_System.md`

## Approved Tutorial Intent

- keys can expose contextual Drop/Destroy actions where allowed;
- dropped key retains the correct identity/data and can be picked up again;
- UI refreshes after transaction.

## Metaworld Upgrades

- avoid separate permanent `DropKeyItem` and `RemoveKeyItem` transaction universes;
- generic drop/disposal operates on Key ItemInstanceID because it is a normal item with credential capability;
- runtime drop does not need a `don't set info` workaround when ItemInstance is the source of truth;
- Destroy is controlled by item/quest/evidence/property policy;
- lost/destroyed key can have world consequences; reissue/rekey paths are separate systems.

### Episode 95 Principle

> A key can be dropped like another physical item, but its credential/world significance travels with the exact ItemInstance.

---

# Episode 96 — Modular Lift / Lever

**Classification:** UPGRADE — APPROVED / NEW LIFT-TRAVERSAL DOMAIN.

**Phase Ownership:** World Interaction + Traversal + Multiplayer + Performance.

Detailed companion:

`Docs/Lift_Elevator_Lever_Traversal_System.md`

## Approved Tutorial Intent

- model simple lever with correct pivots;
- lever can be placed independently and linked to a lift;
- interact interface exposes lever action;
- Timeline can animate lever and lift;
- editor-configurable travel distances support modular placement.

## Metaworld Upgrades

- stable LiftObjectID/ControlID links controls to lift;
- lever requests action; lift state machine owns movement;
- two-stop relative-distance Timeline is valid baseline, with data-driven stop/path profiles for expansion;
- carry players/NPCs safely as moving-platform passengers;
- replicate compact motion state/start-time rather than full transform spam;
- permissions/power/obstruction/safety can block operation;
- no idle Tick.

### Episode 96 Principle

> The lever is a control endpoint; the lift is the authoritative shared traversal machine.

---

# Episode 97 — Lift Interaction Collision Fix + Notification Anti-Spam

**Classification:** LOCKED + UPGRADE MAINTENANCE.

**Phase Ownership:** Lift Traversal + Interaction Targeting + Notification Feed.

Detailed companions:

- `Docs/Lift_Elevator_Lever_Traversal_System.md`
- `Docs/Notification_Deduplication_Cooldown_Priority_System.md`
- `Docs/HUD_Notification_Feedback_System.md`

## Approved Tutorial Intent

- decorative/extra lift meshes should not generate unintended interaction overlaps;
- repeated identical failures should not spam notification feed;
- a different notification type should still be allowed to appear promptly.

## Metaworld Upgrades

- only intended query/interaction components participate in prompt targeting;
- no universal `Do Once + 5.5 second Delay` locking the entire notification system;
- notifications use DedupKey/ContextID/category/priority and data-driven cooldown/merge policy;
- identical `Locked Door`/`Not Enough Currency` messages can suppress/merge;
- different/high-priority warning can appear immediately;
- commerce messages say GrimKoin/PromoKoin, never Gold money;
- critical survival state is not represented only by a transient toast.

### Episode 97 Principle

> Interaction collision must be intentional, and notification anti-spam suppresses repetition without suppressing genuinely new information.

---

# New Cross-System Canon — Gunpowder & Ammunition Are Not Forever

Detailed companion:

`Docs/Gunpowder_Ammunition_Scarcity_Weapon_Resilience_System.md`

Owner direction locked during this intake:

- gunpowder/propellant ammunition is a finite living-world resource;
- ammunition caches/vendor stock do not respawn forever from loot/menu resets;
- the world can reach practical zero accessible firearm ammunition;
- firearms remain persistent objects but can become obsolete/historical tools when supply disappears;
- restoring production requires a legitimate industrial/world supply chain and is not guaranteed;
- GrimKoin cannot buy ammunition that physically does not exist;
- swords, bows, crossbows, spears and other older/maintainable weapon systems remain first-class and strategically important throughout Metaworld;
- other weapon families still have their own durability/material/stamina/logistics pressures, so none become infinite/easy-mode replacements;
- NPCs/factions/economy/news adapt to scarcity.

### Scarcity Principle

> The world does not promise modern ammunition forever. Players must adapt when resources, industries and strategies change.

---

# Current Modern RPG Additions From Episodes 86–97

`Door Mesh/Pivot`
-> `DoorObjectID`
-> `LockID / CredentialID`
-> `Property Access`
-> `Authoritative Open/Close`

`Scrollable Inventory UI`
-> `Large Dynamic Presentation`
-> **Finite Physical Container Capacity**
-> `Encumbrance`

`Physical Key ItemInstance`
-> `CredentialID`
-> `Door/Chest Lock`
-> `Loot / Drop / Theft / Evidence`

`Lift Control`
-> `LiftObjectID`
-> `Authoritative Motion State`
-> `Passenger Traversal`

`Notification Event`
-> `DedupKey / Priority / Cooldown`
-> `Merge / Suppress Repetition`
-> `Allow New Important Message`

`Gunpowder / Ammo Stock`
-> `Finite Supply Chain`
-> `Scarcity / Exhaustion`
-> `Firearms Lose Practical Dominance`
-> `Older Weapon Systems Become Essential`

---

# Playlist Continuation Rule

The owner indicated this playlist still has roughly 200 more videos to review. Future episodes continue in Part 11 until another safe continuation file is needed. Parts 1–11 remain the canonical intake/audit trail; detailed companion documents remain implementation authority for established domains.