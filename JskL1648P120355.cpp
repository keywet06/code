/*
    By keywet06
    Code-key:test
*/
#include <cstdio>
#include <algorithm>
using namespace std;
int n, q, x, l, r, mid;
int a[100005];
int read();
int main()
{
	n = read() * 2;
	for (int i = 1; i <= n; ++i)
	{
		a[i] = read();
	}
	sort(a + 1, a + n + 1);
	a[n + 1] = 1000000000;
	q = read();
	for (int i = 1; i <= q; ++i)
	{
		x = read();
		l = 0;
		r = n + 1;
		while (l < r)
		{
			mid = (l + r) / 2;
			if (x <= a[mid])
			{
				r = mid;
			}
			else
			{
				l = mid + 1;
			}
		}
		while (a[l] < x)
		{
			++l;
		}
		while (a[l] > x)
		{
			--l;
		}
		if (l % 2)
		{
			printf("yes ");
		}
		else
		{
			if (a[l] == x && l)
			{
				printf("yes ");
			}
			else
			{
				printf("no ");
			}
		}
	}
	return 0;
}
int read()
{
	int read_x = getchar(), read_y;
	while (read_x < '0' || '9' < read_x)
	{
		read_x = getchar();
	}
	read_x -= 48;
	while ('0' <= (read_y = getchar()) && read_y <= '9')
	{
		read_x *= 10;
		read_x += read_y - 48;
	}
	return read_x;
}
