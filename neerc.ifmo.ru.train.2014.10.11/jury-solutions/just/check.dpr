(*--------------------------------------------------------------*)
(* ACM ICPC 2008-2009, NEERC                                    *)
(* Northern Subregional Contest                                 *)
(* St Petersburg, November 1, 2008                              *)
(*--------------------------------------------------------------*)
(* Problem J. Just Too Lucky                                    *)
(*                                                              *)
(* Original idea         Andrew Stankevich, Fedor Tsarev        *)
(* Problem statement     Andrew Stankevich                      *)
(* Testset               Andrew Stankevich                      *)
(*--------------------------------------------------------------*)
(* Checker                                                      *)
(*                                                              *)
(* Author                as                                     *)
(*--------------------------------------------------------------*)
 
uses
    testlib, SysUtils;
var
    ja, pa: string;
    i: longint;

function compress(s: string): string;
begin
    if length(s) < 100 then
        compress := s
    else
        compress := copy(s, 1, 50) + '..' + copy(s, length(s) - 24, 50);
end;

begin
    ja := ans.readword(blanks, blanks);
    pa := ouf.readword(blanks, blanks);

    if not (pa[1] in ['-', '0'..'9']) then
        quit(_pe, 'invalid character in answer');
    for i := 2 to length(pa) do
        if not (pa[i] in ['0'..'9']) then
            quit(_pe, 'invalid character in answer');

    if ja <> pa then
        quit(_wa, 'expected: "' + compress(ja) + '", found: "' + compress(pa) + '"');

    quit(_ok, compress(ja));
end.