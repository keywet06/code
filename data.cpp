#include <bits/stdc++.h>
int main() {
	srand(time(NULL));
	printf("10 30 10000\n");
	int n = 10, m = 30, x = 0, y;
	for (int i = 1; i <= n; ++i) printf("%d ", rand() % (10));
	printf("\n");
	for (int i = 1; i <= m; ++i) {
		x = rand() % 3 + 1;
		y = x;
		std::cout << x << " ";
		std::cout << (x = (rand() % (n - 1) + 1));
		std::cout << " " << x + rand() % (n - x);
		if (y < 3) std::cout << " " << rand() % (10) << "\n";
		else std::cout << "\n";
	}
}
