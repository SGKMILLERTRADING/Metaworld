# Metaworld — Construction Build Zone Permission & Restriction System

**Status:** Canonical / Approved Phase 19 + Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative

## Canonical Principle

Construction zones are authoritative spatial policy layered on top of property ownership, zoning, public infrastructure, structural rules and world law.

Core rule:

> A buildable is legal only when its full authoritative placement footprint satisfies every applicable property, zone, support, obstruction and permission rule. One line-trace hit or one Actor tag never decides construction rights by itself.

---

# 1. Tutorial Intake

Approved intent:

- world areas can explicitly allow or forbid construction;
- a project may support both blacklist-style rules (build unless forbidden) and whitelist-style rules (build only where allowed);
- zone state should integrate directly with the build preview and final validation.

Upgraded/rejected tutorial implementation:

- no permanent dependency on a dedicated `BuildArea` trace channel as the whole policy system;
- no `Switch on Name` using loose `allow`/`forbid` Actor tags as authoritative law;
- no single line trace decides whether a large structure crossing several zones is valid.

---

# 2. Build Policy Volumes

Metaworld can use authored or generated 3D build-policy volumes/regions.

Suggested policy modes:

- `Inherit`
- `Allow`
- `Forbid`
- `Conditional`
- `RestrictedToOwner/Lease`
- `RestrictedToPublicContract`
- `RestrictedToProfession/Permit`
- `EmergencyTemporaryRestriction`

Suggested record/definition fields:

- `BuildZoneID`
- `JurisdictionID`
- `PropertyID` when tied to a parcel
- policy mode
- priority/precedence
- allowed/forbidden Buildable tags/families/categories
- allowed owner/organization/faction/public-contract IDs
- permit/license requirements
- minimum/maximum height
- subsurface range
- active time window
- reason/message key
- revision/version

---

# 3. Relationship to Property

Phase 19 property remains the primary private construction-right boundary.

Examples:

- owner-owned parcel -> construction may be allowed subject to zoning/permits;
- leased property -> tenant can build only if lease permissions allow;
- neighboring parcel -> denied without rights;
- public road -> normally denied except authorized public works;
- protected park -> forbidden or tightly restricted;
- designated construction lot -> allow/conditional;
- city project corridor -> authorized contractors may build under a public contract.

Owning land does not automatically override public safety, utility easements, zoning or protected-space rules.

---

# 4. Full-Footprint Evaluation

The candidate placement must be evaluated against its authoritative footprint/volumes, not only its pivot or camera trace hit.

Examples:

- a large prefab whose pivot is inside an allowed parcel but garage crosses into neighboring land -> reject;
- a foundation above an allowed surface but pier extends into a protected utility corridor -> reject/require redesign;
- an upper floor crosses outside vertical air rights -> reject;
- a fence lies partly inside a no-build road setback -> reject or clip only if a deliberately supported segmented workflow exists.

---

# 5. Zone Precedence

When multiple zones overlap, deterministic precedence rules apply.

Suggested order concept:

1. hard safety/legal exclusion
2. explicit temporary emergency restriction
3. authoritative property/lease rights
4. jurisdiction zoning/public policy
5. contract/permit-specific allowance
6. default district/world policy

An explicit allow volume does not automatically override a higher-priority legal/safety forbid.

Every rejection should expose a stable reason such as:

- `OutsideOwnedProperty`
- `NeighborPropertyOverlap`
- `PublicRoadRestricted`
- `ProtectedArea`
- `UtilityEasement`
- `HeightRestricted`
- `SubsurfaceRestricted`
- `PermitRequired`
- `PublicContractRequired`
- `EmergencyBuildRestriction`

---

# 6. Category-Specific Rules

A zone can permit some construction but not others.

Examples:

- residential parcel: house/fence/garden allowed; factory stack forbidden;
- commercial district: storefront/signage allowed under permits;
- farm: agricultural structures allowed;
- historic district: exterior renovation limited by approved variants;
- hospital/public facility: ordinary players cannot modify structure;
- event area: temporary tents/stages allowed during event permit;
- road work zone: barriers/machinery allowed to authorized crew only.

Compatibility uses Gameplay Tags/Buildable definition data rather than a growing collection of trace channels.

---

# 7. Temporary / Dynamic Zones

World events may create temporary restrictions or allowances.

Examples:

- police crime scene;
- fire/structural collapse exclusion area;
- disaster evacuation zone;
- roadwork/public contract area;
- festival/event build permit;
- war/security checkpoint construction;
- condemned building area;
- utility repair corridor.

Dynamic zones are persistent/event-driven state with start/end timestamps and authority, not per-frame scans.

---

# 8. Preview Feedback

Client preview may query locally relevant replicated zone summaries and show:

- valid placement;
- forbidden zone outline;
- parcel boundary;
- height/air-right limit;
- permit/public-contract warning;
- crossed boundary section;
- human-readable blocked reason.

The visualization is advisory. Server validation remains final.

---

# 9. Server Authority

Final placement request sends intent/candidate data.

Server resolves:

- Buildable/Variant Definition;
- authoritative placement footprint;
- property/deed/lease state;
- all intersecting build-policy zones;
- zoning/height/subsurface rights;
- required permit/contract/profession;
- support and obstruction;
- resources/work requirements.

Client cannot forge an `allow` tag, disable a local volume, or claim an empty zone list.

---

# 10. Persistence / Revision

Persist stable zone definitions or source-policy records where required.

Placed structures can record the permission/permit/contract context relevant to historical audit without assuming the structure becomes illegal merely because later zoning changes. Future grandfathering, condemnation, forced acquisition or code-upgrade rules can be explicit systems.

Zone changes increment revisions so cached preview/access decisions can invalidate safely.

---

# 11. Performance

- use spatially bounded zone queries around the candidate footprint;
- do not line trace every zone in the world;
- do not Tick all zone volumes;
- cache static parcel/zoning data where safe;
- dynamic zone changes are event-driven;
- preview queries only while Build Mode is active;
- server evaluates only zones overlapping the authoritative candidate footprint;
- large world zones integrate with World Partition/region data rather than forcing all policy Actors loaded globally.

---

# 12. Controller / UI

Build-zone feedback must be understandable using keyboard/mouse, Xbox-style and PlayStation-style controllers.

Property/permit screens and blocked-reason UI must be controller navigable.

Players should not need to click hidden collision volumes to understand why placement is forbidden.

---

# 13. Initial Tests

1. Blacklist mode allows ordinary construction outside restricted volumes.
2. Blacklist zone blocks full footprint intersection, even when pivot is outside the zone.
3. Whitelist-only parcel blocks construction outside approved land.
4. Structure crossing into neighbor property is rejected.
5. Upper floor exceeding air-right height is rejected.
6. Authorized public contractor can build inside public-work zone.
7. Unauthorized player cannot.
8. Temporary emergency restriction blocks new placement and expires correctly.
9. Category-restricted zone permits fence but rejects incompatible industrial buildable.
10. Client removing/hiding local zone cannot bypass server decision.
11. Preview displays a clear blocked reason.
12. Zone queries stop when Build Mode closes.

---

# Core Rule

> Metaworld construction rights are spatial law, not a trace-channel trick. The complete structure must fit inside the rights and policy volumes that authorize it, and the server resolves overlapping property, zoning, permit, safety and temporary-world restrictions before anything permanent is built.