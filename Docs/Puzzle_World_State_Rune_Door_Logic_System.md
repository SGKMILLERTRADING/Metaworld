# Metaworld — Puzzle World-State, Rune Door & Reversible Logic System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / persistent / server-authoritative / data-driven / interaction-integrated

## Canonical Principle

A puzzle is persistent world logic connecting interactable inputs to authored rules and world outputs. The puzzle UI/VFX show the current state; the server/world-state system decides whether the solution is satisfied and what changes occur.

> Pillars, runes, blocks, levers and plates are inputs. Doors, lifts, traps and other world changes are outputs. The puzzle definition owns the rule connecting them.

---

# 1. Stable Puzzle Identity

Suggested IDs:

- `PuzzleInstanceID`
- `PuzzleDefinitionID`
- `PuzzleInputID`
- `PuzzleOutputID`

A puzzle instance can persist:

- input states;
- solved/unsolved state;
- one-shot/reversible policy;
- reset policy;
- completion timestamp;
- participating world-object IDs;
- revision.

Do not make the current Blueprint Actor transform values the only save truth.

---

# 2. Rune Pillar Puzzle Pattern

A rune door puzzle can define multiple input pillars.

Each pillar may have:

- stable input ID;
- current discrete rotation/state;
- allowed states;
- interaction action;
- visual rune/material profile;
- movement/rotation animation profile;
- lock/disable state.

The tutorial's A/B/C/D enum is acceptable for four prototype states, but Metaworld can represent the state through stable discrete values/tags/data rather than a closed global enum for every future puzzle.

---

# 3. Rotation Interaction

Suggested flow:

`Interact Rotate Pillar`
-> server validates puzzle/input/interactor
-> reserve/reject concurrent conflicting input
-> compute next legal state
-> commit input state
-> replicate state change
-> play local/replicated rotation/audio/VFX
-> evaluate puzzle rule.

The Timeline animates the committed rotation state; it does not decide the solution by itself.

---

# 4. Solution Definition

A puzzle definition may encode expected states, relationships or rules.

For a simple rune sequence:

- Pillar A = State 2
- Pillar B = State 0
- Pillar C = State 3
- Pillar D = State 1

But the framework can later support:

- ordered sequences;
- pressure/weight combinations;
- timed windows;
- logic gates;
- matching symbols/colors;
- environmental clues;
- multi-room puzzles;
- cooperative inputs;
- profession/knowledge-dependent puzzles;
- randomized authored solutions where persistent seed/state is stored.

---

# 5. Evaluation

Puzzle evaluation is event-driven when an input changes.

`Input State Changed`
-> evaluate only affected puzzle
-> compare/compute solution
-> transition `Solved/Unsolved` if state changed
-> notify outputs.

No permanent Tick is required simply to keep asking whether four runes match.

---

# 6. Outputs

Puzzle outputs can include:

- open/close door;
- unlock lock;
- lower/raise lift;
- enable/disable trap;
- reveal hidden compartment;
- activate light/sound/VFX;
- spawn/enable encounter only where authored;
- update quest/world-event state.

Outputs are addressed through stable interaction/world-object contracts rather than hardcoding `Cast to Door_BP` into every puzzle.

---

# 7. Door Movement

For a heavy rune/stone door:

- solution event requests/open state;
- door/world-object system validates current state;
- movement uses local/relative authored transforms, not hardcoded absolute world Z;
- Timeline/root animation can provide smooth heavy movement;
- collision/access state updates at explicit phases;
- audio/dust are presentation.

Relative/local transforms keep the puzzle reusable on different terrain/elevations.

---

# 8. Rune/Clue Presentation

Door runes may display:

- current pillar states;
- target clue states;
- partial progress;
- decorative language;
- difficulty/accessibility hints.

The presentation can use Decals, emissive material instances, meshes or UI where appropriate.

Do not expose the actual solution automatically unless the design intends the door display to be a clue.

---

# 9. Audio / VFX

Approved:

- pillar rotation sound;
- heavy door movement loop;
- impact/bang;
- dust/debris Niagara;
- rune emissive response;
- solved-state feedback.

Audio/VFX are triggered from puzzle/world state events and are not authoritative puzzle state.

---

# 10. Reversible vs One-Shot Puzzles

PuzzleDefinition declares behavior:

- OneShotPermanent;
- Reversible;
- ResetAfterTime;
- ResetOnWorldEvent;
- ResetOnInstance/mission policy;
- ManualReset.

Do not assume every solved puzzle permanently opens forever or every puzzle instantly resets.

---

# 11. Persistence

Save meaningful state, such as:

- current input states;
- solved state;
- persistent output state where required;
- random solution seed if used;
- reset timestamps.

Loading reconstructs the correct pillar/door presentation from saved state; it does not reroll the puzzle unless its definition explicitly says to.

---

# 12. Multiplayer / Concurrency

Server owns puzzle state.

Two players rotating the same pillar at nearly the same time cannot create divergent states.

Clients receive the committed new state and animate it.

A modified client cannot simply call `OpenDoor` without satisfying/authorizing the puzzle output.

---

# 13. Controller / Accessibility

Puzzle interaction supports:

- logical Interact/Rotate actions;
- KBM/Xbox-style/PlayStation-style controls;
- current-device prompts;
- non-color-only rune differentiation where required;
- optional clue/readability assistance depending on difficulty/accessibility design.

---

# 14. Performance

- no Tick for solved-state comparison;
- input actors update only on interaction/state change;
- dormant solved puzzle incurs minimal runtime work;
- Niagara/audio only active during relevant effects;
- distant/unloaded puzzle state persists as data.

---

# Acceptance Tests

1. Each rune pillar advances only through legal states.
2. Two simultaneous interactions cannot desync a pillar.
3. Puzzle evaluates only after relevant changes.
4. Correct combination transitions the puzzle to Solved exactly once per state transition.
5. Door uses relative/local movement and works at different elevations/rotations.
6. Save/load restores pillar states and door solution state.
7. VFX/audio can be disabled without breaking puzzle logic.
8. Reversible puzzle can close/deactivate output when its rule becomes false if configured.
9. One-shot puzzle remains solved if configured.
10. Controller users can operate every required input.

## Core Rule

> Metaworld puzzles are persistent event-driven world logic. Inputs change authoritative puzzle state, puzzle definitions evaluate the rule, and outputs react through reusable world-object contracts; animation, runes, audio and dust simply make that logic readable and satisfying.