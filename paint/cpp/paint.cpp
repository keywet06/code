#include "paint.h"

#include <vector>

int minimumInstructions(int N, int M, int K, std::vector<int> C,
                        std::vector<int> A, std::vector<std::vector<int>> B) {
    std::vector<int> f(K), o(N);
    int tag = 1;
    for (int i = 0; i < K; ++i) f[i] = -1;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < A[i]; ++j) {
            if (~f[B[i][j]]) tag = 0;
            f[B[i][j]] = i;
        }
    }
    if (tag) {
        for (int i = 0; i < N; ++i) o[i] = f[C[i]];
        int now = 1, ans = 0;
        if (o[0] == -1) return -1;
        for (int i = 1; i < N; ++i) {
            if (o[i] == -1) return -1;
            if ((o[i - 1] + 1) % M == o[i]) {
                ++now;
            } else {
                if (now < M) return -1;
                ans += (now - 1) / M + 1;
                now = 1;
            }
        }
        if (!now) return ans;
        if (now < M) return -1;
        ans += (now - 1) / M + 1;
        now = 1;
        return ans;
    } else {
        std::vector<std::vector<int> > f(K);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < A[i]; ++j) {
                f[B[i][j]].push_back(i);
            }
        }
        std::vector<int> now[M];
    }
}
