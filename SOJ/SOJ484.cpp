#include <cstdio>
#include <algorithm>
#define int long long
int n,m,x,y,z,maxx=-1e18;
signed main()
{
	scanf("%lld%lld",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&z);
		maxx=std::max(maxx,z);
	}
	if (maxx==-1e18) maxx=0;
	printf("%lld\n",maxx*maxx);
	return 0;
}