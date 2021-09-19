g++ -o $1 $1.cpp -std=c++14
g++ -o $2 $2.cpp -std=c++14
g++ -o $3 $3.cpp -std=c++14

echo "Compile success"

while true; do

    ./$3 > $1.in
    ./$2 < $1.in > $1.ans
    ./$1 < $1.in > $1.out

    if diff $1.out $1.ans; then
        echo "Success";
    else
        echo "Failed";
        break;
    fi

done
