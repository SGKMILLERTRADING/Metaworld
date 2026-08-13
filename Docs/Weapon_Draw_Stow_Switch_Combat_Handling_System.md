# Metaworld — Weapon Draw, Stow, Switch & Combat Handling System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / ItemInstance-preserving / animation-profile driven

## Canonical Principle

Drawing, stowing and switching weapons changes the presentation/readiness state of the exact equipped ItemInstances. It does not destroy ownership state and create replacement weapons merely because a different mesh/socket becomes active.

> The same sword can be in inventory, equipped-but-stowed, or equipped-in-hand. Those are states/representations of one ItemInstance, not different items.

Related canon:

- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Avatar_Communication_Character_Animation_Architecture.md`
- `Docs/Character_Action_Movement_State_Resolver_System.md`

---

# 1. Combat Handling Profiles

Do not use a permanent numeric enum such as `100 / 200 / Dual Wield / Shield / Bow` as Metaworld combat identity.

Use data/tags/profiles such as:

- `Combat.Handling.Unarmed`
- `Combat.Handling.OneHanded`
- `Combat.Handling.TwoHanded`
- `Combat.Handling.DualWield`
- `Combat.Handling.Shield`
- `Combat.Handling.Bow`
- `Combat.Handling.Handgun`
- `Combat.Handling.Rifle`
- `Combat.Handling.Tool`
- `Combat.Handling.Improvised`

The resolved handling profile comes from the exact equipped ItemInstances, their equipment slots, capabilities and current stance.

---

# 2. Socket / Attachment Profiles

Use semantic attachment points and item-specific AttachmentProfileID rather than converting enums directly to socket-name strings everywhere.

Possible semantic targets:

- MainHandGrip
- OffHandGrip
- BackPrimary
- BackSecondary
- HipRight
- HipLeft
- Holster
- ShieldBack
- BowBack

Actual skeleton/socket names are resolved by avatar/body/attachment profile.

This supports different body rigs and weapon proportions without changing gameplay identity.

---

# 3. Weapon Readiness State

Suggested states:

- Equipped.Stowed
- Drawing
- Equipped.Ready
- Stowing
- Switching

Equipment ownership and hand/slot occupancy remain authoritative throughout.

A weapon can be equipped in Main Hand equipment slot while visually stowed on the back/hip until the combat-ready state draws it.

---

# 4. Draw Flow

`Request Draw / Combat Ready`
-> server validates current equipment and action state
-> resolve handling profile
-> reserve `Action.Combat.DrawingWeapon`
-> play appropriate draw montage
-> at approved attachment phase, change presentation from stow attachment to hand attachment
-> commit Ready state
-> clear action tag/window at approved recovery phase.

Montage Notify can signal the visual attachment moment, but it does not create a new weapon or change ownership by itself.

---

# 5. Stow Flow

`Request Stow`
-> validate no blocking action
-> enter `Action.Combat.StowingWeapon`
-> play stow montage
-> at approved phase move representation from hand to stow attachment
-> commit Stowed state
-> clear action state.

If interrupted, reconcile from the authoritative readiness phase rather than leaving duplicate hand/back meshes.

---

# 6. Weapon Switching

Switching between equipped weapon configurations is one action transaction, not `destroy current weapon actor -> spawn replacement ownership`.

Suggested flow:

`Request Switch Loadout/Weapon`
-> validate target equipped ItemInstance(s)
-> validate slots/conflicts
-> enter `Action.Combat.ChangingWeapon`
-> stow current presentation at defined phase
-> update active handling/readiness selection
-> draw target presentation at defined phase
-> finish action.

The exact ItemInstances remain in Equipment state through the transition.

A lightweight presentation Actor/component may be recreated if implementation requires it, but recreation does not change item identity.

---

# 7. Off-Hand Resolution

Off-hand state follows canonical equipment conflict rules.

Examples:

- one-handed sword + shield;
- one-handed sword + empty off-hand;
- dual wield two compatible weapons;
- two-handed weapon reserves both hands;
- bow reserves required hand profile;
- rifle/two-handed firearm reserves compatible hand posture.

Switching must never silently delete the shield/off-hand item.

If target handling needs both hands, the equipment system resolves the off-hand to a valid stow/inventory state or rejects the switch according to policy.

---

# 8. Animation Montages

Equip/stow montages are approved, including upper-body slots when locomotion is allowed.

Profiles may define:

- draw montage;
- stow montage;
- hand/stow attach notify phase;
- action-open/cancel window;
- movement restrictions;
- IK grip profile;
- sound/VFX;
- handling layer.

Do not hardcode every weapon family into one Player Blueprint Select node as the catalog grows.

---

# 9. Action Spam Prevention

While Drawing/Stowing/Switching:

- incompatible weapon-change input is rejected/queued according to action policy;
- attacks/blocks/dodges are allowed only in defined cancel/open windows;
- repeated input cannot spawn duplicate weapon representations;
- interruption cleans owned action tags exactly once.

This uses the shared Combat Action system rather than a standalone `CanChangeWeapon` Boolean.

---

# 10. Inventory / Upgrade / Quickslot Integration

Because ordinary item upgrades preserve the same ItemInstanceID:

- upgrading a currently assigned/active weapon preserves quickslot identity;
- presentation/stats refresh from the updated ItemInstance;
- current draw/stow representation rebuilds only if the definition/profile changed;
- no replacement weapon reference is required for ordinary +1/+2/+3 upgrades.

Dropping/unequipping the weapon invalidates combat readiness through Equipment state.

---

# 11. Preview Actor

Inventory preview derives the same authoritative equipment/attachment profile but is presentation-only.

The preview may show:

- stowed state;
- ready/held state;
- selected equipment composition.

It never becomes a second weapon owner.

---

# 12. Multiplayer / Authority

Server owns:

- which ItemInstances are equipped;
- readiness state;
- legal switch action;
- hand/off-hand conflict result.

Clients animate and attach visuals responsively from compact state.

A client cannot locally attach an unequipped weapon to Hand_R and gain its combat stats.

---

# 13. Performance

- attachment transforms update only through normal skeletal attachment, not transform replication spam;
- avoid repeatedly spawning/destroying heavy weapon Actors if attachment-state reuse is cheaper;
- pool/lightweight presentations only when profiling supports it;
- soft-load weapon presentation assets where practical;
- distant characters can simplify draw/stow presentation while maintaining correct state.

---

# 14. Acceptance Tests

1. Drawing a sword preserves its ItemInstanceID.
2. Stowing moves visual presentation without moving ownership incorrectly.
3. Two-handed weapon resolves Off-Hand safely.
4. Shield never disappears during weapon switching.
5. Spam during draw/stow cannot duplicate weapon visuals.
6. Interrupting a montage cannot leave weapon simultaneously in hand and on back.
7. Upgrading a ready weapon preserves ItemInstance/quickslot identity.
8. Different avatar profiles can resolve different socket implementations from the same semantic attachment profile.
9. Player/NPC use the same handling contract where practical.
10. Server rejects locally faked ready weapons.

## Core Rule

> Metaworld changes weapon readiness, not weapon identity. Equipment owns the real ItemInstances; handling profiles, sockets, Montages and notifies move their presentation between stowed and ready states while the Combat Action system controls timing and legality.