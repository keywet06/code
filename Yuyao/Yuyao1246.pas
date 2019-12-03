var
  a,f:array[1..3,0..100000]of longint;
  i,n:longint;
function min(a,b:longint):longint;
begin
  if a>b then exit(b) else exit(a);
end;
begin
  readln(n);
  for i:=1 to n do
    read(a[1,i]);
  readln;
  for i:=1 to n do
    read(a[2,i]);
  readln;
  for i:=1 to n do
    read(a[3,i]);
  readln;
  for i:=1 to n do
  begin
     f[1,i]:=min(f[2,i-1],f[3,i-1])+a[1,i];
     f[2,i]:=min(f[1,i-1],f[3,i-1])+a[2,i];
     f[3,i]:=min(f[2,i-1],f[1,i-1])+a[3,i];
  end;
  writeln(min(min(f[1,n],f[2,n]),f[3,n]));
end.
