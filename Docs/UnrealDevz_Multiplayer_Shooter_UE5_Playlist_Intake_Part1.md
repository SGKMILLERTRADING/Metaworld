# Metaworld — UnrealDevz Multiplayer Shooter UE5 Playlist Intake — Part 1

**Status:** Canonical Playlist Intake Log
**Source:** UnrealDevz Multiplayer Shooter tutorial series
**Engine Target for Metaworld:** Unreal Engine 5.8
**Runtime Direction:** Blueprint-first / multiplayer / server-authoritative / persistent

## Scope

This tracker starts a new source-specific intake. Playlist-local numbering restarts at **Episode 1** so this source remains auditable independently of the completed Unreal Click.o playlist.

This Part 1 records **23 unique source entries: Episodes 1–23**.

The source contains many multiplayer-shooter implementations that overlap existing Metaworld inventory/equipment/combat canon. Overlap is used as validation and multiplayer implementation research; duplicate systems are not created when Metaworld already has a stronger canonical contract.

## Episode Classifications

### Episode 1 — Multiplayer Shooter / Vigor-style project introduction
**Classification:** RESEARCH + VALIDATION

Useful source intent:
- multiplayer locomotion/replication;
- inventory/equipment focus;
- primary/secondary switching;
- death inventory bag concept;
- future compass.

Metaworld upgrade:
- confirms value of server-authoritative equipment/pickup and death-container transfers;
- no new shooter-only inventory authority;
- same-character respawn/death loop is not accepted where it conflicts with permanent-death canon.

### Episode 2 — Master Item / Data Table / world interaction / replication
**Classification:** LOCKED + UPGRADE

Keep:
- data-driven item definitions;
- reusable world item actor concept;
- authoritative multiplayer pickup;
- replicated presentation/state.

Upgrade:
- `ItemDefinitionID` + `ItemInstanceID` remain separate;
- ordinary item catalog entries do not require a child Blueprint each;
- overlap only provides candidates;
- `Destroy Actor` happens only after successful authoritative ItemInstance transfer.

Authority:
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`

### Episode 3 — Pickup item widget
**Classification:** UPGRADE — presentation

Keep icon/name proximity presentation.

Upgrade:
- interaction component owns current candidate/target;
- visibility follows candidate/relevance events or bounded local checks rather than permanent world-wide distance work;
- widget reads an Item presentation snapshot and does not own item state.

### Episode 4 — Project preview / shelter exit / save concept
**Classification:** RESEARCH + FUTURE

Keep as research:
- pickup stacking feedback;
- varying item/combat results;
- footsteps;
- transition/exit concept.

Do not lock a Vigor-style shelter extraction loop into Metaworld. Metaworld is a persistent living world; any future safehouse/property/travel transition must respect world persistence, ownership, risk and no magical global save-zone assumptions.

### Episode 5 — Inventory open/close + initial UI
**Classification:** LOCKED + UPGRADE

Keep:
- reusable inventory widget;
- explicit open/close lifecycle;
- weight/capacity presentation.

Upgrade:
- Enhanced Input + shared UI stack/Base Widget;
- no global pause in normal multiplayer;
- controller-complete focus/navigation;
- money display uses canonical GrimKoin/PromoKoin systems rather than tutorial generic money state.

### Episode 6 — Equipment/weapon inventory slot UI
**Classification:** UPGRADE — presentation

Useful layout ideas for:
- Head/Chest/Backpack equipment;
- Primary/Secondary/Melee presentation;
- attachment sub-slots.

UI slots remain views of `BPC_MW_Equipment` and future attachment state, not inventory ownership.

### Episode 7 — Dynamic inventory grid UI
**Classification:** UPGRADE

Keep dynamic slot/list construction and clearing stale children when rebuilding.

Upgrade:
- large inventories should virtualize/paginate rather than creating unlimited widgets;
- UI responds to inventory deltas/events;
- `InventorySize` is a container rule, not necessarily one universal character integer.

### Episode 8 — Pickup stacking / carried weight / inventory display
**Classification:** LOCKED + UPGRADE

Keep:
- stack compatibility search;
- quantity display;
- carried-load feedback.

Upgrade:
- authoritative stack compatibility preserves condition/provenance where relevant;
- carried mass includes equipped equipment;
- UI rebuilds/event updates never create inventory truth.

### Episode 9 — Multiple item categories / Data Table entries
**Classification:** UPGRADE

Keep data-driven definitions and varied world presentations.

Upgrade:
- Medkit, weapons, helmets, armor, backpacks etc. use stable catalog IDs/tags;
- ordinary item definitions use data rather than one child Blueprint per item unless unique behavior requires it;
- validity checks belong at system boundaries, not as a substitute for clear ownership/lifecycle.

### Episode 10 — Inventory weight limits + item tooltip
**Classification:** LOCKED + UPGRADE

Keep:
- capacity rejection feedback;
- contextual item tooltip;
- category-specific presentation.

Upgrade:
- no universal `100 kg` rule;
- capacity may use mass, volume, slots, compartments and allowed tags;
- tooltip uses ItemDefinition/ItemInstance snapshot;
- conditional rows are data-driven rather than a giant weapon-only UI branch.

### Episode 11 — Pickup notifications
**Classification:** LOCKED + UPGRADE

Keep slide/fade pickup feedback.

Upgrade:
- notification is emitted only after committed transfer;
- duplicate/high-frequency pickups may merge;
- local HUD presentation owns widget lifetime, not item state;
- use existing notification dedup/cooldown rules.

### Episode 12 — Primary weapon equip / replicated stowed presentation
**Classification:** LOCKED + UPGRADE

Keep:
- server-authoritative equip request;
- replicated equipment presentation;
- socket-based stowed visual.

Upgrade:
- no authoritative duplicate weapon Actor is created from an inventory row;
- exact Weapon ItemInstanceID becomes equipped/stowed state;
- replicated slot/readiness state lets clients reconstruct presentation;
- RepNotify is useful presentation/state propagation, not a reason to duplicate item ownership.

### Episode 13 — Secondary weapon equip / unequip
**Classification:** LOCKED + UPGRADE

Primary/secondary equipment slots become data-driven loadout/equipment slots. Unequip moves the same ItemInstance to an authorized container/world destination rather than destroying the item.

### Episode 14 — Weapon swapping / stance / weapon wheel preview
**Classification:** UPGRADE

Keep server-authoritative readiness switching and weapon-wheel presentation research.

Upgrade:
- Enhanced Input actions replace hardcoded numeric keys;
- handling/readiness profile derives animation stance;
- swapping changes presentation/readiness of existing equipped ItemInstances;
- controller radial/weapon-wheel selection is strongly compatible with Metaworld input canon.

### Episode 15 — Physical drop / context menu / equip montage
**Classification:** LOCKED + UPGRADE

Keep:
- physical loose-item presentation when dropped;
- context menu actions;
- authored equip timing with Montage Notifies.

Upgrade:
- drop is an authoritative ItemInstance location transaction;
- safe spawn/collision initialization before physics;
- menu supports controller focus as well as right-click/double-click;
- montage notify changes presentation phase but cannot create/delete ownership.

### Episode 16 — Multiplayer weapon firing / Health / death inventory drop
**Classification:** UPGRADE + PERMANENT-DEATH CORRECTION

Useful:
- server-owned action/result flow;
- multiplayer audiovisual feedback;
- Vitals HUD;
- death state cleanup;
- transferring reachable carried inventory into a death/corpse container.

Metaworld correction:
- the dead CharacterID remains dead;
- physical possessions use estate/corpse/container/world rules;
- no same-character resurrection is inferred from this tutorial.

### Episode 17 — Body-zone modifiers + respawn system
**Classification:** SPLIT: UPGRADE / REJECT-AS-CANON

**UPGRADE:**
- physical materials/bones can map authored hit surfaces to semantic body zones;
- body zone can affect shared result/armor coverage.

Authority:
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Armor_Coverage_Durability_Protection_System.md`

**REJECT for normal Metaworld character death:**
- random PlayerStart respawn of the same dead character.

Metaworld permanent-death rule:
`Character A dies -> Character A stays dead -> account survives -> new Character B identity/legacy process`.

The GameMode spawning/UI techniques remain useful for initial spawn, admin/test modes, or creation of the new post-death character, but not resurrection of Character A.

### Episode 18 — Floating result widget + respawn screen
**Classification:** SPLIT: UPGRADE / REINTERPRET

Keep floating-result presentation and death-state UI lifecycle.

Reinterpret the Respawn button for Metaworld as a future **Death / Legacy / Create New Character** flow, not `Respawn Same Character`.

Normal gameplay world continues while the account is in that transition UI.

### Episode 19 — Free starter template / armor preview
**Classification:** RESEARCH

Template/project-file availability is not Metaworld canon.

Useful preview themes:
- Vitals HUD;
- protective equipment condition bars;
- equipment protection before character consequence.

These feed the canonical protective-equipment system rather than creating a separate shooter Stats architecture.

### Episode 20 — Backpack / helmet equipment + HUD
**Classification:** LOCKED + UPGRADE

Keep:
- visible worn backpack/helmet presentation;
- replicated socket/mesh state;
- equipment icons and HUD.

Upgrade:
- same ItemInstanceID across inventory/equipped/world;
- avatar-fitting/coverage profiles remain authoritative;
- HUD is event-driven presentation.

### Episode 21 — Supply delivery + protective equipment condition
**Classification:** UPGRADE — NEW LOGISTICS DOMAIN + EQUIPMENT EXTENSION

Supply-delivery concept creates:
- stable WorldEventID;
- one persistent delivered ContainerID;
- one manifest/current contents state;
- authored delivery presentation;
- safe final placement;
- Event Ledger/News integration where significant.

Authority:
- `Docs/World_Logistics_Delivery_System.md`

Protective equipment uses semantic coverage + exact ItemInstance condition rather than a generic armor health variable.

Authority:
- `Docs/Armor_Coverage_Durability_Protection_System.md`

### Episode 22 — Project content/features preview
**Classification:** RESEARCH + FUTURE

Useful future leads:
- compass;
- map icons;
- attachment customization;
- optional auto-pickup;
- character preview;
- equipment/accessory iconography.

Do not import Patreon/project assets as project dependencies merely because the tutorial uses them.

Future attachment/compass/map features should get focused canon when implementation tutorials provide enough detail.

### Episode 23 — Unequip + Auto-Pickup / Auto-Equip
**Classification:** LOCKED + UPGRADE

Keep optional convenience setting.

Canonical rule:
- Auto-pickup automates the normal pickup request;
- Auto-equip is an optional second transaction after pickup;
- neither bypasses ownership, capacity, stacking, equipment conflicts, encumbrance or server authority.

Authority:
- `Docs/Auto_Pickup_Interaction_Preference_System.md`

## New Companion Documents From Part 1

- `Docs/Armor_Coverage_Durability_Protection_System.md`
- `Docs/World_Logistics_Delivery_System.md`
- `Docs/Auto_Pickup_Interaction_Preference_System.md`

## Existing Canon Reused / Validated

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Real_Time_Life_Utilities_Advertising_VIP_GrimKoin_Death_Legacy.md`
- `Docs/UI_Base_Widget_Modal_Input_Lifecycle_System.md`
- `Docs/Notification_Deduplication_Cooldown_Priority_System.md`

## Permanent Death Compatibility Rule

The shooter tutorial's ordinary respawn loop is not imported into normal Metaworld character life.

Canonical flow remains:

`Character A dies permanently`
-> `Character A identity is retired/dead`
-> `physical inventory/property follow corpse/estate/world rules`
-> `underlying account survives`
-> `player enters death/legacy/new-character flow`
-> `Character B is a new identity`.

Random spawn-point selection may be reused for legitimate initial/new-character/test placement, but never as proof that the dead character resurrected.

## Multiplayer Lessons Retained

This playlist is particularly useful for validating:
- server-authoritative pickup/equipment actions;
- replicated equipment presentation;
- owner/private inventory visibility;
- world-item drop synchronization;
- late-join presentation reconstruction;
- death/container transfers;
- network-aware HUD/client presentation.

Metaworld keeps these multiplayer lessons while preserving its stronger persistent ItemInstance, economy, law, permanent-death and living-world rules.

## Current Playlist Count

**UnrealDevz Multiplayer Shooter playlist: 23 unique entries reviewed.**

Next unique tutorial from this source will be **Episode 24**.

## Core Rule

> This multiplayer-shooter playlist is a source of networking, equipment, UI and world-logistics implementation lessons. Metaworld absorbs the useful multiplayer patterns without replacing its persistent ItemInstance architecture or permanent-death world rules.