(*--------------------------------------------------------------*)
(* ACM ICPC 2008-2009, NEERC                                    *)
(* Northern Subregional Contest                                 *)
(* St Petersburg, November 1, 2008                              *)
(*--------------------------------------------------------------*)
(* Problem C. Class                                             *)
(*                                                              *)
(* Original idea         Georgiy Korneev                        *)
(* Problem statement     Georgiy Korneev                        *)
(* Testset               Georgiy Korneev                        *)
(*--------------------------------------------------------------*)
(* Checker                                                      *)
(*                                                              *)
(* Author                gk                                     *)
(*--------------------------------------------------------------*)
 
{$apptype console}
{$q+,r+,o-}

uses
    testlib, SysUtils, Math;

const
    max_r = 100;
    

var
    n, r, c: longint;
    i, j: longint;
    answer: array [1..max_r] of string;
    row, col, full, desks: longint;
    fullJ, fullP: longint;
begin
    n := inf.readLongint();
    r := inf.readLongint();
    c := inf.readLongint();

    fullP := ouf.readLongint();
    for i := 1 to r do begin
        answer[i] := ouf.readWord(Blanks, Blanks);
        if (length(answer[i]) <> c) then begin
            quit(_wa, format('Incorrect row %d length: %d', [i, length(answer[i])]));
        end;
        for j := 1 to c do begin
            if (not (answer[i][j] in ['.', '#'])) then begin
                quit(_wa, format('Unexpected symbol (%d, %d): %s', [i, j, answer[i][j]]));
            end;
        end;
    end;

    desks := 0;
    for i := 1 to r do begin
        for j := 1 to c do begin
            if (answer[i][j] = '#') then begin
                inc(desks);
            end;
        end;
    end;

    if (desks <> n) then begin
        quit(_wa, format('Expected %d students, found %d', [n, desks]));
    end;

    row := 0;
    for i := 1 to r do begin
        desks := 0;
        for j := 1 to c do begin
            if (answer[i][j] = '#') then begin
                inc(desks);
            end;
        end;
        row := max(row, desks);
    end;

    col := 0;
    for j := 1 to c do begin
        desks := 0;
        for i := 1 to r do begin
            if (answer[i][j] = '#') then begin
                inc(desks);
            end;
        end;
        col := max(col, desks);
    end;

    full := min(row, col);

    if (full <> fullP) then begin
        quit(_wa, format('Promised fullness %d, actual %d', [fullP, full]));
    end;

    fullJ := ans.readLongint();

    if (fullP < fullJ) then begin
        quit(_wa, format('Fullness %d while maximal %d', [fullP, fullJ]));
    end;

    if (fullP > fullJ) then begin
        quit(_fail, format('Fullness %d while jury''s %d', [fullP, fullJ]));
    end;

    quit(_ok, format('Fullness %d', [fullJ]));
end.

