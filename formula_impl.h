#ifndef formula_impl_h
#define formula_impl_h

#include "formula.h"
#include "clause.h"
#include "clause_impl.h"
#include <fstream>
#include <list>
#include <vector>

using namespace std;

namespace Sat {

//class Clause;	


class FormulaImpl : public Formula {
	
public:
  // Constructor and Destructor
  FormulaImpl() {}
  FormulaImpl(const FormulaImpl &f):clauses(f.clauses) {}
  ~FormulaImpl() {}
  
  // Add a new Clause to the Formula
  // Return a reference to the new clause
  Clause& addClause();

  // Get the number of clauses
  int numClauses() const;

  // Get the i^th clause in the formula
  Clause& getClause(int i);

  bool hasLit(int a) const;

  vector<ClauseImpl>& getClauses() {return clauses;};

  void setClauses(vector<ClauseImpl> newClauses) {clauses = newClauses;};


  vector<ClauseImpl> clauses;

private:
//	map<int,ClauseImpl, hash, equal> clauses;
	

};
}

#endif
