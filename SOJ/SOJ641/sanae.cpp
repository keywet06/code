#include <bits/stdc++.h>
#include "sanae.h"

std::vector<int> solve(int n){
	std::vector<int> res;
	for (int i = 1; i <= n; ++i) {
		int t;
		for (int j = 1; j <= 10; ++j)
			t = query(i);
		res.push_back(t);
	}
	return res;
}
