#ifndef TU_HPP
#define TU_HPP
#include <bits/stdc++.h>
class Tu {
    private:
        class edge {
            public:
                int next, to;
                int* data;
        };
        int* arr[100];
        std::vector<edge> ed;
        std::map<int, int> head;
    public:
        Tu();
        ~Tu();
        void addedge(int, int, int);
};
inline Tu::Tu() {}
inline Tu::~Tu() {}
inline void Tu::addedge(int x, int y, int z) {
    edge e;
    e.next = head[x];
    head[x] = ed.size();
    e.to = y;
    ed.push_back(e);
}
#endif
