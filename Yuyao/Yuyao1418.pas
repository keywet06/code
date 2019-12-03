var
  f:array[0..2000000]of longint;
  a:array[0..20]of longint;
  maxw,i,j,n:longint;
begin
  readln(n);
  for i:=1 to n do
  begin
    read(a[i]);
	inc(maxw,a[i]);
  end;
  f[0]:=1;
  for i:=1 to n do
    for j:=maxw downto a[i] do
	  f[j]:=f[j]+f[j-a[i]];
  i:=0;
  while f[i]>0 do inc(i);
  writeln(i);
end.