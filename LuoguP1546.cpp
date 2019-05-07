/*
	By keywet06
	Data:2018/09/03
	Source:luogu(luogu.org)P1546
	Tittle:×î¶ÌÍøÂç Agri-Net
	Code-key:test
	Use:Dev-C++
*/
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<istream>
#include<iterator>
#include<list>
#include<map>
#include<ostream>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<string>
#include<vector>
using namespace std;
const int INF=1e8;
const int maxN=100;
int ans,mins,n,u;
int b[maxN+5],dist[maxN+5];
int f[maxN+5][maxN+5];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			scanf("%d",&f[i][j]);
			if(!f[i][j])
			{
				f[i][j]=INF;
			}
		}
	}
	b[1]=1;
	for(int i=1;i<=n;++i)
	{
		dist[i]=f[1][i];
	}
	for(int i=2;i<=n;++i)
	{
		mins=INF;
		u=0;
		for(int j=2;j<=n;++j)
		{
			if(!b[j]&&dist[j]<mins)
			{
				mins=dist[j];
				u=j;
			}
		}
		b[u]=1;
		ans+=mins;
		for(int j=2;j<=n;++j)
		{
			if(!b[j]&&f[u][j]<dist[j])
			{
				dist[j]=f[u][j];
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}

