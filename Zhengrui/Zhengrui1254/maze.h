#ifndef MAZE_H
#define MAZE_H

#include <vector>

std::vector<int> solve(int k, int lim);

int get_edge_number();
int get_coming_edge();
int get_label();
void set_label(int x);
void move(int e);

#endif
