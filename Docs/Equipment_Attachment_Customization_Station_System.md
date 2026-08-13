# Metaworld — Equipment Attachment Customization Station System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / ItemInstance-aware / data-driven

## Canonical Principle

A customization/repair/upgrade station is a world service that operates on an exact persistent equipment ItemInstance. Attachments, repairs, upgrades and salvage use explicit definitions, requirements and transactions; the station UI and preview never become a second owner of the equipment.

> The station previews a proposed configuration, validates it, and commits one authoritative ItemInstance change.

Related canon:
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Item_Upgrade_Reinforcement_Enhancement_System.md`
- `Docs/Generated_Item_Base_Stats_Affixes_Quality_System.md`
- `Docs/NPC_Dialogue_Service_Conversation_UI_System.md`
- `Docs/Avatar_Preview_Lifecycle_Performance_System.md`

## 1. Station Identity

Suggested records:
- `StationID`;
- `StationProfileID`;
- supported service tags;
- owner/business/property;
- access permissions;
- operating state;
- tool/power/facility requirements;
- service duration policy;
- camera/preview profile;
- accepted equipment categories.

Service tags may include:
- `Service.Equipment.Customize`;
- `Service.Equipment.Repair`;
- `Service.Equipment.Upgrade`;
- `Service.Equipment.Salvage`.

## 2. Attachment Definitions

Use stable `AttachmentDefinitionID`/capability tags rather than one hardcoded button per accessory.

Possible attachment slots:
- optic;
- muzzle/profile slot;
- magazine/ammo-feed presentation slot;
- grip/support slot;
- stock/body slot;
- cosmetic/utility slots;
- future equipment-specific sockets.

Compatibility is data-driven by the equipment definition and attachment profile.

## 3. Exact ItemInstance State

An attachment transaction targets:
- equipment `ItemInstanceID`;
- attachment `ItemInstanceID` where the attachment is a real owned physical item;
- attachment slot/profile;
- current equipment revision.

Installing/removing a physical attachment moves the same ItemInstance between container and equipment attachment state. It is not duplicated by the station.

## 4. Preview vs Commit

Station UI can build a local proposal:
- selected equipment;
- selected attachment/service;
- proposed stat changes;
- visual preview;
- cost/material/time requirements;
- compatibility warnings.

Nothing becomes authoritative until `RequestCommitStationOperation(...)` succeeds.

Canceling preview returns to the unchanged ItemInstance state.

## 5. Dynamic Stat Preview

Stats shown in the station are derived from the proposed configuration using the same modifier rules used by actual equipment state.

Do not permanently add preview values to the player/equipment simply because a button was hovered.

UI may display before/after values, deltas and tradeoffs, but authoritative stats change only after commit.

## 6. Repair / Upgrade / Salvage

Repair reuses item-condition rules.

Upgrade reuses the canonical Item Upgrade system, normally preserving the same ItemInstanceID.

Salvage is an explicit irreversible transaction that consumes/transforms the source item according to a SalvageProfile and creates legitimate outputs once. It never comes from deleting a presentation Actor and guessing rewards client-side.

## 7. Camera / Preview

Temporary station cameras/preview actors are presentation only.

Rules:
- activate only during interaction;
- restore the previous local camera/UI state cleanly;
- preview item is a non-authoritative representation of the exact ItemInstance/proposal;
- no hidden permanent SceneCapture unless profiling justifies it;
- station preview actors/components clean up when closed.

## 8. Station Time / Availability

Some operations may have duration.

Use timestamps/job state rather than one fragile UI countdown as truth. If the player closes UI, the server job can continue or cancel according to the StationProfile.

Station shutdown, loss of power/access, world events or ownership changes can invalidate future operations according to policy.

## 9. NPC / Business Integration

A station may be:
- player-owned;
- business-owned;
- profession-operated;
- NPC service;
- public facility;
- property equipment.

Service fees use canonical GrimKoin/PromoKoin where accepted; physical materials/tools are separate ItemInstances/resources.

## 10. Multiplayer

Server owns compatibility, ownership, inventory transfers, cost/material consumption, item revision and final attachment configuration.

Multiple users interacting with the same station/equipment are protected by revision/reservation rules.

## 11. UI / Controller

Dynamic grid/list population is approved. Must support KBM, Xbox-style and PlayStation-style navigation, category switching, preview, confirm/cancel and close/back.

No essential operation is mouse-only.

## 12. Performance

- populate/update UI from station/equipment revisions rather than Tick;
- soft-load preview assets;
- station lights/ambient animation use significance/proximity policies;
- no permanent preview actor for every station;
- cache compatible-definition lists where safe.

## Acceptance Tests

1. Station selects the exact ItemInstance being modified.
2. Preview does not mutate authoritative state.
3. Cancel leaves equipment unchanged.
4. Physical attachment ItemInstance is not duplicated during install/remove.
5. Incompatible attachment is rejected.
6. Upgrade preserves ItemInstance identity under normal reinforcement rules.
7. Repair changes exact item condition through one transaction.
8. UI closes/restores camera/input cleanly.
9. Two users cannot commit stale conflicting revisions to the same item.
10. Save/reconnect restores committed attachment configuration.

## Core Rule

Metaworld equipment stations are transaction-driven world services. They preview proposed ItemInstance changes locally and commit only validated attachment, repair, upgrade or salvage operations through the existing equipment/item systems.