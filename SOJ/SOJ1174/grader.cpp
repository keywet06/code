#include<bits/stdc++.h> 
#include"DAKLQW.h"

static std::mt19937 gen(114514 + (size_t) new char);
static const int mod0 = 10007;
static const int mod1 = 10009;
static const int mod2 = 10037;
static const int mod3 = 10039;
static bool v0[mod0], v1[mod1], v2[mod2], v3[mod3];
static inline bool getP(unsigned p){
	return v0[p % mod0] ^ v1[p % mod1] ^ v2[p % mod2] ^ v3[p % mod3];
}
static inline void init() {
	for(int i = 0;i < mod0;++i) v0[i] = gen() & 1;
	for(int i = 0;i < mod1;++i) v1[i] = gen() & 1;
	for(int i = 0;i < mod2;++i) v2[i] = gen() & 1;
	for(int i = 0;i < mod3;++i) v3[i] = gen() & 1;
}

static int S, T, call_cnt;
static inline void error(const char * ch) {
	puts(ch), exit(0);
}
char getpos(int pos) {
	if(pos < 1 || pos > S)
		error("invalid position");
	static const int limit = 1e7;
	if(++ call_cnt > limit)
		error("too many calls");
	return 48 + getP(pos);
}
int main() {
	using std::cin;
	using std::cout;
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> S >> T;
	for(int i = 1;i <= 100;++i) {
		init();
		int start_pos = gen() % (S - T + 1) + 1;
		std::string str, answer;
		for(int i = 0;i < T;++i) str += char(48 + getP(start_pos + i));
		int ans = xpptxdy(S, str);
		if(ans < 1 || ans + T - 1 > S) 
			error(("Wrong answer on test " + std::to_string(i)).c_str());
		for(int i = 0;i < T;++i) answer += char(48 + getP(ans + i));
		if(answer != str)
			error(("Wrong answer on test " + std::to_string(i)).c_str());
	}
	printf("%d\n", call_cnt);
} 
