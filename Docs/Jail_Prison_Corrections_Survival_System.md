# Metaworld — Jail, Prison & Corrections Survival System

**Status:** Canonical / Approved Cross-System Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative / persistent

## Canonical Principle

Jail and prison are not the same institution and neither one is a gameplay pause.

> Jail is short-term custody and short sentencing. Prison is longer-term correctional custody. Both remain fully playable living environments where needs, danger, relationships, jobs, crime, evidence, reputation, injury, death and world events continue.

There is no magical safe zone simply because a character is incarcerated.

---

# 1. Jail vs Prison

## Jail

Jail primarily supports:

- arrest/booking and temporary holding;
- pre-trial detention where applicable;
- short local sentences;
- transfers between court, police and correctional systems;
- sentence lengths generally measured in the shorter gameplay range, commonly days when configured that way.

Jail should feel temporary but still playable.

## Prison

Prison supports:

- longer court-imposed sentences;
- sentence lengths commonly measured in weeks or longer gameplay periods where configured;
- persistent inmate social structure;
- longer-term work, survival, relationships, conflicts and reputation;
- higher-security custody where appropriate.

The exact sentence is decided by the authoritative court/sentencing system. Jail/prison duration is data-driven rather than one universal hardcoded number.

---

# 2. Custody Does Not Suspend Metaworld

While jailed or imprisoned, characters still have:

- Health;
- Hunger;
- Thirst;
- Fatigue/Sleep;
- injuries/medical needs;
- inventory/property state according to custody rules;
- social relationships;
- reputation;
- criminal/legal state;
- permanent death risk;
- world-event participation where relevant.

A sentence is not a black screen, timer lobby or safe waiting room.

---

# 3. Food & Survival

Correctional facilities must participate in the real food economy.

Possible food sources include:

- scheduled facility meals;
- prison/jail kitchen operations;
- commissary purchases where available;
- approved visitors/support sending allowed resources where world rules permit;
- inmate trade/social support;
- emergency rations during crises.

Not every inmate has family or friends outside.

The game must therefore support inmates who survive entirely through the correctional environment rather than assuming an outside family feeds them.

Food scarcity, theft, extortion, corruption, lockdowns, riots, infrastructure failures or other world events can create dangerous competition over food.

An inmate may be pressured, robbed, assaulted or even killed during conflict over scarce resources, but these are world events with consequences rather than invisible stat changes.

---

# 4. No Artificial Safe Zone

Canonical rule:

> Safety inside jail or prison comes from the same kinds of systems as safety outside: alliances, awareness, lawful staff, reputation, physical security, preparation, social standing and circumstance. Incarceration itself does not grant immunity.

Possible threats include:

- hostile inmates;
- gangs/factions;
- robbery/extortion;
- fights;
- assaults;
- riots;
- fires;
- disease/medical emergencies;
- utility failures;
- corrupt or abusive staff;
- outside criminal/faction influence;
- supernatural/world-event threats where the setting allows them.

Permanent death rules still apply.

---

# 5. Inmate Social Gameplay

Jail/prison can contain persistent social structures such as:

- friendships;
- enemies/rivals;
- gangs/factions;
- protection relationships;
- reputation/fear/respect;
- debts/favors;
- informal trade;
- shared meals/resources;
- work crews;
- religious/social groups where later supported;
- alliances formed for survival.

A player who enters prison alone can still build a life inside rather than being dependent on outside visitors.

NPC inmates use the same broad relationship/reputation rules as players where practical.

---

# 6. Visits & Outside Contact

Possible outside-contact systems include:

- spouse/family visits;
- friend visits;
- legal/lawyer visits;
- approved phone/communication access;
- letters/messages where supported;
- restricted business/property communication where legal rules allow.

No assumption is made that every inmate has visitors.

Visitor access obeys the authoritative correctional/security schedule and permissions rather than becoming unrestricted teleportation into the facility.

---

# 7. Prison/Jail Jobs & Daily Life

Custody gameplay can include legitimate work and activities such as:

- kitchen work;
- cleaning;
- laundry;
- maintenance;
- sanitation;
- warehouse/supply work;
- supervised repair/building work;
- medical orderly/support roles where qualified;
- library/education roles later;
- yard/exercise;
- scheduled meals;
- showers/hygiene;
- medical appointments;
- legal/court appointments.

Jobs and schedules should come from actual facility needs rather than arbitrary repetitive chores.

Work may affect money/commissary credit, reputation, privileges, skill/profession progress or sentence-related systems where later approved.

---

# 8. Guards / Correctional Officers

Correctional Officers can be player or NPC roles where supported.

Legitimate duties include:

- maintaining order;
- escorts/transfers;
- meal/security supervision;
- responding to fights/medical emergencies;
- searches under facility rules;
- protecting inmates/staff;
- lockdown/emergency response;
- evidence/report handling;
- supervising visits/work areas.

Guards are not automatically perfect.

Possible guard traits/events include:

- corruption;
- favoritism;
- intimidation;
- retaliation;
- panic/bad judgment;
- excessive force;
- unjustified assault;
- cooperation with inmate groups;
- neglect of duties.

A guard may attack or abuse an inmate without a legitimate reason as an emergent misconduct event.

However the world does not erase the consequences. Such incidents can create:

- injuries/death;
- camera/witness evidence;
- inmate testimony;
- complaints;
- internal investigation;
- police/court cases;
- corruption records;
- discipline/firing/imprisonment;
- retaliation;
- reputation effects;
- Smart News coverage when publicly significant.

This preserves a dangerous living world without making arbitrary guard violence consequence-free background scripting.

---

# 9. Crime Inside Custody

Existing crime rules continue inside jail/prison.

Possible offenses include:

- theft;
- assault;
- murder;
- extortion;
- property damage;
- bribery/corruption;
- prohibited trade/contraband possession where later designed;
- escape/escape assistance where later designed.

New crimes can create new charges, disciplinary state, security changes, additional sentencing or court proceedings according to authoritative rules.

Self-defense and disputed incidents require evidence/investigation rather than automatically treating every fight participant identically.

---

# 10. Evidence & Cameras

Correctional facilities can use:

- security cameras;
- guard reports;
- inmate witnesses;
- medical injury records;
- physical evidence;
- door/access logs;
- visitor logs;
- other lawful evidence sources.

Canonical evidence rule remains:

`SERVER TRUTH != IN-WORLD KNOWLEDGE`.

The backend can know who actually started a fight while guards/courts/news only know what available evidence reasonably establishes.

---

# 11. Smart News Selection

Routine correctional activity does not automatically become news.

Usually not news:

- normal meal service;
- one ordinary cell move;
- routine disciplinary action;
- a minor isolated argument with no wider impact.

Potentially newsworthy:

- major riot;
- mass casualty event;
- prison fire/major infrastructure failure;
- high-profile inmate death;
- large escape;
- major corruption scandal;
- systematic guard abuse exposed;
- major hostage/emergency event;
- facility closure/large transfer;
- significant public investigation.

Smart News uses public significance, verified facts and legal/investigative knowledge rather than broadcasting every Event Ledger entry.

---

# 12. Custody Property & Inventory

Arrest/incarceration can separate:

- carried personal property;
- evidence/seized property;
- stored inmate property;
- permitted custody items;
- commissary holdings;
- prohibited items.

Items do not simply disappear because the player enters jail.

Property disposition follows police/court/evidence/correctional rules and persistent Item IDs.

---

# 13. Release / Transfer State

Possible authoritative custody transitions include:

`Arrest -> Booking -> Jail/Holding`

`Jail -> Court -> Release / Short Jail Sentence / Prison Sentence`

`Jail -> Prison Transfer`

`Prison -> Release / Parole or Probation later if approved`

`Custody -> Hospital/Medical Transfer`

`Custody -> Court Appearance`

Release restores the character to the world under the current legal/property state; it does not reset reputation, injuries, debts, relationships or crimes committed during custody.

---

# 14. Persistence

Persist important custody state such as:

- Character ID;
- Custody Status;
- Facility ID;
- Housing/Cell/Unit assignment where needed;
- Sentence/Court Order ID;
- sentence timing/progress state;
- charges/discipline records;
- inmate reputation/relationships where important;
- stored/seized property references;
- health/injury state;
- job/work assignment;
- visitation/access state;
- transfer state;
- significant incident history.

Logging out does not erase custody state or move the character home.

Offline handling of sentence time must remain consistent with Metaworld's real-calendar/persistent-world policy and must not rely on the Actor staying loaded.

---

# 15. Multiplayer & Authority

Server owns:

- arrest/custody status;
- facility assignment;
- sentence/court state;
- doors/locks/security permissions;
- inmate/guard job authority;
- stored/seized property;
- disciplinary/legal outcomes;
- health/damage/death truth;
- transfer/release state.

Clients request actions; they do not set themselves free, alter their sentence, grant themselves visitor/door access, or change authoritative facility state.

---

# 16. NPC & Performance Rules

Nearby important inmates/guards can use full gameplay simulation.

Distant/unloaded correctional population uses:

- schedules;
- timestamps;
- relationship/reputation records;
- aggregate meal/resource consumption;
- event-driven incidents;
- job assignments;
- simplified health/security state.

Do not Tick every inmate's hunger, sentence clock, cell assignment and guard suspicion every frame.

Large correctional facilities must participate in World Partition/relevancy/significance and replication budgets.

---

# 17. Initial Vertical Slice Tests

1. Arrested player is booked into Jail without becoming a cutscene-only character.
2. Jail and Prison use distinct custody states/facilities.
3. Short jail sentence and longer prison sentence are distinguishable in authoritative court data.
4. Hunger/thirst/sleep/health continue in custody.
5. Facility meal actually satisfies hunger through the food system.
6. Inmate with no family/visitors can still survive through facility systems.
7. Inmate relationships/reputation persist.
8. A fight can occur and generate injuries/evidence/legal consequences.
9. Unjustified guard violence can occur as misconduct and create evidence/consequences.
10. Permanent death works inside jail/prison.
11. Stored/seized property survives save/load.
12. Court transfer and prison transfer preserve Character ID/state.
13. Release does not erase injuries/reputation/inside relationships/history.
14. Late joining/reconnect restores correct custody state.
15. NPC inmates/guards function without full per-frame simulation when distant.
16. Smart News ignores routine incidents but can report a major prison event.
17. Keyboard/mouse path works.
18. Xbox-style controller path works.
19. PlayStation-style controller path works.
20. Facility remains within CPU/network/frame-time budgets during populated stress testing.

---

# Core Rule

> Jail is short-term custody; prison is longer-term correctional life. Neither pauses Metaworld. Inmates still need food, sleep, health, relationships, work and protection; violence, corruption, death and world events can still happen; guards are fallible and can abuse power; and every significant action remains part of the same authoritative evidence, law, persistence, reputation and living-world systems used outside the walls.