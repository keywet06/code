var
  a:array[1..13]of longint;
  i,ans,max,len,n,m:longint;
  s:string;
  ch:char;
begin
  for i:=1 to 13 do
  begin
    read(a[i]);
	if a[i]>max then max:=a[i];
  end;
  readln;
  readln(n,m);
  readln(s);
  i:=0;len:=length(s);
  while i<len do
  begin
    inc(i);
    ch:=s[i];
	case ch of
	  'A':inc(ans,a[1]);
	  '2','3','4','5','6','7','8','9':inc(ans,a[ord(ch)-ord('0')]);
	  'J':inc(ans,a[11]);
	  'Q':inc(ans,a[12]);
	  'K':inc(ans,a[13]);
	  '1':begin
                inc(i);
			inc(ans,a[10]);
		  end;
	end;
  end;
  writeln(ans+m*max);
end.
