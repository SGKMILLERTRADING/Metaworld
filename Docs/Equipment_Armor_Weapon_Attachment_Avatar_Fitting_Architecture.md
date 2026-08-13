# Metaworld — Equipment, Armor, Weapon Attachment & Avatar Fitting Architecture

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent

## Canonical Principle

Equipping an item changes the authoritative state of an existing persistent `ItemInstanceID`; it does not create a second unrelated copy just because a weapon or armor mesh appears on the character.

> Inventory, equipment slots, held weapons, worn armor, character visuals and world drops are different states/representations of the same persistent item system.

## Locked Direction

- Data-driven equipment tags/slots replace a closed enum as the scalable catalog taxonomy.
- Recommended component: `BPC_MW_Equipment`.
- Initial slots: Main Hand, Off Hand, Head, Chest, Hands, Legs, Feet; future Back/Belt/Holster/Accessory/etc. additions do not require redesign.
- Equip/unequip is a server-authoritative transaction on the same persistent `ItemInstanceID`.
- Two-handed weapons reserve/conflict with Off Hand by data, not UI special cases.
- Attached weapon/armor visuals reference the original ItemInstanceID; they never become duplicate owned items.
- Unreal Skeletal Mesh Sockets are approved for rigid attachments such as weapons/tools/accessories; mesh-specific sockets may be used when needed.
- Equipped collision differs from dropped-world collision and is controlled by data/combat state so held items do not interfere with the owning character/camera.
- Equipment UI is a view over equipment state, not the source of truth, and supports keyboard/mouse, Xbox-style and PlayStation-style controllers.
- Inventory capacity is validated during equip/unequip/conflict resolution; if no destination exists, world drop or another explicit policy is required rather than silently deleting an item.

## Presentation Assets Per Item Definition

One persistent item can legitimately use different assets for different presentation states.

Recommended Item Definition presentation fields may include:

- `WorldPresentationMesh` — dropped/placed world representation;
- `EquippedStaticMesh` — rigid held/stowed representation where appropriate;
- `EquippedSkeletalMesh` — rigged wearable representation where appropriate;
- `MetaHumanOutfitAsset` or equivalent resizable outfit reference where appropriate;
- `InventoryIcon`;
- `PreviewPresentationProfile`;
- `AttachmentProfileID`;
- `CoverageProfileID`;
- `AnimationProfileID`.

Example:

`PlateChest_ItemInstance_84721`
-> dropped in world uses a lightweight Static Mesh
-> equipped on body uses a rigged Skeletal Mesh or Outfit Asset
-> inventory uses a cached icon
-> preview UI derives the same equipped presentation from the same ItemInstanceID

This is not duplication. These are different representations of one authoritative item.

## Rigged Armor Slot Components

For fixed skeletal armor paths, the character may expose presentation slots/components for body regions such as:

- Chest/Torso
- Hands/Arms
- Legs
- Feet
- Head where deforming headwear requires it

These components are presentation surfaces controlled by `BPC_MW_Equipment`; they are not independent inventories.

When a compatible rigged armor item is equipped:

1. server commits the ItemInstanceID to the authoritative Equipment Slot;
2. the local/replicated character resolves the approved equipped presentation;
3. the correct Skeletal Mesh/Outfit is applied to the presentation slot;
4. Leader Pose / Copy Pose / outfit fitting / post-process method is applied according to the content profile;
5. body/hair coverage rules are refreshed;
6. animation/equipment profile state is refreshed;
7. UI is notified from equipment-state change.

When unequipped:

1. server removes the ItemInstanceID from the slot and resolves the destination container/drop policy;
2. the visual slot returns to the avatar's authoritative base-body/default presentation for that region;
3. coverage/hair/body visibility returns to the avatar/equipment-derived state;
4. the same ItemInstanceID continues to exist in inventory/world state.

Do not hardcode one tutorial default mesh as the universal restore value. The base visual comes from the current avatar/body/outfit profile so character customization survives equip/unequip correctly.

## Full Armor Set Composition

Chest, gloves, pants/legs and boots/feet are separate equipment items unless a deliberate set-item design says otherwise.

Each piece can define:

- allowed slot(s);
- compatible body/skeleton/outfit profiles;
- world/equipped presentation;
- armor coverage;
- protection values/types;
- durability/condition;
- weight/mobility effects;
- material/appearance variant;
- set/collection tags;
- required hiding/masking/corrective behavior.

A matching visual armor set may provide set-bonus or collection metadata later, but the player may mix pieces unless an explicit equipment rule forbids it.

## Hair / Body Coverage

Helmet and clothing definitions can drive coverage rules such as hiding selected hair groups, switching to tucked/compressed hair, hiding covered body regions, using coverage masks, or keeping face/hair visible for open helmets.

Do not use one universal `Helmet = Hair Invisible` rule.

## Armor Fitting Paths

### Fixed Skeletal Armor

A DCC such as Blender may fit armor to an exported source body, transfer/paint skin weights, bind it to the compatible skeleton, export FBX and validate the result in UE5.8.

The tutorial Data Transfer + Armature workflow is a valid starting point but requires deformation, clipping, weight and body-compatibility QA.

For modular follower armor, Leader Pose is allowed where the skeleton hierarchy and behavior fit the use case. Apply it as part of the equipment/avatar presentation setup rather than assuming Construction Script is the only correct runtime place for all future equipment state.

### Parametric / Resizable Outfit Armor

Where UE5.8 MetaHuman Outfit Assets are suitable, use them to resize clothing/armor across supported body shapes.

Rules:

- test the full Metaworld morph/body range;
- multiple source-body outfits may be required for quality at extreme body differences;
- visual correctness matters more than forcing one source body to fit every shape;
- the gameplay armor ItemInstance/Equipment state remains independent of the visual fitting technology.

## Morph Compatibility

Wearables must be tested against slim, average, muscular, heavy and very-heavy body profiles plus approved chest/waist/hip/shoulder/height/proportion ranges and common locomotion/combat/vehicle poses.

Solutions can include parametric Outfit resizing, corrective morphs, multiple body variants, body-region hiding/masking, custom skinning and authored alternate meshes.

Do not shrink the approved player identity range merely to make one armor asset easier to fit.

## Material Policy

`Two-Sided` materials are not a universal clipping fix. Use Two-Sided only when visible backfaces are genuinely required and profiling accepts the cost.

Actual clipping/deformation problems should be corrected through geometry, skin weights, body coverage/hiding, outfit fitting, material masks, corrective morphs or source-body/variant selection.

## Armor Gameplay State

Armor Item Definitions/Instances can carry coverage, protection type/value, durability/condition, damage state, weight, mobility effects where appropriate, weather/temperature protection, profession/faction/uniform tags, supernatural/magic properties, creator appearance and legal restrictions.

Combat reads authoritative equipped ItemInstance/Equipment state; the visual mesh is not the authority for protection.

## Animation Integration

Equipped state can select/layer unarmed, one-handed, two-handed, handgun, rifle, shield, work/tool and magic animation profiles through `ABP_MW_Master`, Linked Animation Layers, Motion Matching/Pose Search where appropriate, Montages, IK and Motion Warping.

## Multiplayer / Persistence

Persist/replicate compact CharacterID + equipment slot IDs + equipped ItemInstanceIDs + active/stowed state + relevant presentation profile revisions.

Server owns equip/unequip legality and item location. Clients reconstruct visual attachments from approved definitions rather than receiving cosmetic transform spam every frame.

The server does not need to replicate entire rigged armor assets as state; clients resolve approved presentation from Item Definition + equipment/avatar profile IDs.

## Performance / Tooling

- equipment visuals change only on equipment-state changes;
- no per-frame UI rebuild;
- no permanent physical simulation on every attached weapon;
- soft-load heavy equipment assets where practical;
- distant characters reduce hair/accessory/armor fidelity;
- modular skeletal component count and cloth/Outfit simulation are profiled;
- fixed and parametric armor paths are selected by measured quality/cost;
- Python Editor tooling can audit slot IDs, tags, sockets, attachment profiles, body-compatibility metadata, coverage rules, skeleton compatibility, collision, Two-Sided use, LOD/Nanite metadata and armor QA fixtures.

## Initial Tests

1. Equip one-handed weapon without creating a duplicate item.
2. Same ItemInstanceID returns to inventory on unequip.
3. Shield occupies Off Hand.
4. Two-Handed weapon resolves Off-Hand conflicts safely.
5. Incompatible item is rejected from wrong slot.
6. Inventory-full unequip resolves safely.
7. Helmet applies configured hair coverage without hiding unnecessary hair.
8. Fixed skeletal armor follows animation on its supported body profile.
9. Parametric Outfit path is tested across multiple body shapes where used.
10. Armor is tested on slim, muscular, heavy and very-heavy supported bodies.
11. Held-item collision does not block player/camera.
12. Drop restores correct world representation/collision.
13. Save/load restores equipped ItemInstanceIDs.
14. Other clients see correct equipped visuals.
15. Combat uses authoritative equipped weapon/armor state.
16. Keyboard/mouse, Xbox-style and PlayStation-style equipment flows all work.
17. Repeated equip changes create no orphan Actors/components.
18. Equipment remains within performance budget across nearby/distant characters.
19. Chest armor can use one world mesh and another equipped skeletal/outfit representation while preserving one ItemInstanceID.
20. Unequipping each armor region restores the current avatar's base-body presentation, not a hardcoded mannequin default.
21. Mixed chest/hands/legs/feet pieces resolve independently and persist correctly.
22. Preview UI shows the same authoritative equipment composition without becoming a second equipment owner.

## Core Rule

> Equip the persistent item, then derive the character presentation. Slots, sockets, meshes and widgets are representations of authoritative ItemInstance and Equipment state, not separate ownership systems.