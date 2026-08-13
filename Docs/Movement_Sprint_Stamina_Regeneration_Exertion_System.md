# Metaworld — Movement, Sprint, Stamina, Regeneration & Exertion System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / server-authoritative gameplay state / event-driven / controller-complete

## Canonical Principle

Sprint is one movement state inside a broader exertion system. Stamina, encumbrance, injuries, needs, equipment and world conditions determine whether the character can sustain that state.

> Movement speed is derived from the character's current movement state and modifiers. Releasing Sprint never blindly restores one hardcoded default speed.

Related canon:

- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/Player_HUD_Vitals_Resources_System.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`
- `Docs/Controller_Input_Compatibility_Architecture.md`

---

# 1. Enhanced Input / Movement Intent

Recommended input intent:

- `IA_MW_Sprint`

Physical mappings can include keyboard, Xbox-style and PlayStation-style controls through Enhanced Input.

Gameplay listens to the Sprint action, not a hardcoded Shift key.

Sprint input expresses intent. The authoritative movement/stamina state decides whether Sprint can begin or continue.

---

# 2. Sprint Eligibility

Possible Sprint eligibility inputs:

- character is in a movement mode/state that supports sprinting;
- movement input/velocity intent is sufficient;
- Stamina is above the configured minimum;
- Encumbrance tier allows sprinting;
- injuries/status effects permit it;
- current action does not prohibit Sprint;
- weapon/equipment posture permits it where relevant;
- terrain/surface/world state permits it;
- jail/prison restraints or other legitimate world rules can restrict it;
- supernatural movement rules may override/extend eligibility only through their own capability state.

Do not reduce eligibility to only `Is Moving + Not Overweight + Stamina > 0` as permanent architecture.

---

# 3. Movement Profile

Suggested derived movement result can consider:

`Base Movement Profile`
+
`Sprint State`
+
`Encumbrance`
+
`Injury / Status Effects`
+
`Needs / Fatigue`
+
`Equipment`
+
`Surface / Environment`
+
`Profession / Supernatural effects where legitimate`
=
`Effective Movement Parameters`

Possible outputs:

- Walk Speed
- Run Speed
- Sprint Speed
- Acceleration
- Deceleration
- Rotation response
- Jump/Vault/Climb permission
- Stamina cost multipliers

When Sprint stops, recompute the effective non-sprint movement state. Do not simply set Max Walk Speed to one tutorial default value.

---

# 4. Stamina Drain

Sprint/exertion consumes authoritative Stamina according to data.

Possible drain inputs:

- movement state;
- current speed/intensity;
- carried load / Encumbrance;
- terrain/slope;
- injuries;
- Fatigue/Needs;
- temperature/weather;
- equipment;
- temporary status effects;
- supernatural modifiers.

A bounded timer/cadence may apply drain while an exertion state is active. Permanent character Tick is not required merely to subtract Stamina.

Suggested state flow:

`Sprint Accepted`
-> enter Exertion.Sprint
-> start bounded Stamina-consumption cadence
-> resource changes emit events
-> stop when input ends / eligibility fails / Stamina reaches threshold
-> recompute movement profile
-> schedule eligible regeneration delay

---

# 5. Stamina Exhaustion

At or below the configured exhaustion threshold:

- Sprint ends authoritatively;
- movement returns to the correct derived non-sprint state;
- HUD remains visible according to contextual policy;
- regeneration follows delay/blocker rules;
- further Sprint attempts fail until the configured recovery requirement is met.

Do not allow input spam to repeatedly start/stop Sprint and bypass exhaustion rules.

---

# 6. Resource Regeneration Policy

Health, Stamina, Mana and other resources may use reusable regeneration math, but each Resource Definition owns its actual policy.

Suggested conceptual policy:

- ResourceStatID
- RegenEnabled
- RegenRate
- RegenCadence
- RegenDelayAfterSpend/Damage
- StartThreshold / StopThreshold
- BlockerTags
- MultiplierSources
- Max clamp policy

Examples:

- Stamina can regenerate after exertion ends;
- Health may have no natural regeneration, slow natural recovery, medical-only recovery, or condition-driven regeneration depending on final design;
- Mana may have lineage/ability-specific regeneration rules.

Do not assume every stat automatically regenerates because the generic component supports it.

---

# 7. Regeneration Delay / Restart

When a resource-consuming/blocking event happens:

1. update resource authoritatively;
2. cancel/restart that resource's regeneration-delay state as required;
3. when the delay expires, revalidate all blockers;
4. start regeneration only if allowed;
5. stop when full or blocked again.

Retriggerable-delay intent is approved, but long-lived resource state should use explicit timer/timestamp state rather than brittle graph chains that become difficult to persist or cancel.

---

# 8. Clamp Rules

Resource CurrentValue is always clamped to its legal authoritative range.

For normal bounded resources:

`0 <= CurrentValue <= EffectiveMaxValue`

Health regeneration cannot push Current Health above Max Health.

Damage/status effects must remain able to reduce Health after regeneration.

UI percentage clamping remains presentation-only; gameplay clamping happens in the Stats/Vitals system.

---

# 9. Encumbrance Integration

Encumbrance is not a single Boolean.

Sprint eligibility and effective movement profile consume the canonical Encumbrance tier/state from the carried-load system.

Possible behavior:

- Comfortable: normal Sprint profile;
- Loaded: mild Stamina/mobility penalty;
- Encumbered: reduced/limited Sprint;
- Heavily Encumbered: Sprint unavailable;
- Unsafe/Immobile: normal locomotion may be severely restricted.

Final thresholds are data-driven/playtested.

If Sprint ends while Encumbered, movement returns to the Encumbered movement profile—not to normal default speed.

---

# 10. HUD Events

Event Dispatcher / event-driven communication between resource state and local HUD is approved.

Preferred flow:

`Authoritative Resource State Changes`
-> local/replicated `OnResourceChanged`
-> `W_MW_PlayerHUD`
-> update only affected resource module

Stamina HUD can become visible when:

- Sprint/exertion begins;
- Stamina falls below full;
- regeneration is active;
- critical/exhausted state occurs.

After full recovery plus configured inactivity delay, the bar may fade/collapse unless accessibility settings keep it visible.

---

# 11. Delayed / Trailing Health Bar

A secondary delayed health bar is approved as local presentation.

Flow:

`Health authoritative value changes`
-> primary bar snaps/updates immediately
-> trailing bar begins bounded interpolation after configured delay
-> trailing bar converges to authoritative health percentage

The trailing value:

- is not a second Health resource;
- is not replicated as gameplay state;
- cannot absorb damage;
- cannot heal the character;
- resets/rebases safely when Max Health changes.

Use bounded timer/animation behavior while convergence is active rather than permanent Widget Tick.

---

# 12. Encumbrance HUD

The Player HUD may display contextual carried-load status.

Possible presentation:

- icon + text such as `Encumbered`;
- carried mass / capacity detail on demand;
- severity tier;
- accessible symbol/label, not color alone.

HUD reads the authoritative/canonical carried-load presentation state. It does not calculate inventory mass independently.

---

# 13. Persistence / Multiplayer

Shared gameplay-relevant Stamina and movement eligibility are server-authoritative.

Persist only resource/state information that the character/persistence design requires. Short transient Sprint input itself does not need long-term persistence.

Reconnect/loading reconstructs Current/Max resource state and any persistent blocker/status timestamps according to their owning systems.

Clients may predict/smooth locomotion presentation, but they cannot authoritatively grant themselves unlimited Stamina or ignore Encumbrance restrictions.

---

# 14. Performance

- no permanent resource-regeneration Tick required;
- active drain/regen uses bounded timers/timestamps/events;
- only resources with enabled/nonzero regeneration schedule work;
- HUD updates on resource/state events;
- trailing-bar animation runs only while converging;
- hidden Stamina/encumbrance modules stop unnecessary animation work;
- recompute movement profile when relevant modifiers/state changes, not every frame without need.

---

# 15. Acceptance Tests

1. Sprint input uses Enhanced Input on KBM/Xbox-style/PlayStation-style controls.
2. Sprint begins only when current movement/resource/encumbrance rules allow it.
3. Sprint drains Stamina once at the configured cadence without duplicate timers.
4. Stamina reaching exhaustion stops Sprint.
5. Releasing Sprint while Encumbered restores the correct Encumbrance movement profile.
6. Stamina regeneration waits for its configured delay and blocker rules.
7. Re-triggering exertion restarts/blocks regeneration correctly.
8. Resource regeneration cannot exceed EffectiveMaxValue.
9. Health regeneration at max does not make later Burning/Damage ineffective.
10. HUD updates through resource events without per-frame stat binding.
11. Stamina bar fades after recovery according to visibility policy.
12. Accessibility option can keep Stamina visible.
13. Trailing health bar is presentation-only and converges correctly after Max Health changes.
14. Encumbrance icon/state matches the canonical carried-load tier.
15. Client cannot bypass Stamina/Encumbrance authority.

## Core Rule

> Sprint and regeneration are stateful resource interactions, not isolated speed/timer tricks. Metaworld derives movement from the whole character state, consumes Stamina authoritatively, regenerates resources only when their own policy allows it, and updates the HUD through events.