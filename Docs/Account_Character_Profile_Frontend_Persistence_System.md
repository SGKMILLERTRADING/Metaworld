# Metaworld — Account, Character Profile, Frontend & Persistence System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / account-aware / server-authoritative persistent world

## Canonical Principle

Metaworld separates permanent Account identity from individual Character identities. Frontend/menu widgets may create, select and present profiles, but persistent multiplayer truth is owned by authoritative backend/save services—not by a local SaveGame file or GameInstance variable alone.

> Account survives. Characters are distinct lives. UI selects identities; it does not own them.

Related canon:
- `Docs/Real_Time_Life_Utilities_Advertising_VIP_GrimKoin_Death_Legacy.md`
- `Docs/Estate_Wills_Inheritance_Succession.md`
- `Docs/Avatar_Preview_Lifecycle_Performance_System.md`
- `Docs/UI_Base_Widget_Modal_Input_Lifecycle_System.md`

## 1. Identity Layers

Canonical hierarchy:

`AccountID` — permanent technical/user identity
-> `CharacterID A` — one persistent character/life
-> `CharacterID B` — another/new life
-> future CharacterIDs according to account rules.

A character profile may include references to:
- display/name identity;
- appearance/avatar parameters;
- progression/attributes;
- owned/possessed world state references;
- profession/skills/abilities;
- bank/estate relationships;
- current location/world context;
- life/death status;
- creation/retirement timestamps.

## 2. Frontend Responsibilities

Frontend/main-menu UI can expose:
- account/profile status;
- Character selection/creation;
- avatar/locker/customization entry;
- settings;
- accessibility/input settings;
- continuation/world-entry actions;
- death/legacy/new-character flow;
- logout/quit.

The menu is presentation/navigation, not the persistence database.

## 3. Character Select

Character selection uses stable CharacterIDs and server-authorized eligibility.

A dead/retired character may remain visible for history/memorial purposes but cannot be selected as a living character unless a special admin/test rule explicitly permits it.

## 4. New Character Creation

New character flow validates:
- account eligibility;
- unique/valid character identity/name rules;
- avatar data;
- starting-world placement policy;
- first-account vs returning-account starter rules;
- lineage/legacy relationships where applicable.

Permanent-death rules remain intact: creating Character B does not revive Character A.

## 5. Local SaveGame vs Authoritative Persistence

Unreal `SaveGame` objects can be useful for local, non-authoritative data such as:
- graphics/audio settings;
- controller preferences;
- accessibility preferences;
- cached UI choices;
- offline development/test fixtures where explicitly allowed.

They must not be the sole authority for multiplayer character inventory, currency, property, abilities, life/death or world ownership.

A local player cannot edit a SaveGame slot to mint persistent world assets.

## 6. GameInstance

GameInstance is useful for runtime continuity between maps/contexts and temporary client/session references, for example:
- selected Account/Character reference;
- connection/session state;
- frontend-to-world handoff;
- local settings cache.

GameInstance lifetime is not a substitute for database/persistent server storage.

## 7. Save/Commit Model

Authoritative systems persist their own stable records through explicit revisions/transactions.

Examples:
- ItemInstance/Container state;
- equipment;
- bank/currency ledger;
- property;
- character stats/progression;
- Conditions;
- abilities/knowledge;
- missions;
- world location/state;
- death/estate history.

Frontend does not perform a single magical `Save All` that becomes the only source of truth.

## 8. Menu Character / Preview

A menu/locker character is a presentation actor derived from the selected CharacterID/avatar/equipment snapshot.

It is not a second living character and does not own duplicate ItemInstances.

Camera transitions for Head/Armor/Locker are approved as local presentation and should clean up/restore state correctly.

## 9. Currency Display

Profile/frontend displays may show authorized GrimKoin/PromoKoin balances according to privacy rules. Generic tutorial `PlayerMoney` variables are not canonical ledger authority.

## 10. Multiplayer / Security

Server/backend validates:
- Character ownership by AccountID;
- life/death eligibility;
- persistent revisions;
- world entry;
- inventory/currency/property state;
- creation/selection requests.

Clients send intents and profile/avatar selections, not trusted final persistent state.

## 11. Recovery / Failure

Persistence operations should be revisioned/idempotent so reconnect/crash does not:
- duplicate inventory;
- duplicate currency;
- revive dead characters;
- reset missions;
- lose committed equipment changes;
- replay one-time rewards.

## 12. Performance

Frontend loads compact profile summaries first. Heavy avatar/equipment presentation soft-loads only for selected/visible character previews. Do not preload every owned asset for every profile simply to render a menu list.

## Acceptance Tests

1. Account can select an eligible living CharacterID.
2. Dead CharacterID cannot be resurrected by changing local menu/SaveGame data.
3. New character receives correct returning-account starter policy.
4. Local settings persist without becoming gameplay authority.
5. GameInstance handoff survives map transition but server remains source of persistent truth.
6. Preview actor does not duplicate real ItemInstances.
7. Currency/inventory cannot be forged by editing client save data.
8. Reconnect restores last committed authoritative state.
9. Profile list can show historical retired characters without enabling them as living avatars.
10. Controller/KBM can fully navigate creation/selection/settings flows.

## Core Rule

Metaworld frontend and profile systems select and present authoritative Account/Character identities. Local SaveGame and GameInstance support settings/session flow, but persistent multiplayer life, property, inventory, currency and death remain server-owned world state.