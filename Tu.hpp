/*
	This C++ header file is writen by ywt.
*/
#ifndef TU_HPP
#define TU_HPP
#include <bits/stdc++.h>
template<int n = 1000, int m = n * n> class Tu {
    public:
        int cnt;
        int head[n], next[m], to[m];
        int* arr[100];
        Tu();
        ~Tu();
        void insert(int, int, int);
};
template<int n, int m> inline Tu<n, m>::Tu() {}
template<int n, int m> inline Tu<n, m>::~Tu() {}
#endif
