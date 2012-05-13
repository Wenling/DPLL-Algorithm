(* Uncomment for access to examples and some useful functions
use "hole.sml";
use "primes.sml";
use "adder.sml";
use "lib.sml";
*)

fun getNextClause [] = ([],[])
  | getNextClause (0::lits) = ([], lits)
  | getNextClause (lit::lits) =
    let val (currentClause, rest) = getNextClause lits
    in
        (lit::currentClause, rest)
    end;

fun getClauses [] = []
  | getClauses lits =
    let val (currentClause, rest) = getNextClause lits
    in
        currentClause::(getClauses rest)
    end;

fun allassign 1 = [[false],[true]]
  | allassign n =
    let val a = allassign (n-1)
        fun consFalse l = (false::l)
        fun consTrue l = (true::l)
    in
        (map consFalse a) @ (map consTrue a)
    end;

fun evalVar _ [] = true
  | evalVar 1 (v::vs) = v
  | evalVar n (v::vs) = evalVar (n-1) vs;

fun evalLit n l =
  if (n > 0) then (evalVar n l)
  else not (evalVar (~n) l);

fun evalClause [] a = false
  | evalClause (lit::lits) a =
    if (evalLit lit a) then true
    else evalClause lits a;

fun evalForm [] a = true
  | evalForm (clause::clauses) a =
    if (evalClause clause a) then evalForm clauses a
    else false;

fun checkAssignments form [] = false
  | checkAssignments form (assn::assns) =
    if (evalForm form assn) then true
    else checkAssignments form assns;

fun maxvar [] = 0
  | maxvar (x::xs) =
    let val max = maxvar xs
        val absx = abs x
    in
        if absx > max then absx else max
    end;

fun sat data =
  let val max = maxvar data
  in
      checkAssignments (getClauses data) (allassign max)
  end;

sat [~1,~3,0,~1,~5,0,~3,~5,0,~2,~4,0,~2,~6,0,~4,~6,0,1,2,0,3,4,0,5,6,0];