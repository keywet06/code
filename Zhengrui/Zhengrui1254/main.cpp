#include <bits/stdc++.h>
#include "maze.h"
// int get_edge_number()
// int get_coming_edge()
// int get_label()
// void set_label(int x)
// void move(int e)

const int N = 205;
const int M = 40005;
int n = 0;
int dis[N][N];
void dfs(int x);
inline void dfs(int x) {
	set_label(++n + 1);
	int c = get_coming_edge();
	for (int i = 1; i <= get_edge_number(); ++i) {
		if (i == c) {
			continue;
		}
		move(i);
		int k = get_coming_edge();
		if (get_label() != 1) {
			dis[x][get_label() - 1] = dis[get_label() - 1][x] = 1;
		} else {
			dfs(n + 1);
			dis[x][get_label() - 1] = dis[get_label() - 1][x] = 1;
		}
		move(k);
	}
}
std::vector<int> solve(int k, int lim) {
	memset(dis, 50, sizeof(dis));
	dfs(1);

	std::vector<int> answer(n);

	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			++answer[dis[i][j] - 1];
		}
	}

	return answer;
}
