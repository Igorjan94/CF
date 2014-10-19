(*--------------------------------------------------------------*)
(* ACM ICPC 2008-2009, NEERC                                    *)
(* Northern Subregional Contest                                 *)
(* St Petersburg, November 1, 2008                              *)
(*--------------------------------------------------------------*)
(* Problem D. Deposits                                          *)
(*                                                              *)
(* Original idea         Roman Satukov                          *)
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
    i, l: longint;
begin
	l := 0;
	while not ans.seekeof do begin
        ja := ans.readword(blanks, blanks);
        if ouf.seekeof then
        	quit(_pe, 'not enough numbers');

        pa := ouf.readword(blanks, blanks);

        inc(l);

        if not (pa[1] in ['-', '0'..'9']) then
            quit(_pe, 'invalid character in answer');
        for i := 2 to length(pa) do
            if not (pa[i] in ['0'..'9']) then
                quit(_pe, 'invalid character in answer');

        if ja <> pa then
            quit(_wa, 'number ' + inttostr(l) + ' - expected: "' + ja + '", found: "' + pa + '"');
    end;

    if not ouf.seekeof then
    	quit(_pe, 'too many numbers');

    quit(_ok, '');
end.