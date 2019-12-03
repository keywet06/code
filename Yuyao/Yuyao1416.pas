var
  f:array[0..50]of int64;
  i,n:longint;
  //j:longint;
begin
  f[1]:=1;for i:=2 to 50 do f[i]:=f[i-1]+f[i-2];
  readln(n);
  i:=0;
  while n>f[i] do inc(i);//writeln(i);
  //for j:=0 to 10 do write(f[j],' ');writeln;
  if abs(f[i]-n)<abs(n-f[i-1]) then writeln(abs(f[i]-n))
                               else writeln(abs(n-f[i-1]));
end.