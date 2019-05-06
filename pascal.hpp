#ifndef PASCAL_HPP
#define PASCAL_HPP
//include:
#include <cstdio>

//Declare:
void readln();
void read(int&);
void readln(int&);
void read(char&);
void readln(int&, int&);

//Implementation:
inline void readln() {
    while (getchar() != '\n');
}
inline void read(int &x) {
    char ch = getchar();
    while (ch < '0' || '9' < ch) {
        ch = getchar();
    }
    x = ch - '0';
    ch = getchar();
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    ungetc(ch, stdin);
}
inline void readln(int &x) {
    read(x);
    readln();
}
inline void read(char &x) {
    x = getchar();
}
inline void readln(int &x, int &y) {
    read(x);
    read(y);
    readln();
}
#endif