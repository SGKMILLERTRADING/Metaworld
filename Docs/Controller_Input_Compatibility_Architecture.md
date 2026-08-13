# Metaworld — Controller & Input Compatibility Architecture

**Status:** Canonical / Approved

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / Enhanced Input

## Canonical Rule

Metaworld must be designed so Xbox-style and PlayStation-style controllers can operate the game alongside keyboard and mouse.

> No gameplay feature is considered complete if its required player interactions are mouse/keyboard-only when a reasonable controller mapping can exist.

This applies to character movement, combat, construction, snapping, inventory, character creation, vehicles, jobs, professions, property, banking, businesses, elections, media, social systems, supernatural systems, and future gameplay features.

This rule concerns controller support. Shipping native Xbox or PlayStation console builds remains a separate future platform, certification, SDK and business decision.

---

# 1. Enhanced Input Foundation

Use Unreal Engine 5.8 Enhanced Input.

Canonical concepts:

- Input Actions describe intent, not a physical key.
- Input Mapping Contexts map those actions to keyboard/mouse and gamepad controls.
- Contexts can change with gameplay state.
- Controls are rebindable where practical.
- Platform-specific redirects/settings may be used where useful.

Examples:

- `IA_MW_Move`
- `IA_MW_Look`
- `IA_MW_Interact`
- `IA_MW_Jump`
- `IA_MW_Sprint`
- `IA_MW_Attack`
- `IA_MW_Aim`
- `IA_MW_ToggleBuildMode`
- `IA_MW_BuildConfirm`
- `IA_MW_BuildCancel`
- `IA_MW_BuildNext`
- `IA_MW_BuildPrevious`
- `IA_MW_BuildRotateLeft`
- `IA_MW_BuildRotateRight`
- `IA_MW_ToggleSnap`
- `IA_MW_OpenBuildCatalog`

The gameplay Blueprint listens to the Input Action. It should not care whether the action came from a keyboard key, mouse button, Xbox controller button, or PlayStation controller button.

---

# 2. Controller Families

Metaworld input design targets at minimum:

- Xbox-style gamepads
- PlayStation-style gamepads
- keyboard and mouse

UI prompts should be capable of displaying the active input family rather than permanently displaying keyboard-only prompts.

Do not hardwire gameplay logic to branded button names. Use logical Input Actions and let mapping/prompt presentation resolve the device-specific button.

---

# 3. Construction Controller Requirements

Construction must be fully usable from controller.

Required controller-capable actions include:

- enter/exit build mode
- open/close build catalog
- next/previous buildable
- navigate categories
- confirm selection
- cancel/back
- rotate left/right
- toggle snapping
- fine adjustment where available
- move/aim placement preview
- confirm placement
- demolition/repair/renovation actions where allowed

The build catalog cannot require precise mouse-only interaction.

Use focus navigation, radial menus, category tabs, lists, shoulder-button cycling, stick/D-pad navigation, or equivalent controller-friendly UX.

---

# 4. Camera / Reticle Placement

Construction placement must not depend on a mouse cursor.

Keyboard/mouse and controller both use the active player view/camera to produce placement targeting.

For controller:

- right stick controls camera/look
- center reticle/view direction can drive placement trace
- left stick can move the character where build mode allows it
- optional fine-placement mode can remap stick behavior contextually

This keeps the construction targeting architecture device-agnostic.

---

# 5. Contextual Mapping

Use mapping contexts for modes such as:

- normal gameplay
- build mode
- vehicle
- inventory/UI
- character creator
- spectator/camera
- phone/device UI

The Input Action/context system should resolve changing controls intentionally rather than creating conflicting hardcoded input branches throughout Blueprints.

---

# 6. UI Navigation

All major menus should support controller navigation where practical.

Required principles:

- visible focused widget/state
- D-pad and stick navigation
- confirm/back actions
- shoulder/tab navigation where useful
- no tiny mouse-only hit targets as the sole way to access critical actions
- sensible default focus when a menu opens
- focus restoration when returning from submenus
- scroll lists usable without a mouse wheel

This applies to inventory, build catalog, character creator, bank, property, jobs, professions, elections, business management, media library, maps and settings.

---

# 7. Character Creator Controller Support

Morph customization must work on gamepad.

Controller-friendly patterns can include:

- category tabs
- D-pad/list navigation
- stick or trigger slider adjustment
- shoulder buttons for previous/next category
- reset individual morph
- compare/preset controls

A player should not need a mouse to make a slim, fat, muscular, elderly-looking, vampire, werewolf, or otherwise customized character.

---

# 8. Vehicles & Combat

Vehicle and combat systems must use the same logical-action architecture.

Vehicle examples:
- steer
- throttle
- brake/reverse
- handbrake
- enter/exit
- horn
- camera
- lights
- media controls where supported

Combat examples:
- aim
- attack/fire
- block
- dodge
- reload
- weapon/item selection
- contextual object use

Controller support is designed alongside each feature rather than added at the end.

---

# 9. Input Prompts

Metaworld should eventually detect/reconcile the active input source and present suitable prompts.

Possible prompt families:

- Keyboard/Mouse
- Xbox-style Gamepad
- PlayStation-style Gamepad

Prompt art/icons must follow platform/licensing requirements when branded assets are used.

The underlying gameplay action remains the same regardless of prompt family.

---

# 10. Accessibility & Rebinding

Approved goals:

- rebindable controls where practical
- stick sensitivity
- dead-zone settings
- invert X/Y where appropriate
- hold/toggle options for selected actions
- aim/look sensitivity
- vibration/haptics toggle where supported
- controller UI navigation
- keyboard/mouse remains supported

No critical gameplay progression should require unusually precise mouse interaction if a controller-friendly alternative can be designed.

---

# 11. Testing Gate

Every major player-facing system should be tested with:

1. Keyboard + mouse
2. Xbox-style controller
3. PlayStation-style controller

Minimum acceptance questions:

- Can the player enter and exit the feature?
- Can every required action be performed?
- Can menus be navigated?
- Can the player cancel/back out safely?
- Are prompts understandable?
- Does switching input device break state?
- Is the experience responsive without introducing per-frame input hacks?

A feature that passes keyboard/mouse but cannot be completed on supported gamepads is not finished.

---

# 12. Core Rule

> Metaworld gameplay is input-action-driven, not keyboard-driven. Xbox-style controllers, PlayStation-style controllers, and keyboard/mouse are first-class control paths, and every new player-facing feature must preserve that compatibility from the beginning.
