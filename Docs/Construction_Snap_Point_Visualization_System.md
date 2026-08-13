# Metaworld — Construction Snap Point Visualization System

**Status:** Canonical / Approved Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Construction snap/query volumes are implementation tools. Players receive clean, contextual placement guides derived from authoritative snap metadata rather than seeing raw developer collision components.

Core rule:

> Show only useful, compatible snap opportunities when they help the player place the selected buildable; hide irrelevant snap points immediately when context changes.

---

# 1. Tutorial Intake

Approved intent:

- nearby valid snap locations can become visible while building;
- only snap locations relevant to the selected buildable should be highlighted;
- indicators should disappear after they are no longer useful;
- color/line presentation should make placement easier to understand.

Upgraded/rejected tutorial implementation:

- do not expose raw Box Collision components as the final player-facing art;
- do not determine semantic compatibility only from one trace channel;
- do not leave every snap volume visible for a fixed arbitrary two-second window;
- do not poll every structure continuously to manage visibility.

---

# 2. Player-Facing Snap Indicators

A snap point may expose lightweight visualization metadata such as:

- `SnapPointID`
- `SnapTypeTags[]`
- local/world transform
- indicator style/profile
- orientation arrow/normal
- occupancy state
- availability state
- optional label/icon
- allowed family/variant tags
- priority/score metadata

Possible presentations:

- small outline box or bracket;
- socket marker;
- directional arrow;
- edge highlight;
- floor/wall/roof anchor glyph;
- door/window opening outline;
- support-point marker;
- valid/occupied/blocked color/state treatment.

The visualization is not authoritative placement geometry.

---

# 3. Contextual Filtering

When the selected Buildable changes, `BPC_MW_BuildComponent` resolves what snap types it accepts.

Example:

`Selected: Wall.Standard`

May reveal nearby:

- `Build.Snap.Wall`
- compatible foundation/floor wall edges

while hiding:

- Door slots
- Window slots
- Utility sockets
- Roof-only anchors

Example:

`Selected: Door.Security.Heavy`

May reveal only compatible unoccupied `Build.Attach.Door` openings whose dimensions/security class permit that Door.

Compatibility comes from stable IDs/tags/data and occupancy state, not only low-level collision response.

---

# 4. Visibility Lifetime

Snap guides appear only while there is a useful construction context.

Show/update when:

- Build Mode is active;
- a selected Buildable supports snapping;
- the player targets/approaches a structure with compatible points;
- the current candidate structure changes;
- occupancy/permission/compatibility changes.

Hide when:

- Build Mode exits;
- selection changes to an incompatible family;
- target structure is lost/out of range;
- placement succeeds/cancels;
- snap point becomes occupied/unavailable;
- relevant menu/context closes.

A short fade or timeout may be used for presentation, but correctness is driven by state/context rather than a hardcoded two-second timer.

---

# 5. Acquisition vs Visualization

Query-only Box Collisions/sockets may still be used internally for efficient snap acquisition.

Canonical separation:

`Query Volume / Socket`
-> finds candidate

`Snap Metadata`
-> decides compatibility

`Player Indicator`
-> communicates opportunity

`Server Validation`
-> decides whether placement is legal

Changing indicator color/visibility never changes authoritative collision or placement permission.

---

# 6. Indicator States

Suggested states:

- `Available`
- `BestCandidate`
- `Occupied`
- `Blocked`
- `RequiresPermission`
- `RequiresSupport`
- `OutOfRange`
- `UnavailableForSelectedBuildable`

Normally only Available/BestCandidate need strong visible presentation. Other states may appear when they help explain why placement fails without producing visual clutter.

---

# 7. Performance

- no idle per-structure Tick;
- no world-wide scan of snap points;
- ask only the hit/relevant nearby structure for filtered points through `BPI_MW_BuildSnapProvider`;
- pool/reuse lightweight indicator widgets/meshes where practical;
- cap visible indicators per candidate structure/interaction context;
- stop immediately when Build Mode exits;
- do not replicate indicator visuals; each client derives them locally from relevant replicated/world state;
- avoid expensive translucent overlays across large buildings when a small marker is sufficient.

---

# 8. Multiplayer Authority

The client may visualize predicted compatible snap points.

The server independently validates:

- Parent Structure ID;
- SnapPointID;
- selected Buildable/Variant;
- occupancy;
- support;
- property/zoning/access;
- obstruction/collision;
- resources/profession/permit rules.

A green indicator is never proof of authoritative permission.

---

# 9. Accessibility / Controller Support

Snap visualization must remain useful with:

- keyboard/mouse;
- Xbox-style controller;
- PlayStation-style controller.

The best candidate should be selectable without precise mouse cursor placement. Camera/reticle targeting, stick movement, candidate cycling and clear orientation indicators should support controller play.

Do not communicate validity through color alone; shape/icon/text/state can supplement green/red presentation.

---

# 10. Python / Editor Validation

Future tooling can audit:

- snap points with no visualization metadata where required;
- duplicate SnapPoint IDs;
- indicators far from their acquisition volumes;
- invalid orientation;
- missing compatibility tags;
- excessively large indicator counts;
- query volumes accidentally Visible/Blocking in gameplay;
- occupied/opening slots lacking clear state metadata.

---

# Initial Tests

1. Selecting a Wall shows only compatible nearby wall-edge points.
2. Selecting a Door shows only compatible Door openings.
3. Occupied Door opening is not presented as a valid target.
4. Changing selection immediately refreshes/hides irrelevant guides.
5. Leaving Build Mode removes all snap guides.
6. Raw Box Collision components remain hidden in normal gameplay.
7. Another client does not receive unnecessary snap-indicator replication.
8. Server can reject a locally highlighted point if authoritative state changed.
9. Controller player can identify/select the intended point without mouse precision.
10. Dense modular structure does not produce uncontrolled indicator clutter or frame spikes.

---

# Core Rule

> Metaworld exposes construction intent, not engine debug geometry. Snap points become clean contextual guides derived from the same stable IDs/tags/data used by placement, and only the nearby compatible opportunities the player actually needs are shown.