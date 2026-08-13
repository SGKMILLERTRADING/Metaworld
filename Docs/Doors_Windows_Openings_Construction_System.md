# Metaworld — Doors, Windows & Structural Opening Construction System

**Status:** Canonical / Approved Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld separates the **structural opening** from the **object installed inside that opening**.

Core rule:

> A DoorOpening wall is not the door. A WindowOpening wall is not the window.

The wall/floor/building structure owns the opening geometry and structural attachment slot. The door or window is a separate persistent buildable object attached to that opening.

This allows doors and windows to be installed, replaced, upgraded, damaged, repaired, removed, secured and persisted without replacing the entire wall.

---

# 1. Structural Opening Types

Initial wall variants remain:

- `Wall.Standard`
- `Wall.DoorOpening`
- `Wall.WindowOpening`

Opening-capable walls expose attachment metadata.

Examples:

- Door wall provides `Build.Attach.Door`
- Window wall provides `Build.Attach.Window`

Recommended opening data:

- Opening ID
- Opening Type
- Local/world attachment transform
- Width
- Height
- Depth tolerance
- Orientation/facing
- Compatible attachment tags
- Occupied state
- Installed Structure/Object ID
- Obstruction bounds
- Frame/support metadata
- Property/permission context

---

# 2. Doors and Windows Are Separate Buildable Families

Recommended families:

`Build.Family.Door`

`Build.Family.Window`

Door examples can eventually include:

- single hinged door
- double door
- sliding door
- reinforced/security door
- interior door
- exterior door
- garage/large opening door where a compatible opening type exists

Window examples can eventually include:

- fixed window
- openable window
- sliding window
- reinforced/security window
- shopfront window
- decorative/specialized window where compatible

Each product/variant has a stable Buildable ID and data definition.

Do not duplicate the entire wall Blueprint merely to obtain another door/window style.

---

# 3. Opening Attachment Contract

Door/window installation uses the same data-driven snapping architecture as the rest of construction.

Possible tags:

- `Build.Attach.Door`
- `Build.Attach.Window`
- `Build.Snap.Door`
- `Build.Snap.Window`

A door definition declares what opening types/sizes it accepts.

A window definition declares what opening types/sizes it accepts.

Recommended flow:

`Select Door/Window`
-> camera/view targets opening wall
-> `BPI_MW_BuildSnapProvider` or opening-provider interface returns compatible opening slot
-> preview aligns to exact opening transform
-> local validation checks compatibility/occupancy/obstruction
-> server resolves authoritative opening
-> server validates permissions/resources/profession/occupancy
-> install persistent door/window

---

# 4. Blueprint Interface Direction

The existing construction interface architecture remains preferred over class-specific casting.

`BPI_MW_BuildSnapProvider` can expose attachment/snap points directly, or a dedicated interface may later be introduced if opening behavior becomes complex.

Possible opening-related calls:

- `GetCompatibleAttachmentSlots(AttachmentTags)`
- `GetOpeningByID(OpeningID)`
- `IsOpeningOccupied(OpeningID)`
- `GetInstalledObjectID(OpeningID)`

The Build Component remains the placement coordinator. The wall/opening provides authoritative structural data; the door/window owns its installed-object state.

---

# 5. Pivot, Alignment & Asset Standards

The tutorial correctly highlights pivot and rotation consistency as critical.

Metaworld upgrades this into an asset-production rule.

Every door/window asset intended for construction should have validated:

- canonical forward direction
- canonical up direction
- consistent origin/pivot convention
- opening attachment transform
- closed-state transform
- hinge/panel pivot where applicable
- collision alignment
- dimensions/opening compatibility metadata

Do not repair inconsistent assets forever through arbitrary Blueprint rotation offsets when the asset can be standardized in the content pipeline.

Per-variant alignment offsets remain allowed where genuinely required, but they are explicit data rather than unexplained graph constants.

Python Editor validation can later flag assets with missing/inconsistent metadata.

---

# 6. Door Runtime Structure

A door can contain separate logical pieces such as:

- frame/static support
- movable door leaf/panel
- interaction component
- lock/security component
- collision
- audio hooks
- damage/condition state
- ownership/property link

The structural wall remains separate.

Door state can include:

- Open
- Closed
- Opening
- Closing
- Locked
- Unlocked
- Jammed/Damaged later
- Destroyed/Breached later

Door motion should be event/timeline/animation driven only while needed, not a permanent expensive Tick loop.

---

# 7. Window Runtime Structure

A window can contain:

- frame
- glass/panel
- optional movable/openable panel
- collision
- interaction hooks
- damage/broken state
- ownership/property link
- optional security state

Window variants can differ in whether they open.

Future systemic upgrades may include:

- breakable glass
- boarded windows
- reinforced glass
- alarms/sensors
- weather exposure when broken/open
- burglary entry where physically possible
- repair/replacement jobs

---

# 8. Collision Policy

The tutorial's custom Box Collision principle is retained, but collision is separated by purpose.

## Gameplay Blocking Collision

Represents the actual wall, frame, door panel, window panel/glass and other physical geometry.

## Snap / Attachment Query Volumes

Used only to find valid attachment locations.

Rules:

- Query Only where possible
- no physics simulation
- do not block player movement
- do not interfere with bullets/normal interaction unless intentionally configured
- use a small number of general build/snap query profiles

## Obstruction Validation

Prevents an object from being installed when another structure/object occupies the required opening space.

Do not rely on one universal tutorial value such as setting every Y Box Extent to `1`.

Box extents are tuned per modular kit, but final validity also uses:

- exact opening ID
- attachment occupancy
- obstruction bounds
- selected object's physical bounds
- parent structure relationship
- server collision/query validation

This prevents accidental building inside walls without making the system dependent on one magic number.

---

# 9. Trace Channel Policy

Metaworld does not add a global Project Settings trace channel for every new buildable object type.

Approved low-level query families can remain limited, for example:

- Build Placement Query
- Build Snap Query
- Build Obstruction Query

High-level compatibility comes from:

- Buildable IDs
- Family/Variant IDs
- Gameplay Tags
- Opening/Attachment Slot metadata
- Interface-provided records

This avoids collision-channel explosion as the catalog grows.

---

# 10. Door and Window Catalog Data

Door/window Buildable Definitions can include:

- Buildable ID
- Family ID
- Variant ID
- Display Name
- mesh/component representation
- preview representation
- dimensions
- accepted Opening Types
- accepted size range
- orientation rule
- hinge/slide behavior
- collision profile
- lock compatibility
- durability
- material cost
- GrimKoin cost
- required Builder skill/certification where applicable
- required permit where applicable
- repair recipe
- replacement/salvage rules
- Nanite/rendering metadata where appropriate
- creator texture entitlement support where approved
- performance cost

---

# 11. Ownership, Property & Permissions

A player cannot install or replace a door/window merely because they can aim at an opening.

Server-side authorization can consider:

- property owner
- tenant modification rights
- spouse/family permission
- business role permission
- Builder contract
- faction/public-project authority
- court/legal authority where deliberately supported
- war/occupation rules where applicable

The installed object inherits or references the correct property/ownership context while retaining its own persistent Object/Structure ID.

---

# 12. Locks, Keys & Security Upgrade

Approved upgrade direction:

Doors can later integrate with:

- physical/digital keys
- household permissions
- business permissions
- guest access
- police/legal access rules
- lock quality
- lock damage
- alarms
- security systems
- forced entry/breaching

A stronger lock does not create magical invulnerability.

Property access, crime, evidence, cameras, repairs and security all remain separate interacting systems.

---

# 13. Damage, Crime & Evidence Integration

Doors/windows are physical world objects and can later participate in:

- damage
- forced entry
- broken glass
- breach evidence
- fingerprints/forensics where implemented
- security camera evidence
- repair jobs
- insurance claims where implemented
- police investigations

The authoritative world records what physically occurred. A broken window does not automatically reveal who broke it unless evidence supports that conclusion.

---

# 14. Builder Profession Integration

Installation complexity can vary.

Possible examples:

General/simple:
- replace a simple owned interior item where rules permit

Builder/profession:
- install structural doors/windows
- resize/convert an opening through renovation
- repair frames
- replace damaged structural units

Advanced/licensed:
- regulated commercial/security/fire-rated installation where later designed

Converting a solid wall into a door/window opening remains a renovation job, not simple door placement.

---

# 15. Multiplayer Authority

Client preview can propose:

- selected Door/Window Buildable ID
- target Parent Structure ID
- Opening/Attachment Slot ID
- candidate transform

Server independently resolves:

- parent structure
- opening definition
- occupancy
- selected Buildable Definition
- compatibility
- property permissions
- Builder/profession requirements
- resources/cost
- obstruction/collision

Only then does the server install the object and persist the relationship.

The client cannot create a fake opening or claim an occupied opening is free.

---

# 16. Persistence

Door/window persistent record should include at minimum:

- Object/Structure ID
- Buildable ID
- Family/Variant ID
- Parent Structure ID
- Opening/Attachment Slot ID
- owner/property link
- installed transform
- open/closed state where persistent
- lock/security state where applicable
- condition/damage state
- permissions
- creator texture entitlement where relevant
- timestamp installed
- Builder/contract reference where relevant

Save/load must restore both the installed object and its parent-opening relationship.

---

# 17. Controller Compatibility

Every installation and interaction path must work with:

- keyboard/mouse
- Xbox-style controllers
- PlayStation-style controllers

Construction targeting remains camera/reticle based rather than requiring precise mouse cursor placement.

Controller-capable actions include:

- select Door/Window category
- cycle variants
- target opening
- confirm/cancel installation
- open/close door
- lock/unlock where authorized
- interact with windows where applicable

Detailed controller rules remain in `Docs/Controller_Input_Compatibility_Architecture.md`.

---

# 18. Performance Rules

- no continuous snap scanning outside build mode
- query only the relevant targeted structure/opening set
- door movement updates only while moving/interactive
- static closed structures should not pay unnecessary per-frame cost
- window/door damage effects obey physics/VFX budgets
- simple collision preferred where accurate
- attachment slots and opening metadata are lightweight data
- do not create one heavy Actor/Blueprint family per cosmetic variant when data/components can share logic

---

# 19. Python Editor Validation Upgrade

Python tooling can later audit:

- missing opening IDs
- duplicate opening IDs
- opening dimensions
- door/window compatibility ranges
- bad pivot/orientation conventions
- collision intruding into required doorway/window space
- missing attachment tags
- missing preview assets
- missing lock/durability/cost metadata
- inconsistent snap/query profiles
- unsupported creator material setup
- performance metadata

---

# 20. Initial Vertical-Slice Test

The first construction vertical slice should prove:

1. Place `Wall.DoorOpening` on a foundation/floor wall edge.
2. Place `Wall.WindowOpening` on another valid edge.
3. Select a compatible Door from the catalog.
4. Door preview snaps only to compatible unoccupied door opening.
5. Server validates and installs the Door as a separate persistent object.
6. Door can open/close and its collision changes correctly with state.
7. Select a compatible Window.
8. Window preview snaps only to compatible unoccupied window opening.
9. Server installs Window as a separate persistent object.
10. Door/window cannot be installed into a solid wall.
11. Second object cannot occupy the same opening unless the definition explicitly supports multi-part attachments.
12. Incorrect size/type is rejected.
13. Obstruction validation prevents building inside the wall or another object.
14. Snap/query volumes do not block character movement.
15. Save/load restores wall, opening, installed door/window and parent relationship.
16. Unauthorized player cannot replace/remove the installed object.
17. Keyboard/mouse can complete the full flow.
18. Xbox-style controller can complete the full flow.
19. PlayStation-style controller can complete the full flow.
20. Performance remains stable during selection, preview, installation and repeated door interaction.

---

# Core Rule

> Metaworld builds the opening first and installs the door or window second. Openings, doors and windows are separate persistent systems connected by data-driven attachment slots, so structures can be repaired, upgraded, secured, damaged and customized without duplicating whole wall Blueprints or relying on fragile collision hacks.