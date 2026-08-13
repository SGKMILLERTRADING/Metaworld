# Metaworld — Organization, Faction, Membership & Authority System

**Status:** Canonical Gap-Closure Architecture

## Purpose

Metaworld needs one reusable framework for organized groups instead of separate membership systems for every business, gang, government body, community group, faction or player-created organization.

## Stable Identity

Use stable records such as:

- OrganizationID;
- OrganizationDefinition/Profile;
- MembershipID;
- RoleID;
- PermissionSetID;
- Treasury/LedgerID;
- OrganizationProperty links;
- OrganizationReputation links.

## Organization Types

The same base framework may represent:

- businesses;
- civic/government bodies;
- clubs/community groups;
- factions;
- gangs;
- unions/guilds;
- teams;
- security/service organizations;
- supernatural organizations.

Type-specific rules extend the shared membership/authority model.

## Membership

A membership record can define:

- CharacterID;
- OrganizationID;
- role/rank;
- joined timestamp;
- status;
- permissions;
- reputation/trust;
- employment/pay relationship where applicable.

Character death does not silently transfer membership to the next CharacterID.

## Roles / Permissions

Roles are data-driven rather than hardcoded into character Blueprints.

Permissions can control actions such as:

- invite/remove members;
- manage property/access;
- manage organization inventory;
- authorize spending;
- create jobs/contracts;
- manage ranks;
- publish announcements;
- operate organization facilities.

Server authority validates permission at the moment of the action.

## Treasury / Assets

Organization money and property are separate from one member's personal wallet/property.

The organization can own:

- currency accounts;
- buildings/property;
- vehicles;
- storage/warehouses;
- businesses/facilities;
- equipment/resources.

Transactions use ordinary authoritative ledger/item systems.

## Reputation / Diplomacy

Track independently:

- character-to-organization reputation;
- organization-to-organization relationship;
- public/community reputation;
- formal alliance/rivalry/neutral state where configured.

Lineage does not automatically decide faction loyalty.

## Governance

Organizations may use different leadership rules:

- owner/founder where appropriate;
- elected leadership;
- appointed hierarchy;
- seniority/service progression;
- council voting;
- inherited/succession rules where appropriate.

Public/government rank still follows the separate canonical eligibility/community rules and cannot simply be purchased.

## Jobs / Duties

Roles can generate duties from actual organization/world needs rather than arbitrary chores.

Examples:

- staffing a business;
- maintaining supplies;
- transport/delivery;
- facility operation;
- public service;
- scheduled meetings/events.

## Persistence / Unloaded Simulation

Organizations persist as records even when no member Actor is loaded. Payroll, dues, scheduled events and business operations use timestamps/jobs rather than requiring members to remain spawned.

## Acceptance Gate

Prove:

- create organization;
- invite/join member;
- assign role;
- role permission gates one persistent action;
- organization owns a ContainerID/property/ledger;
- member leaves without losing organization assets;
- Character permanent death removes that Character membership correctly;
- restart reconstructs membership and ownership.

## Core Principle

> An organization is persistent shared identity, membership, authority and assets — not a tag on one player's Blueprint.