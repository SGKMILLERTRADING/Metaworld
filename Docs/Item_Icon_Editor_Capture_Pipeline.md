# Metaworld — Item Icon Editor Capture Pipeline

**Status:** Canonical / Approved Modern RPG Playlist Tooling Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Static/cached UI assets first; Blueprint + Python Editor automation

## Canonical Principle

Metaworld may generate consistent 3D-rendered inventory/catalog icons inside Unreal Engine, but ordinary inventory UI should consume cached icon textures rather than running a Scene Capture for every item at runtime.

> Render the icon once when content changes; reuse it thousands of times during gameplay.

---

# 1. Approved Tutorial Intent

The tutorial's workflow is approved as an editor-content technique:

- place an item mesh in a controlled capture scene;
- use a Scene Capture Component 2D;
- render to a Render Target;
- control camera, lighting and background/alpha;
- convert/finalize the result into an inventory-friendly Texture asset;
- associate that icon with the item's canonical definition.

The exact tutorial material graph/camera/light values are starting points, not global constants.

---

# 2. Canonical Item Definition Link

`ItemDefinitionID`
-> `InventoryIcon`

The icon is presentation metadata on the item definition.

Runtime inventory code does not need to know how the icon was generated.

Possible definition fields:

- `IconTexture`
- optional `IconMaterial`
- optional fallback category icon
- optional icon framing profile ID
- optional icon revision/version

---

# 3. Capture Blueprint

Recommended editor-only helper:

`BP_EU_MW_ItemIconCapture`

Possible components:

- preview Static/Skeletal Mesh component;
- Scene Capture Component 2D;
- controlled key/fill/rim or simple lighting;
- neutral/background plane if needed;
- framing marker/turntable helper.

Possible data-driven capture profile:

`DA_MW_ItemIconCaptureProfile`

Fields may include:

- render resolution;
- camera projection/FOV/ortho size;
- camera azimuth/elevation;
- mesh rotation;
- framing scale/margin;
- background style;
- lighting preset;
- output folder;
- texture/UI settings.

Different categories can use different profiles when appropriate: weapon, food, clothing, furniture, vehicle part, etc.

---

# 4. Python Editor Automation

Python Editor tooling is approved to batch-generate/audit icons.

Future tool concept:

`MW Item Icon Generator`

Input:
- selected Item Definitions or a catalog folder.

Process:
1. resolve the definition's visual mesh;
2. load the correct capture profile;
3. place/frame the item;
4. capture the Render Target;
5. create/update the Texture asset;
6. apply approved UI texture settings;
7. assign/update the icon reference in content data where safe;
8. report failures/warnings.

Python remains editor-only and does not generate inventory icons in packaged gameplay.

---

# 5. Runtime Performance Rule

Rejected as a universal pattern:

`Every visible inventory slot -> own live SceneCapture2D`

That would scale poorly.

Normal runtime UI uses cached textures/materials.

A dynamic runtime icon capture may be considered only for genuinely unique visual states that cannot be represented cheaply otherwise, such as a highly customized player-created item. If used, it must be:

- on-demand;
- cached;
- limited in concurrency;
- reused until the item's visible state changes;
- disabled/downgraded on lower scalability tiers if required.

---

# 6. Icon Quality / UI Settings

The tutorial's 256x256 icon is a valid prototype size, but output resolution is data/scalability/content-policy driven.

Guidelines:

- transparent or controlled neutral background;
- consistent framing by category;
- readable silhouette at small UI size;
- avoid clipping long weapons/large props;
- controlled exposure so dark/light items remain readable;
- UI-appropriate texture compression/settings;
- mip policy chosen according to actual UI usage rather than blindly disabled for every asset;
- source icon should remain sharp at its intended display scale.

---

# 7. Large / Irregular Items

Automatic framing must use item bounds or authored framing metadata.

Examples:

- knife vs rifle;
- apple vs refrigerator;
- shoes vs long coat;
- small component vs large furniture.

A single fixed camera transform will not frame every item correctly.

Definitions can provide optional icon-framing overrides when automatic bounds fitting is insufficient.

---

# 8. Animated / Skeletal Items

For clothing, armor or skeletal items:

- use a canonical preview pose if needed;
- avoid requiring full gameplay animation systems just to render a static icon;
- capture the visual state that best communicates the item;
- player-worn preview/mannequin systems remain separate from inventory thumbnail generation.

---

# 9. Validation

Future Python/Editor validation can detect:

- missing icon;
- missing mesh/visual source;
- blank/fully transparent capture;
- clipped bounds;
- inconsistent output resolution;
- bad texture settings;
- stale icon revision after source mesh/material change;
- duplicate output paths;
- icons that reference editor-only assets incorrectly.

---

# 10. Inventory Integration

The persistent inventory system uses the cached `IconTexture` only for presentation.

Item identity, quantity, condition, ownership, stack rules and transfer logic come from authoritative item/container data, never from the icon asset.

---

# Core Rule

> Item icons are production assets, not gameplay simulation. Generate them through a controlled Unreal Editor capture pipeline, automate the repetitive work with Blueprint/Python, cache the result, and keep runtime inventory rendering cheap.