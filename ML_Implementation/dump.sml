fun dumpLit lit =
  if (lit > 0) then print (Int.toString lit)
  else (print "~"; print (Int.toString (~lit)));

fun dumpLits [] = ()
  | dumpLits [x] = dumpLit x
  | dumpLits (x::xs) = (dumpLit x; print ", "; dumpLits(xs));

fun dumpClause c =
  (print "["; dumpLits(c); print "]");

fun dumpClausesHelper [] = ()
  | dumpClausesHelper [c] = dumpClause c
  | dumpClausesHelper (c::cs) = (dumpClause c; print ", "; dumpClausesHelper(cs));

fun dumpClauses c =
  (print "[";dumpClausesHelper c; print "]\n");