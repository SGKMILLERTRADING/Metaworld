# Metaworld — Modern RPG UE5 Playlist Intake — Part 19

**Status:** Canonical Playlist Intake Log Continuation

**Continues:** `Docs/Modern_RPG_UE5_Playlist_Intake_Part18.md`

**Playlist Source:** Unreal Engine RPG tutorial series

**Metaworld Target Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first

All permanent intake rules from Part 1 remain active.

This Part contains **Episodes 169–175**.

---

# Episode 169 — Directional Hit Reaction System

**Classification:** UPGRADE — COMBAT REACTION / ANIMATION EXTENSION.

**Phase Ownership:** Combat + Animation + Damage Feedback + Anatomy.

Detailed companion:

`Docs/Combat_Hit_Reaction_Directional_Impact_Animation_System.md`

## Approved Tutorial Intent

- directional hit-reaction animations;
- Front/Back/Left/Right reaction selection;
- upper-body reaction slots where locomotion should continue;
- reusable Combat interface communication;
- player and NPC compatibility.

## Metaworld Upgrades

- hit direction derives from target-local physical impact/source geometry, not only attacker rotation;
- projectile/explosion impact direction remains correct even if attacker is facing elsewhere;
- semantic body zone can influence reaction;
- light flinch, heavy reaction, Stagger, Guard Break, Knockdown and Death remain distinct result classes;
- successful Block/Parry/Dodge selects the appropriate reaction/result rather than always playing flesh flinch;
- animation presents committed combat result and cannot create/cancel damage;
- reaction detail scales by NPC significance.

### Episode 169 Principle

> Commit the hit first, then select a reaction from impact direction, anatomy, severity and current action state.

---

# Episode 170 — Enemy HUD / Sensing / Stack Weight / Combat Event / Stat UI Fixes

**Classification:** LOCKED + UPGRADE — MAINTENANCE / PERFORMANCE.

**Phase Ownership:** Combat HUD + NPC AI + Inventory + Combat Feedback + Stats UI.

Detailed companions:

- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/NPC_Combat_AI_Engagement_Death_System.md`
- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Combat_Feedback_Audio_Blood_VFX_System.md`

## Locked Fixes

- removing stack quantity changes carried mass by `UnitMass * RemovedQuantity`;
- dead NPC cannot restart perception/combat after delayed Stagger/recovery logic;
- block/parry/contact feedback deduplicates per authoritative action/contact rather than firing repeatedly from trace samples/damage channels;
- Stats/Vitals UI updates from event dispatch/change events while open;
- hidden enemy HUD must refresh from current Vitals snapshot when made visible.

## Metaworld Performance Upgrade

Enemy health-bar visibility can depend on:

- current target lock;
- recent damage/combat relevance;
- nearby engaged threat;
- boss/important profile;
- local accessibility setting;
- bounded distance/significance checks.

Do not run a permanent full-fidelity distance check on every enemy solely for a hidden health widget.

### Episode 170 Principle

> Maintenance fixes become invariants: exact stack mass, death-safe AI, deduplicated combat feedback and event-driven HUD state.

---

# Episode 171 — Breakable Wooden Crates / Chaos / Loot

**Classification:** UPGRADE — NEW BREAKABLE WORLD-OBJECT DOMAIN.

**Phase Ownership:** World Objects + Combat Damage + Chaos + Loot + Property/Crime.

Detailed companion:

`Docs/Breakable_World_Object_Destruction_Loot_System.md`

## Approved Tutorial Intent

- Geometry Collection / Fracture workflow;
- fragment collision profile;
- weapon/Point Damage interaction;
- Master Field / destruction impulse;
- destruction particles/audio;
- optional randomized loot;
- reusable child breakable variants.

## Metaworld Upgrades

- breakable has stable WorldObjectID + BreakableProfileID + authoritative durability/destruction state;
- combat/tool hit must be a validated damage event;
- object transitions to Destroyed exactly once;
- Chaos fragment count never controls loot quantity;
- debris cleanup is presentation and does not restore/reseed object;
- contents may be a pre-seeded ContainerID or one destruction-time LootProfile roll, never rerolled by reload/rebreak;
- physical Gold can be commodity loot only;
- tutorial Gold-as-money drop is rejected;
- legitimate GrimKoin/PromoKoin can only come from a real currency source/profile;
- destroying owned property can create crime/evidence/property-damage events.

### Episode 171 Principle

> A crate breaks once, its real contents/loot exist once, and Chaos debris never mints items or money.

---

# Episode 172 — Poison / Burning / Stun Combat Status Effects

**Classification:** UPGRADE — COMBAT/STATUS-EFFECT INTEGRATION.

**Phase Ownership:** Combat + Status Effects + Stats/Vitals + NPC AI.

Detailed companion:

`Docs/Combat_Status_Effect_Application_DoT_Resistance_Visual_System.md`

## Approved Tutorial Intent

- reusable effect definitions/data;
- Poison/Burning/Stun;
- probabilistic effect application;
- periodic damage timers;
- player/enemy shared Conditions Component;
- damage indicators for periodic effects.

## Metaworld Upgrades

- no second combat-only status framework; all effects use `BPC_MW_StatusEffects`;
- stable ConditionDefinitionID replaces closed enum identity;
- AttackDefinition/weapon/ammo/source contributes effect-application entries;
- server validates/rolls chance/potency/resistance;
- periodic damage uses scheduled pulses and the canonical DamagePacket pipeline;
- Status UI is presentation only;
- Stun is an authoritative Condition/state with movement/action restrictions.

### Episode 172 Principle

> Combat can attempt to apply a Condition; the shared Status Effect manager owns whether it becomes active and how it persists/stacks/pulses.

---

# Episode 173 — DoT Resistance / Poison / Stun / Death / Enemy Debuff HUD

**Classification:** LOCKED + UPGRADE — STATUS/DAMAGE MAINTENANCE.

**Phase Ownership:** Status Effects + Damage/Resistance + Vitals/Death + NPC AI + HUD.

Detailed companion:

`Docs/Combat_Status_Effect_Application_DoT_Resistance_Visual_System.md`

## Locked / Approved Corrections

- Poison/Burning periodic damage must pass through relevant resistance/damage policy;
- Poison and Burning can have different mitigation semantics;
- Stun blocks incompatible NPC movement/combat decisions while active;
- Health/Vitals/death pipeline owns death when Health reaches death state, regardless of damage source;
- direct combat, Poison, Burning, drowning and hazards therefore share one death transition;
- enemy HUD may display authorized active Conditions from the same manager;
- hidden widgets resync from current state rather than relying on repeated Construct hacks as gameplay truth.

### Episode 173 Principle

> Damage source changes; death authority does not. Direct hits and DoTs all resolve through shared Vitals, resistance and death state.

---

# Episode 174 — Poison / Burning / Stun Niagara Visuals

**Classification:** UPGRADE — STATUS-EFFECT PRESENTATION.

**Phase Ownership:** Status Effects + Niagara/VFX + Avatar/Equipment Presentation + Performance.

Detailed companion:

`Docs/Combat_Status_Effect_Application_DoT_Resistance_Visual_System.md`

## Approved Tutorial Intent

- Niagara poison visual;
- Burning variation;
- status visuals covering body/armor presentation;
- Stun animation/recovery;
- spawned effect tracking and cleanup;
- performance-conscious effect implementation.

## Metaworld Upgrades

- visual attachment uses semantic body/armor presentation tags/profiles, not hardcoded component arrays forever;
- gameplay Condition stays active even if distant VFX is culled;
- GPU Niagara is a profile/measurement choice, not universal requirement;
- spawned VFX components clean up from authoritative Condition removal;
- Stun montage is presentation of `Condition.State.Stunned`, not the authority that prevents movement;
- action coordinator + movement resolver own restrictions and recovery.

### Episode 174 Principle

> Niagara shows the Condition; it never becomes the Condition.

---

# Episode 175 — Input Release / Dedicated Parry / Stun AI / Friendly Fire / Action Reset Fixes

**Classification:** LOCKED + UPGRADE — COMBAT STATE RECONCILIATION.

**Phase Ownership:** Combat Actions + Parry + NPC AI + Faction/Target Filtering + Status Effects + Input.

Detailed companions:

- `Docs/Combat_Action_Gameplay_Tag_State_System.md`
- `Docs/Combat_Parry_Perfect_Block_Stagger_System.md`
- `Docs/NPC_Combat_AI_Engagement_Death_System.md`
- `Docs/Combat_Hit_Detection_Damage_Resistance_Feedback_System.md`
- `Docs/Combat_Status_Effect_Application_DoT_Resistance_Visual_System.md`

## Locked Fixes

- releasing Block input removes/ends Block only when Block is the relevant held action; it cannot accidentally cancel Attack/other actions;
- Parry may be a dedicated Enhanced Input action rather than being forced inside held Block;
- Parry remains an explicit CombatActionInstance with authored window and server validation;
- tutorial `0.1s` window remains tuning only;
- tutorial global time dilation remains rejected for persistent multiplayer;
- Stun/interrupt causes NPC perception/decision state to re-evaluate and cannot leave AI permanently stuck;
- friendly-fire/target filtering uses faction/relationship/attack rules and targetability, not a single Player-only tag;
- designated breakable world objects can be valid combat targets through their damageable/breakable capability;
- interruption cancels only incompatible active actions with explicit reason/reconciliation;
- do not blindly remove every action/state Gameplay Tag through a global `ResetAllActions` operation;
- key-item loot bug remains governed by generic ItemInstance/container identity rather than special duplicate key arrays.

### Episode 175 Principle

> Combat interruption must reconcile the real active action, input, AI and status state. Never solve one stuck action by erasing unrelated authoritative state.

---

# Part 19 Consolidated Rules

1. Hit reaction follows validated impact direction/body/state; animation is presentation.
2. Enemy combat HUD is significance/event driven; hidden UI stays synchronized from Vitals snapshots.
3. Stack mass changes by quantity, not one-unit assumptions.
4. Death is idempotent and owned by shared Vitals/death state.
5. Breakable objects destroy once and loot once.
6. Chaos fragments do not determine loot amount or persistence.
7. Gold remains physical commodity, never tutorial money.
8. Combat Conditions use the canonical Status Effect manager.
9. DoT damage uses the canonical damage/resistance/death pipeline.
10. Stun is authoritative state and interrupts only incompatible actions.
11. Niagara/status visuals are scalable presentation only.
12. Friendly-fire/target eligibility uses world faction/relationship/damage rules.
13. Dedicated Parry input is allowed; global multiplayer time dilation remains rejected.
14. Do not globally clear action tags to fix interruption bugs; reconcile the current action instance/state.

## Playlist Count

After this Part:

**175 unique Modern RPG playlist tutorials reviewed.**

Next unique tutorial is **Episode 176**.