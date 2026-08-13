# Metaworld — Household Property Access, Locks & Permission System

**Status:** Canonical / Approved Cross-System Upgrade

**Runtime Direction:** Blueprint-first / server-authoritative / persistent

## Canonical Principle

Private homes and private residential spaces are locked by default against everyone who does not have a legitimate access right.

Core rule:

> A private home is not publicly accessible merely because a door is interactable. The owner, approved household members and explicitly authorized guests may enter; everyone else is denied unless a separate legitimate world authority grants access.

Default residential access includes:

- the legal/current property owner;
- the owner's spouse/husband/wife or approved domestic partner when the household relationship grants residence access;
- children/dependents who are registered as members of that household and whose household permissions allow access;
- any person, NPC, employee, tenant, contractor or guest the owner/authorized manager explicitly grants access to;
- any separate legal access right that legitimately overrides the ordinary lock, such as an active tenant lease, valid emergency authority, lawful police/court authority, or other explicitly configured world rule.

Everyone else remains locked out by default.

---

# 1. Property Access Is Separate From Door Animation

The Door/Window interaction system controls whether an object can open/close smoothly.

This system controls whether the requester is authorized to operate a protected opening.

Recommended flow:

`Interact with locked residential door`
-> resolve Door Object ID / Property ID
-> server resolves access policy
-> evaluate owner / household / explicit grant / lease / legal override / key credential
-> if authorized: allow unlock/open according to lock state
-> if unauthorized: deny normal access

A client cannot set itself as authorized.

---

# 2. Default Residential Policy

Recommended default policy for an owner-occupied private house:

- `OwnerAccess = Allow`
- `SpouseAccess = Allow`
- `HouseholdDependentAccess = Allow` where the dependent is a legitimate member of the household and the owner/household policy has not deliberately restricted a specific area
- `ExplicitGrantAccess = Allow`
- `PublicAccess = Deny`
- `UnknownPlayerAccess = Deny`
- `UnknownNPCAccess = Deny`

The property therefore starts effectively locked to outsiders even if the owner never opens a permissions menu.

---

# 3. Household Does Not Mean Unlimited Authority Everywhere

Household membership grants the residential access defined by the household/property policy, but not necessarily every administrative power.

Separate permissions can include:

- Enter Property
- Open Exterior Doors
- Open Interior Shared Doors
- Access Private Bedroom
- Access Garage
- Access Storage
- Use Appliances
- Invite Guests
- Grant/Revoke Access
- Change Locks
- Manage Security System
- Place/Move Furniture
- Construct/Renovate
- Demolish
- Access Business Area
- Access Safe/Vault

Example:

A child may be able to enter the family home and bedroom but not authorize demolition, empty a business safe, or permanently add strangers to the access list.

A spouse may receive broad household access by default while construction, sale, mortgage, estate or business powers remain separate legal permissions.

---

# 4. Explicit Access Grants

The owner or another role with `GrantAccess` authority can explicitly authorize additional people.

Possible grant types:

- permanent until revoked;
- temporary date/time window;
- one-time guest access;
- recurring schedule;
- room/zone-specific access;
- employee/contractor access;
- tenant access;
- delivery/service access where supported;
- event/party guest list.

Suggested record:

`S_MW_PropertyAccessGrant`

Possible fields:

- `AccessGrantID`
- `PropertyID`
- `SubjectCharacterID / OrganizationID / HouseholdID`
- `GrantedByCharacterID`
- `PermissionSetID / AccessTags[]`
- `AllowedZoneIDs[]`
- `ValidFrom`
- `ValidUntil`
- `RecurringScheduleID`
- `CanDelegate`
- `Revoked`
- `RevokedBy`
- `CreatedTimestamp`
- `Revision`

Stable IDs and server-side records are authoritative.

---

# 5. Spouse / Partner Access

A legitimate spouse/husband/wife or approved household partner can receive home-access rights automatically when the relationship becomes an active shared household relationship.

Rules:

- relationship status alone does not silently transfer legal ownership;
- home access can be automatic for the shared residence while sale/title/bank/business rights remain separate;
- separation/divorce/household removal can revoke or modify access according to legal/property rules;
- a spouse may be explicitly given additional permissions such as security management, guest management or construction approval;
- access changes are persistent and server-authoritative.

---

# 6. Children / Dependents

Children/dependents who are legitimate household members can access their home by default where appropriate.

However age/dependent role can limit high-risk permissions.

Possible child/dependent defaults:

- enter home: allow;
- open normal household doors: allow;
- access assigned bedroom/shared rooms: allow;
- invite permanent guests: deny by default;
- change locks/security ownership: deny;
- demolish/renovate structural pieces: deny;
- sell/transfer property: deny;
- access dangerous/secure storage: data/policy dependent.

The system must not treat a dependent as property; the relationship is a household/legal role with permissions and responsibilities.

---

# 7. Tenants / Leases

A legal tenant can have property access even when they are not the owner or owner's family.

Lease/tenancy rights may grant:

- entry to rented unit;
- unit doors/rooms;
- shared building areas;
- mailbox/storage/parking rights;
- limited guest rights according to lease rules.

The owner cannot simply use the ordinary lock UI to bypass active tenant rights if the legal/lease system says the tenant retains access.

Lease expiration, eviction, court order or voluntary termination changes access through the authoritative legal/property state.

---

# 8. Employees, Contractors & Service Workers

The owner or authorized manager can grant limited access to:

- cleaners;
- builders;
- electricians;
- plumbers;
- security staff;
- caregivers;
- delivery/service workers;
- property managers;
- repair technicians.

Access can be limited by:

- time;
- room/zone;
- active work order/contract;
- profession role;
- current job state.

A Builder hired to repair an exterior wall does not automatically gain permanent access to the owner's bedroom or vault.

---

# 9. Legal / Emergency Overrides

Private locks do not override every legitimate world authority.

Possible exceptional access paths include:

- valid search/arrest/court warrant;
- emergency firefighter/medical rescue authority;
- immediate life-safety emergency;
- lawful eviction/property repossession process;
- disaster/emergency management order;
- other explicitly implemented legal authority.

These are not universal admin bypasses.

They require their own server-authoritative legal/event conditions and can create Event Ledger/evidence records.

Unauthorized forced entry remains a crime/security event even if the attacker physically breaches the door.

---

# 10. Keys / Credentials

Physical or digital credentials can be one mechanism for exercising an access right.

Possible credential types:

- physical key;
- keycard;
- digital property credential;
- temporary guest code;
- business employee credential;
- tenant credential;
- security-system authorization.

Credential possession and legal authorization are related but distinct.

Examples:

- stolen key may physically unlock a door but still represent unauthorized entry;
- revoked digital credential no longer authorizes access;
- duplicated/forged credentials can be crime/security gameplay rather than automatic legal access.

---

# 11. Interior Zones / Rooms

A property can expose access zones rather than one all-or-nothing Boolean.

Possible zones:

- Exterior / Yard
- Front Entry
- Shared Living Space
- Kitchen
- Bedrooms
- Office
- Garage
- Basement
- Workshop
- Business Area
- Staff Area
- Storage
- Safe/Vault
- Utility Room

A person can therefore have `EnterHouse` without `AccessVault`.

Prefab houses can author Zone IDs; modular houses can derive/assign zones through property/room systems later.

---

# 12. Default Lock State

For a private residential property, exterior access points should default to protected/locked against unauthorized subjects.

Canonical behavior:

- owner/authorized resident approaches -> interaction can unlock/open according to lock policy;
- stranger approaches -> normal Open request denied while locked;
- owner leaves and closes/locks property -> outsiders remain denied;
- authorized person can be revoked without changing ownership;
- breach/destruction may create physical entry but does not grant legal permission.

An open door can physically allow passage depending collision/world rules, but entering without permission can still constitute trespass. Lock/security state and legal access are not the same concept.

---

# 13. Server Authority

Server owns:

- PropertyID;
- owner/title state;
- household membership relevant to access;
- explicit grants/revocations;
- lease rights;
- lock/security state;
- zone permissions;
- credential validity;
- legal/emergency override state;
- access audit events where needed.

Client may request:

- Open/Unlock;
- Lock;
- Grant Access;
- Revoke Access;
- Change Access Zone;
- Issue Temporary Credential.

Server validates requester authority before committing any change.

---

# 14. Persistence & Replication

Persist compact access policy and grant records independently of currently loaded Door Actors.

A server restart must preserve:

- owner access;
- household grants;
- explicit guests;
- revoked users;
- tenants;
- temporary expiration times;
- zone permissions;
- lock/security state;
- credential validity as applicable.

Replication exposes only what a connection needs.

Do not replicate the owner's full private access list to every nearby player.

An unauthorized player generally needs only the result: `Locked / Access Denied`.

---

# 15. Crime / Evidence / Security Integration

Unauthorized attempts can create security events depending on context:

- repeated lock tampering;
- forced entry;
- stolen-key use;
- alarm trigger;
- door/window breach;
- unauthorized entry into restricted zone;
- security camera/witness evidence.

Canonical evidence rule remains:

`SERVER TRUTH != IN-WORLD KNOWLEDGE`.

The server can know the actual unauthorized actor while police/news only know what legitimate evidence/public investigation establishes.

---

# 16. NPC Compatibility

NPC household members, tenants, employees, guests and service workers use the same access contract.

NPC navigation should respect locked/unauthorized doors rather than walking through them.

An authorized NPC can request the same Open/Unlock action through the shared interaction system.

Distant NPC access can resolve from data/permissions rather than running door interaction Actors continuously.

---

# 17. UI / Controller Support

Property access management must work with:

- keyboard/mouse;
- Xbox-style controllers;
- PlayStation-style controllers.

Owner/manager UI can show:

- household members;
- explicit guests;
- tenants;
- employees/contractors;
- temporary access expiration;
- zone permissions;
- grant/revoke controls;
- blocked/legal constraints.

Do not require mouse-only tiny checkboxes as the only way to manage home access.

---

# 18. Performance

- no per-door Tick checking household lists;
- resolve access when an interaction/access event occurs;
- cache relevant permission results only when safe and invalidate on access-policy revision;
- household/property access lists are compact persistent data;
- temporary grants expire through timestamps/scheduled evaluation rather than continuous scanning;
- Door Actors query the property/access service by stable IDs;
- unloaded properties retain access state without active Actors.

---

# 19. Initial Tests

1. Owner can enter own locked house.
2. Stranger cannot normally open locked house door.
3. Spouse in active shared household can enter.
4. Household child/dependent can enter but cannot demolish/sell property by default.
5. Owner grants friend access -> friend can enter.
6. Owner revokes friend -> future access denied.
7. Temporary guest access expires correctly.
8. Tenant with active lease retains authorized unit access.
9. Contractor has work-zone/time-limited access only.
10. Unauthorized stolen-key use can physically work according to credential rules while still generating trespass/crime consequences.
11. Lawful emergency/legal override works only with valid authoritative condition.
12. Door breach allows physical passage but does not convert intruder into authorized resident.
13. Access survives save/load/server restart.
14. Late joiner receives correct lock/access result.
15. Full private access list is not exposed to unrelated clients.
16. NPC resident can use authorized door.
17. Keyboard/mouse access management works.
18. Xbox-style controller access management works.
19. PlayStation-style controller access management works.
20. Thousands of locked properties incur no per-frame permission-check cost.

---

# Core Rule

> Metaworld homes are private by default. Owners, approved spouses/household dependents and explicitly authorized people can enter according to persistent permissions; everyone else is locked out unless a separate legitimate legal, lease or emergency rule grants access. Physical breach can defeat a lock, but it never becomes legal permission.