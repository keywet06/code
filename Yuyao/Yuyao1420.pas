var
  a,b:longint;
begin
  readln(a,b);
  a:=a-1;
  writeln(b div 3-a div 3+b div 5-a div 5+b div 7-a div 7-b div 15+a div 15-b div 21+a div 21-b div 35+a div 35+b div 105-a div 105);
end.