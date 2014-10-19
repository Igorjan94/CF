(*--------------------------------------------------------------*)
(* ACM ICPC 2008-2009, NEERC                                    *)
(* Northern Subregional Contest                                 *)
(* St Petersburg, November 1, 2008                              *)
(*--------------------------------------------------------------*)
(* Problem I. Important Wires                                   *)
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
    testlib, SysUtils;

const
    max_ops = 100000;
    max_vars = 11;
    max_funcs = 10;
    max_length = 1000;

var
    formula: string;
    pos: longint;
    token: char;
    outcome: tResult;
    op: array [1..3 * max_ops] of char;
    op1, op2: array [1..3 * max_ops] of longint;
    values: array [1..3 * max_ops] of boolean;
    ops: longint;
    vars: array [1..max_vars] of char;
    varValues: array [1..max_vars] of boolean;
    funcs: array [1..max_funcs] of char;
    funcValues: array [1..max_funcs] of boolean;
    ufunc: array [1..max_funcs] of boolean;
    cvars, cfuncs: longint;
    ch: char;


function add(_op: char; _op1, _op2: longint): longint;
begin
    inc(ops);
    op[ops] := _op;
    op1[ops] := _op1;
    op2[ops] := _op2;
    add := ops;
end;

function addVariable(v: char): longint;
var
    i: longint;
begin
    if (outcome <> _fail) then begin
        quit(outcome, format('Variable "%s" used at', [v, pos - 1]));
    end;
    if (not (v in ['a'..'k'])) then begin
        quit(_fail, format('Invalid variable "%s"', [v])); 
    end;
    for i := 1 to cvars do begin
        if (vars[i] = v) then begin
            addVariable := i;
            exit;
        end;
    end;
    inc(cvars);
    vars[cvars] := v;
    addVariable := cvars;
end;

function addFunc(f: char): longint;
var
    i: longint;
begin
    if (outcome = _fail) and (not (f in ['A'..'Z'])) then begin
        quit(_fail, format('Invalid function "%s"', [f])); 
    end;
    for i := 1 to cfuncs do begin
        if (funcs[i] = f) then begin
            if (outcome = _fail) then begin
                quit(outcome, format('Function "%s" defined twice', [f]));
            end;
            ufunc[i] := true;
            addFunc := i;
            exit;
        end;
    end;
    if (outcome <> _fail) then begin
        quit(outcome, format('Unknown function "%s" at %d', [f, pos - 1]));
    end;
    inc(cfuncs);
    if (cfuncs > max_funcs) then begin
    	quit(_fail, 'Too many functions');
    end;
    funcs[cfuncs] := f;
    addFunc := cfuncs;
end;

procedure expectChar(t: char);
begin
    if (ch <> t) then begin
        quit(outcome, format('Character "%s" expected, "%s" found at %d', [t, token, pos]));
    end;
    inc(pos);
    ch := formula[pos];
end;

procedure nextToken();
begin
    while (ch = ' ') do begin
        expectChar(' ');
    end;
    if (ch in ['a'..'z', 'A'..'z', '~', '&', '|', '(', ')', '!']) then begin
        token := ch;
        expectChar(token);
    end else if (ch = ':') then begin
        token := ':';
        expectChar(':');
        expectChar('=');
    end else if (ch = '<') then begin
        token := '=';
        expectChar('<');
        expectChar('=');
        expectChar('>');
    end else if (ch = '=') then begin
        token := '>';
        expectChar('=');
        expectChar('>');
    end else begin
        quit(outcome, format('Unexpected character "%s" at %d', [ch, pos])); 
    end;
end;

function test(t: char): boolean;
begin
    result := token = t;
    if (result) then begin
        nextToken();
    end;
end;

procedure expect(t: char);
begin
    if (not test(t)) then begin
        quit(outcome, format('Token "%s" expected, "%s" found at %d', [t, token, pos - 1]));
    end;
end;

function parseEquivalence(): longint; forward;

function parseTerm(): longint;
begin
    if (test('~')) then begin
        result := add('~', parseTerm(), 0);
    end else if (test('(')) then begin
        result := parseEquivalence();
        expect(')');
    end else if token in ['a'..'z'] then begin
        result := add('v', addVariable(token), 0);
        expect(token);
    end else if token in ['A'..'Z'] then begin
        result := add('f', addFunc(token), 0);
        expect(token);
    end else begin
        result := 0;
        quit(outcome, format('Term expected, "%s" found at %d', [token, pos - 1]));
    end;
end;

function parseAnd(): longint;
begin
    result := parseTerm();
    while (test('&')) do begin
        result := add('&', result, parseTerm());
    end;
end;

function parseOr(): longint;
begin
    result := parseAnd();
    while (test('|')) do begin
        result := add('|', result, parseAnd());
    end;
end;

function parseImplication(): longint;
begin
    result := parseOr();
    if (test('>')) then begin
        result := add('>', result, parseImplication());
    end;
end;

function parseEquivalence(): longint;
var
	first: longint;
begin
    result := parseImplication();
    while (test('=')) do begin
    	first := result;
    	result := add('=', first, parseImplication());
        while (test('=')) do begin
            result := add('&', result, add('=', first, parseImplication()));
        end;
    end;
end;

procedure initParser(s: string);
begin
    if (length(s) > max_length) then begin
        quit(outcome, format('Line too long: %d', [length(s)]));
    end;
    pos := 1;
    formula := s + '!!!';
    ch := formula[pos];
    nextToken();
end;

procedure parseFormula(); overload;
var
    name: char;
    value: longint;
begin
    name := token;
    expect(name);
    expect(':');
    value := parseEquivalence();
    add(':', addFunc(name), value);
end;

procedure parseFormula(line: string); overload;
begin
    initParser(line);
    parseFormula();
    expect('!');
end;

function parse(line: string): longint;
begin
    initParser(line);
    result := parseEquivalence();
    expect('!');
end;

var
    ja, pa: string;
    i, j: longint;
    iroot: longint;
    s: string;
    n: longint;
begin
    ja := ans.readString();
    pa := ouf.readString();

    if (pa <> 'Yes') and (pa <> 'No') then begin
        quit(_wa, format('"Yes" or "No" expected, "%s" found', [pa]));
    end;
    if (pa = 'No') then begin
        quit(_wa, 'Answer exists, but not found');
    end;

    outcome := _fail;

    n := inf.readLongint();
    inf.readString();

    for i := 1 to n do begin
        parseFormula(inf.readString());
    end;

    fillchar(ufunc, sizeof(ufunc), 0);

    outcome := _wa;
    iroot := parse(ouf.readString());

    for i := 1 to cfuncs do begin
        if (not ufunc[i]) then begin
            quit(_wa, format('Function "%s" not used', [funcs[i]]));
        end;
    end;

    for i := 0 to (1 shl cvars) - 1 do begin
        for j := 1 to cvars do begin
            varValues[j] := ((i shr (j - 1)) and 1) = 1;
        end;
        for j := 1 to ops do begin
            case op[j] of
                ':': funcValues[op1[j]] := values[op2[j]];
                '=': values[j] := values[op1[j]] = values[op2[j]];
                '>': values[j] := not values[op1[j]] or values[op2[j]];
                '|': values[j] := values[op1[j]] or values[op2[j]];
                '&': values[j] := values[op1[j]] and values[op2[j]];
                '~': values[j] := not values[op1[j]];
                'v': values[j] := varValues[op1[j]];
                'f': values[j] := funcValues[op1[j]];
                else quit(_fail, 'Unknown op ' + op[j]);
            end;
        end;

        if not values[iroot] then begin
            s := '';
            for j := 1 to cvars do begin                              
                s := s + vars[j] + '=' + intToStr(ord(varValues[j])) + ' ';
            end;
            for j := 1 to cfuncs do begin                              
                s := s + funcs[j] + '=' + intToStr(ord(funcValues[j])) + ' ';
            end;
            quit(_wa, format('Not tautology: %s', [s]));
        end;
    end;

    quit(_ok, 'Yes');
end.

