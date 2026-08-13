# Metaworld — Construction Build Catalog UI System

**Status:** Canonical / Approved Phase 20 + Phase 67 Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / data-driven

## Canonical Principle

The Build Catalog is a scalable, controller-first view of canonical Buildable Definitions. It helps players discover, compare and select construction content without duplicating construction rules inside widgets.

> UI selects construction intent. Authoritative Buildable data and the Build Component determine the actual placement rules, costs and world result.

## Approved Tutorial Intent

Metaworld keeps:

- buildable icons and presentation metadata;
- resource requirements displayed in the menu;
- dynamic population from buildable data;
- both grid/tile and list layouts;
- selecting an entry and transitioning into normal Build Mode.

Metaworld upgrades:

- no mandatory hardcoded `B` key;
- no mouse-only workflow;
- no direct dependency on ThirdPersonCharacter internal arrays;
- no loading every heavy construction asset just to populate the menu;
- widgets display canonical data but do not create permanent world structures themselves.

## Catalog Entry Data

A lightweight catalog record can contain:

- `BuildableID`
- `FamilyID`
- `VariantID`
- display name
- description
- icon/thumbnail soft reference
- category/subcategory
- search tags
- base material/GrimKoin requirement summary
- profession/permit summary
- placement-mode summary
- unlock/availability state
- favorite state
- recently-used ranking
- unavailable reason

The Buildable Definition remains the source of truth; the UI record is derived presentation data.

## Layouts

Supported views can include:

- Grid/Tile catalog
- List catalog
- quick-select strip
- family/variant carousel
- details/requirements panel

Grid is good for visual browsing. List view is useful for dense information and accessibility. Required functions remain available with keyboard/mouse and controller.

## Navigation Hierarchy

`Build Catalog -> Category -> Family -> Variant -> Details -> Select -> Build Mode`

Example categories:

- Foundations
- Walls
- Floors
- Roofs
- Stairs/Ramps
- Doors
- Windows
- Supports/Columns
- Prefab Houses
- Furniture/Placeables
- Utilities
- Exterior/Landscaping
- Security
- authorized temporary/public works

Categories are data-driven rather than one large hardcoded switch graph.

## Search / Filter / Sort

Approved features:

- text search
- category/subcategory
- family/variant
- favorites
- recently used
- available/unavailable
- profession-compatible
- permit-required
- affordable now
- material availability
- placement type
- indoor/outdoor
- structural/decorative
- utility type

Filtering operates on lightweight metadata.

## Resource Display

The resource UI integrates with the canonical Construction Material Delivery system.

Menu entries/details may show:

- required item icon/name
- base required quantity
- available quantity when the selected inventory context is known
- missing amount
- base GrimKoin/fee estimate
- profession/tool requirement
- permit requirement
- contextual warning that terrain supports or other placement conditions can change final cost

The catalog can show `Base Cost` or `Estimated Cost` when the final authoritative site cost depends on terrain, support extensions, zoning or other world conditions.

## Availability Feedback

Unavailable content should explain why where appropriate, for example:

- locked/unlearned
- profession required
- certification required
- permit required
- unavailable for this property/zone
- missing material
- insufficient funds
- restricted organization/public asset

The menu should not merely grey out an item with no explanation.

## Selection Flow

`Open Catalog`
-> browse/filter
-> select stable `BuildableID/VariantID`
-> update `BPC_MW_BuildComponent`
-> close/minimize catalog according to UX context
-> create/refresh local ghost
-> continue normal placement validation

Quick next/previous cycling remains available and uses the same stable selection data.

## Input Architecture

Use Enhanced Input/contextual UI actions instead of a mandatory physical key.

Required capabilities include:

- Open/Close Catalog
- Navigate Up/Down/Left/Right
- Confirm/Select
- Back/Cancel
- Category Next/Previous
- Filter/Search
- Favorite Toggle
- Variant Next/Previous
- Details/Requirements

Keyboard/mouse, Xbox-style controller and PlayStation-style controller paths are required.

## UMG / Common UI Direction

UMG is the baseline.

Common UI may be used for cross-platform focus, input routing, controller prompts and layered menu behavior after validation in the exact UE5.8 project configuration. Phase 20 does not require Common UI in order to function.

ListView/TileView-style entry reuse/virtualization should be preferred for large catalogs rather than creating an uncontrolled number of widget trees.

## Focus Rules

When the catalog opens:

- assign a deterministic focus target;
- restore prior selection when helpful;
- provide a visible focus state;
- deliberately route/wrap grid/list navigation;
- make Back return to the expected layer;
- never require hover to see critical information.

## Performance

- cache a lightweight catalog index;
- soft-reference icons/heavy previews where practical;
- virtualize/reuse list and tile entries;
- load thumbnails/previews on demand;
- never instantiate every Buildable Actor to render the menu;
- do not load every mesh/material family on menu open;
- search/filter metadata instead of heavy content;
- profile menu opening, scrolling and category changes with a large catalog.

## Multiplayer / Authority

Catalog browsing is primarily local UI. The server still validates the selected Buildable/Variant, current requirements, property/zone rules, resources and permanent placement request before changing the persistent world.

## Player Preferences

Optional preferences can persist:

- last-used category
- favorites
- recently used
- preferred grid/list layout
- selected filters where desirable

These are UI/account preferences, not persistent world construction state.

## Accessibility

- readable text/UI scaling;
- color is not the only state indicator;
- visible controller focus;
- list alternative to dense grids where useful;
- keyboard navigation/rebinding;
- icon + text where practical;
- no mandatory fine mouse hover.

## Initial Tests

1. Catalog populates from Buildable Definitions.
2. Grid view works with keyboard/mouse, Xbox-style and PlayStation-style controller.
3. List view works with all supported input families.
4. Search/filter/favorites/recently-used work.
5. Selecting an entry updates `BPC_MW_BuildComponent` by stable ID and starts normal ghost placement.
6. UI does not directly create the permanent build Actor.
7. Missing requirement/permission reason is clear.
8. Large catalog does not synchronously load every heavy mesh.
9. Reopening the menu restores sensible focus.
10. Back/cancel exits cleanly without a stuck cursor/input mode.
11. Final server validation remains authoritative.
12. Menu opening and scrolling remain smooth at stress-test catalog size.

# Core Rule

> Metaworld's Build Catalog is a fast, searchable, controller-complete window into data-driven construction. It shows icons, costs and requirements, but it only selects intent; the Build Component and server still decide what becomes part of the world.