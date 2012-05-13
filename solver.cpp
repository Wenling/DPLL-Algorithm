#include "solver.h"


using namespace std;
using namespace Sat;

bool Solver::solve(FormulaImpl &f) {
	//vector<int> p = findPure(f);
	//pureLit(f,p);
	//int uni = getUnitProp(f.getClauses());
	//unitProp(f, uni);
	//return true;
	return splitting (f);
}

/*
1. If the set of clauses is empty, it returns true
2. Otherwise, if the set of clauses contains an empty clause, it returns false
3. Otherwise, if there is a unit clause, it applies unit propagation and then calls itself recursively
4. Otherwise, if there is a pure literal, it applies the pure literal rule and then calls itself recursively
5. Otherwise, it applies either the resolution rule or the splitting rule and calls itself recursively
*/
bool Solver::splitting (FormulaImpl &f) {
	FormulaImpl c (f);
	pair<int, bool> temp;

	// condition 1
	if (c.getClauses().size() == 0)
		return true;
	// condition 2
	for (int i = 0; i < c.getClauses().size(); ++ i) {
		if (c.getClause(i).numLits() == 0)
			return false;
	}

	int uni = getUnitProp (c.getClauses());

	// condition 3
	if (uni != 0) {
		temp = make_pair(uni, true);
		assgn.insert(temp);
		return splitting (unitProp(c, uni));
	}
	// condition 4
	else {
		vector<int> p = getPure(c);
		if (p.size() != 0) {
			for(int i = 0; i < p.size(); ++ i) {
				temp = make_pair(p[i], true);
				assgn.insert(temp);
			}
			return splitting (pureLit(c, p));
		}
		// condition 5
		else {
			int firstLit = c.getClause(0).getLit(0);
			temp = make_pair(firstLit, true);
			assgn.insert (temp);
			if (splitting (unitProp(c, firstLit)) == true) 
				return true;
			else {
				assgn.erase(firstLit);
				temp = make_pair(firstLit, false);
				assgn.insert (temp);
				return splitting (unitProp(f, -firstLit));
			}
		}
	}
}

/*
a literal and a list of clauses;
returns a new list of clauses resulting from applying the pure literal rule with the given literal.
*/
FormulaImpl& Solver::unitProp(FormulaImpl &f, int uni) {
	
	vector<int> lits;
	while (uni != 0) {
		pair<int, bool> temp;
		temp = make_pair(uni, true);
		assgn.insert(temp);

		vector<ClauseImpl>::iterator it;
		
		for (it = f.clauses.begin(); it != f.clauses.end();) {	
			bool flag = false;
			vector<int>::iterator jt;

			for (jt = it->lits.begin(); jt != it->lits.end(); ) {

				if ((*jt) == -uni) {
					jt = it->lits.erase(jt);
					break;
				}
				else if ((*jt) == uni){
					flag = true;
					break;
				} else {
					++ jt;
				}
			}	
			if(flag == false)
				++ it;
			else {
				//it->clearLits();
				it = f.clauses.erase(it);
			}
		}

		uni = getUnitProp (f.getClauses());
	}
	//f.setClauses (f.clauses);
	return f;
}

int Solver::getUnitProp (vector<ClauseImpl>& c) const {
	for (int i = 0; i < c.size(); ++i) {
		if(c[i].get_lits().size() == 1)	 {
			return c[i].getLit(0);
		}
	}
	return 0;
}

/*
if it creates a clause that contains both a variable and its negation, filter the clause out
*/
FormulaImpl& Solver::pureLit(FormulaImpl &f, vector<int> p) {

	vector<ClauseImpl>::iterator it;
	for (int i = 0; i < p.size(); ++ i) {
		for (it = f.clauses.begin(); it != f.clauses.end();) {
			if (it->hasLit(p[i])) {
				pair<int, bool> temp;
				temp = make_pair(p[i], true);
				assgn.insert(temp);
				it = f.clauses.erase(it);
			} else {
				++ it;
			}
		}
	}
	return f;
}

vector<int> Solver::getPure (FormulaImpl &f) {
	map<int,int> litTable;
	vector<int> p;

	vector<ClauseImpl>::iterator it;
	for (it = f.clauses.begin(); it != f.clauses.end(); ++it) {
		vector<int>::iterator jt;
		for (jt = it->lits.begin(); jt != it->lits.end(); ++jt) {
			if (litTable.find(abs(*jt))==litTable.end()) {
				if (*jt < 0)
					litTable.insert(pair<int,int>(abs(*jt), -1));
				else
					litTable.insert(pair<int,int>(abs(*jt), 1));
			}
			else {
				if (litTable.find(abs(*jt))->second == -1 && *jt > 0) {
					litTable.erase(*jt);
					litTable.insert(pair<int,int>(abs(*jt), 0));
				} else if (litTable.find(abs(*jt))->second == 1 && *jt < 0) {
					litTable.erase(abs(*jt));
					litTable.insert(pair<int,int>(abs(*jt),0));
				}
			}
		}
	}
	map<int,int>::iterator kt;
	int lit;
	for(kt = litTable.begin(); kt != litTable.end(); ++kt) {
		if (kt->second != 0) {
			lit = (kt->first) * (kt->second);
			p.push_back(lit);
		}
	}
	return p;
}

