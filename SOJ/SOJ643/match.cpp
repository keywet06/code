#include "match.h"
#include <bits/stdc++.h>
const int N = 100005;
typedef long long int64;
typedef unsigned long long uint64;
uint64 seed;
int k;
uint64 next_int() {
	seed ^= seed >> 12;
	seed ^= seed << 25;
	seed ^= seed >> 27;
	return seed;
}
int64 randint(int64 l, int64 r) {
	return next_int() % (r - l + 1) + l;
}
std::map<int, int> map[N * 2];
int que(int l, int r) {
	return l < r ?
	  (map[l][r] ? map[l][r] - 1 : (map[l][r] = query(l, r) + 1) - 1) : 0;
}
std::vector<int> match(int n) {
	seed = time(NULL);
	std::vector<int> ret(n * 2);
	for (int i = 0; i < 2 * n; ++i) {
		ret[i] = -1;
	}
	for (int i = 0; i < 2 * n; ++i) {
		if (~ret[i]) {
			continue;
		}
		int l = i + 1, r = 2 * n - 1, mid;
		while (l < r) {
			mid = (r - l) < 170 ? randint(l, r - 1) : l + r >> 1;
			if (que(i, mid) != que(i + 1, mid)) {
				r = mid;
			} else {
				l = mid + 1;
			}
			++k;
		}
		ret[i] = l;
		ret[l] = i;
	}
	return ret;
}
