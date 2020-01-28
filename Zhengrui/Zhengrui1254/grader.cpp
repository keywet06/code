#include "maze.h"

#include <iostream>
#include <cassert>
int _K, _L, _current_node, _move_count;
int _edge[705][705], _label[705], _coming_edge = -1;
std::vector<int> _adj[705];
int get_edge_number() { return _adj[_current_node].size(); }
int get_coming_edge() { return _coming_edge; }
int get_label() { return _label[_current_node] + 1; }
void set_label(int x)
{
	assert(x > 0 && x <= _K);
	_label[_current_node] = x - 1;
}
void move(int e)
{
	assert(++_move_count <= _L);
	assert(e > 0 && e <= get_edge_number());
	int v = _adj[_current_node][e - 1];
	_coming_edge = _edge[v][_current_node];
	_current_node = v;
}
int main()
{
	int n, m;
	std::cin >> n >> m >> _K >> _L;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		std::cin >> u >> v;
		u--;
		v--;
		_adj[u].push_back(v);
		_adj[v].push_back(u);
		_edge[u][v] = _adj[u].size();
		_edge[v][u] = _adj[v].size();
	}
	std::cin >> _current_node;
	_current_node--;
	auto ans = solve(_K, _L);
	std::cout << _move_count << std::endl;
	for (int i = 0; i < ans.size(); i++)
		std::cout << ans[i] << " \n"[i + 1 == ans.size()];
	return 0;
}
