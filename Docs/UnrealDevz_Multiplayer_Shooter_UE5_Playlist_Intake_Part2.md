# Metaworld — UnrealDevz Multiplayer Shooter UE5 Playlist Intake — Part 2

**Status:** Canonical Playlist Intake Log
**Source:** UnrealDevz Multiplayer Shooter tutorial series
**Engine Target for Metaworld:** Unreal Engine 5.8
**Runtime Direction:** Blueprint-first / multiplayer / server-authoritative / persistent

## Scope

Continuation of:
- `Docs/UnrealDevz_Multiplayer_Shooter_UE5_Playlist_Intake_Part1.md`

This Part 2 records **22 unique source entries: Episodes 24–45**.

Existing Metaworld canon is reused wherever it is already stronger. New focused companions are created only for genuinely new domains or material extensions.

---

## Episode 24 — World exit countdown + dynamic crosshair
**Classification:** UPGRADE — NEW TRANSITION DOMAIN + RANGED PRESENTATION

Keep:
- cancellable countdown when entering/leaving an exit zone;
- independent multiplayer transition state;
- smoothly animated dynamic crosshair.

Upgrade:
- transition does not become a magical save/extraction/safety rule;
- continuous Metaworld persistence remains active;
- death before transition invokes permanent-death canon;
- crosshair is local presentation of authorized aim/spread state and does not require replicating private HUD animation to other players.

Authority:
- `Docs/World_Exit_Transition_Countdown_System.md`
- `Docs/Ranged_Equipment_Magazine_Reload_FireMode_State_System.md`

## Episode 25 — Civilian / soldier AI base, roam, interaction, AI HUD
**Classification:** UPGRADE + EXISTING-CANON INTEGRATION

Keep:
- reusable AI base/profile idea;
- data-driven role/stance differences;
- navigation-based free roam;
- civilian interaction behavior;
- multiplayer-aware state replication.

Upgrade:
- use NPC role/service/state data and StateTree/Smart Object style architecture where appropriate rather than a giant closed enum graph;
- vendor behavior routes through existing NPC service/commerce systems;
- enemy/NPC HUD uses event-driven Vitals presentation;
- no every-AI global Tick for simple idle behavior.

Authority includes:
- `Docs/NPC_Combat_AI_Engagement_Death_System.md`
- `Docs/NPC_Dialogue_Service_Conversation_UI_System.md`
- `Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`

## Episode 26 — AI vendor + bounty/wanted mechanic
**Classification:** UPGRADE — NEW LAW RESPONSE COMPANION

Keep:
- civilians/vendors can react to criminal behavior;
- law/service NPC can expose legal response interactions;
- AI hostility/service availability can change according to world state.

Upgrade:
- `Wanted=true` does not globally inform every AI;
- crime/evidence/witness/jurisdiction determines legal knowledge;
- Bounty and Wanted are distinct records;
- generic `Pay Sheriff -> erase all consequences` is rejected as universal canon.

Authority:
- `Docs/Crime_Wanted_Bounty_Law_Response_System.md`

## Episode 27 — Vendor-specific item list + vendor UI population
**Classification:** LOCKED + UPGRADE — existing commerce

Keep vendor-specific offer/catalog presentation.

Upgrade:
- living vendor/business inventory uses real persistent stock containers where appropriate;
- UI offer list is a snapshot/view, not stock authority;
- price/availability revalidated on transaction.

Authority:
- `Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`
- `Docs/Commerce_Buy_Sell_Quantity_Quote_UI_System.md`

## Episode 28 — Player inventory + vendor purchase flow
**Classification:** LOCKED + UPGRADE — existing commerce

Tutorial generic `PlayerMoney` becomes canonical GrimKoin/PromoKoin ledger/payment rules.

Purchase flow remains authoritative/atomic:
- validate offer/price;
- validate accepted currency;
- validate stock and capacity;
- debit/credit/transfer together;
- refresh UI from committed state.

UI button disabled state is helpful presentation but not security.

## Episode 29 — Storage system + side-by-side inventory UI
**Classification:** LOCKED + UPGRADE — existing Container architecture

Keep:
- reusable storage interaction;
- player/storage side-by-side UI;
- multiplayer opening/closing flow.

Upgrade:
- storage has stable `ContainerID`;
- storage contents are not one globally replicated public array;
- transfers are server-authoritative ItemInstance transactions;
- access/property/lock rules remain active.

Authority:
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`

## Episode 30 — Inventory drop + automatic ranged fire + ammo/UI
**Classification:** LOCKED + UPGRADE

Keep:
- safe world drop presentation;
- equipment-defined cadence;
- finite loaded/reserve ammo;
- low-ammo HUD feedback.

Upgrade:
- drop moves same ItemInstance to a legal world location;
- cadence uses authoritative action timing rather than client delay spam;
- HUD ammo count never owns ammunition truth;
- finite-world ammunition canon remains intact.

Authority:
- `Docs/Ranged_Equipment_Magazine_Reload_FireMode_State_System.md`
- `Docs/Gunpowder_Ammunition_Scarcity_Weapon_Resilience_System.md`

## Episode 31 — Crouch locomotion / replication
**Classification:** UPGRADE — movement-state integration

Keep crouch posture, animations and multiplayer state.

Upgrade:
- Enhanced Input intent;
- Crouch is a posture/movement input to the shared Movement Resolver;
- Sprint incompatibility is state policy, not stale hardcoded speed restoration;
- animation follows authoritative/predicted movement state.

Authority:
- `Docs/Character_Action_Movement_State_Resolver_System.md`

## Episode 32 — Reloading + animation timing + temporary magazine prop
**Classification:** UPGRADE

Keep:
- full/empty checks;
- compatible reserve-ammo check;
- authored animation commit timing;
- temporary magazine presentation.

Upgrade:
- reload is an authoritative ItemInstance/ammunition transaction;
- Montage Notify cannot create ammunition;
- interruption/partial commit is data-driven;
- cosmetic magazine actor is not automatically a persistent inventory magazine.

Authority:
- `Docs/Ranged_Equipment_Magazine_Reload_FireMode_State_System.md`

## Episode 33 — Customization/repair/upgrade/salvage station foundation
**Classification:** UPGRADE — NEW EQUIPMENT SERVICE DOMAIN

Keep:
- reusable world station;
- station types/services;
- local camera/preview interaction;
- multiplayer interaction state.

Upgrade:
- one `StationID/StationProfileID` with service capabilities;
- exact equipment ItemInstance targeted;
- UI/camera are presentation only;
- upgrade/repair/salvage reuse canonical Item systems.

Authority:
- `Docs/Equipment_Attachment_Customization_Station_System.md`

## Episode 34 — Customization station UI + equipment stat presentation
**Classification:** UPGRADE

Keep multi-panel station UI, primary/secondary selection, camera transitions and detailed stat preview.

Upgrade:
- displayed stats derive from the exact ItemInstance/configuration;
- no static progress bar value becomes authoritative equipment stats;
- Base Widget/input lifecycle rules replace ad-hoc HUD removal/input restoration.

## Episode 35 — Ranged equipment feature preview: ammo types, fire modes, condition, surface feedback, customization
**Classification:** RESEARCH + FUTURE/UPGRADE

Useful confirmed directions:
- real ammunition types;
- selectable fire-mode capability;
- equipment condition/reliability;
- surface-dependent presentation;
- attachment customization.

These are integrated into existing finite-ammunition, ItemInstance, Combat and Station canon rather than copied as one tutorial graph.

## Episode 36 — Customization station NPC/presentation + service timer + UI scaling
**Classification:** UPGRADE

Keep:
- station attendant/presentation character where desired;
- dynamic category UI/grid;
- timed station job/presentation.

Upgrade:
- timer/job state is server timestamp/profile driven;
- station attendant is a service/NPC integration, not station authority;
- closing UI does not necessarily cancel a committed job unless StationProfile says so.

## Episode 37 — Dynamic attachments, proposed stat changes, equipment preview
**Classification:** LOCKED + UPGRADE

Keep dynamic data-driven attachment categories and preview.

Upgrade:
- physical attachments can be real ItemInstances;
- preview is a proposal, not mutation;
- commit validates compatibility, ownership, cost/material requirements and current revision;
- selected preview modifier never permanently changes equipment until commit.

Authority:
- `Docs/Equipment_Attachment_Customization_Station_System.md`

## Episode 38 — Crafting system preview
**Classification:** RESEARCH + EXISTING-CANON VALIDATION

Tutorial confirms:
- recipe/material details;
- skills/knowledge requirements;
- crafting UI refresh.

Metaworld already has stronger recipe, profession, crafting transaction and UI canon. No new crafting authority is created.

## Episode 39 — Crafting system Part 1 / UI + requirements
**Classification:** LOCKED + UPGRADE — existing Crafting canon

Keep dynamic recipe list/detail UI and data-driven requirements.

Upgrade:
- recipes use stable `RecipeDefinitionID`;
- learned knowledge/profession requirements remain separate;
- server reserves/consumes real materials atomically;
- crafted output creates legitimate ItemInstances;
- UI is view state.

Authority:
- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Crafting_UI_Recipe_Selection_Details_Progress_System.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`

## Episode 40 — Harvesting/melee animation setup
**Classification:** UPGRADE — existing domains

Keep melee handling/animation and tool attachment lessons.

Upgrade:
- Hatchet is exact persistent ItemInstance;
- handling uses shared combat/equipment profile;
- future harvesting actions route through the existing Resource Gathering system and legitimate tool capability/condition;
- animation/overlap never creates resource output by itself.

Authority:
- `Docs/Resource_Gathering_Harvesting_Tools_Depletion_Regeneration_System.md`
- `Docs/Combat_Weapon_Handling_Animation_Profile_System.md`

## Episode 41 — Mission area / objectives / reward container
**Classification:** UPGRADE — NEW MISSION DOMAIN

Keep:
- authored mission trigger;
- notification feedback;
- linked world actors/objectives;
- one reward result.

Upgrade:
- stable `MissionDefinitionID` + `MissionInstanceID`;
- event-driven objective progress;
- multiplayer scope/participant policy;
- reward commits once;
- reward container uses persistent ContainerID/ItemInstances;
- entering trigger repeatedly cannot duplicate the mission/reward.

Authority:
- `Docs/Mission_Event_Objective_Reward_System.md`

## Episode 42 — Backpack adds/removes inventory slots
**Classification:** PARTIAL REJECT + MAJOR UPGRADE

Useful tutorial intent:
- different backpacks provide different carrying capacity;
- capacity changes with equipment.

Rejected as canonical implementation:
- backpack merely adds a number to one PlayerInventorySize;
- unequipping automatically spawns every overflow item loose into the world.

Metaworld upgrade:
- backpack is one persistent ItemInstance with its own `ContainerID`;
- its contents remain in that container when equipped/unequipped/dropped;
- carried mass includes backpack + nested contents;
- capacity/nesting transactions never silently delete items.

Authority:
- `Docs/Wearable_Backpack_Nested_Container_Capacity_System.md`

## Episode 43 — Melee equipment switching + action montage
**Classification:** LOCKED + UPGRADE

Keep primary/secondary/melee switching and animation timing.

Upgrade:
- exact equipment ItemInstances move between stowed/ready presentation;
- one shared Handling Profile/Combat pipeline;
- Montage Notify changes approved attachment/readiness phase only;
- melee/world-resource contact goes through the appropriate Combat or Gathering system.

## Episode 44 — Frontend main menu / locker / camera views
**Classification:** UPGRADE — NEW FRONTEND DOMAIN

Keep:
- separate frontend presentation map/context where useful;
- character/locker preview;
- Head/Armor camera focus transitions;
- Settings/Character Select/Quit navigation.

Upgrade:
- menu character is a non-authoritative preview of selected CharacterID;
- preview does not own duplicate ItemInstances;
- controller-complete Base Widget/UI stack;
- heavy character/equipment assets soft-load for selected profile only.

Authority:
- `Docs/Account_Character_Profile_Frontend_Persistence_System.md`

## Episode 45 — Player profile + SaveGame/GameInstance save/load
**Classification:** PARTIAL APPROVE + MAJOR PERSISTENCE CORRECTION

Keep:
- profile UI;
- structured character/profile data;
- GameInstance for temporary map/session continuity;
- SaveGame for appropriate local settings/development uses.

Reject as persistent multiplayer authority:
- local SaveGame/GameInstance being the sole source of inventory, currency, property, progression or life/death truth.

Metaworld upgrade:
- permanent `AccountID` owns/selects distinct CharacterIDs;
- dead CharacterIDs remain dead;
- authoritative backend/world systems own persistent gameplay state;
- local SaveGame is appropriate for settings/preferences/cache, not minting world assets;
- frontend selects/presents authoritative profiles.

Authority:
- `Docs/Account_Character_Profile_Frontend_Persistence_System.md`

---

## New Companion Documents From Part 2

- `Docs/World_Exit_Transition_Countdown_System.md`
- `Docs/Crime_Wanted_Bounty_Law_Response_System.md`
- `Docs/Ranged_Equipment_Magazine_Reload_FireMode_State_System.md`
- `Docs/Equipment_Attachment_Customization_Station_System.md`
- `Docs/Mission_Event_Objective_Reward_System.md`
- `Docs/Wearable_Backpack_Nested_Container_Capacity_System.md`
- `Docs/Account_Character_Profile_Frontend_Persistence_System.md`

## Strong Existing Canon Reused

- persistent ItemDefinitionID / ItemInstanceID / ContainerID inventory;
- server-authoritative equipment;
- NPC services/commerce;
- crafting recipes/professions/transactions;
- harvesting/resource depletion;
- combat handling/result architecture;
- permanent character death;
- event-driven UI/input stack;
- finite ammunition/scarcity.

## Important Locked Corrections

1. Exit zones coordinate transition; they do not decide whether Metaworld saves.
2. Dynamic crosshair is local presentation and does not need replicated widget motion.
3. Wanted/Bounty is evidence/jurisdiction/legal state, not one global hostility Boolean.
4. Vendor purchase uses canonical currency/stock transactions, not client `PlayerMoney -= Price` truth.
5. Storage is a normal persistent ContainerID.
6. Ranged cadence/reload/ammo state is authoritative and ItemInstance-aware.
7. Crouch feeds the shared Movement Resolver.
8. Customization station previews proposed equipment changes before one validated commit.
9. Mission rewards commit once and use real persistent items/containers.
10. Backpack is a wearable nested container, not just `InventorySize += N`.
11. Main-menu preview actors do not own gameplay state.
12. Local SaveGame/GameInstance are not authoritative multiplayer persistence for inventory/currency/death/property.

## Current Playlist Count

**UnrealDevz Multiplayer Shooter playlist: 45 unique entries reviewed.**

Next unique tutorial from this source will be **Episode 46**.

## Core Rule

This playlist continues to provide strong multiplayer/networking implementation research. Metaworld absorbs the useful transition, AI, ranged-equipment, station, mission, backpack and frontend patterns while preserving its persistent-world ItemInstance, economy, law and permanent-death architecture.