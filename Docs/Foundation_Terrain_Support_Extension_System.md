# Metaworld — Foundation Terrain Support & Extension System

**Status:** Canonical / Approved Phase 20 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

## Canonical Principle

Metaworld foundations must establish a valid support relationship with terrain or another approved structural base. Uneven terrain may require additional foundation support pieces rather than allowing the main foundation to float.

Core rule:

> A foundation may bridge small approved terrain variation, but unsupported height must be resolved by valid structural support or the placement is rejected.

The UE4 tutorial concepts of downward traces, floating-build detection, multiple foundation sample points, preview support extensions, and restoring final materials/collision after placement are approved. Metaworld upgrades them into a data-driven, persistent, resource-aware, server-authoritative support-extension system.

---

# 1. Support Contexts

A foundation can be supported by one or more approved contexts:

- natural terrain/landscape
- engineered ground/foundation surface
- existing compatible structural foundation
- pier/column/footing support
- other explicitly approved structural support types

A random movable prop, vehicle, character, loose item or other non-structural object does not become valid ground merely because a downward trace hits it.

Support compatibility is defined through tags/data rather than raw trace hit alone.

Possible tags:

- `Build.Support.Ground`
- `Build.Support.Foundation`
- `Build.Support.Pier`
- `Build.Support.Column`
- `Build.Support.Structural`

---

# 2. Ground / Support Sampling

The tutorial uses four Arrow Components at foundation corners. Metaworld generalizes this into data-driven support sample points.

A Buildable Definition may provide:

- `SupportSamplePoints[]`
- local transform per sample
- required/optional sample flag
- maximum unsupported distance
- support trace/query distance
- allowed support tags
- slope/normal restrictions
- extension family/type to use when a gap exists

Examples:

- small square foundation: four corners + optional center
- long foundation: corners + intermediate edge points
- irregular foundation: custom sample layout
- large platform: grid or authored structural sample pattern

Exact sample count is content data, not a universal four-point rule.

---

# 3. Floating Placement Detection

During preview:

1. Resolve candidate foundation transform.
2. Transform authored support sample points into world space.
3. Query downward for approved support surfaces.
4. Measure support distance at each required point.
5. Determine whether direct contact, extension support or rejection is required.
6. Update preview/support visualization and placement reason.

Possible placement reasons include:

- `ValidDirectSupport`
- `ValidWithExtensions`
- `NoGroundSupport`
- `SupportTooDeep`
- `InvalidSupportSurface`
- `SlopeTooSteep`
- `OutsidePropertyVolume`
- `SubsurfaceRightsRequired`
- `MissingExtensionResources`
- `SupportCollisionBlocked`

The tutorial's single fixed height threshold becomes per-buildable support data.

---

# 4. Foundation Extensions

When a support sample is above valid support within the allowed extension range, Metaworld may preview one or more foundation extension pieces.

Possible extension families:

- pier
- footing
- column
- foundation post
- stacked modular support segment
- retaining/support structure later

Each extension is a real structural element, not visual filler.

Recommended extension data:

- Extension Buildable ID
- segment height
- minimum/maximum stack count
- allowed support surfaces
- material/resource cost per segment
- Construction Work Units
- durability/condition
- collision
- support capacity/class later
- Nanite/rendering policy where compatible
- persistent parent/child relationships

The number of required segments is derived from the support gap and extension definition. Tutorial-style `for loop` spawning is an implementation option, but the server owns the resulting authoritative support set.

---

# 5. Preview Representation

During build preview:

- main foundation ghost remains transient
- required extension ghosts are also transient
- extension preview can use gray/translucent construction material
- preview collision is Query Only / non-blocking where practical
- invalid extension locations turn the placement blocked/red
- valid extension requirement can use green plus an optional distinct support indicator

Preview extensions do not reserve permanent resources or become world structures until authoritative placement succeeds.

---

# 6. Resource & Construction Cost

Auto-generated support is never free merely because the system calculated it automatically.

Final cost can include:

`Foundation base cost`
+
`Required extension material cost`
+
`Builder labor / Construction Work Units`
+
`permit/inspection fees where applicable`

The build UI should show the added support requirement before confirmation where practical.

If required extension resources are unavailable, the ghost can remain geometrically valid but report `MissingExtensionResources` and block final construction.

Foundation extensions participate in the existing `Construction_Progress_Build_To_Completion_System` rather than instantly becoming completed permanent supports unless a specific simple buildable is deliberately configured for immediate completion.

---

# 7. Structural Relationship

A placed foundation can persist support relationships such as:

`Terrain / Approved Base`
-> `Foundation Extension / Pier`
-> `Foundation`
-> `Wall / Column`
-> `Upper Floor`

Each support element can store:

- Structure ID
- Buildable ID
- parent/support Structure ID
- child-supported Structure IDs where useful
- support sample / support-node ID
- transform
- owner/property
- construction state
- condition/damage
- timestamp / Builder / contract

This connects directly to the existing multi-story support graph.

---

# 8. Damage & Future Structural Failure

Foundation extensions are physical world objects.

Future damage systems may allow:

- damaged pier
- destroyed support segment
- undermined foundation
- damaged retaining support
- collapse/instability when required support is lost
- emergency shoring/repair
- Builder/inspection duties

Support recalculation happens on meaningful placement/damage/demolition events, not continuously every frame.

Metaworld does not need real-world finite-element engineering, but obvious unsupported structures should not remain magically stable when their configured critical support is removed.

---

# 9. Terrain, Slope & Surface Rules

A downward hit is not automatically a valid foundation surface.

Validation may consider:

- terrain/landscape support tag
- slope/normal
- water/deep water
- cliffs/voids
- roads/public infrastructure
- protected land
- underground structures
- existing property/structural ownership
- zoning
- construction exclusion volumes
- future soil/terrain classes where useful

A foundation may be rejected even when geometry exists below it if the surface is not legally or structurally approved.

---

# 10. Property / Depth Rights

Foundation extensions must remain within legal build rights.

Server validation can include:

- parcel footprint
- 3D construction volume
- subsurface/depth rights where configured
- public-road or neighboring-property encroachment
- underground utility exclusion zones later
- maximum foundation/support depth
- zoning/permit restrictions
- parcel build/performance budget

Owning the ground surface does not automatically authorize infinite underground construction.

---

# 11. Collision & Placement Footprints

Foundation and extension placement uses the canonical overlap-validation system.

Each support piece has explicit placement/obstruction footprint data.

Valid intentional contact is allowed between:

- extension and ground
- stacked extension segments
- extension and parent foundation

Invalid overlap with unrelated structures remains blocked.

The tutorial's temporary collision-ignore behavior is retained for preview only where appropriate. Permanent support collision reflects the physical completed construction stage.

---

# 12. Multiplayer Authority

Client preview may calculate:

- support sample hits
- estimated gap distances
- estimated required extension count
- predicted cost
- green/red feedback

But the client never authoritatively decides support.

On confirmation the server independently resolves:

- Foundation Buildable ID
- candidate transform
- authoritative support sample definitions
- valid terrain/structural support hits
- required extension Buildable IDs/counts
- property/depth/zoning rules
- overlap/occupancy
- Builder/permit requirements
- total materials/cost

Only after all checks succeed does the server create/reserve the persistent construction site and support structures.

A modified client cannot submit `SupportCount = 0`, shorten required extensions, fake ground height or bypass depth/resource requirements.

---

# 13. Performance

- support traces/queries run only while the relevant foundation is being previewed or validated
- sample points are authored and bounded, not world-wide scans
- preview extension meshes are lightweight/transient
- no permanent per-frame ground checking after placement
- support graph recalculation is event-driven
- distant/unloaded structures use persisted support relationships rather than live traces
- simple collision/footprints are preferred
- large foundation kits should use reasonable sample counts rather than hundreds of traces per preview update

---

# 14. Controller Compatibility

Foundation height/support preview and placement must work with:

- keyboard/mouse
- Xbox-style controllers
- PlayStation-style controllers

No support-adjustment or confirmation workflow may require precise mouse-only interaction.

The player should receive readable placement feedback such as:

- direct support
- requires 3 support segments
- too high above ground
- invalid terrain
- insufficient materials

through the same controller-navigable construction UI.

---

# 15. Python Editor Validation

Python Editor tooling can later audit:

- missing support sample points
- duplicate sample IDs
- sample points outside expected footprint
- missing extension definition
- invalid segment height
- missing collision/placement footprint
- unsupported support tags
- bad pivot/orientation
- suspiciously high sample counts
- missing resource/work metadata
- Nanite/performance metadata

Python remains Editor automation only.

---

# 16. Initial Vertical-Slice Test

The first terrain-support test should prove:

1. Flat-ground foundation places without extensions.
2. Slight uneven terrain remains valid within configured tolerance.
3. One raised corner previews required support extension(s).
4. Multiple corners can require different extension depths.
5. Preview extensions are visible but non-blocking.
6. Added extension materials/work are shown and validated.
7. Missing resources block final construction.
8. Excessive support depth rejects placement.
9. Invalid support surface rejects placement.
10. Another structure/vehicle/character does not become fake ground support.
11. Extension footprints cannot overlap unrelated structures.
12. Server recalculates all support samples and extension count.
13. Modified client cannot bypass required supports.
14. Successful placement persists foundation + support relationships.
15. Save/load restores support structures correctly.
16. Construction stages apply correct collision/material state.
17. Damaging/removing a critical support can trigger later structural reevaluation where configured.
18. Keyboard/mouse flow works.
19. Xbox-style controller flow works.
20. PlayStation-style controller flow works.
21. Preview remains smooth with the configured support-sample count.

---

# 17. Foundation Raise / Lower Elevation Adjustment

The playlist raise/lower-foundation feature is approved as an extension of this support system.

Canonical rule:

> Vertical foundation adjustment changes the requested candidate elevation; it never bypasses terrain support, overlap, zoning, resource or structural validation.

## 17.1 Data-Driven Elevation Controls

Do not use one universal raw `AddLocation.Z` constant as permanent architecture.

A Foundation Buildable Definition may include:

- `AllowElevationAdjustment`
- `ElevationStep`
- `MinElevationOffset`
- `MaxElevationOffset`
- `MaxTerrainEmbedDepth`
- `MaxRaisedFoundationHeight`
- optional `ElevationMode`
- optional variant-specific extension/support policy

Recommended runtime state in `BPC_MW_BuildComponent`:

- `RequestedFoundationElevationOffset`

The offset resets when:

- Build Mode starts;
- selected Buildable changes to a different definition/family;
- placement completes/cancels;
- the selected definition disallows elevation adjustment.

This prevents the previous foundation's vertical offset leaking into another buildable.

## 17.2 Enhanced Input

Use intent actions such as:

- `IA_MW_BuildRaise`
- `IA_MW_BuildLower`
- optional `IA_MW_BuildResetElevation`

Mappings must support:

- keyboard/mouse;
- Xbox-style controllers;
- PlayStation-style controllers.

The tutorial's physical `8` and `2` keys are examples only, not canonical bindings.

## 17.3 Candidate Transform

Foundation preview resolves:

`Base Candidate Transform`
+
`RequestedFoundationElevationOffset along approved vertical axis`
=
`Adjusted Candidate Transform`

Then the full foundation validation pipeline runs again.

The adjusted transform is not automatically valid just because it is within Min/Max offset.

## 17.4 Raising a Foundation

Raising a foundation can increase the gap between the main foundation body and approved ground/support.

After every meaningful raise step, recalculate:

- support sample distances;
- required extension/pier/footing count;
- added material requirements;
- added Construction Work Units;
- maximum extension depth;
- structural support legality;
- property/air/build-volume limits;
- overlap/clearance;
- slope/surface validity.

Example:

`Foundation raised 40 cm`
-> front samples remain direct support
-> rear samples now require 2 pier segments
-> preview updates supports/cost
-> server independently confirms on placement.

A player cannot raise a foundation beyond the definition's legal support range and leave it floating.

## 17.5 Lowering / Terrain Embed

Lowering a foundation may intentionally embed part of the foundation into terrain where the definition permits it.

This is not implemented by globally shrinking the obstruction box, dividing collision extents, or ignoring terrain overlap for every foundation.

Instead, use authored validation information such as:

- terrain-contact/embed allowance;
- `MaxTerrainEmbedDepth`;
- above-ground obstruction volume;
- below-ground foundation/footing volume;
- intentional-terrain-contact category;
- underground utility/exclusion checks;
- neighboring/public-property penetration rules.

Allowed terrain penetration is valid intentional contact only within the configured embed range.

The same candidate remains blocked if it intersects:

- another building;
- protected utility;
- road/public structure;
- neighboring parcel;
- invalid underground object;
- forbidden terrain volume;
- excessive depth.

The visible mesh and authoritative placement footprint remain separate concepts, consistent with the canonical overlap system.

## 17.6 Walls and Other Buildables

Foundation elevation controls do not automatically apply to walls/floors/doors/windows.

Other buildable families remain governed by their normal snap/support transforms unless their own definitions explicitly expose vertical adjustment.

For example:

- Wall snapped to foundation edge -> uses structural snap transform;
- Upper Floor -> uses supported floor snap rules;
- Furniture/free-standing object later -> may have a different placement-height policy;
- Foundation -> may use controlled terrain elevation adjustment.

No `IsFoundation ? AddLocation : Zero` branch should become a giant hardcoded family architecture; capability comes from Buildable Definition data/tags.

## 17.7 Multiplayer / Server Authority

Client may preview the elevation offset responsively.

Placement request can include the candidate transform/elevation intent, but the server resolves:

- authoritative Foundation Definition;
- legal Min/Max elevation;
- support sample results;
- extension count/cost;
- terrain embed allowance;
- property/build-volume rules;
- collision/overlap;
- resources/work requirements.

A modified client cannot submit an illegal vertical offset, suppress required supports, or claim terrain penetration is allowed when the definition says otherwise.

## 17.8 Persistence

Once placed, the foundation persists its final authoritative transform plus explicit support relationships.

The preview-only `RequestedFoundationElevationOffset` does not need to remain as separate world truth unless useful for audit/UI; the committed transform and support graph are sufficient.

Save/load restores the same StructureID, transform, extensions/supports and relationships rather than recalculating a different elevation from current player settings.

## 17.9 Performance

- no height-adjustment polling when no adjustable foundation is being previewed;
- input changes mark the candidate transform dirty and trigger bounded preview validation;
- support queries remain bounded by authored sample points;
- no permanent terrain-overlap checks after placement;
- no per-frame vertical replication; only final authoritative placement matters;
- preview refresh rate may be throttled/dirty-state driven while preserving responsive controls.

## 17.10 Added Tests

22. Raise foundation one step -> support/cost preview recalculates.
23. Lower foundation within allowed terrain embed -> placement remains valid.
24. Lower beyond `MaxTerrainEmbedDepth` -> blocked.
25. Raise high enough to require support extensions -> correct extension count and cost shown.
26. Raise beyond legal support depth -> blocked.
27. Vertical adjustment cannot bypass another structure's obstruction footprint.
28. Vertical adjustment cannot penetrate protected utilities/public/neighbor property.
29. Offset resets when leaving Build Mode or selecting a non-adjustable buildable.
30. Server rejects forged out-of-range elevation.
31. Save/load restores the exact committed elevated foundation/support graph.
32. Keyboard/mouse raise/lower works.
33. Xbox-style controller raise/lower works.
34. PlayStation-style controller raise/lower works.

---

# Core Rule

> Metaworld foundations adapt to terrain through real structural support, not floating placement or free visual filler. Support sampling predicts the terrain gap, data defines what support is legal, resources and Builder work pay for it, and the server authoritatively creates and persists the resulting foundation/support graph. Raise/lower controls adjust the requested elevation only; every adjusted position must still pass the same structural, legal, collision and resource rules.