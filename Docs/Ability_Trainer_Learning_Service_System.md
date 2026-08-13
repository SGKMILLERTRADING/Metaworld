# Metaworld — Ability Trainer & Learning Service System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / economy-integrated / data-driven

## Canonical Principle

NPC trainers and other world services can teach abilities through the existing Ability knowledge system. Training is a service transaction with explicit requirements, cost policy and authoritative learning state; the widget never grants abilities by itself.

> A trainer offers knowledge. The Ability system records learning, and the Economy/Progression systems validate the service transaction.

Related canon:
- `Docs/Ability_Definition_Learning_Execution_Cooldown_System.md`
- `Docs/NPC_Dialogue_Service_Conversation_UI_System.md`
- `Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`
- `Docs/Gold_Material_Commodity_Not_Currency_Rule.md`
- `Docs/Crafting_Profession_Skill_Progression_System.md`

## 1. Trainer Service Identity

Suggested service/capability:
`NPC.Service.AbilityTraining`

A trainer/business/service profile can define:
- TrainerServiceID;
- offered AbilityDefinitionIDs;
- availability schedule;
- profession/faction/location restrictions;
- trainer qualifications;
- price/fee policy;
- progression/skill/attribute prerequisites;
- reputation/relationship requirements;
- quest/world-state prerequisites;
- legal/licensing requirements where relevant;
- service capacity/cooldown where designed.

## 2. Offer List

The Ability Trainer UI displays an authorized snapshot of currently available training offers.

Each offer can show:
- ability name/icon/description;
- already learned state;
- known prerequisites;
- service fee;
- unavailable reason where appropriate.

The UI does not contain the authoritative learned-ability map.

## 3. Currency Rule

Tutorial `Gold Cost` as money is rejected.

Training fees use canonical Metaworld payment systems:
- GrimKoin;
- PromoKoin only where that service explicitly accepts it.

Physical Gold may appear as a material/reagent requirement only if a specific magical/training ritual legitimately consumes physical Gold ItemInstances. It is not a generic wallet currency.

## 4. Level / Progression Requirements

A tutorial `Level Requirement` is one possible prerequisite, but Metaworld is not limited to one generic level gate.

Requirements may include:
- character progression threshold;
- profession/skill proficiency;
- prerequisite AbilityDefinitionID;
- attribute threshold;
- faction/reputation;
- license/certification;
- lineage/supernatural eligibility;
- quest/world event;
- trainer-specific trust.

Requirements are stable/data-driven.

## 5. Learning Transaction

`RequestPurchaseTraining(TrainerServiceID, AbilityDefinitionID, ExpectedOfferRevision)`
-> trainer/service still valid and available?
-> ability offered?
-> character eligible?
-> not already learned unless upgrade policy allows?
-> authoritative fee quote valid?
-> sufficient accepted currency/resources?
-> atomically commit payment/service transaction
-> grant/learn AbilityDefinitionID through `BPC_MW_Abilities`
-> persist revision
-> emit notification/UI events.

Do not charge the player if the learning commit fails; do not grant the ability if payment/requirements fail.

## 6. Learning vs Quickslot

Training grants knowledge only.

After learning, the player may optionally assign the ability to a Quickslot through the normal Quickslot UI. Trainer UI does not automatically create a shortcut unless an explicit convenience preference is designed.

## 7. NPC / World Integration

Trainer is a living NPC/service, so training availability can respond to:
- work shifts;
- death/incapacitation;
- imprisonment;
- business closure;
- faction hostility;
- travel/location;
- world events;
- supply/facility requirements where relevant.

The same Service routing architecture used by Trader/Crafting/Upgrade interactions can open the trainer interface.

## 8. Ability Upgrades / Ranks

Future advanced training may teach:
- new abilities;
- improved ranks/variants;
- passive abilities;
- specializations;
- profession techniques.

These should use explicit progression/definition relationships rather than silently overwriting one Ability row.

## 9. UI / Controller

Trainer UI must support KBM, Xbox-style and PlayStation-style focus/navigation/confirm/back. Notifications are presentation of the authoritative learning transaction.

Event-driven refresh occurs after:
- learned ability changes;
- currency changes;
- requirements change;
- trainer offer revision changes.

## 10. Multiplayer / Persistence

Server owns offer validation, payment and learning. Learned AbilityDefinitionIDs persist per character. Repeated purchase requests cannot charge twice or duplicate the same one-time ability grant.

## Acceptance Tests

1. Trainer UI cannot grant an ability without server transaction.
2. Already learned ability follows explicit duplicate/upgrade policy.
3. Insufficient GrimKoin/accepted payment rejects training without grant.
4. Tutorial Gold wallet is never used.
5. Physical Gold is only a material/reagent if a specific definition requires it.
6. Stale offer/price revision is safely revalidated.
7. Payment and ability grant commit atomically.
8. Quickslot assignment remains separate from learning.
9. Trainer unavailability/world state prevents invalid service use.
10. Save/reconnect preserves learned ability without duplicate payment.

## Core Rule

Metaworld ability trainers are world services that exchange legitimate requirements/payment for persistent Ability knowledge. Learning is authoritative and atomic; UI merely presents the trainer's current offers and transaction result.