# Metaworld — HUD Notification & Feedback System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / event-driven / controller-complete

## Canonical Principle

Metaworld uses one reusable notification/feedback layer to tell the local player about completed actions, blocked actions, important state changes and short-lived contextual information.

> Notifications report gameplay truth after the responsible gameplay system decides what happened. They do not decide inventory, currency, equipment, crime, stats or world state themselves.

## Recommended Architecture

Suggested local UI manager/component or HUD-owned service:

`BPC_MW_NotificationFeed` or equivalent HUD notification manager

Presentation:

`W_MW_NotifyFeed`
-> `W_MW_NotifyEntry`

Possible notification payload:

- `NotificationID`
- `CategoryTag`
- `Priority`
- `Title/Text`
- optional icon
- optional item/currency/stat presentation snapshot
- quantity/amount where useful
- duration policy
- merge/group key
- timestamp
- optional action/details reference
- accessibility text

Use stable tags/data rather than a permanently closed enum when the category set is expected to grow.

Example tags:

- `Notify.Item.Pickup`
- `Notify.Item.Drop`
- `Notify.Inventory.Full`
- `Notify.Currency.Gained`
- `Notify.Currency.Spent`
- `Notify.Equipment.Changed`
- `Notify.Action.Blocked`
- `Notify.Warning.Encumbered`
- `Notify.Crime.Witnessed`
- `Notify.System.Info`

## Event-Driven Flow

Example pickup:

`Authoritative pickup transaction succeeds`
-> inventory/container state commits
-> gameplay system emits local feedback event
-> notification manager creates/merges a presentation entry
-> slide/fade animation plays
-> entry expires/removes cleanly

A failed pickup may create a different reasoned notification such as `Inventory Full` or `Too Heavy`, but a successful-pickup notification must never fire before the pickup actually succeeds.

This directly prevents duplicate/false messages during equip/unequip or rejected transfers.

## Queue / Stacking / Merge Policy

Metaworld should not spawn unlimited overlapping widgets.

The feed should support:

- maximum visible entries;
- queued lower-priority entries;
- merging repeated events when useful;
- priority/preemption for important warnings;
- duplicate suppression/cooldowns;
- safe cleanup when menus/HUD layers change.

Examples:

`Picked up Apple x1` repeated 5 times in a short interval may become `Picked up Apple x5`.

`Inventory Full` should not spam every frame while the player remains focused on the same item.

## Animation / Lifetime

Slide-in/fade-out animations are approved presentation.

Use animation-completion callbacks or a UI-owned lifetime timer/state machine to remove entries.

Do not couple notification lifetime to global gameplay time dilation. Normal Metaworld inventory/UI does not pause the shared world, and notification cleanup must remain reliable regardless of local menu state.

## Layering / Z-Order

Notifications belong to a deliberate HUD layer above normal inventory/menu content when the design calls for them to remain visible.

The UI stack must prevent:

- notifications rendering behind menus unintentionally;
- click-through/focus theft;
- notifications blocking controller focus;
- notification widgets becoming interactive unless explicitly designed to be.

## Accessibility

Notifications should support:

- readable text contrast;
- icon + text rather than color-only meaning;
- adjustable duration where practical;
- text scaling/accessibility settings;
- optional sound/haptic cue where appropriate;
- important warnings remaining understandable with audio disabled.

Do not communicate critical state only through animation/color.

## Multiplayer / Privacy

The notification feed is local presentation.

It may display only information the local player is authorized to know.

Examples:

- private wallet balance changes are local/private;
- another player's hidden inventory changes are not surfaced;
- crime/evidence notifications follow legitimate knowledge rules;
- a client notification never proves an authoritative transaction occurred unless the server/gameplay state confirms it.

## Performance

- event-driven; no Tick required for deciding whether a notification exists;
- reuse/pool entries if profiling justifies it;
- cap visible/queued entries;
- avoid expensive per-frame bindings;
- icons/text reference existing presentation data;
- notifications expire and release references cleanly.

## Acceptance Tests

1. Successful pickup creates one correct pickup notification.
2. Failed pickup does not create a success notification.
3. Inventory-full message does not spam continuously.
4. Repeated identical pickups can merge where configured.
5. Notifications clean up after animation/lifetime.
6. Inventory/menu layering does not hide or block the feed incorrectly.
7. Keyboard/mouse, Xbox-style and PlayStation-style UI focus remains unaffected.
8. Notifications continue to expire correctly while menus are open.
9. Currency notification shows authoritative amount/currency type.
10. Private information is never exposed to unrelated clients.

## Core Rule

> Gameplay systems decide what happened; the notification system tells the local player clearly, once, and at the right priority.