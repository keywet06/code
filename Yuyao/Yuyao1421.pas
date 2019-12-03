var
  n,i,j,ans:longint;
  ch:char;
begin
  n:=4;
  for i:=1 to n do
  begin
    for j:=1 to n do
	begin
	  read(ch);
	  if ch<>'.' then ans:=ans+abs((ord(ch)-ord('A'))div 4+1-i)+abs((ord(ch)-ord('A'))mod 4+1-j);
	  //if ch<>'.' then writeln(abs((ord(ch)-ord('A'))div 4+1-i),' ',abs((ord(ch)-ord('A'))mod 4+1-j));
	end;
	readln;
  end;
  writeln(ans);
end.