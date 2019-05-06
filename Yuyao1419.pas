var
  a,p,k:array[0..20,0..20]of longint;
  n,i,j,ii,jj,m,max,s,as,ps,ks:longint;
  ch:char;
begin
  readln(n);
  for i:=1 to n do
  begin
    for j:=1 to n do
	begin
	  read(ch);
	  if ch<>'.' then if ch='A' then inc(a[i,j])
	                            else inc(p[i,j])
				 else inc(k[i,j]);
	end;
    readln;
  end;
  readln(m);
  for i:=1 to n do
    for j:=1 to n do
	begin
	  a[i,j]:=a[i,j]+a[i-1,j]+a[i,j-1]-a[i-1,j-1];
	  p[i,j]:=p[i,j]+p[i-1,j]+p[i,j-1]-p[i-1,j-1];
	  k[i,j]:=k[i,j]+k[i-1,j]+k[i,j-1]-k[i-1,j-1];
	end;
  if k[n,n]=0 then m:=0;
  for i:=1 to n do
    for j:=1 to n do
	  for ii:=i to n do
	    for jj:=j to n do
		begin
		  as:=a[ii,jj]-a[i-1,jj]-a[ii,j-1]+a[i-1,j-1];
		  ps:=p[ii,jj]-p[i-1,jj]-p[ii,j-1]+p[i-1,j-1];
		  ks:=k[ii,jj]-k[i-1,jj]-k[ii,j-1]+k[i-1,j-1];
		  s:=(ii-i+1)*(jj-j+1);
		  if (s>a[n,n])or(m<(ks+ps*2)) then break;
		  if max<s then max:=s;
		end;
  writeln(max);
end.
