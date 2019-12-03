var
  a,b:array[1..140000]of longint;
  d:array[1..140000]of string[3];
  n,m,i,k,o:longint;
  f:boolean;
  s:string;
procedure add(s:string);
begin
  inc(n);
  a[n]:=n;
  d[n]:=s;
end;

procedure rotate;
var i:longint;
begin
  b:=a;
  for i:=n-k+1 to n do
    a[i]:=b[n-i+n-k+1];
end;
begin
  readln(n,m,k);
  for i:=n downto 1 do
  begin
    readln(s);
    a[n-i+1]:=i;
    d[n-i+1]:=s;
  end;
  f:=false;o:=0;
  for i:=1 to m do
  begin
    readln(s);
    case s[1] of
      'A':begin
	        if f and(o mod 2=1) then rotate;
                f:=true;
		add(copy(s,5,length(s)-5));
		o:=0;
          end;  
      'R':inc(o);
    end;
  end;
  if (s[1]='R')and(o mod 2=1) then rotate;
  for i:=n downto 1 do
   writeln(d[a[i]]);
end.

