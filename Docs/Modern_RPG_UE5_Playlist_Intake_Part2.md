# Metaworld — Modern RPG UE5 Playlist Intake — Part 2

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part1.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

---

# Episode 7 — Item Types, Weapon Assets & Database Expansion

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 9 Item DNA + Phase 11 Inventory + Equipment/Combat integration.

Detailed companions:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Item_Icon_Editor_Capture_Pipeline.md`

## Approved Tutorial Intent

- equipment-capable items need categories/slot compatibility;
- weapons need world meshes/collision/icons/data entries;
- item data can reference presentation and equipment metadata;
- new items should be addable through data rather than rewriting inventory logic.

## Metaworld Upgrades

- tutorial `ItemTypes_e` values such as Main Hand, Off Hand, Two-Handed and Shield become stable Equipment Slot/Type/Handedness tags/data rather than one permanently closed enum;
- an Item Definition can declare allowed slots, conflicting slots, handedness, combat/tool family, attachment profile, armor coverage, animation profile and other equipment metadata;
- converting a Skeletal Mesh to Static Mesh is approved only when the item is truly a rigid world/held object and does not require skeletal deformation;
- imported weapon collision is authored/tuned for world physics and interaction rather than blindly trusting auto-convex output;
- ordinary item variety remains data-driven; one child Blueprint per weapon is unnecessary unless the item has genuinely unique runtime behavior;
- icons use the existing cached editor capture pipeline;
- asset source/license/provenance is recorded before content is treated as production-approved;
- stable `ItemDefinitionID` / `ItemInstanceID` remain the identity system.

### Episode 7 Principle

> Equipment category is metadata on an item, not the item's identity and not a reason to duplicate item logic.

---

# Episode 8 — Inventory Focus, Capacity & UI Cleanup

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 11 Inventory + Phase 67 UI + Phase 68 Controller/Accessibility.

Detailed companions:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`

## Approved Tutorial Intent

- input focus must return cleanly from inventory UI to gameplay;
- inventory entries can be actionable buttons/controls in preparation for equipment actions;
- inventory capacity must be checked before accepting new items;
- empty visual slots must not create invalid array accesses/log warnings;
- UI readability/polish matters.

## Metaworld Upgrades

- inventory open/close uses Enhanced Input and explicit Game/UI focus routing for keyboard/mouse and both controller families;
- multiplayer world does not globally pause because one player opens inventory;
- clickable inventory entries become controller-focusable actions, not mouse-only buttons;
- capacity validation belongs to the authoritative Container/Inventory transaction, not only a Player Blueprint branch;
- future capacity may include slot count, mass, volume, dimensions, compartments and allowed-item rules;
- widget generation reads valid container records/deltas and never assumes every grid cell maps to a valid array element;
- no output-log warnings are accepted as normal empty-slot behavior;
- visual styling never changes item truth.

### Episode 8 Principle

> UI focus and polish must be clean, but capacity and inventory correctness live in the authoritative container system beneath the widget.

---

# Episode 9 — Equipment Slots & Equip/Unequip State

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 3 Clothing/Body Fitting + Phase 11 Inventory + Phase 35 Combat + Phase 67 UI.

Detailed companion:

`Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`

## Approved Tutorial Intent

- character equipment has dedicated slots;
- inventory selection can request an equip operation;
- the UI refreshes when equipment state changes;
- item type/slot compatibility decides where equipment may go.

## Metaworld Upgrades

- recommended runtime system is `BPC_MW_Equipment` rather than keeping authoritative equipment maps inside a Player Widget/Character graph;
- initial slots can include Main Hand, Off Hand, Head, Chest, Hands, Legs and Feet, with scalable IDs/tags for future slots;
- `EquipmentSlotIndex` is UI/local presentation metadata only, not permanent identity;
- authoritative slot state stores equipped `ItemInstanceID` and revision/state;
- `RequestEquip(ItemInstanceID, DesiredSlotID)` is server-validated for possession, compatibility, conflicts, condition and requirements;
- Two-Handed items can reserve/block Off Hand by data;
- Shield/dual-wield/tool/weapon conflicts are resolved through equipment rules rather than hardcoded widget branches;
- UI refreshes from equipment change events/deltas and supports keyboard/mouse, Xbox-style and PlayStation-style controller navigation.

### Episode 9 Principle

> Equipment UI requests a state change; the authoritative Equipment system decides which persistent item occupies which slot.

---

# Episode 10 — Spawn & Attach Equipped Weapons/Items

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Equipment + Phase 4 Animation + Phase 35 Combat.

Detailed companion:

`Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`

## Approved Tutorial Intent

- held/stowed equipment needs explicit attachment points;
- sockets provide reliable transforms relative to the character skeleton;
- an equipped item can have a runtime Actor/mesh representation;
- equipped collision may differ from dropped world collision;
- unequip must clean up the attached representation.

## Metaworld Upgrades

- use semantic attachment profiles/socket IDs instead of tutorial-only MainHand/OffHand placements scattered through Blueprint graphs;
- shared Skeleton Sockets are used when compatible meshes share the attachment; Mesh Sockets are available for mesh-specific placement;
- the attached Actor/component is a representation of the same `ItemInstanceID`, not a newly owned duplicate item;
- equip creates/enables presentation only after the authoritative equip transaction succeeds;
- unequip removes/disables the presentation while preserving the same persistent item identity;
- equipped collision policy is data/combat-state driven so held equipment does not block the owning character/camera while attack/block hit logic still works when required;
- stow/back/holster representations can use separate attachment profiles;
- grip alignment and animation later integrate with IK/animation profiles rather than one transform fitting every weapon.

### Episode 10 Principle

> Attach the representation of the equipped item; never create a second gameplay item just because a mesh appears in the character's hand.

---

# Episode 11 — Steel Helmet, Head Attachment & Hair Coverage

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 3 Clothing/Body Fitting + Equipment + creator-content pipeline.

Detailed companion:

`Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`

## Approved Tutorial Intent

- armor/helmet assets need correct scale/material/icon/item data;
- rigid head equipment can use a head attachment/socket where appropriate;
- hair/body presentation may need to change while armor is equipped to prevent clipping.

## Metaworld Upgrades

- external content is not production-approved merely because it is free; source/license/provenance must be recorded and verified;
- rigid helmets/goggles/hard accessories may use sockets, while deforming clothing/armor uses skeletal/outfit fitting instead;
- helmet definitions carry coverage rules rather than one universal `hide all hair` Boolean;
- possible policies include hide selected groom groups, use tucked/compressed hair, hide scalp/cards under full helmets, or keep hair/face visible for open helmets;
- armor/hair visibility derives from Equipment state and persists/replicates;
- helmet gameplay protection/durability is authoritative ItemInstance/Equipment data rather than inferred from the visible mesh.

### Episode 11 Principle

> A helmet can change hair/body presentation, but coverage is data-driven per item so player identity is hidden only where the equipment actually requires it.

---

# Episode 12 — Custom MetaHuman Armor Rigging / Blender Weight Transfer

**Classification:** UPGRADE — APPROVED CONTENT PIPELINE.

**Phase Ownership:** Phase 2 Character Creator + Phase 3 Clothing/Body Fitting + Phase 4 Animation + Equipment.

Detailed companions:

- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Playable_MetaHuman_Modular_Character_Assembly_Architecture.md`
- `Docs/Character_Morph_Customization_System.md`

## Approved Tutorial Intent

- custom armor must be fitted to the player body/skeleton;
- DCC tools such as Blender can transfer/paint skin weights and bind armor to a compatible skeleton;
- imported armor must animate correctly with the body;
- material/deformation/clipping QA is required after import.

## Metaworld Upgrades

- the tutorial Blender Data Transfer + Armature workflow is approved as one fixed skeletal armor path, not the only UE5.8 solution;
- UE5.8 MetaHuman Outfit Assets/parametric clothing are also an approved path where they preserve quality while resizing across Metaworld body shapes;
- fixed skeletal armor remains valid where custom skin weights/rigid-body behavior or a deliberate body profile requires it;
- multiple source-body outfits/variants, corrective morphs, body-region hiding and custom skinning may be needed across extreme body differences;
- every wearable is tested against Metaworld's broad slim-to-very-heavy/muscular body range and common movement/combat/vehicle poses;
- the project does not reduce the approved player morph range merely because one armor asset clips;
- `Two-Sided` material is not a universal clipping solution; use it only when visible backfaces are genuinely required and fix fitting through geometry/weights/coverage/outfit/morph methods;
- armor visual technology stays separate from armor gameplay ItemInstance/Equipment data;
- Python/Editor tooling can later audit skeleton compatibility, body profiles, coverage metadata, material policy, LOD/Nanite metadata and armor QA fixtures.

### Episode 12 Principle

> Armor adapts to Metaworld's player identities. The player creator is not narrowed to make armor authoring easier.

---

# Current Modern RPG Equipment Stack

`ItemDefinitionID`
-> `ItemInstanceID`
-> `Container / Inventory`
-> `RequestEquip`
-> `BPC_MW_Equipment`
-> `EquipmentSlotID + persistent ItemInstanceID`
-> `Attachment / Skeletal Outfit Presentation`
-> `ABP_MW_Master / Combat profile`
-> `Replication + Persistence`

Player-facing UI remains a controller-complete view over this state.

---

# Playlist Continuation Rule

Future episodes continue in Part 2 until another safe continuation is needed. Parts 1–2 are the canonical intake log for this Modern RPG playlist; detailed companion documents remain the implementation authority for domains already established.