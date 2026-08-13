# Metaworld — Auto-Pickup & Interaction Preference System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative transfer / player-configurable presentation

## Canonical Principle

Auto-pickup is a player preference that may request eligible item transfers automatically when the normal interaction system identifies a valid nearby item. It never bypasses ownership, capacity, stacking, access, reservation or server validation.

> Auto-pickup automates the request, not the rules.

Related canon:
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Inventory_Stack_Quantity_Selection_Drop_Transfer_UI_System.md`

## 1. Preference Scope

Possible settings:
- AutoPickupEnabled;
- allowed item categories/tags;
- minimum/maximum value or rarity filters where useful;
- auto-equip policy for specific categories;
- notification preference;
- capacity warning preference.

The setting belongs to the player/account preference layer, not to item ownership truth.

## 2. Candidate Detection

The existing Interaction system may expose eligible nearby world-item candidates from overlap/query events.

Auto-pickup does not run an unlimited world scan or per-frame search for every item.

## 3. Transfer Flow

`Eligible nearby ItemInstanceID`
-> preference allows this item?
-> submit normal `RequestPickup(ItemInstanceID, TargetContainerID)`
-> server validates reach/access/ownership/capacity/stacking/reservation
-> commit transfer or reject
-> emit one pickup result/notification.

The same request path is used by manual pickup.

## 4. Auto-Equip

Optional auto-equip is a second policy after a successful pickup.

Examples:
- empty Head slot + allowed helmet -> optionally request equip;
- empty Back/Backpack slot -> optionally request equip;
- weapon category -> follow loadout/equipment policy.

Auto-equip still uses `BPC_MW_Equipment` and can fail independently if slot/conflict/capacity rules reject it.

Do not merge pickup and equip into one client-owned mutation.

## 5. Capacity / Encumbrance

Auto-pickup cannot exceed container limits or bypass carried-load/encumbrance rules.

A rejected item remains in the world and can provide a concise reason such as capacity, access, reservation or incompatible item state.

## 6. Ownership / Crime

Auto-pickup does not imply permission to take every nearby item.

Items with ownership/restriction/theft consequences still follow the same world-law/interaction policy as manual pickup. Player preference may optionally disable auto-pickup for owned/restricted items by default.

## 7. UI / Feedback

Pickup notifications are event-driven and can show item icon/name/quantity. Repeated low-value pickups may merge according to notification policy.

Controller, keyboard and mouse players receive equivalent settings/options.

## 8. Multiplayer / Anti-Duplication

Server commits each transfer exactly once. Two players attempting the same loose item cannot both receive it. Auto-pickup preferences remain local/user-specific, while the resulting item transfer is authoritative.

## 9. Performance

- use bounded interaction/proximity candidates;
- no global item scanning;
- no permanent Tick solely for auto-pickup;
- batch/merge notifications where high pickup frequency warrants it;
- auto-equip evaluation runs only after relevant successful transfers.

## Acceptance Tests

1. Disabling auto-pickup returns to manual interaction without changing item rules.
2. Auto-pickup cannot exceed capacity.
3. Auto-pickup cannot duplicate an ItemInstance contested by two players.
4. Restricted/owned item follows normal authorization policy.
5. Auto-equip uses the existing Equipment transaction.
6. Failed auto-equip does not delete the picked-up item.
7. Notifications reflect committed transfers only.
8. No permanent world scan/Tick is required.

## Core Rule

Metaworld auto-pickup is convenience automation over the existing authoritative interaction/pickup transaction. It can request pickup and optional equip, but it cannot bypass world ownership, inventory capacity or ItemInstance identity.