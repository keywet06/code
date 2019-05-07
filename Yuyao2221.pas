var
  b:array['A'..'Z']of boolean;
  a:array[1..50]of string;
  n,i,l:longint;
  s:string;
  ch:char;
begin
  readln(n);
  for i:=1 to n do
    readln(a[i]);
  readln(s);l:=length(s);
  for i:=1 to n do
    if (length(a[i])>l)and(copy(a[i],1,l)=s) then b[a[i][l+1]]:=true;
  write('***');//1
  for ch:='A' to 'E' do
    if b[ch] then write(ch) else write('*');
  writeln;
  for ch:='F' to 'M' do//2
    if b[ch] then write(ch) else write('*');
  writeln;
  for ch:='N' to 'U' do//3
    if b[ch] then write(ch) else write('*');
  writeln;
  for ch:='V' to 'Z' do//4
    if b[ch] then write(ch) else write('*');
  writeln('***');
end.
