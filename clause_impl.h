#ifndef clause_impl_h
#define clause_impl_h

#include "clause.h"
#include <fstream>
#include <vector>
using namespace std;

namespace Sat {

class ClauseImpl : public Clause {

public:
  // Constructor and Destructor
  ClauseImpl() {}
	ClauseImpl(const ClauseImpl &c):lits(c.lits) {
	  //++clause_num;
  }
  ~ClauseImpl() {
	  //--clause_num;
  }


  // Add a literal to the clause
  void addLiteral(int lit);

  // Get the largest variable in the clause
  int maxVar() const;

  // Get the number of variables in the clause
  int numLits() const;

  // Get the i^th literal in the clause
  int getLit(int i) const;

  //static size_t numOfClauses(){return clause_num;}

  vector<int> get_lits() const;

  void add_lits(int lit);

  vector<int> lits;

  bool hasLit (int i) const;
  
  
private:
	//static size_t clause_num;
  // Data structure for saving one clause
	

};

}

#endif
