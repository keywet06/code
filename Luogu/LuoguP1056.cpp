#include<cstdio>
#include<algorithm>
using namespace std;
const int n_MAX = 1000 + 5;
int m, n, k, l, d, x_1, x_2, y_1, y_2;
int ls[n_MAX], ks[n_MAX], f1[n_MAX], f2[n_MAX];
int cmp1(int x, int y)
{
	return ks[x] > ks[y];
}
int cmp2(int x, int y)
{
	return ls[x] > ls[y];
}
int main()
{
	scanf("%d %d %d %d %d", &m, &n, &k, &l ,&d);
	for (int i = 1; i <= d; ++i)
	{
		scanf("%d %d %d %d", &x_1, &y_1, &x_2, &y_2);
		if (x_1 == x_2)
		{
			++ks[min(y_1, y_2)];
		}
		else
		{
			++ls[min(x_1, x_2)];
		}
	}
	for (int i = 1; i <= m; ++i)
	{
		f1[i] = i;
	}
	for (int i = 1; i <= n; ++i)
	{
		f2[i] = i;
	}
	sort(f1 + 1, f1 + m + 1, cmp1);
	sort(f2 + 1, f2 + m + 1, cmp2);
	sort(f1 + 1, f1 + l + 1);
	sort(f2 + 1, f2 + k + 1);
	for(int i = 1; i < k; ++i)
	{
		printf("%d ", f2[i]);
	}
	printf("%d\n", f2[k]);
	for(int i = 1; i < l; ++i)
	{
		printf("%d ", f1[i]);
	}
	printf("%d\n", f1[l]);
	return 0;
}
