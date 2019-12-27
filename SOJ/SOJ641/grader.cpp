#include <bits/stdc++.h>
#include "sanae.h"

const int N = 10010;

int n;
int A[N], B[N], now[N];
int tot_call;
int MAX_CALL;

void bye(const char * buf) { printf("%s\n", buf), exit(0); }
int query(int i){
	if (tot_call == MAX_CALL) bye("To many calls");
	if(i <= 0 || i > n) bye("Invalid argument");
	int res = now[i];
	static int tmp[N];
	for (int i = 1; i <= n; ++i) tmp[B[i]] = now[i];
	memcpy(now, tmp, n + 1 << 2);
	++tot_call;
	return res;
}

int main(){
	assert(scanf("%d", &n) == 1);
	for (int i = 1; i <= n; ++i) assert(scanf("%d", A + i) == 1);
	memcpy(now, A, n + 1 << 2);
	for (int i = 1; i <= n; ++i) assert(scanf("%d", B + i) == 1);
	tot_call = 0; MAX_CALL = n * 10;
	std::vector<int> res(solve(n));
	if(res.size() != n) bye("Wrong size of the returned vector");
	int can = true;
	for(int i = 0; i < n; ++i) can &= A[i + 1] == res[i];
	if (!can) bye("Wrong answer\n");
	printf("%d\n", tot_call);
	return 0;
}
