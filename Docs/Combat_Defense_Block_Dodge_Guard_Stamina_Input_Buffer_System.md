# Metaworld — Combat Defense, Block, Dodge, Guard, Stamina & Input Buffer System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / action-window-driven / resource-aware / movement-resolver integrated

## Canonical Principle

Blocking, dodging and buffered combat inputs are explicit combat actions with bounded timing windows, resource costs and movement policies. Defense state is derived from the active CombatActionInstance and equipment profile; it is not a loose Boolean that makes all incoming damage disappear.

> Stamina pays for exertion. Guard represents defensive stability. Dodge invulnerability, if used, is a short authored defense window. Input buffering remembers intent without bypassing legality.

Related canon:

- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Combat_Combo_Action_Windows_Attack_Timing_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Character_Action_Movement_State_Resolver_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`

---

# 1. Block Action

Suggested semantic action/tag:

`Action.Combat.Blocking`

A BlockProfile can define:

- compatible equipment/handling profiles;
- guard angle/arc;
- movement/strafe policy;
- stamina drain/cost policy;
- Guard resource profile;
- damage channels that can/cannot be blocked;
- block efficiency/mitigation;
- perfect-block/parry window;
- block reaction montage/profile;
- guard-break/stagger response;
- audio/VFX profile.

Holding Block requests/maintains a defensive action; it does not itself zero all damage.

---

# 2. Block Direction / Coverage

A successful block can require:

- attacker/impact lies within valid defensive arc;
- shield/weapon is in valid ready state;
- active action permits guarding;
- defender is not stunned/broken;
- damage channel is blockable;
- block occurred before impact.

Rear attacks or unblockable attacks can bypass ordinary guarding according to profile.

---

# 3. Guard / Block Power Is Separate From Stamina

Recommended resource concept:

`Guard` / `BlockStability`

Guard represents how much defensive pressure the current stance/equipment can absorb before guard break.

It may derive from:

- shield/weapon ItemInstance;
- blocking profile;
- character stats/skill;
- equipment condition;
- stance;
- conditions/buffs/debuffs.

Do not treat Guard as a fake replacement for Stamina.

Stamina remains the exertion/action resource.

---

# 4. Block Damage / Guard Damage

A blocked attack can resolve multiple outputs:

- reduced/zero/partial Health damage according to profile;
- Guard damage;
- Stamina cost;
- knockback/reaction;
- equipment durability loss;
- audio/VFX feedback.

Heavy attacks may deal high Guard damage even when Health damage is fully prevented.

Damage/guard formulas are data-driven; tutorial multipliers are prototype tuning only.

---

# 5. Guard Break / Stagger

When Guard reaches its break threshold:

`Guard <= 0`
-> commit `State.Combat.GuardBroken` / stagger action
-> end active block
-> play block-break/stagger animation
-> restrict incompatible actions for configured duration/window
-> regenerate/recover Guard according to policy.

The character cannot clear stagger merely by locally removing a tag.

---

# 6. Guard Regeneration

Guard recovery can have:

- delay after blocking/impact;
- rate/curve;
- equipment/profile modifiers;
- conditions/injury modifiers.

Event/timer/timestamp logic is preferred over permanent Tick.

Guard may not regenerate while actively holding a stressed block if the profile says so.

---

# 7. Block Movement / Strafing

Blocking may request a movement profile such as:

`Movement.Profile.CombatGuard`

The Character Action/Movement Resolver derives:

- walk speed;
- acceleration;
- orientation/strafe behavior;
- Sprint restriction;
- jump/dodge restrictions.

Do not directly set a hardcoded MaxWalkSpeed and later restore a stale default.

---

# 8. Capsule / Clipping Correction

The tutorial's dynamic capsule enlargement is not canonical as a general blocking solution.

Changing capsule radius can affect:

- doorways;
- navigation;
- overlap interactions;
- network collision;
- nearby actors;
- traversal.

Preferred fixes include:

- correct combat spacing;
- weapon/character collision profiles;
- movement separation;
- attack/guard root-motion tuning;
- animation/IK;
- target avoidance.

A bounded collision-profile adjustment may be used only if specifically tested and authored for the action.

---

# 9. Dodge Action

Suggested semantic action/tag:

`Action.Combat.Dodging`

DodgeProfile may define:

- direction selection;
- stamina cost;
- montage/root-motion profile;
- movement/collision policy;
- invulnerability window if any;
- cancel/recovery window;
- allowed starting states;
- input-buffer rules.

Dodge does not universally replace Jump. Input mapping/context can choose whether the same physical button means Jump, Dodge or another action based on combat state while preserving separate logical intents internally where practical.

---

# 10. Invulnerability / Iframes

If a dodge has an invulnerability window, represent it as a bounded defense state tied to the exact Dodge CombatActionInstance.

Possible semantic state:

`Defense.Invulnerability.Dodge`

Rules:

- starts/ends at authored action phases;
- server validates timing;
- applies only to configured damage families/events;
- cannot remain stuck after montage interruption;
- client cannot grant itself immunity by adding a tag.

Environmental damage such as drowning/fall/fire zones can follow separate rules and need not be ignored by combat dodge if the design says otherwise.

---

# 11. Combat Stamina Costs

Attacks/dodges/blocks may consume Stamina.

Cost can derive from:

- Attack/Dodge/Block profile base cost;
- exact weapon ItemInstance mass/handling;
- off-hand equipment;
- character stats/skills;
- Encumbrance;
- conditions/injuries;
- current movement state.

Do not equate `weapon weight = exact stamina cost` universally.

Weight can be one input to a data-driven formula.

---

# 12. Resource Reservation / Commit

For discrete actions:

`Request Attack/Dodge`
-> calculate authoritative cost
-> verify enough Stamina
-> reserve/commit cost according to action policy
-> start action.

A modified client cannot skip cost deduction.

For maintained block, Stamina/Guard costs can occur on start, over time, and/or on impact according to BlockProfile.

---

# 13. Input Buffer

Recommended conceptual record:

`S_MW_BufferedActionIntent`

Possible fields:

- InputActionID;
- requested action/context;
- requested timestamp;
- expires at;
- held/released state where relevant;
- target/context snapshot ID where appropriate.

Buffer stores intent only.

It does not pre-authorize the action.

---

# 14. Buffer Validation

When a legal action/cancel window opens:

- inspect highest-priority/latest valid buffered intent according to profile;
- verify it has not expired;
- revalidate current resources/equipment/state/target;
- execute if legal;
- otherwise reject/retain only if policy says so.

Example: Block was buffered, but player released Block before the action window opened -> do not begin a held Block.

---

# 15. Buffer Priority

Do not use one global closed enum forever for `LMB/RMB/Dodge/ToggleWeapon`.

Buffer operates on logical InputActionID / ActionDefinitionID and can support:

- AttackPrimary;
- AttackSecondary;
- Block;
- Dodge;
- WeaponChange;
- UseItem;
- future combat/magic actions.

Priority/replace/queue policy is data-driven.

---

# 16. Enhanced Input / Controllers

All defense actions are logical inputs with mappings for:

- KBM;
- Xbox-style;
- PlayStation-style.

Holding/releasing Block uses proper input trigger lifecycle so buffered block does not activate after the player has already released the button.

---

# 17. Acceptance Tests

1. Block only mitigates attacks inside its valid defensive arc/profile.
2. Guard and Stamina remain distinct resources.
3. Heavy blocked hit can break Guard without necessarily dealing full Health damage.
4. Ending Block restores movement through the Movement Resolver.
5. Blocking cannot permanently change capsule size/collision after interruption.
6. Dodge consumes authoritative Stamina once.
7. Dodge iframe exists only inside its authored action window.
8. Client-added invulnerability tag cannot block server damage illegally.
9. Buffered Attack executes only when a legal action window opens and resources remain valid.
10. Buffered held Block is discarded if the player released Block before execution.
11. Input buffer expires stale commands rather than executing them much later.
12. Guard recovery uses bounded event/timer logic rather than permanent Tick.
13. Controllers and KBM receive identical defense legality.

## Core Rule

> Metaworld defense is action-driven and resource-aware. Block uses directional coverage plus Guard/Stamina, Dodge uses authored movement and optional bounded iframes, and input buffering preserves responsiveness by remembering intent without ever bypassing current combat legality.