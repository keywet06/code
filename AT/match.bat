kwcode compile ARC066C_match.cpp
kwcode compile ARC066C_data.cpp
kwcode compile ARC066C.cpp
:roof1
ARC066C_data > ARC066C.in
ARC066C < ARC066C.in > ARC066C.out
ARC066C_match < ARC066C.in > ARC066C.ans
fc ARC066C.out ARC066C.ans
if errorlevel 1 pause
goto roof1