var
  a:array[1..15000,1..1000]of longint;
  a:array[1..140000,1..4]of longint;
  n,m,i,j,k,t1,t2,t3,t4:longint;
begin
  readln(n,m);
  for i:=1 to m do
  begin
    read(j);
    inc(a[j,0]);
    a[j,a[j,0]]:=i;
  end;
  for k:=1 to n do
    for i:=1 to (n-k) div 3 div 2 do
      for j:=i*3 to n-i-k do
      begin
        t1:=k; t2:=k+i*2; t3:=t2+j; t4:=t3+i;
        if (a[t1,0]>0)and(a[t2,0]>0)and(a[t3,0]>0)and(a[t4,0]>0) then
        begin
          inc(b[a[t1,0],1],a[t2,0]*a[t3,0]*a[t4,0]);
          inc(b[a[t2,0],2],a[t1,0]*a[t3,0]*a[t4,0]);
          inc(b[a[t3,0],3],a[t1,0]*a[t2,0]*a[t4,0]);
          inc(b[a[t4,0],4],a[t1,0]*a[t2,0]*a[t3,0]);
        end;
      end;
  for i:=1 to m do
  begin
    for j:=1 to 4 do
      write(a[i,j],' ');
    writeln;
  end;
end.