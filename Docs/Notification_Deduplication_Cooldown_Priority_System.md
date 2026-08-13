# Metaworld — Notification Deduplication, Cooldown & Priority System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / event-driven / local-presentation-only

## Canonical Principle

Metaworld notifications must tell the player what matters without becoming spam. Repeated identical feedback can merge or cool down, while new higher-priority information can still appear immediately.

> Suppress repetition, not information.

Related canon:

- `Docs/HUD_Notification_Feedback_System.md`
- `Docs/Commerce_Buy_Sell_Quantity_Quote_UI_System.md`
- `Docs/Interaction_Hold_Progress_Modal_Input_State_System.md`

---

# 1. No Global DoOnce Lock

The tutorial's `Do Once + 5.5 second Delay` is a useful prototype but is not the final architecture.

A global lock could hide unrelated important messages.

Example bad result:

`Chest Locked` notification appears
-> global DoOnce blocks feed
-> player is then critically Encumbered / Bleeding / transaction fails for another reason
-> important message is hidden.

Metaworld rate-limits by notification identity/category/context rather than freezing the whole feed.

---

# 2. Stable Notification Key

Suggested payload fields:

- NotificationID / CategoryTag
- DedupKey / MergeKey
- ContextID / target ItemInstanceID / ObjectID where useful
- Priority
- CooldownProfileID
- MergePolicy
- Quantity/amount
- CreatedAt

Examples:

- `Notify.Lock.AccessDenied + DoorObjectID`
- `Notify.Commerce.NotEnoughCurrency + VendorID`
- `Notify.Inventory.TooHeavy`
- `Notify.Item.Pickup + ItemDefinitionID`

This allows precise suppression/merging.

---

# 3. Dedup Policies

Possible policies:

- AlwaysShow
- SuppressWhileVisible
- CooldownByKey
- MergeCount
- ReplaceExisting
- RefreshLifetime
- EscalatePriority
- QueueLatest

Examples:

Repeated locked-door attempts:
- show once;
- suppress same DoorObjectID reason for a short data-driven cooldown.

Repeated apple pickups:
- merge into `Picked up Apple x5`.

Different critical message:
- show immediately even while another lower-priority notification exists.

---

# 4. Cooldowns Are Data-Driven

Do not hardcode one universal `5.5 seconds`.

Profiles can vary:

- interaction denial: short;
- inventory full: short/medium;
- repeated commerce failure: short;
- critical survival warning: may refresh/escalate rather than suppress;
- tutorial/system information: longer.

Cooldowns use local notification-manager timestamps/timers, not gameplay-wide delays.

---

# 5. Different Message While One Is Active

The tutorial correctly notices that a new notification type should not be blocked by the old one.

Metaworld generalizes this with priority/category rules.

Example:

`Not enough GrimKoin`
then immediately
`You are Burning`

The Burning warning is not suppressed merely because a commerce message is still visible.

Higher-priority warnings can preempt or appear above lower-priority entries according to the feed policy.

---

# 6. Commerce Terminology

Tutorial messages such as:

- Player not enough gold
- Trader not enough gold

are translated to canonical currency/context feedback:

- `Not enough GrimKoin`
- `PromoKoin not accepted`
- `Vendor cannot afford this purchase`
- `Vendor storage full`
- `Quote expired`

Physical Gold material is never treated as the wallet currency.

---

# 7. Interaction Denials

Examples:

- Locked
- Requires Key/Credential
- Access Denied
- Too Far
- In Use
- Power Unavailable
- Container Empty

Repeated holding/pressing should not create dozens of identical cards.

The Interaction system emits a reason/result; notification manager decides presentation/cooldown.

---

# 8. Accessibility

If repeated visual notifications are suppressed, critical warnings may still use:

- persistent HUD icon/state;
- accessible text;
- sound/haptic cue where configured;
- refreshed severity indicator.

Do not make a one-time toast the only source of critical survival information.

---

# 9. Performance

- no Tick required for deciding duplicate messages;
- use timestamp maps/active-entry records;
- prune expired keys opportunistically/timer-based;
- cap visible and queued entries;
- merge repeated events before creating widgets;
- no duplicated notification widgets for suppressed events.

---

# 10. Acceptance Tests

1. Repeated same locked-door denial does not spam the feed.
2. Different notification type can appear immediately during another message's cooldown.
3. Repeated item pickups merge where configured.
4. Critical warning can preempt lower-priority commerce feedback.
5. Cooldown duration comes from data/profile rather than universal 5.5 seconds.
6. Same notification category can remain separate for different ContextIDs where needed.
7. GrimKoin/PromoKoin messages use correct terminology; Gold material is never called wallet currency.
8. Suppressed toast does not hide persistent critical HUD state.
9. Notification lifecycle remains event-driven and bounded.

## Core Rule

> Metaworld notifications are keyed, prioritized and data-rate-limited. Repeating the same failure should not flood the player, but a new or more important event must still be heard.