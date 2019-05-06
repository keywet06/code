#include <algorithm>
#include <cstdlib>
using namespace std;
struct node {
    int size;
    int weight;
    int val;
    node *ch[2];
};
node *root;
node *null;
node *new_node(int x) {
    static node a[100005];
    static int top = 0;
    node *t = &a[top++];
    t->size = 1;
    t->weight = rand();
    t->val = x;
    t->ch[0] = null;
    t->ch[1] = null;
    return t;
}
void rotate(node *&x, int c) {
    node *y = x->ch[c];
    x->ch[c] = y->ch[!c];
    y->ch[!c] = x;
    y->size = x->size;
    x->size = x->ch[0]->size + x->ch[1]->size + 1;
    x = y;
}
void insert_node(node *&x, node *y) {
    if (x == null) {
        x = y;
        return;
    }
    x->size++;
    int c;
    if (y->val > x->val) {
        c = 1;
    } else {
        c = 0;
    }
    insert_node(x->ch[c], y);
    if (x->ch[c]->weight > x->weight) {
        rotate(x, c);
    }
}
void delete_node(node *&x, int k) {
    if (x == null) {
        return;
    }
    x->size--;
    if (x->val == k) {
        int c;
        if (x->ch[0]->weight > x->ch[1]->weight) {
            c = 0;
        } else {
            c = 1;
        }
        rotate(x, c);
        delete_node(x->ch[!c], k);
    } else {
        int c;
        if (x->val > k)
            c = 0;
        else
            c = 1;
        delete_node(x->ch[c], k);
    }
}
int find_maxxer_node_val(node *&now, int k) {
    // 不可以相等
    if (now == null)
        return 999999999; // inf
    if (now->val > k) {
        return min(now->val, find_maxxer_node_val(now->ch[0], k));
    } else {
        return find_maxxer_node_val(now->ch[1], k);
    }
}
int find_minner_node_val(node *&now, int k) {
    // 可以相等
    if (now == null)
        return -999999999; // -inf
    if (now->val <= k) {
        return max(now->val, find_minner_node_val(now->ch[1], k));
    } else {
        return find_minner_node_val(now->ch[0], k);
    }
}
bool find(node *&now, int k) {
    if (now == null) {
        return false;
    }
    if (now->val == k) {
        return true;
    } else if (now->val < k) {
        return find(now->ch[1], k);
    } else {
        return find(now->ch[0], k);
    }
}
int get_kth(node *&now, int k) {
    if (k == now->ch[0]->size + 1) {
        return now->val;
    } else if (k <= now->ch[0]->size) {
        return get_kth(now->ch[0], k);
    } else {
        return get_kth(now->ch[1], k - now->ch[0]->size - 1);
    }
}
int get_rank(node *now, int k) {
    if (now == null)
        return 1;
    if (now->val < k) {
        return now->ch[0]->size + 1 + get_rank(now->ch[1], k);
    }
    return get_rank(now->ch[0], k);
}
int main() {
    null = new_node(0);
    null->ch[0] = null;
    null->ch[1] = null;
    null->size = 0;
    null->weight = -1;

    return 0;
}