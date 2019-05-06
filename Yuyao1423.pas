var
  a,b,c:array[0..100]of longint;
  d:array[0..100]of boolean;
  n,i,xb,ans,s,xb2:longint;
function cj:longint;
var
  i,j:longint;
begin
  cj:=0;
  for i:=1 to n-1 do
    for j:=i+1 to n do
	  if a[i]<a[j] then inc(cj);
end;

procedure qpl(m:longint);
var  i,j:longint;
begin
  if m>xb then
  begin
    //for j:=1 to n do
    //  write(a[j],' ');
    //writeln;
    if cj=s then inc(ans);
	exit;
  end;
  for i:=1 to xb do
    if not d[c[i]] then
	begin
        //write('//');
        //for j:=1 to n do
        //  write(a[j],' '); 
        //writeln;       
	  d[c[i]]:=true;
	  a[b[m]]:=c[i];
	  qpl(m+1);
	  d[c[i]]:=false;
        a[b[m]]:=0;
	end;
end;

begin
  readln(n,s);
  for i:=1 to n do
  begin
    read(a[i]);
	d[a[i]]:=true;
	if a[i]=0 then 
	begin
	  inc(xb);
	  b[xb]:=i;
	end;
  end;  
  for i:=1 to n do
    if not d[i] then
    begin
	  inc(xb2);
	  c[xb2]:=i;
    end;
  qpl(1);
  writeln(ans);
end.