# Metaworld — Ability Targeting, Channel, Cancel & Commit System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade
**Engine:** Unreal Engine 5.8
**Runtime:** Blueprint-first / server-authoritative / phase-driven / controller-complete

## Canonical Principle

Abilities that require aiming, placement, charging or extended execution use explicit phases. UI and world indicators help the player choose an intent; one authoritative execution record owns validation, commitment, cancellation and completion.

## 1. Ability Phases

Suggested phases:
- Requested;
- Targeting / Preparing;
- Validated Ready;
- Committed;
- Executing;
- Recovering;
- Completed;
- Canceled / Interrupted.

Not every ability uses every phase.

## 2. Targeting Presentation

A targeting ability may show a local ground circle, projected decal, mesh, reticle or other indicator.

The server validates the selected context using definition rules such as range, line of sight where required, legal surface/volume, relationship/type, character state and equipment requirements.

The indicator is presentation only.

## 3. Commit Timing

Each AbilityDefinition declares when canonical resource cost and cooldown are committed.

Examples:
- instant action: commit on accepted activation;
- targeted action: target first, commit on successful confirm;
- channeled action: initial and/or periodic cost according to profile;
- repeated execution: reserve/consume required resources according to explicit policy.

A canceled pre-commit targeting phase normally clears transient state without applying the final cooldown/cost, unless the definition intentionally charges an activation fee.

## 4. Cancellation

Before commitment, cancel can remove targeting presentation, release temporary reservations and restore the correct camera/movement/action profile.

After commitment, interruption follows the AbilityDefinition's refund/cooldown policy and cannot undo already-committed results.

## 5. Multi-Step Abilities

Rapid Fire, Evade and Rain of Arrows are examples of multi-step AbilityDefinitions rather than separate Ability systems.

They use the same:
- learned-ability state;
- AbilityExecutionID;
- cost/cooldown validation;
- Character Action coordinator;
- movement resolver;
- item/equipment requirements;
- result/status systems;
- controller input architecture.

## 6. Evade

Evade is a bounded CharacterAction movement request. An implementation may use Launch Character, root motion or another validated movement profile, but the action and movement resolver remain authoritative.

Ordinary multiplayer Evade does not apply global world time dilation. Dramatic presentation should be local/participant-focused.

## 7. Area Targeting

An area ability such as Rain of Arrows stores a validated target-area context in its active execution. Visual effects and spawned presentation represent that execution; authoritative gameplay queries/results are produced by the owning gameplay systems.

The visual effect does not become the gameplay authority.

## 8. Interruption

Stun, death, knockdown or another blocking state can interrupt the exact active AbilityExecutionID according to definition.

Do not clear unrelated Conditions, traversal state, equipment state or Gameplay Tags just to stop one ability.

## 9. Tooltip / UI

Ability tooltip presentation may include:
- icon/name/description;
- known cost;
- cooldown;
- equipment/handling requirements;
- targeting/range summary;
- unavailable reason where appropriate.

Mouse hover and controller focus expose equivalent information.

## 10. Performance

- targeting work exists only while targeting;
- inactive abilities run no permanent trace/timer loop;
- visual indicators stop immediately on commit/cancel;
- cooldowns use canonical timestamp state;
- UI reads snapshots/events rather than owning execution state.

## Acceptance Tests

1. Canceling before commit removes targeting state cleanly.
2. Successful confirm commits cost/cooldown exactly once according to definition.
3. Stun interrupts the exact active ability without wiping unrelated state.
4. Target UI cannot authorize invalid range/surface/context.
5. Closing/removing presentation cannot cancel an already-committed result unless policy says so.
6. Controller confirm/cancel matches keyboard/mouse behavior.
7. Reconnect cannot duplicate a committed execution.
8. No inactive ability needs permanent targeting work.

## Core Rule

Metaworld targeted abilities are explicit phased transactions. The player can preview and cancel before commitment; once validated and committed, one AbilityExecutionID owns the authoritative execution while UI and effects merely present it.