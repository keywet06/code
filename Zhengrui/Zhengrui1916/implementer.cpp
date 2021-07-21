#include <bits/stdc++.h>

#include "guess.h"
using namespace std;
typedef vector<int> V;

namespace {
const int MAXN = 100005;
int n, P, Q, R, pos, tag[MAXN];
V arr;

int sign(int x) { return x < 0 ? -1 : (x == 0 ? 0 : 1); }
int _ask1(const V &S, const V &T) {
    if (S.empty() || T.empty()) {
        puts("you ask empty set");
        exit(0);
    }
    P -= 1;
    ++pos;
    if (P < 0) {
        puts("total count > P");
        exit(0);
    }
    Q -= S.size() + T.size();
    if (Q < 0) {
        puts("total size > Q");
        exit(0);
    }
    int l = 0, r = 0;
    for (int i : S) {
        tag[i] = pos;
        if (i < 0 || i >= n) {
            puts("query id < 0 or >= n");
            exit(0);
        }
        l += arr[i];
    }
    for (int i : T) {
        if (tag[i] == pos) {
            puts("S cap T is not empty set");
            exit(0);
        }
        if (i < 0 || i >= n) {
            puts("query id < 0 or >= n");
            exit(0);
        }
        r += arr[i];
    }
    return sign(l) * sign(r);
}
bool _ask2(const V &a) {
    R -= 1;
    if (R < 0) {
        puts("ask2 can only be used once");
        exit(0);
    }
    return arr == a;
}
void run() {
    srand(time(NULL));
    int p, q;
    scanf("%d %d %d", &n, &P, &Q);
    p = P, q = Q;
    for (int i = 0; i < n; i++) {
        int x = 0;
        // x = (rand() % 3) - 1;
		if (i == 0) x = 1;
		if (i == n - 1) x = -1;
        arr.push_back(x);
    }
    R = 1;
    vector<int> ans = solve(n, P, Q);
    if (ans != arr) {
        puts("wrong answer");
    } else
        printf("accepted, P = %d, Q = %d", p - P, q - Q);
}
}  // namespace

int ask1(const V &S, const V &T) { return _ask1(S, T); }
bool ask2(const V &a) { return _ask2(a); }

int main() {
    run();
    return 0;
}
