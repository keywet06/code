var
  f:array[0..100000]of longint;
  a:array[1..500]of longint;
  n,ans,i,j:longint;
begin
  readln(n);
  ans:=0;
  for i:=1 to n do
  begin
    readln(a[i]);
	ans:=ans+a[i];
  end;
  f[0]:=true;
  for i:=1 to n do
    for j:=ans div 2 downto 1 do
      f[j-a[i]]:=f[j-a[i]] or f[j];
  for i:=ans div 2 downto 0 do
    if f[i] then begin n:=i; break; end;
  writeln(ans-n);
end.