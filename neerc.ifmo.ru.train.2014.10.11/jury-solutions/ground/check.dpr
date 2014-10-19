(*--------------------------------------------------------------*)
(* ACM ICPC 2008-2009, NEERC                                    *)
(* Northern Subregional Contest                                 *)
(* St Petersburg, November 1, 2008                              *)
(*--------------------------------------------------------------*)
(* Problem G. Ground Works                                      *)
(*                                                              *)
(* Original idea         Iskander Akishev                       *)
(* Problem statement     Pavel Mavrin                           *)
(* Testset               Pavel Mavrin                           *)
(*--------------------------------------------------------------*)
(* Checker                                                      *)
(*                                                              *)
(* Author                pm                                     *)
(*--------------------------------------------------------------*)
 
{$apptype console}
{$q+,r+,o-}

uses
    testlib, SysUtils, Math;

const
    eps = 1.1e-7;

var
    ja, pa: double;
begin
    pa := ouf.readReal();
    ja := ans.readReal();

    if (abs(ja - pa) / ja > eps) then begin
       quit(_wa, format('%0.9f expected, %0.9f found', [ja, pa]));
    end;

    quit(_ok, format('%0.9f', [pa]));
end.
