#include <bits/stdc++.h>
#include "sanae.h"
std::vector<int> solve(int n) {
    int cnt = -1, x, sti, fir;
    std::vector<int> ans(n);
    ++n;
    std::vector<int> vis(n), number(n), start(n), longs(n), ps(n);
    std::vector<int> list[n];
    --n;
    for (int i = 1; i <= n; ++i) {
        fir = x = query(i);
        #ifndef ONLINE_JUDGE
        std::cerr << "query " << i << " get " << x << "." << std::endl;
        #endif
        list[fir].push_back(fir);
        sti = ++cnt;
        if (vis[x]) {
            int len = longs[start[x]];
            #ifndef ONLINE_JUDGE
            std::cerr << x << " " << len << " " << number[x] << " "
             << cnt << " " << ps[x] << std::endl;
            #endif
            ans[i - 1] = 
              list[start[x]][(len * 2 - cnt % len + longs[fir] - ps[fir] - 1) % len];
            continue;
        }
        do {
            vis[x] = 1;
            start[x] = fir;
            ps[x] = sti;
            number[x] = cnt - sti;
            list[fir].push_back(x = query(i));
            #ifndef ONLINE_JUDGE
            std::cerr << "query " << i << " get " << x << "." << std::endl;
            #endif
            ++cnt;
        } while (x != fir);
        int len = longs[fir] = list[fir].size() - 1;
        #ifndef ONLINE_JUDGE
        std::cerr << sti << " " << longs[fir] << std::endl;
        #endif
        x = fir;
        ans[i - 1] = 
          list[start[x]][(len * 2 - sti % len + longs[fir] - ps[fir] - 1) % len];
    }
    for (int i = 0; i < n; ++i) {
        #ifndef ONLINE_JUDGE
        std::cerr << ans[i] << " ";
        #endif
    }
    #ifndef ONLINE_JUDGE
    std::cerr << std::endl;
    #endif
    return ans;
}