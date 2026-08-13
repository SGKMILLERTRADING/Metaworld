# Metaworld — Ranged Weapons, Bow, Ammunition & Quiver Container System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent / data-driven

## Canonical Principle

Bows, arrows, quivers and other ranged equipment use the same persistent ItemInstance, Equipment and Container architectures as every other item. A quiver is a specialized container/compartment for compatible ammunition, not a disconnected second inventory universe.

> Ranged combat consumes real persistent ammunition from an authorized source while the equipped weapon remains the same exact ItemInstance the character owns.

Related canon:

- `Docs/Persistent_Item_Interaction_Inventory_Architecture.md`
- `Docs/Equipment_Armor_Weapon_Attachment_Avatar_Fitting_Architecture.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`

---

# 1. Bow Item Definition / Instance

A bow is a normal Item Definition and persistent ItemInstance.

Possible definition data:

- `ItemDefinitionID`
- equipment category/tags
- two-handed equipment rule
- world/equipped presentation
- attachment profile/socket
- animation profile
- compatible ammunition tags
- draw/charge profile
- base damage/contribution profile
- durability/condition rules
- weight/mass
- upgrade/affix profiles
- sound/VFX presentation

Exact ItemInstance carries condition, quality, upgrades, generated affixes, ownership, provenance and other persistent state.

Do not require a unique child Blueprint for every ordinary bow when data/presentation profiles are sufficient.

---

# 2. Two-Handed Equipment

Bow commonly uses a Two-Handed equipment rule.

Equipping the bow can reserve/conflict with Main Hand + Off Hand according to `BPC_MW_Equipment` data.

If an Off-Hand shield/item is equipped, server resolves the conflict through normal equipment destination rules:

- move to inventory/container if capacity exists;
- stow to another legal slot where defined;
- reject bow equip;
- explicit world drop only where policy permits.

No item is silently destroyed.

Equipping an Off-Hand item while a bow is active resolves the reverse conflict through the same system.

---

# 3. Bow Attachment / Sockets

Sockets/attachment profiles are approved for rigid bow presentation.

Possible semantic attachments:

- `Socket.Weapon.Hand.L`
- `Socket.Weapon.Hand.R`
- `Socket.Weapon.Back`
- `Socket.Quiver.Back`

Actual hand choice depends on animation/weapon profile.

Attachment transforms are authored in reusable profiles rather than hardcoded throughout Player Blueprint graphs.

---

# 4. Ammunition Item Definitions

Arrows are normal persistent ItemDefinitions/ItemInstances or compact stack/lot records where stack policy permits.

Suggested tags:

- `Item.Category.Ammunition`
- `Ammo.Arrow`
- `Ammo.Arrow.Standard`
- `Ammo.Arrow.Fire`
- `Ammo.Arrow.Poison`
- `Ammo.Arrow.Broadhead`

Possible arrow state:

- quantity/stack;
- mass;
- quality;
- material;
- owner/possessor;
- stolen/evidence provenance;
- condition where meaningful;
- applied poison/condition metadata where supported;
- creator/crafter provenance;
- value.

Stack compatibility must preserve all state that cannot be erased.

---

# 5. Quiver Is a Specialized Container

Recommended conceptual container:

`ContainerID = Quiver ItemInstance / equipped quiver container`

Possible rules:

- allowed tags = `Ammo.Arrow.*`;
- slot/quantity capacity;
- mass/volume limits;
- quick-access ordering;
- equipped-only availability policy;
- owner/permission state;
- visible arrow-count presentation;
- attachment profile.

A quiver may itself be an equipable persistent ItemInstance with its own:

- ItemInstanceID;
- condition/quality;
- creator/provenance;
- capacity modifiers;
- appearance;
- upgrade state.

The arrows inside remain normal ItemInstances/stacks located in that ContainerID.

---

# 6. Backpack vs Quiver UI

A UI switcher/tab can present:

- Backpack / general carried containers;
- Quiver;
- future ammunition pouches/magazines where applicable.

But switching tabs does not move items or create a second inventory.

Preferred stable UI addressing:

- `UI.Inventory.General`
- `UI.Inventory.Quiver`

The selected container is a real `ContainerID`.

Widget index is presentation only.

---

# 7. Pickup Routing

Tutorial intent to route arrows to the quiver is approved with correction.

On pickup, the server/container resolver determines legal destination based on:

- item/ammunition tags;
- equipped/accessible quiver;
- quiver capacity;
- player preference/auto-route policy;
- general inventory capacity;
- ownership/access rules.

Possible policy:

1. compatible equipped quiver if space;
2. compatible carried ammo container;
3. general inventory if permitted;
4. reject pickup / leave in world if no valid destination.

Do not hardcode an `IsArrow` macro across every pickup/drop/remove/tooltip function.

Use container/item capability/tag rules centrally.

---

# 8. Ammo Source Resolution

When preparing a shot, the ranged-weapon system resolves compatible ammunition from approved accessible sources.

Possible priority:

- selected arrow/ammo type in equipped quiver;
- fallback compatible arrow in quiver;
- other explicitly allowed quick-access ammo container;
- general inventory only if design permits combat access from it.

The UI may show current ammo type and count, but the server owns available quantity/consumption.

---

# 9. Shot / Ammo Transaction

Suggested high-level flow:

`Player Draws / Releases Bow`
-> authoritative combat state validates weapon and character state
-> resolve compatible ammunition
-> reserve/consume one arrow according to shot policy
-> create/launch projectile representation or resolve shot according to combat architecture
-> apply durability/condition changes where required
-> persist inventory/ammo delta
-> replicate relevant combat result.

Client cannot fire infinite arrows by merely playing a local animation.

If no compatible ammunition is available, shot cannot commit as a normal arrow shot.

---

# 10. Projectile Identity / Recoverable Arrows

Not every fired arrow must remain a fully persistent ItemInstance while flying.

Possible policy:

- consume/decrement arrow stack at shot;
- spawn lightweight projectile presentation/combat Actor;
- on impact, result may break, despawn or create a recoverable world arrow ItemInstance/lot according to arrow definition and world rules.

Recoverable arrows preserve appropriate material/type/provenance where useful without requiring every in-flight projectile to become expensive persistent storage/network state.

Gameplay-important special arrows can use richer authoritative state.

---

# 11. Bow Stats / Combat Integration

The tutorial's damage, attack speed and critical chance concepts are compatible with the canonical Stats/Generated Item layers, but the Bow mesh/Data Table is not the combat authority by itself.

Effective shot outcome can depend on:

- bow definition/base stats;
- exact bow ItemInstance condition/quality/upgrades/affixes;
- arrow definition/type/quality;
- character skill/profession/attributes;
- draw state;
- target armor/resistance;
- distance/trajectory;
- status effects;
- server combat rules.

Avoid double-counting damage if both bow and arrow contribute.

---

# 12. Conditions on Ammunition

Special ammunition may carry condition application metadata.

Examples:

- poison arrow;
- burning arrow;
- tranquilizer-style effect where game/world rules support it;
- supernatural arrow effects.

On valid impact, the server may apply a condition through `BPC_MW_StatusEffects` according to the arrow/effect definition.

The arrow does not directly mutate target Stats from client-side projectile logic.

---

# 13. Encumbrance / Weight

Arrows, bow and quiver all contribute to carried load according to their real mass.

Moving arrows from backpack to quiver does not make their weight disappear.

Quiver can improve organization/quick access/capacity but does not bypass the canonical Carried Load system.

---

# 14. Inventory Operations

Pickup, remove, drop, split, transfer and tooltip operations remain generic Container/Item actions.

They do not require separate bow-specific copies of core functions.

Example:

`TransferItem(ItemInstanceID/Stack, SourceContainerID, QuiverContainerID)`

server validates compatibility/capacity and commits.

Dropping arrows from quiver uses the normal authoritative drop transaction.

---

# 15. UI / HUD

Possible ranged HUD presentation:

- equipped bow/weapon icon;
- current selected arrow type;
- accessible ammo count;
- draw/charge state where useful;
- no-ammo indicator;
- quiver/container shortcut.

UI refreshes from equipment/container/combat state events.

Do not calculate authoritative ammo count only from Widget children.

Controller navigation supports ammo selection and quiver management where exposed.

---

# 16. Persistence / Multiplayer

Persist:

- bow ItemInstance state;
- quiver ItemInstance/container identity;
- arrows/ammo stacks and exact persistent properties;
- current selected ammo preference where character/UI design chooses to persist it.

Server owns equip conflicts, ammo transfer and shot consumption.

Clients receive only relevant inventory/equipment/combat presentation state.

---

# 17. Performance

- ordinary arrows are compact stack/lot records while stored;
- quiver is a container record, not a live Actor full of arrow Actors;
- no global search of all inventory every frame for ammo;
- cache accessible ammo aggregates and update from container deltas;
- projectile Actors exist only while needed;
- recoverable arrows become world items only according to definition/significance policy;
- UI updates on inventory/equipment/ammo changes.

---

# 18. Acceptance Tests

1. Bow equips as Two-Handed and resolves Off-Hand conflicts without item loss.
2. Same Bow ItemInstanceID survives equip/unequip/drop/save/load.
3. Quiver is a real specialized ContainerID rather than a second inventory authority.
4. Only compatible ammunition can enter the quiver unless its profile explicitly allows more.
5. Arrow pickup auto-routes according to centralized container rules, not duplicated IsArrow macros.
6. Full quiver falls back/rejects according to defined destination policy.
7. Moving arrows backpack <-> quiver preserves same item/stack state and total carried mass.
8. Shot consumes/reserves ammunition authoritatively.
9. Client cannot fire when authoritative compatible ammo count is zero.
10. Different arrow types remain distinct when stacking rules require it.
11. Special condition-bearing arrows preserve/apply their effect metadata correctly.
12. Fired projectile does not require permanent persistent Actor state unless the arrow definition needs it.
13. Recoverable arrow result creates legitimate world item state without duplication.
14. Tooltip/pickup/drop/remove work through generic Item/Container contracts.
15. Keyboard/mouse, Xbox-style and PlayStation-style bow/quiver flows all work.

## Core Rule

> The bow is persistent equipment, arrows are persistent ammunition, and the quiver is a specialized persistent container. Ranged combat consumes real ammo under server authority while UI, sockets and projectile visuals remain presentations of that shared item/container truth.