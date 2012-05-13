#include "debug.h"
#include "clause.h"
#include "clause_impl.h"
#include "formula.h"
#include "formula_impl.h"


using namespace std;
using namespace Sat;


// Add a new Clause to the Formula
// Return a reference to the new clause
Clause& FormulaImpl::addClause() {

	ClauseImpl c;
	clauses.push_back(c);
	return clauses.back();
}

  // Get the number of clauses
  int FormulaImpl::numClauses() const {
	  return clauses.size();
  }

// Get the i^th clause in the formula
Clause& FormulaImpl::getClause(int i) {

	return clauses.at(i);

}

