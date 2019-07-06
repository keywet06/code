#include <bits/stdc++.h>
int year;
int howmanydaysinayear(int);
int thefirstdayofmay(int);
int main() {
    scanf("%d", &year);
    if (thefirstdayofmay(year) == 0) {
        puts("8");
    } else if (thefirstdayofmay(year) == 1) {
        puts("14");
    } else if (thefirstdayofmay(year) == 2) {
        puts("13");
    } else if (thefirstdayofmay(year) == 3) {
        puts("12");
    } else if (thefirstdayofmay(year) == 4) {
        puts("11");
    } else if (thefirstdayofmay(year) == 5) {
        puts("10");
    } else if (thefirstdayofmay(year) == 6) {
        puts("9");
    }
    return 0;
}
inline int howmanydaysinayear(int year) {
    if (year % 4) {
        return 365;
    }
    if (year % 100) {
        return 366;
    }
    if (year % 400) {
        return 365;
    }
    return 366;
}
int thefirstdayofmay(int year) {
    int x = 2000, y = 1;
    if (year > x) {
        for (; x < year; ++x) {
            y += howmanydaysinayear(x + 1);
            y %= 7;
        }
    } else {
        for (; x > year; --x) {
            y -= howmanydaysinayear(x) - 700;
            y %= 7;
        }
    }
    return y;
}