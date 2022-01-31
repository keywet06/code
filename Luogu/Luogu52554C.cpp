#include <bits/stdc++.h>

int Query(int x);

void init() {}

std::pair<int, int> Guess(int n, int c) {
    int l = 1, r = n, q, Mid, Flag = true;
    while (true) {
        if (Flag) {
            int c = 0;
            while (1 << c + 1 <= n) ++c;
            Mid = 1 << c, Flag = false;
        } else {
            Mid = l + r >> 1;
        }
        if (!(q = Query(Mid))) break;
        if (q == -1) {
            l = Mid + 1;
        } else {
            r = Mid - 1;
        }
    }
    int cMid = Mid;
    int cl = l, cr = cMid;
    while (cl < cr) {
        Mid = cl + cr >> 1;
        if (Query(Mid) == -1) {
            cl = Mid + 1;
        } else {
            cr = Mid;
        }
    }
    int dl = cMid, dr = r;
    while (dl < dr) {
        Mid = dl + dr + 1 >> 1;
        if (Query(Mid) == 1) {
            dr = Mid - 1;
        } else {
            dl = Mid;
        }
    }
    return std::make_pair(cl, dr);
}