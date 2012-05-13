#ifndef solver_h
#define solver_h

#include <map>
#include "formula_impl.h"

using namespace std;

namespace Sat {

	class Solver {

	public:
		map<int,bool> assgn;
		bool solve(FormulaImpl &f);
		bool splitting (FormulaImpl &c);
		FormulaImpl& unitProp(FormulaImpl &f, int uni);
		FormulaImpl& pureLit(FormulaImpl &f, vector<int> p);
		int getUnitProp(vector<ClauseImpl>& c) const;
		vector<int> getPure (FormulaImpl &f);
	};
}

#endif