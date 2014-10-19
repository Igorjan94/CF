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
(* Checker                                                      *)
(*                                                              *)
(* Author                ds                                     *)
(*--------------------------------------------------------------*)
 
uses
  testlib, SysUtils;

var
  ja, pa: string;

begin
  pa := ouf.readString;
  ja := ans.readString;

  pa := trim(pa);
  ja := trim(ja);

  if (ja <> pa) then begin
      quit(_wa, format('"%s" expected, "%s" found', [ja, pa]));
  end;
  quit(_ok, ja);
end.
