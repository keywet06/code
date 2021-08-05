#include "guess.h"
#include <bits/stdc++.h>

inline int checknum(int x, int y, int l, int r) {
    if (l == r) return l;
    std::vector<int> a, b, c;
    int mid = l + r >> 1;
    for (int i = x; i <= y; ++i) a.push_back(i);
    for (int i = l; i <= mid; ++i) b.push_back(i);
    for (int i = mid + 1; i <= r; ++i) c.push_back(i);
    return ask1(a, b) ? checknum(x, y, l, mid) : checknum(x, y, mid + 1, r);
}

inline int findnum(int l, int r) {
    if (l >= r) return 0;
    int mid = l + r >> 1, c;
    std::vector<int> a, b;
    for (int i = l; i <= mid; ++i) a.push_back(i);
    for (int i = mid + 1; i <= r; ++i) b.push_back(i);
    if (ask1(a, b)) return checknum(l, mid, mid + 1, r);
    return (c = findnum(l, mid)) ? c : findnum(mid + 1, r);
}

std::vector<int> solve(int n, int P, int Q) {
    int p = findnum(0, n - 1);
    std::vector<int> ans(n), a(1), b(1);

    a[0] = p;
    for (int i = 0; i < n; ++i) ans[i] = p == i ? 1 : (b[0] = i, ask1(a, b));
    
    if (!ask2(ans)) {
        for (int i = 0; i < n; ++i) ans[i] = ans[i] * -1;
    }
    
	return ans;
}
