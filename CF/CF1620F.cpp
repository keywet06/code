#include <bits/stdc++.h>

template <typename Type>
using A2 = std::array<Type, 2>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) std::cin >> a[i];
        struct Node {
            int Flag, Max, Last, RLast;
            inline Node() : Flag(0), Max(0), Last(0), RLast(0) {}
            inline Node(int x) : Flag(0), Max(x), Last(x), RLast(0) {}
            inline Node(int F, int M, int L, int RL)
                : Flag(F), Max(M), Last(L), RLast(RL) {}
            inline Node Append(int x) {
                Node Ret = *this;
                Ret.RLast = Last, Ret.Last = x, Ret.Max = std::max(Max, x);
                if (Flag) return Ret;
                if (Last < Max && x < Last) return Ret.Flag = 1, Ret;
                return Ret;
            }
        };
        auto Better = [](Node a, Node b) -> bool {
            if (a.Flag || b.Flag) return b.Flag;
            if (a.Max != b.Max) return a.Max < b.Max;
            return a.Last < b.Last;
        };
        auto Max = [&](Node a, Node b) -> Node { return Better(a, b) ? a : b; };
        std::vector<A2<Node> > f(n);
        f[0][0] = Node(a[0]), f[0][1] = Node(-a[0]);
        for (int i = 0, I = 1; I < n; ++i, ++I) {
            f[I][0] = Max(f[i][0].Append(a[I]), f[i][1].Append(a[I]));
            f[I][1] = Max(f[i][0].Append(-a[I]), f[i][1].Append(-a[I]));
        }
        if (f.back()[0].Flag && f.back()[1].Flag) {
            std::cout << "NO" << '\n';
        } else {
            std::stack<int> Sta;
            for (int i = n - 1, u = f.back()[0].Flag; i >= 0; --i) {
                Sta.push(u ? -a[i] : a[i]);
                u = f[i][u].RLast < 0;
            }
            std::cout << "YES" << '\n';
            while (!Sta.empty()) std::cout << Sta.top() << ' ', Sta.pop();
            std::cout << '\n';
        }
    }
    return 0;
}