type cybxb=record
  c,yb,xb:longint;
end;
var
  a:array[0..1000]of cybxb;
  n,i,j:longint;
  max:cybxb;
begin
  readln(n);
  for i:=1 to n do
  begin
    read(a[i].c);
	a[i].yb:=i;
  end;
  for i:=1 to n do
    for j:=n-1 downto i do
	  if a[j].c<a[j+1].c then
	    begin
		  a[0]:=a[j];
		  a[j]:=a[j+1];
		  a[j+1]:=a[0];
		end;
  for i:=1 to n do
    a[i].xb:=i;
  for i:=1 to n do
    if a[i].yb-a[i].xb>max.c then max:=a[i];
  writeln(max.xb);
  writeln(max.yb);
end.