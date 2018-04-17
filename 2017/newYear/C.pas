uses SysUtils;

var s: string;
var v: integer;
var r: integer;

begin
    readln(s);
    if Pos('.', s) = 0 then
    begin
        s := s + '.'
    end;
    if copy(s, 2, 1) = '.' then
    begin
        s := '0' + s
    end;
    s := s + '00';
    s := copy(s, 1, 5);
    s := StringReplace(s, '.', '', [rfReplaceAll]);
    v := StrToInt(s);
    if (v mod 100 <> 0) and (v mod 100 <> 50) then
    begin
        writeln(-1);
    end
    else
    begin
        v := (v * 2) div 100;
        writeln('0 0 ', v, ' 0 ', v, ' ', 1);
    end
end.
