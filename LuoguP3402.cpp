#include <bits/stdc++.h>
const int C = 10000005;
const int M = 200005;
const int N = 100005;
class node {
   public:
    int lson, rson;
    short int sum, deep;
};
node nod[C];
int cnt, n, m, x, y;
int version[M];
short int &query(int, int, int, int = 1, int = n);
short int &query2(int, int, int, int = 1, int = n);
int find(int, int &);
void merge(int, int, int &);
inline short int &query(int x, int v, int flag, int l, int r) {
	if (l == r) {
		return nod[v].sum;
	}
	int mid = (l + r) / 2;
	if (x <= mid) {
        if (flag) {
            nod[++cnt] = nod[nod[v].lson];
            nod[v].lson = cnt;
        }
		return query(x, nod[v].lson, flag, l, mid);
	} else {
        if (flag) {
            nod[++cnt] = nod[nod[v].rson];
            nod[v].rson = cnt;
        }
		return query(x, nod[v].rson, flag, mid + 1, r);
	}
}
inline short int &query2(int x, int v, int flag, int l, int r) {
	if (l == r) {
		return nod[v].deep;
	}
	int mid = (l + r) / 2;
	if (x <= mid) {
        if (flag) {
            nod[++cnt] = nod[nod[v].lson];
            nod[v].lson = cnt;
        }
		return query(x, nod[v].lson, flag, l, mid);
	} else {
        if (flag) {
            nod[++cnt] = nod[nod[v].rson];
            nod[v].rson = cnt;
        }
		return query(x, nod[v].rson, flag, mid + 1, r);
	}
}
inline int find(int x, int &nodes) {
    short int *a = &query(x, nodes, 0);
    if (*a == x) {
        return *a;
    } else {
        int b = find(*a, nodes);
        // if (*a != b) {
        //     query(*a, nodes, 1) = b;
        // }
        return b;
    }
    return *a == x ? *a : find(*a, nodes);
}
inline void merge(int x, int y, int &nodes) {
    short int *a = &query2(find(x, nodes), nodes, 0),
      *b = &query2(find(y, nodes), nodes, 0);
    if (*a > *b) {
    // if (cnt & 1) {
        query(find(x, nodes), nodes, 1) = find(y, nodes);
    // } else {
    } else if (*a < *b) {
        query(find(y, nodes), nodes, 1) = find(x, nodes);
    } else {
        query(find(x, nodes), nodes, 1) = find(y, nodes);
        ++query2(find(y, nodes), nodes, 1);
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    version[0] = ++cnt;
    for (int i = 1; i <= n; ++i) {
        query(i, version[0], 1) = i;
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> x;
        if (x == 1) {
            std::cin >> x >> y;
            nod[version[i] = ++cnt] = nod[version[i - 1]];
            merge(x, y, version[i]);
        } else if (x == 2) {
            std::cin >> x;
            nod[version[i] = ++cnt] = nod[version[x]];
        } else {
            std::cin >> x >> y;
            nod[version[i] = ++cnt] = nod[version[i - 1]];
            std::cout << (find(x, version[i]) == find(y, version[i])) <<
              std::endl;
        }
    }
    return 0;
}