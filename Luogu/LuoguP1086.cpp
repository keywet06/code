#include <cstdio>
#include <algorithm>
using namespace std;
class point
{
  public:
    int x, y, z;
};
int n, m, k, x, cnt, ans;
point a[505];
int cmp(point, point);
int main()
{
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &x);
            if (x)
            {
                ++cnt;
                a[cnt].x = i;
                a[cnt].y = j;
                a[cnt].z = x;
            }
        }
    }
    sort(a + 1, a + cnt + 1, cmp);
    if (k < 2 * a[1].x + 1)
    {
        puts("0");
        return 0;
    }
    k -= a[1].x + 1;
    ans = a[1].z;
    for (int i = 2; i <= cnt; ++i)
    {
        if (k < abs(a[i].x - a[i - 1].x) + abs(a[i].y - a[i - 1].y) + a[i].x + 1)
        {
            printf("%d\n", ans);
            return 0;
        }
        k -= abs(a[i].x - a[i - 1].x) + abs(a[i].y - a[i - 1].y) + 1;
        ans += a[i].z;
    }
    printf("%d\n", ans);
    return 0;
}
int cmp(point cmp_x, point cmp_y)
{ 
    return cmp_x.z > cmp_y.z;
}
