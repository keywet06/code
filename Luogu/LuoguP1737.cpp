#include <bits/stdc++.h>
const char s[32][25] = {
    "\0",
    "4398046510884",
    "8796093021988",
    "17592186044196",
    "35184372088612",
    "70368744177444",
    "140737488355108",
    "281474976710436",
    "562949953421092",
    "1125899906842404",
    "2251799813685028",
    "4503599627370249",
    "9007199254740772",
    "18014398509481764",
    "36028797018963748",
    "72057594037927716",
    "144115188075855652",
    "288230376151711524",
    "576460752303423268",
    "1152921504606846756",
    "2305843009213693732",
    "4611686018427387684",
    "9223372036854775588",
    "18446744073709551396",
    "36893488147419103012",
    "73786976294838206244",
    "147573952589676412708",
    "295147905179352825636",
    "590295810358705651492",
    "1180591620717411303204",
    "2361183241434822606628",
    "4722366482869645213476",
};

class point {
   public:
    int t;
    point();
    point(int t);
    point(std::string str);
    friend point operator+(point a, point b);
    friend point operator+(point a, std::string b);
    friend point operator-(point a);
    friend point operator<<(point a, std::string b);
    friend point operator>>(point a, std::string b);
};

point I();
point O(point x);
point S(point x);

int cnt, n;
point p[1000];

inline point::point() {}
inline point::point(int x) { t = x; }
inline point::point(std::string str) {
    std::cout << "c 1 -1000000000000000" << std::endl;
    t = ++cnt;
}
inline point operator+(point a, point b) {
    std::cout << "+ " << a.t << " " << b.t << std::endl;
    return ++cnt;
}
inline point operator+(point a, std::string b) {
    std::cout << "C " << a.t << " " << b << std::endl;
    return ++cnt;
}
inline point operator-(point a) {
    std::cout << "- " << a.t << std::endl;
    return ++cnt;
}
inline point operator<<(point a, std::string b) {
    std::cout << "< " << a.t << " " << b << std::endl;
    return ++cnt;
}
inline point operator>>(point a, std::string b) {
    std::cout << "> " << a.t << " " << b << std::endl;
    return ++cnt;
}
inline point I() {
    std::cout << "I" << std::endl;
    return ++cnt;
}
inline point O(point x) {
    std::cout << "O " << x.t << std::endl;
    return ++cnt;
}
inline point S(point x) {
    std::cout << "S " << x.t << std::endl;
    return ++cnt;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    if (n == 1) {
        O(-((I() + I()) << "1"));
    } else if (n == 2) {
        O(S(-(((I()) << "4") + 1)));
    } else if (n == 3) {
        O((S(I() << "100") + "-0.5") << "1");
    } else if (n == 4) {
        point a = I(), p, y;
        p = S((a + "0.000000000000000000000000000001") << "500") << "152";
        y = S(p + (a >> "150"));
        O(a + (-(y + "-0.5") << "153") + p);
    } else if (n == 5) {
        for (int i = 1; i <= 32; ++i) {
            printf("I\n");
        }
        for (int i = 1; i <= 31; ++i) {
            printf("< %d %d\n", i, 32 - i);
        }
        printf("+ 63 32\n");
        for (int i = 64; i <= 93; ++i) {
            printf("+ %d %d\n", i, i - 31);
        }
        printf("O 94");
    } else if (n == 6) {
        printf("I\n");
        printf("< 1 41\n");
        for (int i = 3, j = 31; j >= 1; --j, i += 6) {
            printf("C %d -%s\n", i - 1, s[j]);
            printf("S %d\n", i);
            printf("O %d\n", i + 1);
            printf("- %d\n", i + 2);
            printf("< %d %d\n", i + 3, 41 + j);
            printf("+ %d %d\n", i + 4, i - 1);
        }
        printf("> 188 41\n");
        printf("O 189");
    } else if (n == 7) {
        printf("I\n");
        printf("I\n");
        printf("< 1 41\n");
        for (int i = 4, j = 31; j >= 1; --j, i += 5) {
            printf("C %d -%s\n", i - 1, s[j]);
            printf("S %d\n", i);
            printf("- %d\n", i + 1);
            printf("< %d %d\n", i + 2, 41 + j);
            printf("+ %d %d\n", i + 3, i - 1);
        }
        printf("> 158 41\n");
        printf("< 2 41\n");
        for (int i = 161, j = 31; j >= 1; --j, i += 5) {
            printf("C %d -%s\n", i - 1, s[j]);
            printf("S %d\n", i);
            printf("- %d\n", i + 1);
            printf("< %d %d\n", i + 2, 41 + j);
            printf("+ %d %d\n", i + 3, i - 1);
        }
        printf("> 315 41\n");
        for (int i = 5, j = 1; j <= 31; ++j, i += 5) {
            printf("+ %d %d\n", i, i + 157);
        }
        printf("+ 159 316\n");
        for (int i = 317, j = 1; j <= 32; ++j, ++i) {
            printf("C %d -1.5\n", i);
        }
        for (int i = 349, j = 1; j <= 32; ++j, ++i) {
            printf("< %d 41\n", i);
        }
        for (int i = 381, j = 1; j <= 32; ++j, ++i) {
            printf("S %d\n", i);
        }
        for (int i = 413, j = 1; j <= 32; ++j, ++i) {
            printf("< %d 1\n", i);
        }
        for (int i = 445, j = 1; j <= 32; ++j, ++i) {
            printf("- %d\n", i);
        }
        for (int i = 477, j = 1; j <= 32; ++j, ++i) {
            printf("+ %d %d\n", i, i - 160);
        }
        for (int i = 509, j = 31; j >= 1; --j, ++i) {
            printf("< %d %d\n", i, j);
        }
        for (int i = 540, j = 1; j <= 31; ++j, ++i) {
            printf("+ %d %d\n", i, i + 31);
        }
        printf("O 602\n");
    } else if (n == 8) {
        printf("I\n");
        printf("> 1 178\n");
        printf("C 2 2.0634370688955605467272811726201\n");
        printf("S 3\n");
        printf(
            "C 4 "
            "-0."
            "887298334620741688517926539978236773937633025540819832675154107295"
            "416657242528255923059519\n");
        printf("< 5 178\n");
        printf("O 6");
    } else if (n == 9) {
        int node[17], p = 16;
        for (int i = 1; i <= 16; i++) {
            puts("I"), node[i] = i;
        }
        for (int i = 1; i <= 15; i++) {
            for (int j = i + 1; j <= 16; j++) {
                printf("+ %d %d\n", node[i], node[j]);
                printf("- %d\n", node[j]);
                printf("+ %d %d\n", node[i], p + 2);
                printf("C %d 0.000000000000000000000000000001\n", p + 3);
                printf("< %d 200\n", p + 4);
                printf("S %d\n", p + 5);
                printf("< %d 200\n", p + 6);
                printf("> %d 199\n", p + 3);
                printf("+ %d %d\n", p + 7, p + 8);
                printf("S %d\n", p + 9);
                printf("< %d 1\n", p + 10);
                printf("- %d\n", p + 6);
                printf("+ %d %d\n", p + 11, p + 12);
                printf("C %d -1\n", p + 13);
                printf("< %d 200\n", p + 14);
                printf("- %d\n", p + 15);
                printf("+ %d %d\n", node[i], p + 16), node[i] = p + 17;
                printf("- %d\n", node[i]);
                printf("+ %d %d\n", p + 1, p + 18), node[j] = p + 19;
                p += 19;
            }
        }
        for (int i = 16; i >= 1; i--) {
            printf("O %d\n", node[i]);
        }
    } else {
        puts("I");
        puts("I");
        puts("I");
        puts("> 1 180");
        puts("< 2 180");
        for (int i = 31; i >= 1; i--) {
            std::stringstream s;
            s.precision(0);
            s << std::fixed << pow(2.0L, 180 + i);
            std::string ss = s.str();
            ss[25] = ss[26] = ss[27] = '0';
            int p = (32 - i) * 12 - 7;
            printf("C %d -%s\n", i == 31 ? 5 : p - 7, ss.c_str());
            printf("S %d\n", p + 1);
            printf("- %d\n", p + 2);
            printf("< %d %d\n", p + 3, 180 + i);
            printf("+ %d %d\n", i == 31 ? 5 : p - 7, p + 4);
            printf("C %d -1\n", p + 2);
            printf("< %d 180\n", p + 6);
            printf("+ %d %d\n", p + 7, 4);
            printf("S %d\n", p + 8);
            printf("< %d 1\n", p + 9);
            printf("+ %d %d\n", p + 10, p + 3);
            printf("< %d %d\n", p + 11, i + 181);
        }
        puts("> 370 180");
        puts("C 378 -1");
        puts("< 379 180");
        puts("+ 380 4");
        puts("S 381");
        puts("< 382 1");
        puts("- 378");
        puts("+ 383 384");
        puts("< 385 181");
        for (int i = 1; i <= 31; i++) {
            printf("+ %d %d\n", 385 + i, i * 12 + 5);
        }
        puts("> 3 200");
        puts("C 417 0.5");
        for (int i = 63; i >= 0; i--) {
            int p = (63 - i) * 15 + 419;
            printf("< 3 %d\n", i);
            printf("- %d\n", p + 1);
            printf("+ %d %d\n", p, p + 2);
            printf("< %d 500\n", p + 3);
            printf("S %d\n", p + 4);
            printf("C %d -1\n", p + 5);
            printf("< %d 500\n", p + 6);
            printf("+ %d 418\n", p + 7);
            printf("S %d\n", p + 8);
            printf("< %d 1\n", p + 9);
            printf("- %d\n", p + 5);
            printf("+ %d %d\n", p + 10, p + 11);
            printf("< %d %d\n", p + 12, i + 201);
            printf("- %d\n", p + 13);
            printf("+ %d %d\n", p, p + 14);
        }
        puts("C 1379 -0.5");
        puts("O 1380");
    }
    return 0;
}