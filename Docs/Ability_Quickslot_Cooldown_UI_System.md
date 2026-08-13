# Metaworld — Ability Quickslot & Cooldown UI System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / controller-complete / event-driven / authoritative activation

## Canonical Principle
Ability quickslots are saved shortcuts to `AbilityDefinitionID` values. They do not duplicate learned abilities or own cooldown truth. The Ability system owns legality/cooldown; the HUD presents current state.

## 1. Quickslot Assignment
Extend `S_MW_QuickslotAssignment` with an Ability target type:
- QuickslotID;
- AssignmentType = Ability;
- AbilityDefinitionID;
- optional display/profile data;
- revision.

Assigning an ability does not learn it automatically.

## 2. Activation
`IA_MW_Quickslot_*` -> resolve assignment -> `RequestActivateAbility(AbilityDefinitionID, TargetContext)`.

The widget does not deduct resources, start cooldowns, or directly apply effects.

## 3. Learned Ability Browser
Suggested UI:
- learned ability list/grid;
- icon/name/description;
- requirements where player knowledge permits;
- cooldown/cost summary;
- quickslot assignment mode;
- controller focus/navigation.

Data comes from learned Ability state plus definition presentation snapshots.

## 4. Duplicate Assignment Policy
Ability shortcuts follow the canonical Quickslot duplicate policy. A profile may allow one ability in one slot only or allow duplicates deliberately. Reassignment updates compact assignment state, not copied widget data.

## 5. Cooldown Presentation
The Ability system exposes `CooldownStarted/Changed/Ended` state or snapshots including `EndsAt`.

Visible slot derives:
`Remaining = max(0, EndsAt - CurrentAlignedTime)`
`Percent = Remaining / Duration`

The radial overlay is presentation only.

## 6. No 0.01-Second Global Timer Pattern
The tutorial's 0.01-second timer is useful for demonstrating a smooth radial material, but Metaworld does not run one high-frequency timer per quickslot/ability permanently.

Preferred approach:
- hidden slots perform no cooldown animation work;
- visible active cooldown slots update through widget animation/tick/timer only while needed;
- frequency is presentation-tuned and can scale by platform/performance;
- authoritative cooldown still ends from timestamp/state, not UI percentage.

## 7. Reopen / Reconnect
Opening the HUD or reconnecting resolves current cooldown from authoritative timestamp. Closing UI does not pause cooldown. A stale radial meter cannot extend or shorten cooldown.

## 8. Charges / Shared Groups
UI may later show:
- charges;
- next charge recovery;
- shared cooldown/category lock;
- unavailable requirement badge;
- insufficient resource state.

These derive from Ability snapshots rather than hardcoded widget assumptions.

## 9. Controller / Accessibility
Support KBM, Xbox-style and PlayStation-style navigation/activation. Input glyphs follow current bindings. Cooldown meaning is not communicated only through color; use radial fill, disabled state, optional remaining time/icon treatment.

## 10. Performance
No `GetAllWidgetsOfClass`, no per-frame full ability scans, no per-slot 100 Hz timers. Update assignment/cost/cooldown presentation from compact Ability/Quickslot events.

## Acceptance Tests
1. Assigning ability does not learn or duplicate it.
2. Unlearned ability shortcut cannot activate.
3. Cooldown overlay follows Ability `EndsAt`.
4. Closing/reopening UI shows correct remaining cooldown.
5. UI reaching zero cannot authorize activation early.
6. Hidden slots stop unnecessary animation work.
7. Shared cooldown/charges can be represented without redesign.
8. Controller assignment/activation works through same stable IDs.

## Core Rule
Ability quickslots are presentation shortcuts. Learned Ability state and cooldown timestamps remain authoritative; visible widgets simply render current assignment, availability and remaining time.