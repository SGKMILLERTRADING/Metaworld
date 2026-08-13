# Metaworld — Master Development Roadmap v3.1 — Corrections Overlay

**Status:** Canonical / Approved

**Preserves:** `Docs/Master_Development_Roadmap.md` v2.9 and the Phase 20 v3.0 overlay except where this document adds or clarifies corrections/custody gameplay.

**Detailed Companion:** `Docs/Jail_Prison_Corrections_Survival_System.md`

## Locked Corrections Direction

Metaworld distinguishes Jail and Prison as separate persistent gameplay states.

### Jail

- booking/temporary holding;
- pre-trial detention where applicable;
- short local sentences;
- generally shorter gameplay duration, commonly days where configured;
- court/transfer staging.

### Prison

- longer court sentences;
- generally weeks or longer where configured;
- deeper persistent inmate social/economic/survival gameplay;
- longer-term work, relationships, conflict, security and reputation.

## Corrections Is Playable World Gameplay

Custody never becomes a black-screen timer or magical safe zone.

While incarcerated, the character still participates in:

- Health/Hunger/Thirst/Fatigue;
- food and facility supply economy;
- injuries/medical treatment;
- inmate relationships/gangs/rivalries/friendships;
- jobs/work schedules;
- visits/outside contact when available;
- property/seized-item persistence;
- crime/evidence/court systems;
- guard/correctional-officer systems;
- reputation/history;
- permanent death;
- Smart News when incidents are publicly significant.

## No Safe-Zone Rule

Jail/prison does not create artificial immunity.

Danger can come from inmates, gangs, resource conflict, riots, emergencies, corruption, abusive staff, infrastructure failure and other world threats.

Correctional staff may commit misconduct, including unjustified violence, but those actions remain real Event Ledger/evidence/legal events and can produce discipline, investigation, criminal liability, reputation consequences and Smart News coverage when significant.

## Phase Integration

### Phase 32 — Crime

Crime continues inside custody. New offenses can create additional legal/disciplinary consequences.

### Phase 33 — Evidence

Correctional cameras, witnesses, reports, medical records, access logs and physical evidence participate in ordinary evidence rules. `SERVER TRUTH != IN-WORLD KNOWLEDGE` remains canonical.

### Phase 34 — Police, Courts & Corrections

Expand Phase 34 to include:

- booking;
- Jail custody;
- Prison sentencing/transfer;
- Correctional Officer duties;
- inmate custody state;
- sentence/court-order records;
- release/transfer handling;
- guard misconduct/corruption investigations;
- prison/jail incident handling.

### Phase 37 — Player Needs

Needs continue during custody. Inmates must eat, drink, sleep and receive/seek medical care through real facility/world systems.

### Phase 38 — Food Economy

Jails and prisons consume real food supply. Facility kitchens, deliveries, shortages and emergency rations connect corrections to the wider food economy.

### Phase 47 — Real-Time Calendar

Sentence timing and custody transitions use authoritative persistent calendar/state rules rather than requiring an Actor to remain loaded.

### Phase 52–54 — NPC Population

Inmates and guards use significance-aware simulation. Distant/unloaded facilities use scheduled/data simulation rather than full per-frame NPC processing.

### Phase 57 — World Event Director

Correctional events can include fights, riots, medical emergencies, fires, lockdowns, shortages, escapes later, corruption investigations and major security incidents.

### Phase 59–60 — Authority & Replication

The server owns custody, sentence, release, facility access, stored property and legal/disciplinary state. Replication exposes only relevant current state.

### Phase 61 — Smoothness

Large populated correctional facilities must be stress-tested for NPC, animation, networking, evidence-camera, food and incident load without violating frame-time budgets.

## Locked Principle

> Jail is short-term custody. Prison is longer-term correctional life. Both are living Metaworld environments, not waiting rooms. The same needs, danger, relationships, law, evidence, economy, death, persistence and performance rules continue inside the walls.