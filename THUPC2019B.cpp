#include <bits/stdc++.h>
int a1, a2, a3, a4, n, size, x, y;
std::queue<int> p1;
std::stack<int> p2;
std::priority_queue<int> p3;
std::priority_queue<int, std::vector<int>, std::greater<int> > p4;
int main() {
    scanf("%d", &n);
    a1 = a2 = a3 = a4 = 1;
    while (n--) {
        scanf("%d %d", &x, &y);
        if (x == 1) {
            ++size;
            p1.push(y);
            p2.push(y);
            p3.push(y);
            p4.push(y);
        }
        if (x == 2) {
            if (size == 0) {
                puts("No");
                puts("No");
                puts("No");
                puts("No");
                return 0;
            }
            --size;
            if (p1.front() != y) {
                a1 = 0;
            }
            if (p2.top() != y) {
                a2 = 0;
            }
            if (p3.top() != y) {
                a3 = 0;
            }
            if (p4.top() != y) {
                a4 = 0;
            }
            p1.pop();
            p2.pop();
            p3.pop();
            p4.pop();
        }
    }
    if (a1) {
        puts("Yes");
    } else {
        puts("No");
    }
    if (a2) {
        puts("Yes");
    } else {
        puts("No");
    }
    if (a3) {
        puts("Yes");
    } else {
        puts("No");
    }
    if (a4) {
        puts("Yes");
    } else {
        puts("No");
    }
    return 0;
}