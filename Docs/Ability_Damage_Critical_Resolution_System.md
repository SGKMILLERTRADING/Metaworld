# Metaworld — Ability Damage & Critical Result System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / shared result pipeline

## Canonical Principle
Abilities may contribute modifiers to an existing gameplay result packet, but they do not bypass the canonical result resolver. Critical outcomes are resolved authoritatively from the active action, character stats, equipment state and target context.

## 1. Ability Result Contribution
An AbilityDefinition can reference a result profile or multiplier profile. Example:
`Whirlwind -> ResultProfile.Ability.Whirlwind`

The active `AbilityExecutionID` is included in the shared result pipeline. Existing character stats, exact equipped-item state, action profile, target defenses, body-zone context and active Conditions still determine the committed outcome.

A tutorial `DamageMultiplier` field is accepted as content data, never as a trusted client-submitted final value.

## 2. Critical Eligibility
Each action/result profile declares whether critical outcomes are allowed.

Possible inputs:
- attacker effective CriticalChance;
- ability/action critical modifier;
- equipped-item/affix state;
- target state/weakness where designed;
- semantic body-zone rules;
- guaranteed/noncritical tags;
- authoritative random stream.

Periodic effects and environmental effects do not automatically use critical logic unless their profile explicitly allows it.

## 3. Critical Resolution
`Validated gameplay contact/result`
-> build base result packet
-> critical eligible?
-> server resolves critical state
-> apply configured critical profile/multiplier in explicit ordering
-> continue defense/resistance resolution
-> commit final outcome
-> emit presentation snapshot.

The receiving client never decides whether the result is critical.

## 4. Weak-Point / Body-Zone Result Is Separate
A semantic weak-point/body-zone result and a random critical are separate facts.

A result may be:
- weak-point but not critical;
- critical but not weak-point;
- both;
- neither.

Multiplier ordering is explicit in the result profile so stacking is deterministic and balanceable. Tutorial values are tuning only.

## 5. Whirlwind Example
Whirlwind can apply its ability modifier to each legitimate target result while preserving per-action repeat rules. Each target independently resolves defenses and critical eligibility through the same server logic.

## 6. UI Presentation
Authorized feedback may include:
- final committed value;
- critical flag/style;
- weak-point flag;
- result-channel presentation.

Larger text/icon/animation for a critical is presentation only.

## 7. Provenance
A committed result can retain:
- Result/Damage Event ID;
- AbilityExecutionID where applicable;
- ActionDefinitionID;
- source ItemInstanceID(s) where applicable;
- critical result;
- semantic body zone;
- final components.

## Acceptance Tests
1. Ability modifier flows through the canonical result pipeline.
2. Client cannot submit the final ability result as trusted truth.
3. Critical resolution is server-side and profile-gated.
4. Weak-point/body-zone and Critical remain separate flags.
5. Periodic effects do not crit unless explicitly configured.
6. Multi-target ability results resolve independently.
7. UI cannot alter the committed result.
8. Effective equipment/affix state contributes through canonical stats.

## Core Rule
Metaworld abilities and critical outcomes enrich one authoritative result pipeline. They are resolved once with explicit ordering and provenance; presentation only communicates the committed result.