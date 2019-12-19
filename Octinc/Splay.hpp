#ifndef OCTINC_SPLAY_HPP
#  define OCTINC_SPLAY_HPP
#  ifndef STD_BITS_STDCPP_H
#    define STD_BITS_STDCPP_H
#    include <bits/stdc++.h>
#  endif
#  if __cplusplus < 201103L && !defined(nullptr)
#    define nullptr NULL
#  endif
namespace Octinc {
class Splay {
   protected:
    class point {
       public:
        point *fa;
        point *son[2];
        int val, size, num;
        point() {
            fa = son[0] = son[1] = nullptr;
            val = size = num = 0;
        }
    };
    point *root;
   public:
    Splay() { this->root = nullptr; }
    inline int get(point *v) {
        return v == this->root ? -1 : v->fa == v->fa->son[1];
    }
    inline int getsize(point *v) { return v ? v->size : 0; }
    inline void pushup(point *v) {
        v->size = getsize(v->son[0]) + getsize(v->son[1]) + v->num;
    }
    inline void rotate(point *v) {
        if (v->fa == root) {
            root = v->fa;
        }
        int t = get(v);
        if (v->fa->son[t] = v->son[t ^ 1]) {
            v->fa->son[t]->fa = v->fa;
        }
        v->son[t ^ 1] = v->fa;
        v->fa = v->fa->fa;
        v->son[t ^ 1]->fa = v;
        if (v->fa) {
            v->fa->son[v->fa->son[1] == v->son[t ^ 1]] = v;
        }
        pushup(v->son[t ^ 1]);
        pushup(v);
    }
    inline void splay(point *v) {
        while (v != root) {
            get(v) == get(v->fa) ? rotate(v->fa) : rotate(v);
        }
    }
    inline point *insert(int x) {
        if (!root) {
            root = new point;
            root->num = root->size = 1;
            root->val = x;
            return;
        }
        point *v = root;
        while (1) {
            if (v->val == x) {
                ++v->num;
                splay(v);
                return;
            }
            if (!v->son[v->val > x]) {
                break;
            }
            v = v->son[v->val > x];
        }
        v = v->son[v->val > x] = new point;
        v->num = v->size = 1;
        v->val = x;
        splay(v);
        return v;
    }
    inline int rank(int x) {
        int ans = 0;
        point *v = root;
        while (1) {
            if (x < v->val) {
                v = v->son[0];
            } else {
                ans += getsize(v->son[0]);
                if (x == v->val) {
                    splay(v);
                    return ans + 1;
                }
                ans += v->num;
                v = v->son[1];
            }
        }
    }
    inline point *kth(int x) {
        point *v = root;
        while (1) {
            if (x <= getsize(v->son[0])) {
                v = v->son[0];
            } else {
                x -= getsize(v->son[1]);
                if (x <= v->num) {
                    splay(v);
                    return v;
                }
                x -= v->num;
                v = v->son[1];
            }
        }
    }
    inline point *lower(point *v) {
        splay(v);
        v = v->son[0];
        while (v->son[1]) {
            v = v->son[1];
        }
        return v;
    }
    inline point *upper(point *v) {
        splay(v);
        v = v->son[1];
        while (v->son[0]) {
            v = v->son[0];
        }
        return v;
    }
};
} // namespace Octinc
#endif