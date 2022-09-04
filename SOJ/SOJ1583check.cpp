#include "testlib.h"
using std::vector;

int n, m;
vector<int> a, ks;

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);

	int i;
	n = inf.readInt();
	a = inf.readInts(n);

	m = ouf.readInt(0, 3 * n, "m");
	ks = ouf.readInts(m, 1, n, "k");

	for (const int k : ks) {
		std::reverse(a.begin(), a.begin() + k);
		for (i = 0; i < k; ++i) a[i] = -a[i];
	}

	for (i = 0; i < n && a[i] == i + 1; ++i);
	ouf.ensuref(i == n, "the final deck is not sorted and : a[%d] = %d", i + 1, a[i]);

	if (m <= 2 * n) ouf.quitf(_ok, "%d operations", m);
	else if (10 * m <= 22 * n) quitp(.8, "%d operations", m);
	else if (10 * m <= 24 * n) quitp(.7, "%d operations", m);
	else if (10 * m <= 27 * n) quitp(.6, "%d operations", m);
	else quitp(.5, "%d operations", m);

	return 0;
}
