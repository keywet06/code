#include <bits/stdc++.h>
const int N = 100005;
long double p;
int n, m, u, v, t, q, x, y;
int a[N];
std::priority_queue<int> pq;
std::priority_queue<int> q1, q2, q3;
int main() {
    scanf("%d %d %d %d %d %d", &n, &m, &q, &u, &v, &t);
    p = (long double)(u) / (long double)(v);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    std::sort(a + 1, a + n + 1);
    for (int i = n; i; --i) {
        q1.push(a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        x = 0;
        y = -1e8;
        if (!q1.empty() && q1.top() > y) {
            x = 1;
            y = q1.top();
        }
        if (!q2.empty() && q2.top() > y) {
            x = 2;
            y = q2.top();
        }
        if (!q3.empty() && q3.top() > y) {
            x = 3;
            y = q3.top();
        }
        if (x == 1) {
            q1.pop();
        }
        if (x == 2) {
            q2.pop();
        }
        if (x == 3) {
            q3.pop();
        }
        x = y + (i - 1) * q;
        if (i % t == 0) {
            printf("%d ", x);
        }
        q2.push((int)(x * p) - i * q);
        q3.push(x - (int)(x * p) - i * q);
    }
    printf("\n");
    while (!q1.empty()) {
        pq.push(q1.top());
        q1.pop();
    }
    while (!q2.empty()) {
        pq.push(q2.top());
        q2.pop();
    }
    while (!q3.empty()) {
        pq.push(q3.top());
        q3.pop();
    }
    for (int i = 1; i <= m + n; ++i) {
        x = pq.top() + m * q;
        if (i % t == 0) {
            printf("%d ", x);
        }
        pq.pop();
    }
    printf("\n");
    return 0;
}