# Metaworld — Player HUD Vitals & Resource Bars System

**Status:** Canonical / Approved Modern RPG Playlist Upgrade

**Engine:** Unreal Engine 5.8

**Runtime Direction:** Blueprint-first / event-driven / controller-neutral / performance-budgeted

## Canonical Principle

The player HUD presents authoritative character resources such as Health, Stamina and Mana clearly and responsively. It does not own, calculate or mutate the gameplay truth behind those resources.

> The HUD shows the character's condition. The Stats/Vitals systems decide the character's condition.

Related canon:

- `Docs/Stats_Attributes_Item_Modifiers_Encumbrance_System.md`
- `Docs/HUD_Notification_Feedback_System.md`
- `Docs/RPG_Interface_Shell_Widget_Data_Contracts_Navigation_System.md`
- `Docs/Performance_Smoothness_FrameTime_Architecture.md`

---

# 1. HUD Shell

Suggested local widget:

`W_MW_PlayerHUD`

The HUD may host or coordinate presentation modules such as:

- Health;
- Stamina;
- Mana;
- interaction prompt;
- notification feed;
- contextual combat/status indicators;
- future needs/vehicle/weapon/mission presentation where appropriate.

Do not turn one HUD Widget Blueprint into the authoritative home of gameplay resources.

---

# 2. Vitals Source

Health/Stamina/Mana values come from the authoritative character Stats/Vitals architecture.

Suggested presentation record:

`S_MW_ResourcePresentation`

Possible fields:

- `ResourceStatID`
- CurrentValue
- MaxValue
- normalized percent
- display name/icon
- semantic state (Normal/Low/Critical/Empty/etc.)
- visibility policy
- accessibility text
- revision

UI receives resource snapshots/change events and renders them locally.

---

# 3. Percentage Calculation

Progress bars may use:

`Percent = CurrentValue / MaxValue`

with safe rules:

- if MaxValue <= 0, use a defined zero/hidden/unavailable presentation rather than dividing by zero;
- clamp visual percentage to the valid progress-bar range;
- do not clamp the authoritative stat merely because the UI range is 0–1;
- Current/Max text may still show exact configured values.

The server owns gameplay Current/Max. The client may interpolate only visual presentation between received states where appropriate.

---

# 4. Health

Health presentation may include:

- Current/Max percentage;
- optional numeric text;
- low/critical state;
- damage/healing feedback hooks;
- incapacitated/downed/dead state where the relevant character system defines it.

Permanent-death rules remain external to the HUD.

A red-looking bar alone must not be the only indication of critical health; use icon/state/text/pulse/audio/haptic accessibility options where appropriate.

---

# 5. Stamina

Stamina is a current/max resource and may be presented persistently or contextually.

Possible visibility policies:

- always visible;
- visible while sprinting/climbing/swimming/combat exertion;
- visible while below full, then fade after recovery;
- user accessibility setting keeps it always visible.

Stamina UI listens to stamina-state changes; it does not calculate sprint drain itself.

Encumbrance/needs/injuries may influence Stamina through the authoritative systems and the HUD simply reflects the result.

---

# 6. Mana / Supernatural Resource

Mana is presented when the character/system actually uses that resource.

Possible policies:

- visible for characters with Mana capability;
- hidden/collapsed for characters with no active Mana system;
- replaced/extended by lineage-specific supernatural resources through the same data-driven HUD module contract where future design requires it.

Do not force every human character to display a meaningless empty magical bar merely because the prototype HUD has one.

---

# 7. Event-Driven Updates

Preferred flow:

`Authoritative resource changes`
-> replicated/local resource state updates
-> `OnResourceChanged(ResourceStatID, Current, Max)`
-> update affected HUD module

Also refresh on:

- local character possession/spawn;
- MaxValue modifier changes;
- respawn/new-character setup according to world rules;
- HUD recreation/resolution changes.

Do not bind every bar to functions that repeatedly fetch Player Blueprint stats every frame.

---

# 8. Visual Interpolation

Presentation may interpolate bars for readability (for example a delayed damage trail), but visual smoothing never changes the underlying resource.

Possible layers:

- immediate current bar;
- delayed damage/heal ghost bar;
- low-resource pulse;
- recovery animation.

Any interpolation is local presentation and should use bounded/efficient animation/timer behavior.

---

# 9. Styling

Custom Fill Image / Background Image materials/textures are approved presentation techniques.

Metaworld rules:

- use reusable style assets/material instances;
- do not hardcode style separately for every resource widget;
- ensure sufficient contrast at supported display scales;
- textures/gradients must not make value boundaries hard to read;
- Border Padding / layout adjustments are allowed to prevent clipping/pixel artifacts;
- style remains readable at different resolutions and UI scales.

---

# 10. Accessibility

Resource meaning must not depend on color alone.

Possible additional channels:

- unique resource icon;
- label;
- bar shape/pattern;
- optional numeric value;
- critical-state symbol;
- screen/audio/haptic cue where enabled.

Provide settings where feasible for:

- numeric values on/off;
- HUD scale;
- opacity;
- persistent vs contextual resource visibility;
- reduced flashing/pulsing;
- color-vision-friendly presentation.

---

# 11. Multiplayer / Privacy

The local HUD receives only resource state appropriate to its own character/view.

Do not replicate one player's private full resource/UI data to unrelated clients solely for HUD purposes.

Other players/NPCs may expose health/status indicators only through separate world/UI rules where legitimately visible.

---

# 12. Performance

- event-driven updates;
- no resource-widget Tick required for static values;
- bounded animation/timers only while an animation is active;
- no repeated GetPlayer/GetComponent lookup every frame;
- cache local owning-character/component references safely and refresh on possession changes;
- hidden contextual modules stop unnecessary animation/work;
- resource texture/material effects stay inside UI performance budget.

---

# 13. HUD Lifecycle

The HUD should be owned by the local player/controller/UI layer rather than spawned as gameplay authority inside the character.

Required behavior:

- initialize when the local gameplay UI becomes available;
- bind to the currently possessed Metaworld character;
- unbind cleanly when possession/character changes;
- rebuild presentation from current snapshot after UI reload;
- no duplicate HUDs after respawn/reconnect/menu transitions.

---

# 14. Acceptance Tests

1. Health bar matches authoritative Current/Max state.
2. Stamina bar updates when stamina changes without per-frame stat binding.
3. Mana hides/collapses correctly for characters without Mana capability when configured.
4. MaxValue 0 cannot cause divide-by-zero/UI corruption.
5. Equipment modifier changing Max Health updates percentage/text correctly without free healing.
6. HUD does not mutate Health/Stamina/Mana.
7. Reconnect/possession change binds to the correct character exactly once.
8. No duplicate PlayerHUD Widget is created after character changes.
9. Critical-resource meaning remains understandable without color alone.
10. HUD scale/resolution changes preserve readable layout.
11. Contextual Stamina visibility can hide/fade after recovery without losing actual state.
12. Visual interpolation does not change authoritative resource value.
13. Health/Mana/Stamina presentation remains smooth within frame-time budget.

## Core Rule

> Metaworld's HUD is a lightweight live instrument panel for the character. It responds to authoritative resource events, presents them clearly and accessibly, and never becomes the system that owns the player's life, stamina or supernatural energy.