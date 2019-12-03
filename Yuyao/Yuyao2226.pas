var
  n,m,max,i,j,x,ans,p:longint;
begin
  readln(n,m);
  max:=0;
  for i:=1 to n do
  begin
    ans:=0;
	for j:=1 to m do
	begin
	  read(x);
	  if x mod 8=0 then ans:=ans+x;
	end;
	if ans>max then begin max:=ans; p:=i; end;
  end;
  writeln(p);
end.
