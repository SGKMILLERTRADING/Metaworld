# Metaworld — Ranged Equipment Magazine, Reload, Fire-Mode & Crosshair State System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / ItemInstance-aware / finite-ammunition compatible

## Canonical Principle

Ranged-equipment operation is persistent state belonging to the exact equipped ItemInstance and its legitimate ammunition supply. Fire mode, loaded quantity, reload state, condition and aiming presentation are coordinated through the shared Combat/Equipment/Ammo systems.

> A HUD counter does not create ammunition, a reload montage does not refill a magazine, and switching equipment cannot rewrite a previously committed ranged action.

Related canon:
- `Docs/Gunpowder_Ammunition_Scarcity_Weapon_Resilience_System.md`
- `Docs/Ranged_Action_Source_Snapshot_Provenance_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Quickslot_Hotbar_Item_Action_Assignment_System.md`

## 1. Exact Equipment State

A ranged ItemInstance can expose compact persistent/authoritative operational state such as:
- ItemInstanceID;
- compatible ammunition profile;
- current loaded quantity;
- capacity/profile reference;
- selected fire-mode profile;
- condition/durability;
- ready/stowed state;
- attachment revision;
- action/reload state.

Do not store authoritative loaded quantity only in HUD text or a spawned presentation Actor.

## 2. Fire Modes

Supported fire modes are data-driven capabilities, for example:
- single activation;
- repeated activation while input remains held;
- bounded burst profiles where explicitly authored.

The exact input key is not canonical. Enhanced Input exposes an intent such as `IA_MW_FireModeCycle`.

Server validates that the current ItemDefinition/attachment configuration permits the requested mode.

## 3. Cadence

Rate/cadence comes from the item/action profile and effective modifiers. The tutorial's retriggerable-delay pattern is useful for prototyping, but production state should use explicit action timing/timestamps so cadence remains stable under latency and cannot be accelerated by client event spam.

## 4. Ammunition Consumption

Each accepted ranged action resolves legitimate loaded ammunition and consumes the appropriate amount exactly once.

No action may create infinite ammunition. World scarcity, caliber/type compatibility, stacks/lots and source provenance remain governed by the existing ammunition architecture.

## 5. Reload Transaction

Conceptual reload flow:

`RequestReload(ItemInstanceID)`
-> item supports reload?
-> not already full?
-> compatible reserve ammunition available?
-> current action/state permits it?
-> start `Action.Combat.Reloading`
-> reserve/identify compatible source quantity
-> presentation montage
-> at authored commit phase, server transfers legitimate quantity into loaded state
-> update source container/stack and ItemInstance operational state
-> complete/cancel according to policy.

A montage notify marks an authored presentation/commit phase but does not create ammunition by itself.

## 6. Partial Reload / Interruption

Definitions can specify whether interruption:
- leaves no transfer before commit;
- preserves an already committed partial transfer;
- uses per-round/per-stage commit points;
- requires restarting the process.

Do not blindly restore a hardcoded full amount after any reload animation.

## 7. Magazine / Dropped Presentation

A temporary magazine-like prop may be spawned for animation presentation and cleaned up after significance timeout. It is not automatically a persistent inventory item unless the item's design explicitly models detachable magazine ItemInstances.

If Metaworld later models physical detachable magazines, they must use the normal ItemInstance/Container transaction system rather than a cosmetic actor becoming inventory truth.

## 8. Condition / Jam State

Equipment condition may influence reliability according to a data-driven gameplay profile. Any temporary malfunction state is server-authoritative, bounded and repair/maintenance-aware.

Do not use a reload counter as universal condition truth. The exact ItemInstance's persistent condition remains authoritative.

## 9. Surface / Impact Presentation

Surface material/body-zone result can select local audiovisual feedback, but the surface effect does not decide the authoritative result. Shared Combat/World result processing remains the source of truth.

## 10. Dynamic Crosshair

Crosshair spread is local presentation derived from an authorized aim/accuracy snapshot such as:
- movement velocity;
- airborne/crouched/stance state;
- aiming state;
- equipment handling/accuracy profile;
- recent action/spread impulse;
- injury/condition modifiers where designed.

The tutorial's `FInterpTo` smoothing is approved for presentation.

The crosshair itself does not need to replicate as widget animation to other clients. Remote players need character/action state, not another player's private HUD state.

## 11. Crouch / Movement Resolver Integration

Crouch declares a movement/posture state. It does not directly own every speed write.

The Character Movement Resolver combines crouch with Sprint restrictions, Encumbrance, injuries, Conditions, aiming, water/traversal and other current facts.

## 12. Networking

Server owns:
- accepted ranged action;
- cadence legality;
- loaded quantity;
- compatible ammunition transfer;
- reload commit;
- equipment condition state;
- hit/result validation.

Owning client predicts/presents input/camera/crosshair where safe. Other clients receive compact replicated action/equipment state and audiovisual events relevant to them.

## 13. Performance

- no permanent fire/reload Tick;
- use action timestamps/timers only while active;
- crosshair updates only for the local visible HUD;
- impact presentation is significance-scaled;
- ammo/UI refreshes on state changes;
- debug traces/effects disabled outside development.

## Acceptance Tests

1. Accepted shot consumes legitimate loaded ammo exactly once.
2. Empty loaded state prevents normal fire.
3. Reload cannot exceed capacity or available compatible reserve.
4. Client cannot speed up authoritative cadence.
5. Switching equipment cannot alter a previously committed ranged-source snapshot.
6. Reload interruption follows the selected definition policy.
7. Crosshair can be hidden without changing accuracy/gameplay truth.
8. Crosshair is local HUD presentation rather than replicated UI authority.
9. Crouch composes with the Movement Resolver instead of restoring stale speeds.
10. Condition/jam state persists on the exact ItemInstance where designed.

## Core Rule

Metaworld ranged-equipment state belongs to the exact persistent ItemInstance and shared ammunition/action systems. Fire mode, reload, condition and crosshair presentation all derive from that truth; none of them can mint ammo or bypass authoritative combat state.