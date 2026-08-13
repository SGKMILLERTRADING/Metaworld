# Metaworld — Protective Equipment Coverage & Condition System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / ItemInstance-aware

## Canonical Principle

Protective equipment uses the exact equipped ItemInstance, its semantic body coverage and its current condition. Shared gameplay resolution consults that authoritative equipment state; visible meshes and HUD bars only present it.

Related canon:
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

## 1. Exact Item Identity

A helmet, vest or other protective item keeps the same ItemInstanceID while stored, equipped, worn, damaged, repaired or dropped.

Possible persistent state:
- ItemInstanceID;
- ItemDefinitionID;
- CoverageProfileID;
- current condition;
- material/protection profile;
- quality/upgrades;
- owner/possessor;
- provenance.

Equipping never creates a second authoritative copy.

## 2. Semantic Coverage

Character anatomy maps raw skeleton/physical-surface information into stable semantic zones such as Head, Torso, Arms and Legs.

CoverageProfileID maps an equipped item to the zones it protects.

Do not make one raw bone name or one material slot the persistent identity of a body zone.

## 3. Resolution Contract

When shared gameplay resolution needs protection information it:
1. resolves the semantic body zone;
2. finds authoritative equipped protective ItemInstances covering that zone;
3. evaluates their protection profile and current condition;
4. commits any legitimate item-condition change;
5. passes the remaining gameplay result onward through the shared character systems;
6. emits equipment/UI presentation events.

Different result channels may interact differently with different materials/profiles.

## 4. Equipment Families

Helmet, vest, plate, limb protection and future protective equipment all use data-driven coverage profiles rather than one permanent `Head -> Helmet, everything else -> Vest` branch.

## 5. Condition / Durability

Condition may influence:
- protection effectiveness;
- visual wear;
- repair requirements;
- value;
- broken/unusable thresholds.

The authoritative ItemInstance owns the condition value. HUD widgets do not.

## 6. Failure State

At a configured failure threshold the definition can specify whether the item is:
- broken but still worn;
- reduced in effectiveness;
- repairable;
- salvageable;
- explicitly destroyed only where item rules permit it.

Do not silently delete a persistent item merely because a progress bar reached zero.

## 7. HUD

Authorized UI may show:
- equipped protective item icon;
- current condition percentage;
- broken state;
- useful coverage summary.

Hide/collapse presentation when no relevant item is equipped. Update from equipment/item-condition events rather than permanent Tick/property binding.

## 8. Multiplayer / Persistence

Server owns equipped ItemInstanceIDs, coverage lookup, condition changes and gameplay-relevant protection state. Save/load restores exact item condition and slot assignment. Clients receive compact state needed for presentation and cannot submit final protection values as trusted truth.

## 9. Performance

- evaluate only on relevant gameplay events;
- cache coverage lookup by equipment revision where useful;
- no per-frame protective-equipment calculation;
- UI refreshes on condition/equipment changes;
- distant visual fidelity may scale without changing authoritative equipment state.

## Acceptance Tests

1. A protective item affects only zones included in its CoverageProfileID.
2. Exact ItemInstance condition persists through equip/unequip/save/load.
3. UI cannot alter authoritative condition.
4. Failure state follows the item definition instead of silently deleting the item.
5. Unequip removes protection only after the equipment transaction commits.
6. Different protective materials/profiles can behave differently.
7. Player and NPC equipment can use the same contract where applicable.
8. Multiplayer clients cannot forge protection/condition state.

## Core Rule

Metaworld protective equipment is persistent ItemInstance state with semantic coverage and condition. Gameplay systems consult it; meshes and bars only present it.