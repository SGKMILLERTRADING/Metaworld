# Metaworld — Accessibility, Localization, Input & Presentation System

**Status:** Canonical Gap-Closure Architecture

## Purpose

Accessibility and localization must be designed into Metaworld's UI/input/content systems rather than added after hundreds of hardcoded widgets and strings exist.

## Input Accessibility

Metaworld already requires Enhanced Input and keyboard/mouse + Xbox-style + PlayStation-style support.

Extend this with:

- full remapping where practical;
- hold/toggle alternatives for sustained actions;
- adjustable sensitivity/dead zones;
- independent aim/look settings where useful;
- controller vibration/haptics controls;
- reduced repeated-input requirements;
- clear focus/navigation for all major UI.

## UI Accessibility

Support scalable presentation options such as:

- UI scale;
- readable text sizing;
- contrast options;
- color-independent status communication;
- configurable damage/interaction feedback intensity;
- subtitle/background styling;
- icon + text combinations for critical meaning;
- reduced motion/flash options where presentation permits.

Gameplay truth must never depend only on one color.

## Audio Accessibility

Important information should have alternatives where practical:

- subtitles/captions;
- speaker/channel labels;
- optional directional indicators for critical gameplay sounds;
- independent voice/music/effects volume;
- mono/communication controls where supported.

## Localization Rule

Player-facing text uses Unreal localization-ready `Text`/String Table style workflows rather than hardcoded display strings spread through Blueprints.

Stable gameplay IDs remain language-neutral.

Example:

`ItemDefinitionID = Item.Food.Apple`

Display Name is localized presentation data.

## Content That Must Localize

Plan localization support for:

- UI/menu text;
- item names/descriptions;
- abilities/conditions;
- professions/jobs;
- missions/objectives;
- notifications;
- subtitles/dialogue;
- legal/service messages;
- settings/accessibility descriptions.

## Layout Resilience

Widgets must tolerate translated text being longer/shorter than English. Avoid fixed-size layouts that break when strings expand.

## Number / Date / Time Presentation

Use localization-aware formatting for:

- dates;
- times;
- numbers;
- currency display;
- measurements where player settings support alternatives.

Gameplay calculations remain canonical internally; presentation converts/formats for the user.

## Accessibility Acceptance Gate

A major player-facing system is not complete until tested with:

- keyboard/mouse;
- Xbox-style controller;
- PlayStation-style controller;
- UI scaling;
- non-color-only critical feedback;
- subtitles where spoken information matters;
- at least one pseudo-localization/long-string pass.

## Core Principle

> Accessibility and localization are interface contracts, not cosmetic patches. Build them into the data/input/UI architecture early.