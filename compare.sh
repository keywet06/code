if g++ -o $1 $1.cpp -std=c++14 -O2 &&
   g++ -o $2 $2.cpp -std=c++14 -O2 &&
   g++ -o $3 $3.cpp -std=c++14 -O2; then

    echo "Compile success"

    while true; do

        time ./$3 > $1.in
        time ./$2 < $1.in > $1.ans
        time ./$1 < $1.in > $1.out

        if diff $1.out $1.ans; then
            echo "Success";
        else
            echo "Failed";
            break;
        fi

    done

else

    echo "Compile Failed"

fi
