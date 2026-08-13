# Metaworld — Inventory & Equipment UX: Character Preview, Tooltips, Rarity & Interaction Prompts

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / controller-complete / performance-budgeted

## Canonical Principle

Inventory and equipment UI presents authoritative Item, Avatar and Equipment state. It never becomes a second gameplay simulation.

> The preview, tooltip, rarity marker and interaction prompt are views over existing world truth. They do not own items, equipment, stats, input authority or persistent state.

Related systems:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Playable_MetaHuman_Modular_Character_Assembly_Architecture.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`

---

# 1. Inventory / Equipment Character Preview

A character preview is approved, but it must not duplicate the full gameplay Player Blueprint.

Recommended local presentation actor:

`BP_MW_AvatarPreviewActor`

The preview actor contains only the presentation pieces needed to render the avatar, for example:

- avatar/body/face presentation components;
- hair/groom presentation where enabled;
- equipment presentation slots/components;
- `ABP_MW_Master` or a dedicated compatible preview animation layer/profile;
- Scene Capture Component 2D when that implementation is selected;
- preview-only lighting/background helpers where useful.

It does **not** own authoritative:

- inventory;
- currency;
- combat;
- needs;
- property;
- skills/professions;
- world interaction;
- save state;
- multiplayer authority.

## Preview Data Flow

`CharacterID / AvatarCustomizationSnapshot / EquipmentSnapshot`
-> `BP_MW_AvatarPreviewActor`
-> presentation assembly
-> Scene Capture / UI output

When equipment changes, the preview receives the changed snapshot/ItemInstance presentation state and refreshes the affected visual slot.

Do not create a second inventory or a second owned copy of equipment for the preview.

## Preview Time / Animation

Normal persistent multiplayer gameplay does not globally pause when inventory opens.

Therefore the tutorial pattern:

`Global Time Dilation = 0`
+
`Preview Custom Time Dilation`

is rejected as the standard inventory-preview architecture.

Preferred behavior:

- world continues under normal multiplayer rules;
- preview actor animates locally at an appropriate preview rate;
- preview capture updates on menu open, avatar/equipment change and any deliberate low-rate idle animation refresh;
- no global physics freeze/unfreeze is performed merely to display inventory;
- if a deliberate single-player/debug pause mode exists, preview ticking is solved locally/isolated rather than changing the whole project's gameplay model.

## Preview Performance

- do not duplicate expensive gameplay components;
- disable/reduce preview cloth, groom physics and other simulation when not needed;
- capture only while the preview is visible;
- allow event-driven capture for static preview states;
- if an animated preview is desired, use a capped/quality-scaled capture update rate;
- reuse the preview actor/render target where practical instead of constantly spawning/destroying it;
- preview fidelity can scale independently from the actual local-player avatar.

---

# 2. Item Tooltips / Detail Panels

The tutorial's dynamic tooltip concept is approved.

A tooltip/detail model may include:

- display name;
- icon;
- category/type;
- rarity/presentation tier;
- quantity;
- condition/durability;
- weight/volume;
- protection/damage/tool capability where appropriate;
- equipped status;
- legal/stolen/evidence indicators only when the viewing character legitimately knows them;
- creator/provenance information where relevant;
- requirements/restrictions;
- contextual actions;
- comparison delta against equipped gear where useful.

## Data Flow

Do not make a tooltip repeatedly query the Player Blueprint through expensive per-frame bindings.

Recommended flow:

`Focused/Selected ItemInstanceID`
-> resolve authorized Item Definition + Instance presentation snapshot
-> populate/update tooltip once
-> refresh only when the selected item or relevant state changes.

UE5.8 project/widget compiler settings allow teams to restrict property bindings because they can carry significant performance cost; Metaworld should prefer event-driven widget updates for high-frequency inventory screens.

## Mouse + Controller

Tooltips are not hover-only.

- mouse hover can open/update a tooltip;
- controller focus on an inventory/equipment entry must provide the same information;
- keyboard focus/navigation must also work;
- compare/details can be opened through explicit actions when screen space is limited;
- focus returns predictably when overlays close.

---

# 3. Item Rarity / Presentation Tier

Classic tiers are approved as an optional/default presentation vocabulary:

- Common
- Uncommon
- Rare
- Epic
- Legendary

But rarity does **not** automatically equal:

- market value;
- power;
- legality;
- condition;
- quality;
- creator prestige;
- historical significance;
- uniqueness.

Those are separate item properties.

Recommended canonical metadata:

`RarityProfileID` or a stable Gameplay Tag such as:

- `Item.Rarity.Common`
- `Item.Rarity.Uncommon`
- `Item.Rarity.Rare`
- `Item.Rarity.Epic`
- `Item.Rarity.Legendary`

A small internal enum is acceptable for a deliberately closed default tier set, but UI styling must not depend on a Player Blueprint `Switch` scattered across widgets.

Use a central Rarity Presentation profile/table containing:

- display name/localization key;
- accessible color;
- icon/badge;
- optional border/material style;
- optional sound/VFX policy for special acquisition moments;
- sort priority.

## Accessibility Rule

Rarity is never communicated by color alone.

Use at least one additional channel such as:

- text label;
- icon/badge shape;
- border/pattern;
- symbol.

Inventory icon, Equipment Slot, Tooltip and Interaction Prompt may all consume the same Rarity Presentation profile.

---

# 4. Contextual Interaction Prompt

The tutorial's `Press E to pick up` widget is upgraded into the existing `BPC_MW_Interaction` architecture.

Recommended one-player HUD presentation:

`W_MW_InteractionPrompt`

The prompt is driven by the currently resolved interaction option rather than being a Widget Component attached to every ordinary item by default.

Possible prompt data:

- `ActionID`
- input action / glyph reference
- verb (`Pick Up`, `Open`, `Talk`, `Use`, `Repair`, etc.)
- target display name;
- target icon/category;
- optional rarity presentation for visible loot;
- hold/tap behavior;
- enabled/disabled state;
- unavailable reason;
- optional secondary actions.

Flow:

`BPC_MW_Interaction`
-> resolve current target through `BPI_MW_Interactable`
-> request available actions
-> select/current action
-> update HUD prompt
-> player activates Enhanced Input action
-> authoritative gameplay request executes.

## Device-Aware Input

Hardcoded `Press E` is rejected.

The prompt must support:

- keyboard/mouse binding;
- Xbox-style controller glyph/action;
- PlayStation-style controller glyph/action;
- rebinding;
- device changes during play.

UMG + Enhanced Input is the baseline. UE5.8 Common UI/Common Input may be used after project validation for cross-platform input routing and device-specific action/glyph presentation.

## World-Space Widgets

A Widget Component attached to a world object is allowed only when the game deliberately wants a world-space label/display.

For ordinary pickup/open prompts, prefer one contextual HUD widget per player because it avoids maintaining UI components on every interactable object and prevents screen clutter.

---

# 5. Input Focus / Menu Layering

Inventory, equipment, tooltip/details and preview layers must cooperate with input focus.

Required behavior:

- opening inventory selects a valid initial focus target;
- opening a tooltip/details overlay preserves the underlying selection;
- closing the overlay restores focus predictably;
- closing inventory returns gameplay input cleanly;
- mouse and controller can switch without trapping focus;
- no click-through caused by incorrect Z-order/layering;
- player movement/look handling follows the active menu's intended input configuration without pausing the shared persistent world.

Common UI can be evaluated for layered Activatable Widgets, action routing and controller-specific UI prompts, but Metaworld does not make it a mandatory dependency until validated in the project.

---

# 6. Multiplayer / Privacy

UI reads only state the local player is authorized to know.

- private inventory details are not replicated to unrelated clients just to support a local tooltip;
- preview is local presentation and is not a second network character;
- rarity/definition presentation may be public while hidden instance/evidence/legal properties remain permissioned;
- equip state still comes from server-authoritative Equipment state;
- interaction prompt never grants authority simply because an action appears locally—the server still validates the action.

---

# 7. Acceptance Tests

1. Inventory opens without globally pausing multiplayer.
2. Character preview shows current avatar and armor without duplicating gameplay inventory/equipment.
3. Equip/unequip updates real character and preview consistently from the same ItemInstance state.
4. Preview actor owns no authoritative gameplay systems.
5. Preview capture stops/reduces cost when hidden.
6. Tooltip works with mouse hover and controller/keyboard focus.
7. Tooltip refreshes from item-state changes without per-frame polling.
8. Rarity style is consistent across inventory, equipment, tooltip and prompt.
9. Rarity is readable without relying on color alone.
10. Market value/condition/quality remain separate from rarity.
11. Interaction prompt shows the currently bound keyboard or gamepad action rather than hardcoded `E`.
12. Switching Xbox-style/PlayStation-style/keyboard input updates prompt presentation where supported.
13. Ordinary world items do not each require an always-active Widget Component.
14. Opening/closing detail overlays restores focus correctly.
15. Invalid/unauthorized interaction can display a reason but still fails server validation.
16. UI state survives large inventories without warning spam or frame-time spikes.

## Core Rule

> Metaworld's RPG UI can be rich and informative, but it remains a lightweight, controller-complete presentation layer over persistent authoritative character, item, equipment and interaction systems.