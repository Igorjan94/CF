var ok, ok1, ok2, ok3, i : integer;
s : string;

begin
    readln(s);
    if length(s) >= 5 then
        ok := 1;
    ok1 := 0;
    ok2 := 0;
    ok3 := 0;
    for i := 1 to length(s) do
    begin
        if (s[i] >= 'a') and (s[i] <= 'z') then
            ok1 := 1;
        if (s[i] >= 'A') and (s[i] <= 'Z') then
            ok2 := 1;
        if (s[i] >= '0') and (s[i] <= '9') then
            ok3 := 1;
    end;
    if ok + ok1 + ok2 + ok3 = 4 then
        writeln('Correct')
    else
        writeln('Too weak');
end.
