use "lib.sml";
use "sat.sml";
use "hole.sml";
use "primes.sml";
use "adder.sml";

(* length l: get length of a clause *)
fun length [] = 0
  | length (x::xs) = 1 + length xs;

(* getUnitLit l: takes a single argument, a list of clauses, and returns 0 if there are no unit clauses. Otherwise, if there is at
least one unit clause, it returns a literal (non-zero integer) that appears in a unit clause. *)
fun getUnitLit [] = 0
  | getUnitLit (x::xs) = 
    if (length x = 1) then hd x else getUnitLit xs;

(* unitProp x l: takes two arguments: a literal and a list of clauses,
returns a new list of clauses resulting from doing unit propagation with the given literal. *)
fun unitProp x [] = []
  | unitProp x (y::ys) =
    if (mem x y) then unitProp x ys 
	else if (mem (~x) y) then ((del (~x) y)::unitProp x ys)
	else (y::unitProp x ys);

(* getPosNeg l: takes a list l of clauses and returns a pair of lists,
the first list in the pair should contain all the variables that appear positively in l and the second list in the pair should
contain all the variables that appear negatively in l. *)
fun getPosNeg2 (pos,neg,[]) = (pos,neg)
  | getPosNeg2 (pos,neg,x::xs) =
    if (x > 0) then getPosNeg2 ((x::pos), neg, xs) else getPosNeg2 (pos, (~x::neg), xs);
	
fun getPosNeg xs = getPosNeg2 ([],[],(setify (flatten xs)));

(* getPureLit l: returns 0 if it does not conatin any pure literals.
Otherwise, it returns a literal: either a variable that appears only positively in l or the
negation of a variable that appears only negatively in l. *)
fun getPureLit2 ([], ys) = 0
  | getPureLit2 (x::xs, ys) =
    if (mem x ys) then getPureLit2 (xs, ys)
    else x;

fun getPureLit xs = getPureLit2 (getPosNeg xs);

(* pureLitRule x l: a literal and a list of clauses;
returns a new list of clauses resulting from applying the pure literal rule with the given literal. *)
fun pureLitRule x [] = []
  | pureLitRule x (y::ys) = 
    if (mem x y) then pureLitRule x ys
    else (y::pureLitRule x ys);
	
(* hasBoth clause: check if the clause has the variable and its negation *)
fun hasBoth [] = false
  | hasBoth (x::xs) =
    if (mem (~x) xs) then true
	else hasBoth xs;

(* findResPair clause1 clause2: see if both clauses has the same prop., if so union them *)
fun findResPair [] ys = []
  | findResPair xs [] = xs
  | findResPair (p::xs) ys =
    if (mem (~p) ys) then union xs (del (~p) ys)
	else findResPair xs ys;

(* resRule2 y l: if it creates a clause that contains both a variable and its negation, filter the clause out *)
fun resRule2 y [] = [y]
  | resRule2 y ([]::xs) = [[]]
  | resRule2 y (x::xs) = 
  let val pair = findResPair y x
  in
    if (pair = []) then x::(resRule2 y xs)
    else if (hasBoth pair) then xs
    else resRule2 pair xs
  end;

fun resRule xs =
  resRule2 (hd xs) (tl xs);
  
fun dp2 [] = true
  | dp2 ([]::xs) = false
  | dp2 xs =
    let val uni = getUnitLit xs
	    val pure = getPureLit xs
	in
	  if (uni <> 0) then dp2 (unitProp uni xs)
      else if (pure <> 0) then dp2 (pureLitRule pure xs) 
	  else dp2 (resRule xs)
	end;
  
(* driver for dp *)
fun dp xs =
  dp2 (getClauses xs);

(* spltRule l: pick a variable to use for this rule from clauses 
Right now it just picks the first propagation in the first clause. *)
fun spltRule xs = hd (hd xs);

(* dpll2 st l: a function that checks the following cases:
1. If the set of clauses is empty, it returns true
2. Otherwise, if the set of clauses contains an empty clause, it returns false
3. Otherwise, if there is a unit clause, it applies unit propagation and then calls itself recursively
4. Otherwise, if there is a pure literal, it applies the pure literal rule and then calls itself recursively
5. Otherwise, it applies either the resolution rule or the splitting rule and calls itself recursively *)
fun dpll2 st [] = true
  | dpll2 st ([]::xs) = false
  | dpll2 st xs =
  let val uni = getUnitLit xs
      val pure = getPureLit xs
      val p = spltRule xs	  
  in
    if (uni <> 0) then (dpll2 (uni::st) (unitProp uni xs))
    else if (pure <> 0) then dpll2 (pure::st) (pureLitRule pure xs) 
	else if (dpll2 (p::st) (unitProp p xs)) then true 
	else (dpll2 ((~p)::st) (unitProp (~p) xs))
  end;

(* driver *)
fun dpll data =
  dpll2 [] (getClauses data);