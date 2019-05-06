/*
    By keywet06
    Code-key:test
*/
#include <cstdio>
using namespace std;
const int int_INF = 1000000000;
const int n_MAX = 2000 + 5;
int n, m;
int a[n_MAX][n_MAX], b[n_MAX][n_MAX], dp[n_MAX][n_MAX];
int fastread();
template <typename T> T max(T min_x, T min_y);
int main()
{
	n = fastread();
	m = fastread();
	for (int i = 1; i <= n; ++i)
	{
		b[i][0] = -int_INF;
		b[0][i] = -int_INF;
		for (int j = 1; j <= m; ++j)
		{
			a[i][j] = fastread();
			b[i][j] = -int_INF;
		}
	}
	b[1][1] = a[1][1];
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (!(i + j - 2))
			{
				continue;
			}
			b[i][j] = max(b[i - 1][j], b[i][j - 1]);
			dp[i][j] = b[i][j] + a[i][j];
			b[i][j] = max(b[i][j], dp[i][j]); 
		}
	}
	printf("%d\n", dp[n][m]);
	return 0;
}
int fastread()
{
	char fastread_ch;
	int fastread_x, fastread_f = 1;
	fastread_ch = getchar();
	while (fastread_ch < '0' || '9' < fastread_ch)
	{
		if (fastread_ch == '-')
		{
			fastread_f = -1;
			fastread_ch = getchar();
			break;
		}
		fastread_ch = getchar();
	}
	fastread_x = fastread_ch - '0';
	fastread_ch = getchar();
	while ('0' <= fastread_ch && fastread_ch <= '9')
	{
		fastread_x = (fastread_x << 3) + (fastread_x << 1) + fastread_ch - '0';
		fastread_ch = getchar();
	}
	return fastread_x * fastread_f;
}
template <typename T> T max(T min_x, T min_y)
{
	return min_x > min_y ? min_x : min_y;
}
