# Metaworld — Wearable Backpack & Nested Container Capacity System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / persistent ItemInstance + ContainerID

## Canonical Principle

A backpack is a persistent equipment ItemInstance that owns or references its own real ContainerID. Equipping a backpack gives the character authorized access to that container; unequipping it does not convert its contents into magical extra character slots or spill them merely because a UI capacity integer decreased.

> The backpack carries its contents. The character carries the backpack.

Related canon:
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

## 1. Identity

Example:

`Backpack ItemInstanceID #B71`
-> `ContainedContainerID #C904`

The exact backpack and its contained inventory persist together across equip, unequip, storage, world drop, transfer, theft and recovery.

## 2. Capacity

A backpack definition/container profile may define:
- slots where used;
- maximum mass;
- volume;
- dimensions;
- compartments;
- allowed/forbidden tags;
- accessibility while equipped/stowed;
- condition effects on capacity where designed.

The tutorial's `+N InventorySize` is a useful UI simplification but is not Metaworld's authoritative model.

## 3. Equip

Equip flow:
1. server validates Backpack ItemInstance and Back equipment slot;
2. equipment transaction commits same ItemInstance to Back slot;
3. character inventory access graph exposes its ContainerID where permitted;
4. carried mass/volume includes backpack + contents;
5. UI refreshes available container views.

No contained ItemInstances are copied into a generic PlayerInventory array.

## 4. Unequip

Unequip moves the same backpack ItemInstance, still containing its ContainerID/content state, to an authorized destination:
- another container with sufficient capacity;
- storage;
- world drop;
- transfer/trade destination.

Its contents normally remain inside it.

Do not automatically spawn every contained item onto the ground simply because the backpack was unequipped.

## 5. Dropping a Loaded Backpack

A loaded backpack can be dropped as one world object/container relationship:

`World Backpack #B71`
-> `Container #C904`
-> same contained ItemInstances.

The contents do not need one separate loose-world actor each unless the backpack is explicitly emptied/broken/spilled by a legitimate gameplay rule.

## 6. Capacity Conflicts

If a destination cannot accept the loaded backpack because of mass/volume/container nesting policy, the transaction is rejected or another explicit policy is offered.

Never silently delete overflow items.

## 7. Nested Containers

Nested containers require cycle prevention and policy controls.

Rules may include:
- no container can contain itself directly or indirectly;
- nesting depth limits where needed;
- container-in-container compatibility;
- compressed capacity is not assumed unless explicitly designed;
- total carried mass includes nested contents.

## 8. Condition / Damage

Backpack condition can influence presentation and, where explicitly designed, container availability/capacity/security. A capacity reduction must resolve existing contents safely; it cannot delete items.

Possible policies include temporary over-capacity state, restricted new deposits, spill only after an explicit rupture event, or repair requirement.

## 9. Multiplayer / Privacy

Server owns backpack/container linkage and transfers. Other nearby clients do not need the private full contents just because they see the backpack mesh. Authorized open/loot/trade interactions request container snapshots according to permission.

## 10. UI

UI may present the backpack as:
- an equipment slot;
- a separate container tab/panel;
- part of a unified inventory view with source-container indicators.

UI must preserve which ContainerID actually owns each ItemInstance.

## 11. Performance

- loaded backpack persists as compact data when not actively opened;
- no active Actor per contained item is required;
- inventory UI refreshes from container deltas;
- nested mass/capacity aggregates can cache and invalidate on content changes rather than recalculate every frame.

## Acceptance Tests

1. Equip loaded backpack without copying/duplicating its contents.
2. Unequip loaded backpack and contents remain inside it.
3. Dropping backpack preserves same ItemInstanceID, ContainerID and contents.
4. Carried mass includes backpack and nested contents.
5. Destination capacity can reject loaded-backpack transfer safely.
6. No container cycle can be created.
7. Restart/save restores backpack-content linkage.
8. Nearby unauthorized client cannot read full backpack contents.
9. UI can show unified inventory while preserving source ContainerIDs.
10. Capacity change never silently destroys overflow.

## Core Rule

Metaworld backpacks are wearable persistent containers, not temporary inventory-size bonuses. Their ContainerID and contents travel with the same backpack ItemInstance through every legitimate world state.