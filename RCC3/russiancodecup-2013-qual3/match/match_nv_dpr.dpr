program solve;

{$APPTYPE CONSOLE}

uses
  SysUtils;

const MAXN = 10000007;

var a: array[0..MAXN] of longint;
    n, i, t, j: longint;
    ans: int64;
function search (l, r, k: longint): longint;
var
  i, j, key, buf: longint;
begin
  key := a[l + random(r - l + 1)];
  i := l;
  j := r;
  repeat
    while a[i] < key do
      inc(i) ;
    while key < a[j] do
      dec(j) ;
    if i <= j then begin
      buf := a[i];
      a[i] := a[j];
      a[j] := buf;
      inc(i);
      dec(j);
    end;
  until i > j ;
  if ((j - l + 1) <k) and (i - l >= k) then begin
    result := key;
    exit;
  end;
  if (j - l + 1) >= k then result := search(l, j, k)
  else result := search(i, r, k - (i - l));
end ;
begin
  randomize;
  readln(t);
  for j := 1 to t do begin
  	read(n);
  	for i := 1 to n do
  		read(a[i]);
  	i := search(1, n, n div 2);
  	ans := 0;
  	for i := 1 to n div 2 do
  		ans := ans - a[i];
  	for i := n div 2 + 1 to n do
  		ans := ans + a[i];
  	writeln(ans);
  end;
end.      
