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
#include <cstdio>
#include <queue>
#include <ext/hash_map>
#include <cmath>
#ifndef KW_POINT_HPP
#define KW_POINT_HPP
// Class Definition
template<typename DataType> class point;
// Class Realization & Function Definition
template<typename DataType> class point {
    // Variable Definition
    public:
        DataType x, y;
};
template<typename DataType> int operator < (point<DataType>, point<DataType>);
template<typename DataType> int operator == (point<DataType>, point<DataType>);
template<typename DataType> point<DataType> operator + (point<DataType>, point<DataType>);
template<typename DataType> point<DataType> &operator += (point<DataType>&, point<DataType>);
template<typename DataType> DataType dist(point<DataType>, point<DataType>);
// Function Realization
template<typename DataType> inline int operator < (point<DataType> x, point<DataType> y) {
    return x.x != y.x ? x.x < y.x : x.y < y.y;
}
template<typename DataType> inline int operator == (point<DataType> x, point<DataType> y) {
    return x.x == y.x && x.y == y.y;
}
template<typename DataType> inline point<DataType> operator + (point<DataType> x, point<DataType> y) {
    point<DataType> tmp;
    tmp.x = x.x + y.x;
    tmp.y = x.y + y.y;
    return tmp;
}
template<typename DataType> inline point<DataType> &operator += (point<DataType>& x, point<DataType> y) {
    return x = x + y;
}
template<typename DataType> inline DataType dist(point<DataType> x, point<DataType> y) {
    return std::abs(x.x - y.x) * std::abs(x.x - y.x) + std::abs(x.y - y.y) * std::abs(x.y - y.y);
}
#endif
namespace __gnu_cxx {
    template<> struct hash<point<long long> > {
        inline size_t operator()(point<long long> x) const {
            return x.x + (x.y) << 32;
        }
    };
}
const int lx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int ly[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
point<long long> x, y;
double dis, la, lb, lc;
long long cnt, mpv, i;
long long *it;
int (*check)(point<long long>);
__gnu_cxx::hash_map<point<long long>, long long> map;
std::queue<point<long long> > queue;
double sqr(double);
int check1(point<long long>);
int check2(point<long long>);
int main() {
    register point<long long> n, v;
    scanf("%lld %lld %lld %lld", &x.x, &x.y, &y.x, &y.y);
    la = x.y - y.y;
    lb = y.x - x.x;
    check = la < 100 && lb < 100 ? check2 : check1;
    lc = x.x * y.y - x.y * y.x;
    dis = sqr(sqrt(dist(x, y)) + 5);
    map[x] = 1;
    queue.push(x);
    while (!queue.empty()) {
        v = queue.front();
        queue.pop();
        mpv = map[v];
        ++cnt;
        for (i = 0; i < 8; ++i) {
            n.x = v.x + lx[i];
            n.y = v.y + ly[i];
            if (!check(n) || *(it = &map[n])) {
                continue;
            }
            if (n == y) {
                printf("%lld\n", mpv);
                return 0;
            }
            queue.push(n);
            *it = mpv + 1;
        }
    }
    return 0;
}
inline double sqr(double x) {
    return x * x;
}
inline int check1(point<long long> a) {
    return dist(a, x) <= dis && dist(a, y) <= dis && (sqr(std::abs(la * a.x + lb * a.y + lc))) <= sqr(la) + sqr(lb);
}
inline int check2(point<long long> a) {
    return dist(a, x) <= dis && dist(a, y) <= dis && sqr(std::abs(la * a.x + lb * a.y + lc)) <= 25 * (sqr(la) + sqr(lb));
}