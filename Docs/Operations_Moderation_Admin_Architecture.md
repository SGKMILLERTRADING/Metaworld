# Metaworld — Operations, Moderation & Administration Architecture

**Status:** Canonical Gap-Closure Architecture

## Purpose

A persistent multiplayer world needs administration, moderation, auditability, recovery and account support that remain separate from in-world playable ranks.

## Admin vs In-World Authority

Platform administration is operational authority outside normal roleplay.

It is not a playable civic, professional, business or faction rank.

Administrative actions are logged and exist for platform maintenance, moderation and recovery.

## Authoritative-State Principle

Persistent gameplay changes follow normal server/service rules. Platform tools inspect or modify durable state only through controlled operational workflows.

## Audit Records

Important operational actions create durable records containing, as appropriate:

- AuditEventID;
- acting operator/service reference;
- action type;
- target stable IDs;
- revision reference;
- timestamp;
- reason/source;
- linked support/report case.

## Moderation Capabilities

Platform moderation may include:

- communication mute/restriction;
- account suspension;
- report review;
- content removal/quarantine;
- creator-marketplace moderation;
- name/profile moderation;
- appeal/review workflow.

In-world legal consequences remain separate from platform rules enforcement.

## Report Cases

A player report can create a persistent case with:

- ReportID;
- reporter;
- reported account/content/event reference;
- category;
- timestamp;
- relevant system-record references;
- review state;
- outcome.

Reports follow review/rule policy rather than automatically changing another player's state.

## Recovery / Support

Support tools need controlled ways to inspect and recover durable state after verified technical failures.

Recovery should use authoritative history/snapshots rather than relying only on a player's claimed inventory or balance.

## Backups / Restore

Production readiness requires:

- scheduled backups;
- tested restoration;
- migration rollback planning;
- durable history for critical systems;
- consistency monitoring.

A backup is not considered proven until a test restoration succeeds.

## Creator / Media Operations

Player-created media or marketplace content needs:

- ownership/provenance metadata;
- publishing status;
- review/moderation state;
- quarantine/removal state;
- entitlement policy for existing buyers where applicable.

## Privacy Boundaries

Expose only account/player information needed for a legitimate gameplay, support or moderation purpose. Public Character identity and private account/platform identity remain separate concepts.

## Acceptance Gate

Prove:

- admin role is separate from playable Character rank;
- operational action creates an audit record;
- communication restriction works without changing world ownership;
- report case can be created/reviewed;
- backup restoration recreates a known test state;
- technical recovery uses durable records and revisions.

## Core Principle

> Metaworld's living-world rules govern characters; operational systems govern the service. The two remain distinct and auditable.