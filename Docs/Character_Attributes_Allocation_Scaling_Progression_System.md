# Metaworld — Character Attributes, Allocation, Scaling & Progression System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / data-driven

## Canonical Principle

Primary character attributes such as Strength, Dexterity and Intelligence are persistent progression values. Attribute points are awarded by progression systems, previewed in UI, and committed through one authoritative allocation transaction.

## 1. Stable IDs

Use stable IDs such as:
- `Attribute.Strength`
- `Attribute.Dexterity`
- `Attribute.Intelligence`

Display names/enums are presentation/authoring aids, not save identity.

## 2. Persistent State

Character attribute state can include:
- permanent base attribute values;
- unspent AttributePoints;
- progression source/revision;
- explicit respec policy where applicable.

Temporary bonuses remain source-aware modifiers and do not rewrite permanent base values.

## 3. Awarding Points

Legitimate sources can include level/progression milestones, quests, lineage/supernatural progression, and controlled development/admin grants.

UI never creates points by itself.

## 4. Pending Allocation

UI may maintain local pending choices:

`Committed Strength 10`
`Pending +3`
`Preview 13`

Reset before commit only clears the pending preview.

## 5. Commit Transaction

`RequestCommitAttributeAllocation(AllocationDelta, ExpectedRevision)`
-> validate available points
-> validate legal attributes/caps
-> deduct unspent points
-> increase permanent values
-> recalculate affected derived values
-> persist/replicate revision
-> emit UI/stat events.

Repeated confirm or stale UI cannot spend the same points twice.

## 6. Respec

Resetting uncommitted choices is not the same as changing already-committed values.

A committed respec requires a separate explicit game/world rule, service, cost, cooldown or prohibition.

## 7. Data-Driven Scaling

Do not lock all gameplay definitions to one universal `2% per point` formula.

A `ScalingProfileID` can define which attributes matter and how strongly, including curves, coefficients, caps or diminishing returns.

Different equipment, abilities, tools or professions can use different profiles, and some may use no attribute scaling at all.

## 8. UI Presentation

Character/stat UI may show:
- committed values;
- unspent points;
- pending allocation;
- current derived preview;
- requirements/scaling summary where useful.

Mouse and controller focus expose equivalent information.

## 9. Health / Mana / Stamina Investment

Metaworld may deliberately allow progression points to increase Max Health, Max Mana or Max Stamina through explicit per-point gain profiles. Tutorial values such as `+5` are tuning only.

### Current/Max Rule

Increasing a Max resource does **not** automatically refill Current to the new Max by default.

If progression is intended to restore Current Health/Mana/Stamina, that restoration must be an explicit reward/effect of the progression event.

## 10. Persistence / Multiplayer

Server owns permanent attribute values and unspent points. Persist compact values/revisions. Clients may preview local pending allocations but cannot submit an unchecked final total.

## 11. Performance

- no Tick;
- recalculate only affected derived values when a committed attribute changes;
- batch recomputation after multi-point commit;
- UI updates on state change rather than permanent binding.

## Acceptance Tests

1. Player cannot allocate more points than available.
2. Reset before commit affects only pending preview.
3. Double-confirm cannot duplicate spending.
4. Committed values survive reconnect.
5. Different definitions can use different ScalingProfileIDs.
6. No universal 2% scaling formula is required.
7. Increasing Max Health does not auto-refill Current unless explicitly configured.
8. Temporary modifiers do not overwrite permanent values.
9. Controller and mouse can both review/commit allocation.
10. Server can reconstruct authoritative values from persisted state.

## Core Rule

Metaworld attributes are persistent progression inputs. Players preview and commit limited points into stable attributes, while data-driven scaling profiles decide how those attributes influence the rest of the game.