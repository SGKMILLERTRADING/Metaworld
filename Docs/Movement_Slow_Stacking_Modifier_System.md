# Metaworld — Movement Slow Stacking & Modifier System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / status-driven / server-authoritative / event-driven

## Canonical Principle

Movement slows are Status/Condition modifiers that feed the shared Character Movement Resolver. Multiple active slows are tracked by source and combined according to a data-driven stacking policy. No Condition directly owns MaxWalkSpeed.

> Status effects declare movement influence; the Movement Resolver computes the final movement result together with Sprint, Encumbrance, swimming, blocking, injuries and traversal.

Related canon:
- `Docs/Status_Effects_Conditions_Buffs_Debuffs_System.md`
- `Docs/Combat_Status_Effect_Application_DoT_Resistance_Visual_System.md`
- `Docs/Character_Action_Movement_State_Resolver_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

## 1. Slow Identity

Use stable ConditionDefinitionID / ActiveConditionID records instead of five hardcoded slow enums as world truth.

A slow definition may include:
- movement modifier profile;
- magnitude/curve;
- duration;
- source identity;
- stacking group;
- stacking policy;
- immunity/resistance tags;
- minimum/maximum legal output;
- presentation profile.

## 2. Source-Aware Active Slows

Track each active source independently so removing one does not erase another.

Example:
- Ice Spike Slow 20%;
- Poison Slow 10%;
- Injury Slow 15%.

If the stacking group policy is `StrongestOnly`, effective slow is 20% while all three ActiveCondition records still exist for their own durations and other effects.

## 3. Stacking Policies

Supported policies may include:
- StrongestOnly;
- Additive with cap;
- Multiplicative;
- RefreshSameSource;
- ExclusiveGroup;
- custom curve/profile.

The tutorial's `highest percentage wins` is approved as one useful default for a Slow stacking group, not a universal rule for every movement effect.

## 4. Movement Resolver Integration

The Status Effect manager exposes the current effective movement modifier(s) after stacking resolution.

The Movement Resolver combines them with:
- base movement profile;
- Sprint/FastSwim;
- Encumbrance;
- Block/Guard state;
- drinking/rest/action restrictions;
- water/traversal;
- injury;
- other buffs/debuffs.

Do not move global SetMovementSpeed ownership into the Conditions component. Conditions provide inputs; the Movement Resolver owns outputs.

## 5. Sprint Interaction

A slow may:
- reduce normal/sprint speed;
- increase exertion cost;
- prohibit Sprint above a configured severity;
- leave Sprint permitted but slower.

If Sprint becomes illegal because of a slow, Sprint state/action reconciles cleanly. When the slow ends, current movement is recomputed from the remaining facts rather than restoring a stale numeric default.

## 6. Duplicate Sources

If two sources apply the same ConditionDefinition, each ActiveCondition/source record follows its stack/refresh policy.

Do not rely only on an integer duplicate counter without retaining enough source identity to remove the correct effect, preserve duration/provenance, and support dispels/immunities later.

## 7. Resistance / Immunity

Movement slow application can use canonical Status Effect resistance/immunity rules. A character can be resistant to a specific magical Slow, physically impaired by an injury, or protected from one source without becoming immune to every mobility penalty.

## 8. UI

Authorized UI may show:
- Slow icon;
- strongest/effective magnitude where useful;
- stack/source count where player knowledge permits;
- remaining duration;
- movement restriction reason.

UI never computes authoritative final movement speed.

## 9. Persistence / Multiplayer

Long-lived slows persist according to Condition timestamp policy. Server owns active Conditions and effective stacking result. Clients cannot clear a Slow by locally resetting CharacterMovement speed.

## 10. Performance

- recalculate slow aggregate only when relevant Condition is added/removed/changed;
- no per-frame scan of every Condition;
- maintain stacking-group aggregates/indexes;
- Movement Resolver updates only when effective input changes.

## Acceptance Tests

1. Three overlapping StrongestOnly slows produce the strongest effective magnitude.
2. Removing the strongest reveals the next strongest still-active slow.
3. Expiring one duplicate source does not remove unrelated sources.
4. Slow composes correctly with Encumbrance and Block state.
5. Ending a slow does not restore a stale hardcoded speed.
6. Severe slow can cancel Sprint only according to profile.
7. Server-authoritative Slow cannot be bypassed by local movement writes.
8. UI reflects effective state without owning final speed.
9. No Tick is required for static magnitude stacking.
10. Other stacking policies can be added without replacing the architecture.

## Core Rule

Metaworld slows are source-aware Status Effect modifiers. Their stacking group determines the effective mobility influence, and the shared Movement Resolver turns that influence into final character movement.