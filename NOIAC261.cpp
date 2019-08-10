#include <bits/stdc++.h>
const int C = 5;
const int T = 604529631;
const int x_and = 1879048192;
const int x_hl = 28;
const int y_and = 234881024;
const int y_hl = 25;
const int z_and = 33554431;
const int lx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int ly[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
char ch;
int S, Ts, v, x, y, z, nx, ny, nz, to, mpv;
std::map<int, int> map;
std::queue<int> queue;
void ReadRealChar(char&);
void init();
int Main();
int main() {
    scanf("%d", &Ts);
    while (Ts--) {
        init();
        Main();
    }
}
inline void init() {
    map.clear();
}
inline int Main() {
    S = 0;
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < C; ++j) {
            ReadRealChar(ch);
            if (ch == '*') {
                S |= i << x_hl;
                S |= j << y_hl;
            } else if (ch == '1') {
                S |= 1 << (i * C + j);
            }
        }
    }
    if (S == T) {
        puts("0");
        return 0;
    }
    while (!queue.empty()) {
        queue.pop();
    }
    map[S] = 1;
    queue.push(S);
    while (!queue.empty()) {
        v = queue.front();
        queue.pop();
        mpv = map[v];
        x = (v & x_and) >> x_hl;
        y = (v & y_and) >> y_hl;
        z = v & z_and;
        for (int i = 0; i < 8; ++i) {
            nx = x + lx[i];
            ny = y + ly[i];
            if (nx < 0 || nx >= C || ny < 0 || ny >= C)  {
                continue;
            }
            nz = z;
            if (nz & (1 << (nx * C + ny))) {
                nz ^= 1 << (x * C + y);
                nz ^= 1 << (nx * C + ny);
            }
            to = nz | (nx << x_hl) | (ny << y_hl);
            if (to == T) {
                printf("%d\n", mpv);
                return 0;
            }
            if (!map[to] && mpv <= 7) {
                queue.push(to);
                map[to] = mpv + 1;
            }
        }
    }
    while (!queue.empty()) {
        queue.pop();
    }
    map[T] = 11;
    queue.push(T);
    while (!queue.empty()) {
        v = queue.front();
        queue.pop();
        mpv = map[v];
        x = (v & x_and) >> x_hl;
        y = (v & y_and) >> y_hl;
        z = v & z_and;
        for (int i = 0; i < 8; ++i) {
            nx = x + lx[i];
            ny = y + ly[i];
            if (nx < 0 || nx >= C || ny < 0 || ny >= C)  {
                continue;
            }
            nz = z;
            if (nz & (1 << (nx * C + ny))) {
                nz ^= 1 << (x * C + y);
                nz ^= 1 << (nx * C + ny);
            }
            to = nz | (nx << x_hl) | (ny << y_hl);
            if (map[to] && map[to] <= 10) {
                printf("%d\n", map[to] + map[v] - 11);
                return 0;
            }
            if (!map[to] && mpv <= 17) {
                queue.push(to);
                map[to] = mpv + 1;
            }
        }
    }
    puts("-1");
    return 0;
}
inline void ReadRealChar(char &a) {
    do {
        a = getchar();
    } while (a == '\n' || a == '\r' || a == ' ');
}