(*--------------------------------------------------------------*)
(* ACM ICPC 2008-2009, NEERC                                    *)
(* Northern Subregional Contest                                 *)
(* St Petersburg, November 1, 2008                              *)
(*--------------------------------------------------------------*)
(* Problem H. Holes                                             *)
(*                                                              *)
(* Original idea         Jury                                   *)
(* Problem statement     Dmitry Shtukenberg                     *)
(* Testset               Dmitry Shtukenberg                     *)
(*--------------------------------------------------------------*)
(* Solution                                                     *)
(*                                                              *)
(* Author                Dmitry Shtukenberg                     *)
(*--------------------------------------------------------------*)
 
{$apptype console}

function rep (n: integer; c: char): string;
var s: string; i: integer;
begin
  s := '';
  for i := 1 to n do s := s + c;
  rep := s;
end;

var n: integer;
begin
  assign (input, 'holes.in');
  reset (input);
  assign (output, 'holes.out');
  rewrite (output);

  readln (n);
  case n of
    0: writeln ('1');
    1: writeln ('0');
    else writeln (rep (n mod 2, '4') + rep (n div 2, '8'));
  end;
end.
