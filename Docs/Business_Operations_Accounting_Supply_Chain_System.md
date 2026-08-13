# Metaworld — Business Operations, Accounting & Supply Chain System

**Status:** Canonical Gap-Closure Architecture

## Purpose

Metaworld already supports ownership, jobs, commerce and taxation. This document adds the missing business-operations layer so businesses can actually function over time through stock, workers, payroll, expenses, suppliers and services.

## Stable Business Identity

Use records such as:

- BusinessID;
- BusinessType/ProfileID;
- Owner/OrganizationID;
- Property/FacilityID;
- BusinessLedgerID;
- StockContainerIDs;
- EmployeeMembership/Job records;
- Supplier/Contract records;
- Schedule/OperatingHours profile.

## Business State

A business can track:

- open/closed status;
- cash/ledger balances;
- inventory/stock;
- employees and scheduled shifts;
- payroll obligations;
- rent/mortgage/property costs where applicable;
- utilities;
- taxes/fees;
- supplier orders;
- sales/service revenue;
- maintenance requirements;
- reputation/customer demand summaries.

## Stock Is Physical

Retail/production businesses use real ContainerID stock where items physically matter.

A shop cannot sell an item that its authoritative stock does not contain unless the business model explicitly sells a service/digital entitlement.

## Suppliers / Orders

Supplier transactions can create PurchaseOrderID / DeliveryID records.

Typical flow:

`Order -> reserve/pay according to contract -> logistics delivery -> receiving -> stock container`.

Supply failure, transport delay or scarcity can therefore affect businesses naturally.

## Employees / Payroll

Employees connect through Organization/Job records.

Payroll uses scheduled authoritative transactions rather than frame-based deductions.

A business without enough funds can incur unpaid wages/debt/consequences according to later economic policy rather than silently creating currency.

## Services

Service businesses can sell legitimate actions instead of physical stock, for example:

- repair/customization;
- medical/health care;
- training;
- transportation;
- lodging;
- entertainment;
- professional work.

Service completion uses an explicit transaction/job state.

## Operating Hours

Business operating hours use persistent calendar/time rules. NPC staffing and player-operated exceptions can modify availability.

The business record persists when the storefront is unloaded.

## Accounting

Maintain auditable categories rather than one unexplained balance change:

- sales revenue;
- service revenue;
- payroll;
- rent/property expense;
- utilities;
- taxes/fees;
- supplier purchases;
- maintenance;
- owner distributions/investment where allowed.

## Taxes

Tax calculation/collection integrates with city/government rules. Tax obligations are separate from ordinary business profit and should be reconstructable from authoritative records.

## Failure / Closure

Businesses can reduce hours, run out of stock, lose employees, accumulate obligations, close temporarily or permanently, transfer ownership or become part of an estate.

Closing the UI/storefront does not erase the persistent BusinessID.

## NPC / Player Ownership

The same core system supports NPC-owned, player-owned, household-owned and organization-owned businesses.

## Acceptance Gate

Prove one small shop can:

1. own a stock ContainerID;
2. receive a supplier delivery;
3. employ one NPC/Character;
4. open on schedule;
5. sell real stock through authoritative commerce;
6. record revenue;
7. process one expense/payroll event;
8. survive unload/restart;
9. show no stock after selling the final unit.

## Core Principle

> A business is a persistent economic actor with stock, workers, expenses, income and obligations — not just a vendor widget.