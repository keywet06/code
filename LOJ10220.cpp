#include <bits/stdc++.h>
/*
 * A two-times-two matrix.
 */
class matrix {
	public:
		long long a[2][2];
		matrix();
		matrix(long long, long long, long long, long long);
};
matrix m1(1, 0, 0, 1), fi(1, 1, 1, 0);
long long n, mod;
matrix operator * (matrix, matrix);
matrix power(matrix, int);
/*
 * Use nothing to init the matrix.
 */
inline matrix::matrix() {
	a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0;
}
/*
 * Use four long long ints to init the matrix.
 */
inline matrix::matrix(long long a1, long long a2,
	long long b1, long long b2) {
	a[0][0] = a1;
	a[0][1] = a2;
	a[1][0] = b1;
	a[1][1] = b2;
}
/*
 * Return two matrix to times.
 */
inline matrix operator * (matrix x, matrix y) {
	matrix z;
	(z.a[0][0] = x.a[0][0] * y.a[0][0] + x.a[1][0] * y.a[0][1]) %= mod;
	(z.a[0][1] = x.a[0][1] * y.a[0][0] + x.a[1][1] * y.a[0][1]) %= mod;
	(z.a[1][0] = x.a[0][0] * y.a[1][0] + x.a[1][0] * y.a[1][1]) %= mod;
	(z.a[1][1] = x.a[0][1] * y.a[1][0] + x.a[1][1] * y.a[1][1]) %= mod;
	return z;
}
/*
 * Return $x^y$
 */
inline matrix power(matrix x, int y) {
	return y ? power(x * x, y / 2) * (y & 1 ? x : m1) : m1;
}
int main() {
	scanf("%lld %lld", &n, &mod);
	matrix m = power(fi, n - 1);
	printf("%lld\n", (m.a[1][0] + m.a[1][1]) % mod);
	return 0;
}
