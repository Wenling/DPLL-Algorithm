(* flip f: return a binary function with its operand order swapped *)
fun flip f x y = f y x;

(* upto n: generate a list from 1 up to n *)
fun upto 0 = []
  | upto n = (upto (n-1)) @ [n];

(* flatten l: turn a list of lists into a single list containing all the
   elements in the inner lists *)
fun flatten [] = []
  | flatten ([]::xs) = flatten xs
  | flatten ((x::xs)::ys) = x::(flatten (xs::ys));

(* mem x l: return true if x is in the list l *)
fun mem x [] = false
  | mem x (y::ys) = if (x = y) then true else (mem x ys);

(* del x l: return a list obtained by deleting all occurrences of x in l *)
fun del x [] = []
  | del x (y::ys) =
    let val ys' = del x ys
    in  if (x = y) then ys' else (y::ys')
    end;

(* setify l: remove all duplicates from list l *)
fun setify [] = []
  | setify (x::xs) =
    let val xs' = setify xs in
        if (mem x xs') then xs' else (x::xs')
    end;

(* union l1 l2: assuming two lists with no duplicates, merge them and remove
   duplicates (i.e. set union) *)
fun union [] l = l
  | union (x::xs) l =
    let val u = (union xs l) in
      if (mem x u) then u else (x::u)
    end;

(* intersect l1 l2: assuming two lists with no duplicates, return a list of all
   elements in both lists *)
fun intersect l [] = []
  | intersect l (x::xs) =
    let val i = (intersect l xs) in
      if (mem x l) then (x::i) else i
    end;

(* minus l1 l2: assuming two lists with no duplicates, return a list of all
   elements in l1 but not in l2 *)
fun minus l [] = l
  | minus l (x::xs) = del x (minus l xs);

(* filter pred l: return a list of those elements x of l for which pred x is true *)
fun filter pred [] = []
  | filter pred (x::xs) =
    let val xs' = filter pred xs in
      if (pred x) then (x::xs') else xs'
    end;