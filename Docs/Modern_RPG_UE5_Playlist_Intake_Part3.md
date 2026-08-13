# Metaworld — Modern RPG UE5 Playlist Intake — Part 3

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part2.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

---

# Episode 13 — Rigged Armor Equip / Unequip

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 3 Clothing/Body Fitting + Phase 11 Inventory + Equipment + Phase 35 Combat.

Detailed companion:

`Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`

## Approved Tutorial Intent

- rigged armor needs dedicated presentation slots/regions such as chest, hands, legs and feet;
- item data may reference a dropped/world mesh and a worn rigged mesh;
- equipping/unequipping should refresh the character presentation;
- equip logic belongs below the Inventory Widget instead of being owned by UI.

## Metaworld Upgrades

- authoritative equip logic lives in `BPC_MW_Equipment`, not merely moved from Widget to Player Blueprint;
- one `ItemInstanceID` may use different world, equipped and UI presentation assets without becoming duplicate items;
- Item Definition may contain world Static Mesh + equipped Skeletal Mesh/Outfit + icon + attachment/coverage/animation profiles;
- fixed skeletal armor components are presentation slots driven by equipment state, not independent inventories;
- equip transaction commits authoritative slot state first, then derives the appropriate visual mesh/outfit;
- unequip returns the same ItemInstanceID to a valid container/drop destination and restores the current avatar's base-body presentation for that region;
- do not restore one hardcoded mannequin/default mesh when the player's actual body/customization profile may differ;
- server validates possession, slot compatibility, requirements/conflicts and destination capacity;
- equipment UI refreshes from equipment-state events/deltas.

### Episode 13 Principle

> Equip the persistent armor item first; then resolve how that same item should look on the current avatar.

---

# Episode 14 — Full Plate Armor Pieces / Rigging Pipeline

**Classification:** UPGRADE — APPROVED CONTENT PIPELINE.

**Phase Ownership:** Phase 2 Character Creator + Phase 3 Clothing/Body Fitting + Phase 4 Animation + Equipment.

Detailed companion:

`Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`

## Approved Tutorial Intent

- pants/legs, gloves/hands and boots/feet are rigged to the compatible body skeleton;
- Data Transfer / Armature workflows are useful for fixed skeletal armor;
- world pickup representation can use Static Mesh/collision while worn representation uses rigged armor;
- icons and Item Definition data connect the pieces into inventory/equipment.

## Metaworld Upgrades

- chest/hands/legs/feet remain separate equipment ItemInstances unless a deliberate set-item design says otherwise;
- fixed skeletal Blender workflow remains one approved path while UE5.8 MetaHuman Outfit Assets remain another approved resizable path;
- Leader Pose / Copy Pose / Outfit fitting is chosen by content needs and profiling rather than hardcoding all wearable setup into Construction Script;
- every piece is tested against Metaworld's supported morph/body range, animation poses and vehicle/interactions;
- world collision is tuned for pickup/drop; equipped armor does not use dropped-world physics collision;
- item/world/equipped assets are presentation references under the same stable ItemDefinitionID/ItemInstanceID;
- armor sets may later define set metadata/bonuses, but matching appearance does not force all pieces to be one inseparable item.

### Episode 14 Principle

> A full armor set is a coordinated collection of persistent equipment pieces, not one hardcoded character costume.

---

# Episode 15 — Inventory Character Preview

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 67 UI + Phase 2/3 Avatar presentation + Equipment.

Detailed companion:

`Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`

## Approved Tutorial Intent

- inventory/equipment UI may display an animated 3D preview of the player's current avatar and gear;
- Scene Capture 2D + Render Target is a valid implementation path;
- preview equipment must remain synchronized with actual equipment state;
- preview hair/physics may need reduced simulation for stability/performance.

## Metaworld Upgrades

- do not duplicate the full Player Blueprint; use a local presentation-only `BP_MW_AvatarPreviewActor`;
- preview owns no authoritative inventory, combat, needs, currency, property, skills or networking state;
- feed preview compact AvatarCustomization + Equipment snapshots and derive visuals from the same ItemInstanceIDs;
- normal persistent multiplayer inventory does not pause the world;
- reject `Global Time Dilation = 0 + Custom Time Dilation` as the standard preview architecture;
- preview animates locally while the shared world continues normally;
- Scene Capture updates only while visible and can be event-driven/capped rather than an unlimited permanent capture;
- disable/reduce expensive preview cloth/groom physics when unnecessary;
- do not globally disable world-item physics merely because the local player opened inventory.

### Episode 15 Principle

> The inventory preview is a lightweight visual mirror of the player's avatar state, not a second player simulation.

---

# Episode 16 — Dynamic Item Tooltip / Details

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 9 Item DNA + Phase 11 Inventory + Phase 67 UI + Phase 68 Controller/Accessibility.

Detailed companion:

`Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`

## Approved Tutorial Intent

- inventory/equipment entries can expose a reusable item tooltip/detail view;
- tooltip can display item name, type/category, icon and future statistics;
- the same tooltip presentation should work for inventory and equipment slots;
- layered UI/Z-order must keep equipment controls clickable.

## Metaworld Upgrades

- tooltip accepts/derives an authorized Item Definition + Item Instance presentation snapshot rather than owning gameplay data;
- event/selection-driven refresh is preferred over repeated Player Blueprint/property bindings;
- tooltip can include quantity, condition, quality, weight, protection/damage, requirements, creator/provenance and comparison information where relevant;
- hidden/private/evidence data appears only when the local character is authorized to know it;
- mouse hover and controller/keyboard focus provide equivalent details;
- item comparison/detail overlays preserve and restore focus correctly;
- no mouse-only tooltip dependency.

### Episode 16 Principle

> A tooltip explains item truth already owned by the item/inventory/equipment systems; it does not calculate or store that truth independently.

---

# Episode 17 — Item Rarity / Presentation Tiers

**Classification:** UPGRADE — APPROVED PRESENTATION SYSTEM.

**Phase Ownership:** Phase 9 Item Definition presentation + Phase 67 UI.

Detailed companion:

`Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`

## Approved Tutorial Intent

Default familiar tiers may include:

- Common
- Uncommon
- Rare
- Epic
- Legendary

Inventory icons, equipment slots, tooltips and interaction prompts may share a consistent rarity style.

## Metaworld Upgrades

- rarity is presentation/classification metadata and does not automatically equal market value, power, condition, quality, legality, creator status or historical uniqueness;
- canonical style uses `RarityProfileID` / stable Gameplay Tag data; a small closed enum is acceptable internally only when deliberately limited;
- rarity style lives in one central profile/table rather than duplicated Player Blueprint `Switch` functions;
- profile may contain display name, color, badge/icon, border/material style and sort priority;
- rarity is never communicated by color alone—text/icon/symbol/pattern provides an accessibility-equivalent cue;
- item instance quality/durability/provenance remain separate from definition rarity unless a specific system explicitly connects them.

### Episode 17 Principle

> Rarity helps players read the catalog; it does not replace Metaworld's real item condition, value, provenance or world history.

---

# Episode 18 — Contextual Interaction Prompt

**Classification:** UPGRADE — APPROVED.

**Phase Ownership:** Phase 5 Interaction + Phase 67 UI + Phase 68 Controller/Accessibility.

Detailed companion:

`Docs/Inventory_Equipment_UI_Preview_Tooltip_Rarity_Interaction_Prompt_Architecture.md`

## Approved Tutorial Intent

- players receive a contextual prompt for actions such as Pick Up Item or Open Door;
- prompt visibility follows the current interaction target/range;
- item name/presentation can appear in the prompt;
- different interaction verbs/actions share one reusable prompt style.

## Metaworld Upgrades

- hardcoded `Press E` becomes the current Enhanced Input action/glyph;
- keyboard/mouse, Xbox-style and PlayStation-style prompts are supported and can change when the active device/binding changes;
- `BPC_MW_Interaction` + `BPI_MW_Interactable` remain the authoritative targeting/action contract;
- prefer one contextual HUD prompt per player for ordinary interactions rather than an always-present Widget Component on every item;
- world-space Widget Components remain allowed only where a deliberate world-space label/display is actually desired;
- prompt data can contain ActionID, verb, target name, optional rarity presentation, hold/tap behavior, enabled state and unavailable reason;
- seeing a prompt never bypasses server authority; the actual requested action is still validated;
- rarity/name styling does not expose hidden information the player should not know.

### Episode 18 Principle

> Show the player the action their current input device can perform on the resolved target; keep the actual interaction authority in the shared interaction system.

---

# Current Modern RPG UX Stack

`Authoritative Item / Equipment / Avatar State`
-> `Inventory / Equipment UI`
-> `Character Preview`
-> `Tooltip / Detail Panel`
-> `Rarity Presentation Profile`

`BPC_MW_Interaction`
-> `BPI_MW_Interactable`
-> `Current Interaction Option`
-> `Device-Aware Interaction Prompt`
-> `Server-Validated Action`

---

# Playlist Continuation Rule

Future episodes continue in Part 3 until another safe continuation is needed. Parts 1–3 remain the canonical intake/audit trail for this Modern RPG playlist; detailed companion documents remain implementation authority for established domains.