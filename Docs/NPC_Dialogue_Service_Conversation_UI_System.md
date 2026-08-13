# Metaworld — NPC Dialogue, Service Selection & Conversation UI System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative service validation / controller-complete / event-driven

## Canonical Principle

NPC dialogue is a contextual conversation/service layer over a living NPC. The dialogue widget may present actions such as Talk, Trade, Craft, Upgrade, Hire, Ask Information or other services, but the widget never creates those capabilities by itself.

> The NPC exposes what it can legitimately do right now; the dialogue UI presents those options; the owning gameplay system validates and performs the selected service.

Related canon:

- `Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`
- `Docs/Crafting_Recipes_Materials_Production_System.md`
- `Docs/Item_Upgrade_Reinforcement_Enhancement_System.md`

---

# 1. Dialogue Is Not Just A Trader Menu

A living NPC can expose different interactions according to current role, state and relationship.

Possible service/action IDs:

- `NPC.Action.Talk`
- `NPC.Action.Trade`
- `NPC.Action.CraftService`
- `NPC.Action.UpgradeService`
- `NPC.Action.RepairService`
- `NPC.Action.MedicalService`
- `NPC.Action.Hire`
- `NPC.Action.AskInformation`
- `NPC.Action.Quest`
- `NPC.Action.ReportCrime`
- `NPC.Action.Bribe` where legal/game rules permit
- `NPC.Action.Threaten` / crime-related actions where supported

Do not permanently close the architecture into one enum containing only Trade/Craft/Upgrade.

Use stable action/service IDs or gameplay tags/data so new professions and services can be added without rewriting the dialogue shell.

---

# 2. Service Availability Comes From World State

The dialogue UI asks the NPC/service resolver for currently available options.

Availability may consider:

- NPC role/profession;
- employer/business;
- business hours;
- current schedule;
- NPC alive/conscious/free to interact;
- combat/emergency state;
- player relationship/reputation;
- legal restrictions;
- licenses/permissions;
- required station/equipment availability;
- stock/funds/service capacity;
- faction/quest/world state;
- current conversation state.

Example:

A blacksmith might expose:

- Talk
- Trade
- Repair
- Upgrade

while the forge is operating.

If the forge loses power/fuel, `UpgradeService` can disappear or return a reasoned unavailable state while Talk remains available.

---

# 3. Suggested NPC Service Presentation Record

Conceptual:

`S_MW_NPCServiceOptionPresentation`

Possible fields:

- `ServiceActionID`
- display text/localization key
- icon
- availability state
- unavailable reason text/key
- priority/order
- hold/confirm policy if required
- target service/profile ID
- accessibility text

The widget receives presentation data. It does not hold raw NPC gameplay structs as authority.

---

# 4. Dialogue Widget Shell

Suggested local widgets:

`W_MW_NPCDialogue`
-> `W_MW_NPCDialogueOption`

Possible presentation:

- NPC name/identity known to player;
- portrait/avatar presentation where desired;
- dialogue/subtitle text;
- scrollable option list;
- service/action entries;
- close/back action;
- relationship/context indicators only where legitimately known.

Large option sets use scalable list presentation rather than manually placing fixed buttons.

---

# 5. Selecting A Service

Flow:

`Interact with NPC`
-> server/local interaction context resolves NPC
-> obtain current authorized service options
-> open `W_MW_NPCDialogue`
-> player selects `ServiceActionID`
-> revalidate NPC/context
-> route to owning service UI/system.

Examples:

`NPC.Action.Trade`
-> `W_MW_TraderCommerce`

`NPC.Action.CraftService`
-> Crafting service context bound to this NPC/business/workstation

`NPC.Action.UpgradeService`
-> Upgrade context bound to this service provider/profile

The dialogue option does not copy Trade/Craft/Upgrade logic into itself.

---

# 6. One Routing Layer, Not A Giant Select Node Forever

The tutorial's one `Open NPC Widget` event is a good cleanup step compared with one event per menu.

Metaworld generalizes it into an action/service router.

Conceptually:

`ServiceActionID`
-> service registry/router
-> target UI/service controller

Do not grow one giant Blueprint `Select` node with hundreds of service types.

A registry/data-driven router allows later systems to add services without rebuilding the NPC dialogue graph.

---

# 7. References & Context

Service UIs receive a compact context record, for example:

`S_MW_NPCServiceContext`

Possible fields:

- NPC CharacterID
- BusinessID optional
- ServiceProviderID/ProfileID
- interaction session/context ID
- relevant workstation/container IDs
- player CharacterID
- context revision/expiration

Do not pass transient Actor pointers as the only durable reference across menu transitions.

If the NPC becomes invalid/unavailable, the service closes or blocks commit safely.

---

# 8. Conversation vs Service Menu

Metaworld separates:

- conversational dialogue content;
- selectable service actions;
- authoritative service transactions.

A Talk path can later support:

- branching authored dialogue;
- quest/world-state responses;
- relationship-aware dialogue;
- voice/subtitles;
- facial/gesture animation;
- AI-assisted presentation where later permitted, but verified world facts remain authoritative.

Trading/crafting/upgrading remain their own systems rather than conversation-script side effects.

---

# 9. Input / Focus

Dialogue/service UI follows the canonical UI stack/input system.

Requirements:

- world does not globally pause;
- local movement/look may be restricted while a blocking dialogue menu is active;
- default focus goes to first valid option;
- D-pad/stick navigation works;
- Confirm/Back are logical input actions;
- mouse/keyboard works;
- Xbox-style controller works;
- PlayStation-style controller works;
- focus transfers cleanly when opening Trade/Craft/Upgrade and returns appropriately when backing out.

Do not hardcode `E` as both open and close logic throughout widgets.

---

# 10. NPC State Can Invalidate Dialogue

While a menu is open, the NPC/world can change.

Examples:

- NPC is attacked;
- NPC dies/is incapacitated;
- shop closes;
- player leaves allowed range;
- police action interrupts;
- business loses access/stock/service capability;
- multiplayer authority changes the context.

The UI must revalidate before meaningful commits and close/disable safely when the interaction session is no longer valid.

---

# 11. Presentation Cleanup

Reusable button styling, hover/focus indicators, backgrounds and close buttons are approved.

Rules:

- focus state is visible, not hover-only;
- active/disabled state is readable without color alone;
- close action uses shared UI behavior;
- hidden widgets stop unnecessary work;
- no forced garbage collection on normal close.

---

# 12. Performance

- options are built on dialogue open or when service availability changes;
- no per-frame scanning of every NPC service;
- NPC service capability is data/component driven;
- hidden dialogue/service UI stops work;
- heavy portraits/preview assets are soft/lazy loaded where useful;
- one interaction candidate is resolved through normal interaction significance rules.

---

# 13. Acceptance Tests

1. NPC can expose Talk/Trade/Craft/Upgrade independently according to role.
2. A service unavailable due to current world state cannot be opened by stale UI.
3. New service type can be added without rewriting every NPC class.
4. Dialogue option routes to owning service system rather than duplicating its logic.
5. Backing out of Trade returns to dialogue when policy allows.
6. NPC death/combat invalidates dialogue safely.
7. Hardcoded `E` is not required for dialogue navigation/close.
8. KBM/Xbox-style/PlayStation-style users can navigate all options.
9. Focus state is visible without mouse hover.
10. No gameplay transaction is committed solely because a dialogue button was clicked.

## Core Rule

> Metaworld dialogue is a contextual gateway into what a living NPC can currently say or do. Stable service actions, current world validation and shared UI routing keep Talk, Trade, Craft, Upgrade and future services modular instead of turning every NPC into a custom widget graph.