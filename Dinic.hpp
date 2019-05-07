#ifndef DINIC_HPP
#define DINIC_HPP
#include <bits/stdc++.h>
template<int n, int m = n * n> class Dinic {
    private:
        void insert(int, int, int);
    public:
        int cnt;
        int dis[n], head[n];
        int next[m], to[m], liu[m];
        Dinic();
        ~Dinic();
        void addOAE(int, int, int); //Add a only-advance-edge
        void addBAE(int, int, int); //Add a both-advance-edge
};
template<int n, int m> inline Dinic<n, m>::Dinic() {
    cnt = -1;
    memset(dis, -1, sizeof(dis));
    memset(dis, -1, sizeof(head));
}
template<int n, int m> inline Dinic<n, m>::~Dinic() {
}
template<int n, int m> inline void Dinic<n, m>::insert(int x, int y, int z) {
    ++cnt;
    next[cnt] = head[x];
    to[cnt] = y;
    liu[cnt] = z;
}
#endif