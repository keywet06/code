cd "$( dirname "${BASH_SOURCE[0]}" )"

if [[ -f "$1/$1$2.cpp" ]]; then
    ADDFILE="$1/$1$2.cpp";
    ADDMESSAGE="$1$2";
elif [[ -f "$1/$2.cpp" ]]; then
    ADDFILE="$1/$2.cpp";
    ADDMESSAGE="$2";
else
    echo "FILE is not exist";
    exit 1;
fi

git add $ADDFILE
git commit $ADDFILE -m"accept $ADDMESSAGE"

exit 0;