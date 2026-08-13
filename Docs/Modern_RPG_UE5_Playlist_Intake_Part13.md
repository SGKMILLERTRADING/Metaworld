# Metaworld — Modern RPG UE5 Playlist Intake — Part 13

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part12.md`

**Playlist Engine:** Unreal Engine 5.4 tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

**Counting Note:** This batch contains 8 unique tutorials, Episodes 104–111.

---

# Episode 104 — Player Blueprint / Quickslot Cleanup & Organization

**Classification:** LOCKED + UPGRADE — MAINTENANCE / MODULARIZATION.

**Phase Ownership:** Architecture Quality + Quickslots + UI + Blueprint Standards.

Detailed companions:

- `Docs/Quickslot_Hotbar_Item_Action_Assignment_System.md`
- `Docs/UI_Base_Widget_Modal_Input_Lifecycle_System.md`
- `Docs/Avatar_Communication_Character_Animation_Architecture.md`

## Approved Tutorial Intent

- fix stale Quickslot unavailable/overlay presentation after item state changes;
- organize large Blueprint graphs;
- categorize variables/functions;
- comment non-obvious logic;
- use Validated Get/optional-reference safety.

## Metaworld Upgrades

- Quickslot overlay derives from current Assignment + Availability state and refresh events rather than manually hiding one overlay at scattered call sites;
- `Collapse to Nodes` is useful for readability but does not replace extracting true gameplay domains into components/services/interfaces;
- Player Blueprint remains orchestration shell, not permanent home of Inventory/Stats/Quickslots/UI/Trade/etc.;
- optional transient widget references are validated, but system ownership prevents missing UI references from breaking gameplay;
- use naming/category/comment standards consistently so long-running Blueprint development remains maintainable.

### Episode 104 Principle

> Clean graphs matter, but real modularity comes from clear ownership. Collapse visual clutter, then move reusable domains out of the Player Blueprint instead of hiding a monolith inside collapsed nodes.

---

# Episode 105 — NPC Dialogue Window / Service Options

**Classification:** UPGRADE — APPROVED / NEW DIALOGUE-SERVICE UI DOMAIN.

**Phase Ownership:** NPC Interaction + Dialogue + Services + UI/Controller.

Detailed companion:

`Docs/NPC_Dialogue_Service_Conversation_UI_System.md`

## Approved Tutorial Intent

- reusable NPC dialogue/service screen;
- scalable option list;
- reusable option button;
- hover/selection presentation;
- NPC can expose options such as Trade, Craft or Upgrade;
- close restores normal input state.

## Metaworld Upgrades

- stable `ServiceActionID` / tags replace permanently closed `DialogueOptions_E` enum;
- service list comes from current NPC role/business/world state;
- focus presentation must work for controller, not hover only;
- Dialogue UI is a gateway into services, not the implementation of Trade/Crafting/Upgrading;
- Talk/conversation is distinct from service actions and may later support authored branching dialogue/voice/relationships;
- world does not globally pause while dialogue UI is open.

### Episode 105 Principle

> The dialogue screen presents what this living NPC can legitimately say or do now; it does not invent permanent services just because a button exists.

---

# Episode 106 — Modular NPC Dialogue Routing To Trade / Craft / Upgrade

**Classification:** UPGRADE — APPROVED / SERVICE ROUTING.

**Phase Ownership:** NPC Services + UI Shell + Crafting + Upgrade + Commerce.

Detailed companions:

- `Docs/NPC_Dialogue_Service_Conversation_UI_System.md`
- `Docs/UI_Base_Widget_Modal_Input_Lifecycle_System.md`

## Approved Tutorial Intent

- replace separate menu-opening events with one reusable routing path;
- pass required NPC/service references/context;
- centralize input/focus behavior;
- standardize close buttons/background style;
- keep Craft/Upgrade service UI synchronized.

## Metaworld Upgrades

- one prototype Select node can become a data/service registry rather than growing into a giant switch forever;
- service screens receive stable `NPC CharacterID`, `BusinessID`, `ServiceProviderID/ProfileID`, workstation/container IDs and interaction-session context where relevant;
- Actor pointer alone is not the durable service identity;
- stateful UI ownership stays in local UI manager/base-widget lifecycle rather than static function libraries;
- Craft/Upgrade/Trade commits remain owned by their server-authoritative systems;
- NPC becoming unavailable invalidates the service safely.

### Episode 106 Principle

> One service router opens specialized systems from one NPC interaction context; it does not merge those gameplay systems into the dialogue widget.

---

# Episode 107 — Final Cleanup: Talk Prompt, Key Quickslot, Rarity Helper & Input Refactor

**Classification:** LOCKED + UPGRADE — ARCHITECTURE MAINTENANCE.

**Phase Ownership:** NPC Interaction + Quickslots + UI Helpers + Input.

Detailed companions:

- `Docs/NPC_Dialogue_Service_Conversation_UI_System.md`
- `Docs/Quickslot_Hotbar_Item_Action_Assignment_System.md`
- `Docs/UI_Base_Widget_Modal_Input_Lifecycle_System.md`
- `Docs/Physical_Keys_Locks_Doors_Access_Credentials_System.md`

## Approved Tutorial Intent

- NPC prompt should say Talk when Talk is the current action;
- prevent unsupported Quickslot assignment from causing key-item errors;
- move pure rarity-style logic out of Player Blueprint;
- standardize UI-only input/focus across screens;
- remove forced garbage collection workaround.

## Metaworld Upgrades

- prompt comes from current resolved `InteractionActionID`, so Talk/Trade/etc. cannot drift from NPC service truth;
- keys/credentials can be Quickslot-compatible only if they expose a legitimate quick-access capability; otherwise UI simply marks action unavailable rather than key-specific crash logic;
- rarity style lookup is a pure presentation service/helper and does not require Player Blueprint reference;
- shared UI manager/base lifecycle owns input modes/focus;
- forced GC on normal menu close is rejected; correct cleanup unbinds delegates, stops timers and clears transient references.

### Episode 107 Principle

> Clean UI behavior should come from shared contracts—resolved interaction actions, capability-aware Quickslots, pure presentation helpers and one input lifecycle—not one-off fixes in every widget.

---

# Episode 108 — Held-Key Input Fix & Base Widget Architecture

**Classification:** UPGRADE — APPROVED / SHARED UI-LIFECYCLE FOUNDATION.

**Phase Ownership:** Input + Phase 67/68 UI + Modal Screens.

Detailed companion:

`Docs/UI_Base_Widget_Modal_Input_Lifecycle_System.md`

## Approved Tutorial Intent

- prevent held keys from reopening/closing/activating UI unexpectedly;
- restore focus correctly after closing containers;
- fix slider/input-mode conflicts;
- create shared Base Widget behavior for input mode, cursor and Close.

## Metaworld Upgrades

- tutorial `CanPressKey` Legacy Input gate is replaced by Enhanced Input action states/context transitions;
- originating action does not leak into newly opened modal/service context;
- Base Widget owns only reusable lifecycle/presentation behavior, not gameplay authority;
- local UI manager owns the screen/modal stack and restores previous focus/input state;
- logical UI Back/Cancel replaces hardcoded physical close keys;
- no forced GC/delays required for correct lifecycle.

### Episode 108 Principle

> Fresh logical input actions and one modal/UI stack solve held-key bugs more reliably than Legacy Input booleans scattered across widgets.

---

# Episode 109 — Control Rig / Sequencer Animation Editing, Root Motion & Sprint Polish

**Classification:** UPGRADE — APPROVED ANIMATION-AUTHORING EXTENSION.

**Phase Ownership:** Character Animation + Locomotion + Interaction Animation + Editor Tooling.

Detailed companions:

- `Docs/Animation_Authoring_Control_Rig_Root_Motion_Workflow.md`
- `Docs/Avatar_Communication_Character_Animation_Architecture.md`

## Approved Tutorial Intent

- create animation directly with Control Rig/Sequencer;
- bake/edit existing animations for fixes;
- use Curve Editor/keyframes for polish;
- understand/use Root Motion where appropriate;
- add/repair sprint animation and foot synchronization;
- fix stale Quickslot listeners/widgets.

## Metaworld Upgrades

- Control Rig + Sequencer are approved production tools for custom/fixed animations;
- reusable runtime actions are baked/organized into canonical animation assets rather than leaving ordinary gameplay dependent on live Sequencer;
- Root Motion is used for appropriate discrete/contextual actions and never bypasses gameplay authority;
- Motion Warping/context targets handle ladder/vehicle/interaction alignment where appropriate;
- sprint animation reads authoritative Sprint/Stamina/Encumbrance state;
- canonical locomotion direction remains `ABP_MW_Master` + Motion Matching/Pose Search/animation layers where appropriate, not one permanent Blend Space-only architecture;
- quickslot double-trigger from discarded widgets is fixed through UI lifecycle/listener cleanup.

### Episode 109 Principle

> Unreal's in-engine animation tools are first-class production tools, but finished animation still plugs into one shared runtime animation architecture and cannot become gameplay authority by itself.

---

# Episode 110 — Ladder Actor / Interaction / Climb Animation Preparation

**Classification:** UPGRADE — APPROVED / NEW LADDER-TRAVERSAL DOMAIN.

**Phase Ownership:** Traversal + Interaction + Animation + World Objects.

Detailed companion:

`Docs/Ladder_Climbing_Traversal_System.md`

## Approved Tutorial Intent

- modular ladder asset and correct pivots;
- reusable ladder Blueprint/interactable;
- authored front direction and entry/exit reference points;
- interaction only from a reasonable approach side;
- prepare climb up/down/idle animations;
- imported animation can be repaired in Sequencer/Control Rig.

## Metaworld Upgrades

- stable traversal object/profile owns entry/top exit/climb axis/usable height rather than Player Blueprint magic offsets;
- facing/dot product is one interaction eligibility check inside the common resolver;
- no permanent proximity/facing Tick for idle ladders;
- 1D climb Blend Space is an approved prototype/content technique within a dedicated Ladder animation profile/layer;
- imported Mixamo/Fab/other animation requires license/provenance, retarget and root/orientation QA;
- ladder supports player and future NPC traversal through one interaction/traversal contract.

### Episode 110 Principle

> A ladder provides authored traversal targets and animation context; the common interaction/traversal system decides whether the character can enter it.

---

# Episode 111 — Functional Ladder Climbing / Vertical Movement / Exit

**Classification:** UPGRADE — APPROVED WITH MOVEMENT-STATE CORRECTION.

**Phase Ownership:** Traversal + Character Movement + Animation + Multiplayer.

Detailed companion:

`Docs/Ladder_Climbing_Traversal_System.md`

## Approved Tutorial Intent

- align character to ladder entry;
- constrain movement vertically while climbing;
- suspend gravity during climb;
- use climb state/Blend Space animation;
- use authored exit montage/root motion at top;
- restore normal movement/collision after exit.

## Metaworld Upgrades

- Character Movement `MOVE_Flying` may be used underneath a Blueprint prototype because it ignores gravity, but semantic gameplay state remains `Climbing.Ladder`;
- traversal component/state machine owns Entering/Climbing/Exiting/Interrupted state;
- climb movement is projected along authored ladder axis and cannot drift freely like real flight;
- Stamina, Encumbrance, injuries/status conditions may modify/block climb according to design;
- top/bottom exits validate clearance/target before root-motion/Motion-Warped transition;
- cancellation/death/interruption always restores a safe collision/movement state;
- multiplayer server validates ladder entry/exit and traversal state; client animation cannot teleport itself to the top;
- NPCs may use same traversal object where AI navigation supports it;
- different ladder heights reuse authored data rather than bespoke player graphs.

### Episode 111 Principle

> Ladder climbing is a real traversal state with constrained movement and authoritative entry/exit. Flying mode can be an implementation mechanism, but the character never gains free-flight semantics from climbing a ladder.

---

# Current Modern RPG Additions From Episodes 104–111

`Quickslot Assignment`
-> `Availability Event`
-> `HUD Presentation`
-> no stale overlay/listener state

`Living NPC`
-> `Current ServiceActionIDs`
-> `Dialogue / Service Selector`
-> `Trade / Craft / Upgrade / Future Service`
-> owning authoritative system

`Local UI Manager`
-> `Base Widget`
-> `Modal Stack`
-> `Enhanced Input Context`
-> `Focus Restore`
-> no forced GC / held-key leakage

`Control Rig / Sequencer`
-> create/edit/bake animation
-> `ABP_MW_Master / Animation Profile`
-> Root Motion / Motion Warping where appropriate

`Ladder TraversalObjectID`
-> validate approach
-> enter climbing state
-> constrained climb movement
-> climb animation
-> validated top/bottom exit
-> restore normal movement

---

# Playlist Continuation Rule

Future episodes continue in Part 13 until another safe continuation is needed. Parts 1–13 remain the canonical intake/audit trail; detailed companion documents remain implementation authority for established domains.