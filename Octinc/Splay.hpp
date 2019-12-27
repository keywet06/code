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
   public:
    point *root;
    Splay() { root = nullptr; }
    inline int get(point *v) {
        return !v || !v->fa ? -1 : v == v->fa->son[1];
    }
    inline int getsize(point *v) { return v ? v->size : 0; }
    inline void pushup(point *v) {
        v->size = getsize(v->son[0]) + getsize(v->son[1]) + v->num;
    }
    inline void rotate(point *v) {
        if (v->fa == root) {
            root = v;
        }
        int t = get(v);
        if (v->fa->son[t] = v->son[t ^ 1]) {
            v->fa->son[t]->fa = v->fa;
        }
        v->son[t ^ 1] = v->fa;
        if (v->fa = v->fa->fa) {
            v->fa->son[get(v->son[t ^ 1])] = v;
        }
        v->son[t ^ 1]->fa = v;
        pushup(v->son[t ^ 1]);
        pushup(v);
    }
    inline void splay(point *v) {
        while (v != root) {
            if (get(v) == get(v->fa)) {
                rotate(v->fa);
            }
            rotate(v);
        }
    }
    inline point *insert(int x) {
        if (!root) {
            root = new point;
            root->num = root->size = 1;
            root->val = x;
            return root;
        }
        point *v = root;
        while (1) {
            if (v->val == x) {
                ++v->num;
                pushup(v);
                splay(v);
                return root;
            }
            if (!v->son[x > v->val]) {
                break;
            }
            v = v->son[x > v->val];
        }
        v->son[x > v->val] = new point;
        v->son[x > v->val]->fa = v;
        v = v->son[x > v->val];
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
                x -= getsize(v->son[0]);
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
    inline point *lower() { return lower(root); }
    inline point *upper() { return upper(root); }
    inline point *find(int x) {
        point *v = root;
        while (1) {
            if (v->val == x) {
                splay(v);
                return v;
            }
            v = v->son[x > v->val];
        }
    }
    inline void del(point *v) {
        splay(v);
        if (v->num > 1) {
            --v->num;
            return;
        }
        if (v->size == 1) {
            delete v;
            root = nullptr;
            return;
        }
        if (!(v->son[0] && v->son[1])) {
            root = v->son[(bool)(v->son[1])];
            root->fa = nullptr;
            delete v;
            return;
        }
        splay(lower());
        root->son[1] = v->son[1];
        v->son[1]->fa = root;
        delete v;
        pushup(root);
    }
    inline void del(int x) { del(find(x)); }
};
} // namespace Octinc
#endif