#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int8 = int8_t;
using int16 = int16_t;

struct Node {
    int8 Op;
    int16 x;
    int Id;
    Node(int O, int X, int I) : Op(O), x(X), Id(I) {}
};

const int N = 8005;
const int D = N << 1;
const int M = 2000005;

int n, m;
int Ch[N], Pre[N], QL[M], QR[M], LtR[N], RtL[N], Ans[M], Con[N], Size[D];

inline void Clear() { memset(Con, 0, sizeof(Con)); }

inline void Add(int i, int x) {
    while (i < N) Con[i] += x, i += i & -i;
}

inline int Sum(int i) {
    int Ans(0);
    while (i) Ans += Con[i], i &= i - 1;
    return Ans;
}

std::string s;

std::vector<std::pair<int16, int16> > Query1[D];

std::vector<int> Query2[D];

int main() {
    std::cin >> n >> m;
    std::cin >> s;
    for (int i = 1; i <= n; ++i) Ch[i] = s[i - 1] == '(' ? 1 : -1;
    for (int i = 1; i <= n; ++i) Pre[i] = Pre[i - 1] + Ch[i];
    for (int i = 1; i <= m; ++i) std::cin >> QL[i] >> QR[i];
    for (int i = 1; i <= n; ++i) {
        LtR[i] = n;
        for (int j = i, p = 0; j <= n; ++j) {
            if ((p += Ch[j]) < 0 && (LtR[i] = j, true)) break;
        }
        RtL[i] = 1;
        for (int j = i, p = 0; j >= 0; --j) {
            if ((p -= Ch[j]) < 0 && (RtL[i] = j, true)) break;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i, p = 0; j <= n; ++j) Query1[N + (p += Ch[j])].emplace_back(i, j);
    }
    for (int i = 1; i <= m; ++i) Query2[N + Pre[QR[i]] - Pre[QL[i] - 1]].push_back(i);
    for (int c = 0; c < D; ++c) {
        if (Query1[c].empty() || Query2[c].empty()) continue;
        std::vector<Node> v;
        for (auto [l, r] : Query1[c]) v.emplace_back(0, l, r);
        for (auto i : Query2[c]) {
            v.emplace_back(-1, QL[i] - 1, i);
            v.emplace_back(1, LtR[QL[i]], i);
        }
        std::sort(v.begin(), v.end(), [](Node a, Node b) { return a.x == b.x ? bool(a.Op) < bool(b.Op) : a.x < b.x; });
        Clear();
        for (auto t : v) {
            int Op = t.Op, x = t.x, Id = t.Id, l = RtL[QR[Id]], r = QR[Id];
            if (Op) {
                Ans[Id] += Op * (Sum(r) - Sum(l - 1));
            } else {
                Add(Id, 1);
            }
        }
        v.clear();
    }
    for (int i = 1; i <= m; ++i) std::cout << Ans[i] << '\n';
    return 0;
}