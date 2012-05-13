#include <iostream>
#include <stdlib.h>
#include "clause.h"
#include "clause_impl.h"


using namespace std;
using namespace Sat;

//size_t ClauseImpl::clause_num = 0;

// Add a literal to the clause
void ClauseImpl::addLiteral(int lit){
	add_lits(lit);
}

// Get the largest variable in the clause
int ClauseImpl::maxVar() const{ 

	int max = -1;
	for (int i = 0; i < lits.size(); ++ i) {
		if(max < abs(lits[i]))
			max = abs(lits[i]);
	}
	return max;
}

// Get the number of variables in the clause
int ClauseImpl::numLits() const{
	return lits.size();
}

// Get the i^th literal in the clause
int ClauseImpl::getLit(int i) const{
	return lits.at(i)	;
}

  vector<int> ClauseImpl::get_lits() const {return lits;}

  void ClauseImpl::add_lits(int lit) {
	  lits.push_back(lit);
  }

  bool ClauseImpl::hasLit(int a) const {
	  for (int i = 0; i < lits.size(); ++ i) {
		  if (lits[i] == a) {
			return true;
		  }
	  }
	  return false;
  }

