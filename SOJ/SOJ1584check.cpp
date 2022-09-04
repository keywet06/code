#include "testlib.h"
using std::vector;

const int N = 200054;

int n, r, m, ref;
int count[N];

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);

	int i, u, v;
	n = inf.readInt(), ref = ans.readInt();
	std::fill(count + 1, count + (n + 1), 1);

	r = ouf.readInt(-1, ref, "r");
	if (r == -1) {
		if (ref == -1) ouf.quit(_ok, "no solution");
		else ouf.quit(_wa, "you didn't find the solution while jury did");
		return 0;
	}

	m = ouf.readInt(0, 500000, "m");
	for (i = 0; i < m; ++i) {
		u = ouf.readInt();
		ouf.ensuref(0 <= u && u < N && count[u], "There is no number %d at the beginning of the %d%s operation", u, i + 1, englishEnding(i + 1).c_str());
		v = ouf.readInt();
		ouf.ensuref(0 <= v && v < N && count[v], "There is no number %d at the beginning of the %d%s operation", v, i + 1, englishEnding(i + 1).c_str());
		if (u == v)
			ouf.ensuref(count[u] > 1, "The number of numbers %d is less than 2 at the beginning of the %d%s operation", u, i + 1, englishEnding(i + 1).c_str());
		ouf.ensuref(u <= v, "x (%d) > y (%d) in the %d%s operation", u, v, i + 1, englishEnding(i + 1).c_str());
		ouf.ensuref(u + v <= r, "x + y [equals to %d] is greater than r [equals to %d] after the %d%s operation", u + v, r, i + 1, englishEnding(i + 1).c_str());
		--count[u], --count[v], ++count[v - u], ++count[v + u];
	}

	if (count[r] == n) ouf.quitf(_ok, "%d operations", m);
	ouf.quit(_wa, "Not all numbers are equal in the end");

	return 0;
}
