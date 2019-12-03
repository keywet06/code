#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int B = 3000;
const int S = 1000;
const int N = B * S;
int n;
char str[N + 5];
struct BlockList {
    int sz;
    char data[B + 5];
    int find(int pos) {
        return data[pos];
    }
    void insert(int pos, char c) {
        sz++;
        for (int i = sz; i > pos; i--) 
            data[i] = data[i - 1];
    	data[pos] = c;
    }
} block[S + 5];
void init() {
    int len = strlen(str);
    n = len / S + 1;
    for (int i = 0; str[i]; i++)
        block[i / S + 1].insert(block[i / S + 1].sz + 1, str[i]);
}
char Find(int pos) {
    int p = 1;
    while (block[p].sz < pos && p < n)
        pos -= block[p].sz, p++;
    return block[p].data[pos];
}
void Insert(int pos, int c) {
    int p = 1;
    while (block[p].sz < pos && p < n)
        pos -= block[p].sz, p++;
    block[p].insert(min(block[p].sz + 1, pos), c);
}
int main() {
    scanf(" %s", str);
    int m;
    scanf("%d", &m);
    init();
    while (m--) {
        char op;
        scanf(" %c", &op);
        if (op == 'I') {
            char c;
            int p;
            scanf(" %c%d", &c, &p);
            Insert(p, c);
        } else if (op == 'Q') {
            int p;
            scanf("%d", &p);
            printf("%c\n", Find(p));
        }
    }
    return 0;
}