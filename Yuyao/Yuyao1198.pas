var
  n,k,a,b,c,ans,i:longint;
begin
  readln(n);
  for i:=1 to n do
  begin
    read(k);
	case k of
	  1:begin readln(a,b);   inc(ans,2*a+2*b); end;
	  2:begin readln(a);     inc(ans,4*a);     end;
	  3:begin readln(a,b,c); inc(ans,a+b+c);   end;
	end;
  end;
  writeln(ans);
end.