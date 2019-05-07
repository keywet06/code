/*
	This C++ header file is writen by ywt.
*/
#ifndef KMP_HPP
#define KMP_HPP
#include <bits/stdc++.h>
void KMPinit(std::string, int*);
int KMP(std::string, std::string, int*);
std::vector<int> KMPs(std::string, std::string, int*);
/*

*/
void KMPinit(std::string a, int *b) {
    int len = a.length();
    b[0] = -1;
    for (int i = 1; i < len; ++i) {
        b[i] = b[i - 1];
        while (b[i] + 1 && a[b[i] + 1] != a[i]) b[i] = b[b[i]];
        b[i] += a[b[i] + 1] == a[i];
    }
}
int KMP(std::string a, std::string b, int *c) {
    int len1 = a.length(), len2 = b.length(), now = -1;
    for (int i = 0; i < len2; ++i) {
        while (a[now + 1] != b[i] && now + 1) now = c[now];
        now += a[now + 1] == b[i];
        if (now + 1 == len1) return i - now;
    }
    return -1;
}
std::vector<int> KMPs(std::string a, std::string b, int *c) {
    std::vector<int> v;
    int len1 = a.length(), len2 = b.length(), now = -1;
    for (int i = 0; i < len2; ++i) {
        while (a[now + 1] != b[i] && now + 1) now = c[now];
        now += a[now + 1] == b[i];
        if (now + 1 == len1) {
            v.push_back(i - now);
            i -= now - c[now] - 1;
            now = c[now];
        }
    }
    return v;
}
#endif
