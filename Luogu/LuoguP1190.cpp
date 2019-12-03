/*
    By keywet06
    Code-key:test
*/
#include <cstdio>
#include <iostream>
using namespace std;
const int m_MAX = 105;
int n, m, ans, maxn;
int a[m_MAX];
int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d", &a[i]);
	}
	for (int i = m + 1; i <= n;)
	{
		++ans;
		for (int j = 1; j <= m; ++j)
		{
			--a[j];
			if (a[j] == 0 && i <= n)
			{
				scanf("%d", &a[j]);
				++i;
			}
		}
	}
	for (int i = 1; i <= m; ++i)
	{
		maxn = max(maxn, a[i]);
	}
	ans += maxn;
	printf("%d\n", ans);
	return 0;
}
