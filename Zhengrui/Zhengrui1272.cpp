#include <bits/stdc++.h>
const int Ni = 10;
const int Nip = Ni + 5;
const int mod = 998244353;
int T, n, a, b, c, d;
int f[Nip];
class matrix {
   private:
    long long data[2][2];
   public:
    matrix();
    long long *operator[](int i);
    friend matrix operator*(matrix x, matrix y);
    friend matrix operator^(matrix x, int y);
};
inline matrix::matrix() {};
inline long long *matrix::operator[](int i){ return data[i]; }
inline matrix operator*(matrix x, matrix y) {
    matrix ans;
    ans[0][0] = (x[0][0] * y[0][0] + x[0][1] * y[1][0]) % mod;
    ans[0][1] = (x[0][0] * y[0][1] + x[0][1] * y[1][1]) % mod;
    ans[1][0] = (x[1][0] * y[0][0] + x[1][1] * y[1][0]) % mod;
    ans[1][1] = (x[1][0] * y[0][1] + x[1][1] * y[1][1]) % mod;
    return ans;
}
inline matrix operator^(matrix x, int y) {
    return ;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i < Nip; ++i) {
        f[i] = f[i - 2] + f[i - 1];
    }
    std::cin >> T;
    while (T--) {
        std::cin >> n >> a >> b >> c >> d;
        if (n <= 10) {
            std::cout << std::__gcd(f[n] * a + f[n + 1] * b,
                                    f[n] * c + f[n + 1] * d)
                      << std::endl;
            continue;
        }
    }
    return 0;
}