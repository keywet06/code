var
  a,b:array[0..50000]of longint;
  xb,ans,i,n,m:longint;

procedure qsort(l,r:longint;var a:array of longint);
var
  k,t,i,j:longint;
begin
  k:=(l+r)div 2;
  t:=a[k];
  i:=l;
  j:=r;
  repeat
    while a[j]>t do dec(j);
    while a[i]<t do inc(i);
    if i<=j then
      begin
        a[0]:=a[i];
        a[i]:=a[j];
        a[j]:=a[0];
        inc(i);
        dec(j);
      end;

  until i>j;
  if i<r then qsort(i,r,a);
  if j>l then qsort(l,j,a);
end;

begin
  readln(n,m);
  for i:=1 to n do
    read(a[i]);
  for i:=1 to m do
    read(b[i]);
  qsort(1,n,a);
  qsort(1,m,b);
  xb:=0;
  for i:=1 to n do
  begin
    inc(xb);
    while (xb<=m)and(b[xb]<a[i]) do inc(xb);
    if xb>m then begin writeln(-1);exit; end;
    inc(ans,b[xb]);
  end;
  writeln(ans);
end.
