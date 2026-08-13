# Metaworld — Ranged Action Source Snapshot & Provenance System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / immutable source snapshot / ItemInstance-aware

## Canonical Principle

A committed ranged action captures the authoritative source state that is supposed to remain fixed for that shot/execution. Later weapon switches, equipment changes, temporary buffs or UI state cannot retroactively rewrite an already-released projectile.

> Commit the source once; resolve the target when contact occurs.

Related canon:
- `Docs/Archery_Aiming_Draw_Crosshair_Projectile_Ammo_System.md`
- `Docs/Ranged_Weapons_Bow_Ammo_Quiver_Container_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Ability_Damage_Critical_Resolution_System.md`
- `Docs/Item_Infusion_Enchant_Visual_State_System.md`

## 1. Snapshot Timing

Create the authoritative source snapshot at the action's commitment/release point, after legality and resource/ammunition validation but before the projectile can be affected by later loadout changes.

For an arrow this commonly means:
`valid bow action -> reserve/consume ammo -> build source snapshot -> launch projectile`.

Do not read the attacker's current equipped weapon again at impact time to determine what the already-fired arrow should have been.

## 2. Suggested Source Snapshot

Conceptual `S_MW_RangedSourceSnapshot` may include:
- SourceSnapshotID;
- CombatActionInstanceID / AbilityExecutionID;
- source CharacterID;
- exact weapon ItemInstanceID;
- exact ammo definition/lot provenance where applicable;
- attack/spell/ability definition IDs;
- relevant effective source stats/modifiers already approved for snapshotting;
- active infusion/effect applications that belong to the shot;
- critical/weak-point eligibility rules, not final target-dependent result;
- launch timestamp/revision;
- authoritative random seed/context where needed.

The snapshot should be compact and contain only state that must remain fixed for this action.

## 3. What Stays Live Until Impact

Do **not** snapshot target defenses at fire time.

At contact, current target state can still matter:
- current armor/coverage;
- current resistance;
- current Block/Parry/Dodge window;
- target Conditions;
- body zone actually contacted;
- target alive/damageable state;
- world obstruction/collision result.

This means the attacker cannot stat-swap after firing, while the defender can still legitimately change state before impact.

## 4. Weapon-Switch Exploit Prevention

Example:

`Bow A fires Arrow #Shot72`
-> source snapshot records Bow A and its approved stats/effects
-> player switches to stronger Sword/Staff/Bow B
-> Arrow #Shot72 impacts
-> result still uses the source snapshot from Bow A.

The reverse is also true: switching to a weaker item after release cannot reduce or invalidate an already-committed legal shot unless the action definition explicitly supports remote cancellation.

## 5. Ammo / Effect Provenance

If the projectile came from Poison Arrow ammunition, Fire-infused equipment, a Rapid Fire ability or another approved source, the snapshot records the relevant exact source/effect IDs.

Do not mutate the player Stats component by "equipping an arrow type" merely so the projectile can read those temporary stats later. Ammo contribution belongs to the shot source/ammo data.

## 6. Breakables / Other Targets

Projectile/result routing uses target capabilities/interfaces/profiles such as Damageable/Breakable rather than one fragile actor-tag branch.

A crate, character or other valid world object can receive the correct shared result path according to its capability and damage policy.

## 7. Persistence / Network

Ordinary short-lived projectiles do not need full persistent save records, but the server owns the authoritative snapshot for their lifetime.

Long-lived/special projectiles can persist the compact snapshot/provenance if world design requires it.

Clients may receive enough source data for prediction/presentation but cannot replace the authoritative snapshot.

## 8. Performance

- snapshot only on committed ranged actions;
- keep snapshot compact;
- do not clone the entire player Stats/Inventory structs into every projectile;
- store stable IDs plus the specific resolved values needed for deterministic outcome;
- discard short-lived snapshot state when projectile/action is definitively complete.

## Acceptance Tests

1. Firing with Bow A then switching to Bow B does not alter the in-flight shot's source result.
2. Ammo-specific effect metadata remains the same after weapon/ammo selection changes.
3. Target armor/resistance at impact time still affects the result.
4. Target can legitimately Block/Dodge according to its current state at impact.
5. Client cannot replace the authoritative source snapshot.
6. Projectile does not need a copied full player Stats struct.
7. Breakable targets use shared capability/result routing rather than one tag-only branch.
8. Save/reconnect cannot duplicate consumed ammunition or reroll the committed shot.

## Core Rule

Metaworld locks the source facts of a committed ranged action at release and resolves target-dependent facts at contact. This prevents stat-swapping exploits without freezing the living defender/world state.