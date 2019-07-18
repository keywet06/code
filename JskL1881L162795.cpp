#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 1e5 + 5;
const int S = 316 + 5;
typedef long long ll;
ll a[N], sum[S], add[S];
int n, m, B;
int get(int x) {
    return (x + B -1) / B;
}
int main() {
    cin >> n >> m;
    B = sqrt(n);
    memset(a, 0, sizeof(a));
    memset(sum, 0, sizeof(sum));
    memset(add, 0, sizeof(add));
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[get(i)] += a[i];
    }
    while (m--) {
        int op, l, r, x;
        cin >> op >> l >> r;
        int idl = get(l), idr = get(r);
        if (op == 1) {
            cin >> x;
            if (idl == idr) {
                for (int i = l; i <= r; i++)
                    a[i] += x;
                sum[idl] += (r - l +1) * x;
            } else {
                for (int i = idl +1; i <= idr -1; i++)
                    add[i] += x;
                for (int i = l; i <= idl * B; i++)
                    a[i] += x;
                sum[idl] += (idl * B - l +1) * x;
                for (int i = (idr - 1) * B +1; i <= r; i++)
                    a[i] += x;
                sum[idr] += (r - (idr - 1) * B) * x;
            }
        } else if (op == 2) {
            ll ans = 0;
            if (idl == idr) {
                for (int i = l;i <= r; i++)
                    ans +=a[i] + add[idl] ;
            } else {
                for (int i = idl + 1; i <= idr - 1; i++)
                    ans += sum[i] + add[i] * B;
                for (int i = l; i <= idl * B; i++)
                    ans += a[i] + add[idl];
                for (int i = (idr -1) * B + 1; i <= r; i++)
                    ans += a[i] + add[idr];
            }
            cout << ans << endl;
        }
    }
    return 0;
}