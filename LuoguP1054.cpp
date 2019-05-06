#include <bits/stdc++.h>
class mult {
    public:
        int a[105];
        mult();
        int& operator[](int);
};
int operator==(mult, mult);
mult operator+(mult, mult);
mult operator-(mult, mult);
mult operator*(mult, mult);
mult operator^(mult, int);
mult f(std::string);
mult f(std::string&, int, int);
mult zero(int);
std::string s;
int n;
mult ms, one;
int main() {
    one[1] = 1;
    getline(std::cin, s);
    ms = f(s);
    scanf("%d", &n);
    getline(std::cin, s);
    for (register int i = 0; i < n; ++i) {
        getline(std::cin, s);
        if (f(s) == ms) printf("%c", i + 'A');
    }
    puts("");
    return 0;
}
inline mult::mult() {
    memset(a, 0, sizeof(a));
}
inline int& mult::operator[](int x) {
    return a[x];
}
inline int operator==(mult x, mult y) {
    for (register int i = 0; i < 100; ++i)
        if (x[i] != y[i]) return 0;
    return 1;
}
inline mult operator+(mult x, mult y) {
    mult a;
    for (register int i = 0; i < 100; ++i) a[i] = x[i] + y[i];
    return a;
}
inline mult operator-(mult x, mult y) {
    mult a;
    for (register int i = 0; i < 100; ++i) a[i] = x[i] - y[i];
    return a;
}
inline mult operator*(mult x, mult y) {
    mult a;
    for (register int i = 0; i < 50; ++i)
        for (register int j = 0; j < 50; ++j)
            a[i + j] += x[i] * y[j];
    return a;
}
inline mult operator^(mult x, int y) {
    mult a = x;
    for (int i = 1; i < y; ++i) a = a * x;
    return a;
}
inline mult f(std::string s) {
    std::string s1;
    for (register int i = 0; i < s.length(); ++i)
        if (s[i] != ' ') s1 = s1 + s[i];
//	printf("Debug: s1 = %s;\n", s1.data());
    mult e = f(s1, 0, s1.length() - 2);
//	printf("Debug: e = {");
//	for (int i = 0; i < 10; ++i) printf("%d, ", e[i]);
//	printf("%d};\n", e[10]);
    return e;
}
inline mult f(std::string &s, int begin, int end) {
//	printf("Debug: s[from begin = %d to end = %d] = ", begin, end);
//	for (register int i = begin; i <= end; ++i) printf("%c", s[i]);
//	printf(";\n");
    int now = 0, flag = 1;
    for (register int i = begin; i <= end; ++i) {
        if (s[i] == '(') ++now;
        if (s[i] == ')') --now;
    }
    if (now != 0) return zero(-10000);
    if (begin == end && s[begin] == 'a') return one;
    for (register int i = begin; i <= end; ++i)
        if (s[i] < '0' || '9' < s[i]) flag = 0;
    if (flag) {
        int k = 0;
        for (register int i = begin; i <= end; ++i) k = k * 10 + s[i] - '0';
        return zero(k);
    }
    flag = 1;
    for (register int i = begin; i <= end; ++i) {
        if (s[i] == '(') ++now;
        if (s[i] == ')') --now;
        if (now == 0 && i != end) flag = 0;
    }
    if (flag) return f(s, begin + 1, end - 1);
    for (register int i = end; i >= begin; --i) {
        if (s[i] == '(') ++now;
        if (s[i] == ')') --now;
        if (now == 0 && s[i] == '+') return f(s, begin, i - 1) + f(s, i + 1, end);
        if (now == 0 && s[i] == '-') return f(s, begin, i - 1) - f(s, i + 1, end);
    }
    for (register int i = end; i >= begin; --i) {
        if (s[i] == '(') ++now;
        if (s[i] == ')') --now;
        if (now == 0 && s[i] == '*') return f(s, begin, i - 1) * f(s, i + 1, end);
    }
    if (s[end - 1] == '^') return f(s, begin, end - 2) ^ (s[end] - '0');
    if (s[end - 2] == '^') return f(s, begin, end - 3) ^ 10;
}
inline mult zero(int x) {
    mult k;
    k[0] = x;
    return k;
}
