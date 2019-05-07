#include <bits/stdc++.h>
double a, b, c, d;
double f(double x) {return ((a * x + b) * x + c) * x + d;}
int main() {
	std::cin >> a >> b >> c >> d;
	for (double i = -100; i < 100; i += 0.001)
		if (f(i) * f(i + 0.001) < 0) printf("%.2f ", i);
	printf("\n");
}
