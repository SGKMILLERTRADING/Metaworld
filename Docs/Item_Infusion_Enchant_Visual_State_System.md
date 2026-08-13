# Metaworld — Item Infusion, Enchant & Visual State System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / ItemInstance-aware / server-authoritative / data-driven

## Canonical Principle
A temporary infusion or enchant is an authoritative effect tied to one exact ItemInstance and one source ability/effect record. Visual materials, Niagara and trails present that state but do not own it.

## 1. Active Infusion Record
Recommended fields:
- ActiveInfusionID;
- InfusionDefinitionID;
- TargetItemInstanceID;
- source AbilityExecutionID/CharacterID;
- StartedAt/ExpiresAt;
- stacking/exclusive-group policy;
- linked gameplay effect references;
- presentation profile;
- revision.

## 2. Eligibility
The target item must expose an approved infusion capability/profile and remain a valid accessible item. Unsupported equipment types are rejected by definition data rather than widget special cases.

## 3. Stacking
Definitions can choose RejectDuplicate, Refresh, Replace, ExclusiveGroup, or explicitly compatible layering. Tutorial behavior of replacing a previous infusion is a useful default, not a universal rule.

## 4. Item Identity
The infusion follows `TargetItemInstanceID`, not a hand/socket. Changing equipment cannot transfer an active infusion from Item A to Item B accidentally.

A definition may end on stow/switch, or may remain on the same exact item until timestamp/removal if designed as a longer-lived enchantment.

## 5. Gameplay Integration
An infusion can contribute approved effect/application metadata to a valid committed gameplay result through the existing shared Combat/Status Effect systems. Presentation never creates the gameplay Condition.

## 6. Presentation
A presentation profile may include:
- Niagara attachment effect;
- material overlay;
- ribbon/trail;
- audio/light hooks;
- size/length parameters from semantic item presentation endpoints;
- main/off-hand presentation support.

## 7. Trails
Trails are enabled only during defined action/presentation windows. They do not run permanently just because an item is infused. Main/off-hand presentation resolves from the actual source ItemInstance and shared handling profile.

## 8. Persistence
Temporary infusions follow explicit persistence policy. Save/load reconstructs remaining duration from timestamps and never duplicates the active record or resets its full lifetime accidentally.

## 9. Performance
- no Tick required for lifetime;
- VFX can be reduced/culled by significance without removing gameplay state;
- spawned presentation handles clean up exactly on removal/state change;
- trail work occurs only while visible and active;
- Niagara simulation mode is chosen by profiling/platform needs.

## Acceptance Tests
1. Infusion targets the intended exact ItemInstance.
2. Unsupported equipment is rejected.
3. Reapplication follows configured stacking/exclusive policy.
4. Equipment change cannot transfer infusion to another item.
5. Gameplay effect application goes through shared authoritative systems.
6. Removing VFX does not remove unrelated state.
7. Main/off-hand visuals resolve from correct ItemInstance.
8. Distant culling does not remove gameplay infusion.
9. Save/load preserves remaining duration without duplication.
10. Trail runs only during configured presentation windows.

## Core Rule
Metaworld infusions are exact-item gameplay effect records. Shared gameplay systems own consequences; material/Niagara/trail presentation only visualizes authoritative item state.