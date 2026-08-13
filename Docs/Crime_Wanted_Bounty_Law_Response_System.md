# Metaworld — Crime, Wanted Status, Bounty & Law Response System

**Status:** Canonical / Approved UnrealDevz Multiplayer Shooter Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / evidence-aware / persistent

## Canonical Principle

Wanted status and bounties are consequences derived from committed crimes, evidence, warrants, jurisdiction and law-enforcement policy. A civilian death does not simply flip one permanent `Wanted=true` Boolean, and a player cannot erase legal consequences by clicking a generic Sheriff payment button unless a legitimate legal process explicitly permits settlement.

> Crime creates records. Evidence changes what authorities know. Warrants/bounties express legal response. Clearing them requires an authorized world process.

Related canon:
- `Docs/Security_Cameras_Evidence_Identity.md`
- `Docs/Smart_News_Event_Selection_System.md`
- `Docs/NPC_Combat_AI_Engagement_Death_System.md`
- `Docs/NPC_Interaction_Trader_Merchant_Commerce_System.md`
- `Docs/Jail_Prison_Corrections_Survival_System.md`

## 1. Crime Event Identity

Suggested records:
- `CrimeEventID`;
- jurisdiction;
- suspected/known CharacterID;
- victim/property reference;
- crime category/severity;
- timestamp/location;
- evidence references;
- witness/report state;
- investigation status;
- warrant/bounty references;
- adjudication/closure state.

Gameplay must distinguish server truth from what police/NPCs actually know.

## 2. Wanted State Is Derived

A character may be:
- unknown suspect;
- person of interest;
- identified suspect;
- wanted for questioning;
- arrest-warrant active;
- dangerous/high-priority wanted;
- cleared/acquitted/closed according to legal outcome.

Exact labels are jurisdiction/data policy, not one universal enum forever.

## 3. Evidence & Witnesses

Authorities may learn about crimes through:
- witnesses;
- cameras;
- physical evidence;
- reports;
- investigation;
- caught-in-act observation;
- other approved information channels.

A hidden crime with no discoverable evidence does not automatically give every NPC perfect knowledge.

## 4. NPC Response

NPC response is role/knowledge/context dependent.

Examples:
- civilians may flee, report, hide or avoid;
- guards/police may investigate, pursue, detain or arrest according to authority;
- vendors may refuse service when they know the customer is wanted;
- factions may react differently based on allegiance/reputation.

Do not globally make every AI hostile merely because one Wanted Boolean changed.

## 5. Bounties

A bounty is an explicit legal/faction contract or reward record, not an automatic synonym for Wanted.

Possible fields:
- `BountyID`;
- issuer/jurisdiction/faction;
- target CharacterID;
- authorized objective/outcome;
- reward;
- eligibility;
- start/expiry;
- evidence/verification requirements;
- status.

Public bounty information must follow what the issuer is legally/world-wise willing to publish.

## 6. Clearing / Resolving Wanted Status

Possible legitimate paths include:
- charges dropped;
- evidence disproves involvement;
- court outcome;
- fine/settlement for eligible offenses;
- sentence served;
- warrant satisfied;
- amnesty/pardon by authorized office;
- mistaken identity corrected;
- other jurisdiction-specific legal process.

A generic `Pay Sheriff -> erase all crimes` interaction is rejected as universal canon.

## 7. Arrest / Jail / Prison Integration

When applicable, arrest flows into the existing corrections architecture. Short-term jail and long-term prison remain distinct systems with persistent gameplay consequences.

## 8. Commerce / Services

A law NPC can expose services/information through the existing NPC Dialogue/Service architecture, for example:
- view known warrants;
- pay eligible fine;
- surrender;
- request information;
- begin legal/administrative process.

UI never directly clears authoritative crime records.

## 9. Persistence / Multiplayer

Crime, evidence, warrants and bounties persist across logout/server restart. Server owns legal records and state transitions. Clients receive only information their character/UI is authorized to know.

## 10. Performance

Law state changes are event-driven. Do not have every NPC globally scan every wanted character every frame. NPC knowledge/reaction updates through local perception, faction/law dispatch, significance and relevant world events.

## Acceptance Tests

1. A crime creates one persistent CrimeEventID.
2. Unknown crime does not magically inform every NPC.
3. Witness/camera evidence can update authority knowledge.
4. Wanted response varies by NPC role and knowledge.
5. Bounty and Wanted status remain distinct records.
6. Paying an ineligible fee cannot erase serious/active legal state.
7. Arrest can feed jail/prison correctly.
8. Logout/restart does not clear warrants.
9. UI cannot modify authoritative legal records.
10. Cleared/closed legal state retains history/audit linkage where appropriate.

## Core Rule

Metaworld law is evidence-aware persistent world state. Wanted status, warrants and bounties are consequences of legal knowledge and authorized processes—not a global hostility Boolean or a one-button reset.