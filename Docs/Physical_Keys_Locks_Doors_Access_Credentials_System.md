# Metaworld — Physical Keys, Locks, Doors & Access Credentials System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / persistent / server-authoritative / property-aware

## Canonical Principle

Keys and locks are part of the same persistent item, property, interaction and access-control architecture as the rest of Metaworld.

> A physical key can operate a compatible lock, but possession of that key is not automatically legal authorization to enter. Keys are real persistent items/credentials, not a separate magical inventory universe.

Related canon:

- `Docs/Interactive_Doors_Windows_Runtime_System.md`
- `Docs/Household_Property_Access_Lock_Permissions_System.md`
- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Loot_Containers_Bags_Corpses_Chests_Transfer_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`

---

# 1. Door / Lock / Credential Separation

Keep these concepts separate:

- `DoorObjectID` / protected object identity;
- `LockID` / lock mechanism identity;
- `CredentialDefinitionID` / credential type or authorization token;
- `ItemInstanceID` for the exact physical key/keycard item;
- Property/AccessGrant records for legal authorization.

A door can be replaced while a lock remains conceptually associated with a property/opening, and a lock can be rekeyed without changing the door mesh.

---

# 2. Physical Key Item

A physical key is a normal persistent item.

Possible state:

- ItemDefinitionID;
- ItemInstanceID;
- CredentialID / key-cut/code identity;
- owner/current possessor;
- current ContainerID/world location;
- creator/manufacturer/provenance where relevant;
- copied/original status where designed;
- stolen/evidence state;
- condition/damage where meaningful.

It can be:

- picked up;
- stored;
- dropped;
- stolen;
- inherited;
- looted;
- transferred;
- destroyed/lost where item policy permits;
- seized as evidence.

A dedicated `Keys` UI tab is allowed as a filter/category view, but the key remains in the canonical Item/Container system.

---

# 3. Lock Definition / State

A protected object may reference a persistent LockID/profile.

Possible lock state:

- Locked;
- Unlocked;
- Jammed;
- Broken;
- Breached;
- Disabled;
- destroyed/replaced according to object state.

Possible lock profile data:

- accepted CredentialID(s)/credential tags;
- mechanical/digital/security type;
- auto-lock policy;
- relock policy;
- property/access association;
- tamper/breach rules;
- security/alarm integration;
- rekey/change-lock permissions.

Do not rely on one integer KeyID stored independently in every Door Blueprint as the permanent architecture.

---

# 4. Unlock Request

Conceptual flow:

`Player Interacts With Locked Door/Chest`
-> common Interaction system identifies action
-> server resolves Door/Chest ObjectID + LockID
-> resolve legitimate access rights and/or usable possessed credential
-> validate item/credential still exists and is accessible
-> apply unlock policy
-> update authoritative lock state
-> persist/replicate
-> local motion/UI responds.

The client cannot submit `I have Key 12, unlock this` as authoritative truth without server validation.

---

# 5. Possession vs Legal Authorization

This is critical.

A stolen physical key may mechanically unlock a door while the user is still unauthorized.

Example:

`Stolen House Key`
-> physically compatible with LockID
-> opens door
-> property access policy says intruder has no legal access
-> entry can become trespass/burglary/security/evidence event.

Conversely, an authorized resident may have another valid access method even if they are not carrying one particular physical key.

Physical access and legal authorization are related but distinct systems.

---

# 6. Doors, Chests, Safes & Other Protected Objects

The same credential/lock contract can protect:

- doors;
- gates;
- chests;
- safes/vaults;
- lockers;
- cabinets;
- vehicles;
- restricted rooms;
- machinery/control panels;
- portals or special world objects where designed.

Each protected object references lock/access data rather than copying a unique key-check graph.

---

# 7. Key Loot / Drops

Keys can legitimately exist in loot/container state.

Examples:

- enemy carried key;
- boss-dropped key;
- chest contains a key;
- employee carries business key;
- property owner loses key;
- police evidence contains seized key.

The loot system transfers the actual key ItemInstance. It does not create a parallel `KeyID` Boolean on the player.

Take/Take All uses normal authoritative container transfers.

---

# 8. Unique / Quest / Critical Keys

A key may be important to a quest/world sequence, but importance does not require a separate inventory authority.

Possible policies:

- normal droppable/destructible physical key with real consequences;
- protected from accidental Destroy but still transferable/drop-capable;
- replacement/reissue path through NPC/property/world logic;
- one-of-a-kind credential whose loss changes the world/quest;
- credential can be copied/rekeyed according to future profession/security systems.

Do not globally make every key indestructible just because some quests use keys.

The item's own policy defines available actions.

---

# 9. Key Inventory UI

A Key tab/filter may show:

- key icon;
- display name;
- description;
- known associated property/door only if player knowledge permits;
- owner/provenance indicators where legitimate;
- quantity only where duplicates/stacking are logically valid.

Do not show irrelevant RPG stats such as Damage/Armor/Weight/Market Value when the UI profile says they are not useful, but underlying physical properties can still exist.

Tooltips update event-driven from item presentation snapshots.

---

# 10. Key Drop / Destroy / Options

The existing contextual action/quantity architecture applies.

Possible actions:

- Inspect;
- Use/Unlock when in context;
- Drop;
- Give/Transfer;
- Store;
- Destroy only if item policy allows;
- Copy/Rekey later through profession/service systems.

Do not create separate permanent `DropKeyItem` / `RemoveKeyItem` gameplay universes when generic item transactions can handle the item through capabilities/tags.

A specialized UI adapter is acceptable, but transaction authority stays generic.

---

# 11. Rekeying / Lock Replacement

Changing a lock can invalidate old credentials without deleting those physical keys from the world.

Example:

`House Lock A`
accepts Credential A

Owner changes lock -> `House Lock B`
accepts Credential B

Old Key A remains a physical item but no longer opens the new lock.

This supports lost/stolen-key security without magical deletion.

---

# 12. NPC Compatibility

NPC residents, employees, guards, tenants and service workers use the same access/credential logic.

NPC knowledge can include which key/credential is required and whether they are authorized.

Distant NPC access can resolve from data/state rather than physically simulating key use every time.

---

# 13. Crime / Evidence

Possible events:

- stealing a key;
- using a stolen key;
- unauthorized entry;
- lock tampering;
- forced breach;
- copying credentials illegally;
- possessing restricted keys;
- losing business/security keys.

These can integrate with cameras, witnesses, evidence and law.

`SERVER TRUTH != IN-WORLD KNOWLEDGE` remains active.

---

# 14. Performance / Persistence

- no per-door Tick scanning player key inventory;
- resolve credentials only on relevant interaction/access request;
- stable IDs persist with unloaded doors/properties;
- private access lists/credential details are permissioned;
- UI key list updates from item/container deltas;
- lock state persists independently of transient Door Actor animation.

---

# 15. Acceptance Tests

1. Correct physical key unlocks compatible lock when server validates it.
2. Wrong key cannot unlock lock.
3. Key remains normal ItemInstance through pickup/drop/store/save/load.
4. Key tab is a view/filter, not separate authoritative inventory.
5. Chest and door can use the same lock/credential contract.
6. Take All can transfer a key exactly once without special duplicate state.
7. Stolen key can physically work while still causing unauthorized-entry consequences.
8. Rekeying invalidates old key without deleting old physical item.
9. Destroy action respects per-key policy.
10. NPC authorized user can operate compatible lock.
11. No per-frame key search is required.
12. KBM/Xbox-style/PlayStation-style interaction works.

## Core Rule

> Metaworld keys are persistent physical credentials. Locks validate compatible credentials and property/access rights under server authority; a key can open a lock without making an intruder legally authorized, and keys remain ordinary items that can move through the living world.