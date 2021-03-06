#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include "scenario.h"
#include "deal.h"
#include "cashflows.h"

class CashFlowEngine
{
public:
  CashFlows runCashFlows(const Deal &deal, const Scenario &scenario);
  CashFlows runCashFlows(const Loan &loan, const Scenario &scenario);
};

#endif