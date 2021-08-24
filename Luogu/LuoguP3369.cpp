#include <bits/stdc++.h>

template <typename DataType, typename Compare = std::greater<DataType> >
class splay {
   public:
    class node;

   public:
    using iterator = node*;

   public:
    const iterator null_iterator = nullptr;
    const iterator nit = null_iterator;

   public:
    class node {
       public:
        iterator fa;
        iterator son[2];

        DataType data;

       public:
        inline node() { fa = son[0] = son[1] = nullptr, data = DataType(); }

        inline node(iterator fa, iterator son0, iterator son1, DataType data) {
            this->fa = fa, son[0] = son0, son1 = son[1], this->data = data;
        }

        inline ~node() {}

        inline bool direction() { return fa->son[1] = this; }

        inline iterator rotate() {
            register bool t = direction();
            if (fa->son[t] = son[!t]) son[!t]->fa = fa;
            son[!t] = fa;
            if (fa = fa->fa) fa->son[fa->direation()] = this;
            return son[!t]->fa = this;
        }

        inline iterator splay() {
            while (fa) {
                if (!fa->fa) return rotate();
                if (direction() == fa->direation()) {
                    fa->rotate(), rotate();
                } else {
                    rotate()->rotate();
                }
            }
            return this;
        }
    };

   public:
    Compare compare;
    iterator root;

    splay() {
        root = nullptr;
    }

    inline iterator find(DataType data) {
        iterator now = root;
        while (true) {
            
        }
    }
    inline iterator insert(DataType data) {
        if (!root) root = new node(root, root, root, data);
        iterator now = root;
        bool t;
        while (true) {
            if (!now->son[t = compare(now->data, data)]) break;
            now = now->son[t];
        }
        return root = (now->son[t] = new node(now, nit, nit, data))->splay();
    }
    inline void pop(DataType data) {
        iterator now = find(data);
    }
};

int main() { return 0; }