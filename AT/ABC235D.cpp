#include <bits/stdc++.h>

using int64 = long long;

int main() {
    const int N = 1000000;
    int a, n;
    std::cin >> a >> n;
    std::vector<int> Step(N);
    std::queue<int> Que({1});
    Step[1] = 1;
    while (!Que.empty()) {
        int u = Que.front();
        int64 x = int64(u) * a;
        Que.pop();
        if (x < N && !Step[x]) Step[x] = Step[u] + 1, Que.push(x);
        int d = u % 10;
        if (d == 0) continue;
        x = u / 10;
        while (x) d *= 10, x /= 10;
        x = d + u / 10;
        if (x < N && !Step[x]) Step[x] = Step[u] + 1, Que.push(x);
    }
    std::cout << Step[n] - 1 << std::endl;
    return 0;
}