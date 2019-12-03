var
  a:array[0..50]of longint;
  n,i,x,ans:longint;
begin
  readln(n);
  for i:=1 to n do
    read(a[i]);
  for i:=1 to n do
  begin
    read(x);
	if x<a[i] then inc(ans);
  end;
  writeln(ans);
end.