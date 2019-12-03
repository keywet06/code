var
  a,b:array[1..100000]of longint;
  n,m,l,r,mid,ts:int64;
  f:boolean;
  i:longint;
begin
  readln(n,m);
  for i:=1 to n do
    read(a[i]);
  for i:=1 to n do
    read(b[i]);
  l:=0;
  r:=2000000000;
  while l<r do
  begin
    mid:=(l+r+1)div 2;
	ts:=m;f:=true;
	for i:=1 to n do
    begin
      if b[i]*mid>a[i] then m:=m-(b[i]*mid-a[i]);
	  if m<0 then begin f:=false; break; end;
    end;       m:=ts;
	if f then l:=mid else r:=mid-1;
  end;
  writeln(l);
end.
