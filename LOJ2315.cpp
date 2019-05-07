#include <bits/stdc++.h>
const int N = 205;
int T, ci, cont, n, now, x, y;
int a[N], c[N], ch[N], d[N];
int map[256];
std::string s;
int main() {
    scanf("%d", &T);
    while (T--) {
        ci = cont = now = x = y = 0;
        memset(a, 0, sizeof(a));
        memset(c, 0, sizeof(a));
        memset(ch, 0, sizeof(a));
        memset(d, 0, sizeof(a));
        scanf("%d", &n);
        std::cin >> s;
        ci = 0;
        if (s[2] != '1') {
            for (int i = 4; s[i] != ')'; ++i) {
                ci = ci * 10 + s[i] - '0';
            }
        }
        a[0] = 0;
        while (n--) {
            std::cin >> s;
            if (s[0] == 'E') {
                --now;
                if (now < 0) {
                    cont = 1;
                    for (int i = 0; i <= n; ++i) {
                        getline(std::cin, s);
                    }
                    puts("ERR");
                    break;
                }
                a[now] = std::max(a[now], (a[now + 1] + c[now + 1]) * d[now + 1]);
                map[ch[now + 1]] = 0;
            } else {
                ++now;
                a[now] = 0;
                std::cin >> s;
                ch[now] = s[0];
                if (map[s[0]]) {
                    cont = 1;
                    for (int i = 0; i <= n; ++i) {
                        getline(std::cin, s);
                    }
                    puts("ERR");
                    break;
                }
                map[s[0]] = 1;
                std::cin >> s;
                if (s[0] == 'n') {
                    std::cin >> s;
                    c[now] = 0;
                    if (s[0] == 'n') {
                        d[now] = 1;
                    } else {
                        d[now] = 0;
                    }
                } else {
                    x = 0;
                    for (int i = 0; i < s.length(); ++i) {
                        x = x * 10 + s[i] - '0';
                    }
                    std::cin >> s;
                    if (s[0] == 'n') {
                        c[now] = 1;
                        d[now] = 1;
                    } else {
                        c[now] = 0;
                        y = 0;
                        for (int i = 0; i < s.length(); ++i) {
                            y = y * 10 + s[i] - '0';
                        }
                        if (x <= y) {
                            d[now] = 1;
                        } else {
                            d[now] = 0;
                        }
                    }
                }
            }
        }
        memset(map, 0, sizeof(map));
        if (cont) {
            --cont;
            continue;
        }
        if (now > 0) {
            puts("ERR");
            now = 0;
        } else if (ci == a[0]) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}
