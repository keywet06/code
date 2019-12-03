#include <iostream>
#include <cstring>
#include <cstdio>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
const int C = 26;
const int D = 70;
const int N = 10505;
const int M = 1000005;
char p[M];
int ans, cnt, lp, n, now;
int no[D];
int a[N], b[N], is[N], fa[N], t[N];
int trie[N][C];
void init();
int Main();
int main() {
    scanf("%d", &n);
    while (n) {
        init();
        Main();
        scanf("%d", &n);
    }
    return 0;
}
void init() {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(is, 0, sizeof(is));
    memset(fa, 0, sizeof(fa));
    memset(t, 0, sizeof(t));
    memset(trie, 0, sizeof(trie));
    memset(no, 0, sizeof(no));
}
int Main() {
    cnt = 1;
    for (register int i = 0; i < C; ++i) {
        trie[0][i] = 1;
    }
    for (register int i = 1; i <= n; ++i) {
        scanf("%s", p);
        lp = strlen(p);
        now = 1;
        for (register int j = 0; j < lp; ++j) {
            p[j] -= 'a';
            if (!trie[now][p[j]]) {
                trie[now][p[j]] = ++cnt;
                t[cnt] = p[j];
                fa[cnt] = now;
            }
            now = trie[now][p[j]];
        }
        ++is[now];
        b[i] = now;
    }
    scanf("%s", p);
    lp = strlen(p);
    ans = 0;
    for (register int i = 0; i < lp; ++i) {
        p[i] -= 'a';
    }
    for (register int i = 0; i < lp; ++i) {
        no[i % 70] = 1;
        for (register int j = 0; j < 70; ++j) {
            if (!no[j]) {
                continue;
            }
            no[j] = trie[no[j]][p[i]];
            if (is[no[j]]) {
                ++a[no[j]];
                ans = std::max(ans, a[no[j]]);
            }
        }
    }
    printf("%d\n", ans);
    for (register int i = 1; i <= n; ++i) {
        cnt = 0;
        if (a[b[i]] == ans) {
            for (register int j = b[i]; j > 1; j = fa[j]) {
                p[++cnt] = t[j] + 'a';
            }
            for (register int j = cnt; j; --j) {
                printf("%c", p[j]);
            }
            printf("\n");
        }
    }
    return 0;
}