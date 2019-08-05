#include <bits/stdc++.h>
#include <conio.h>
int op(char*, char*);
int chcpinit();
int main(int n, char* a[]) {
    int f, flag = chcpinit();
    if (n == 2) {
<<<<<<< HEAD
        if (op(a[1], (char *)"-c")) {
=======
        if (op(a[1], (char*)"-c")) {
>>>>>>> 345b19d6521e4ab31d826845f178af65e26e9cfd
            system("del *.in /s");
            system("del *.out /s");
            system("del *.gch /s");
            system("del *.exe /s");
            system("del *.ans /s");
            system("del *.bak /s");
            system("del *.tmp /s");
            system("del *.o /s");
            system("rd tmp /s /q");
            return 0;
        }
<<<<<<< HEAD
        if (op(a[1], (char *)"-h")) {
            f = 1;
        }
    } else if (n == 3) {
        if (op(a[1], (char *)"-r")) {
=======
        if (op(a[1], (char*)"-h")) {
            f = 1;
        }
    } else if (n == 3) {
        if (op(a[1], (char*)"-r")) {
>>>>>>> 345b19d6521e4ab31d826845f178af65e26e9cfd
            std::string s = "g++ -o ";
            s = s + (std::string)a[2];
            s = s + (std::string)" ";
            s = s + (std::string)a[2];
            s = s + (std::string)".cpp -lm -O3";
            system(s.data());
            if (flag == 936) {
                printf("??????锟斤拷?\n");
            } else if (flag = 437) {
                printf("Complie is over.\n");
            }
            s = (std::string)a[2];
            system(s.data());
            if (flag == 936) {
                printf("???????????\n");
            } else if (flag == 437) {
                printf("The program is over.\n");
            }
            while (_kbhit()) {
                getchar();
            }
            if (flag == 936) {
                printf("???????????. . .");
            } else if (flag == 437) {
                printf("Press any key to continue . . .");
            }
            _getch();
            return 0;
<<<<<<< HEAD
        } else if (op(a[1], (char *)"-o")) {
=======
        } else if (op(a[1], (char*)"-o")) {
>>>>>>> 345b19d6521e4ab31d826845f178af65e26e9cfd
            std::string s = "g++ -o ";
            s = s + (std::string)a[2];
            s = s + (std::string)" ";
            s = s + (std::string)a[2];
            s = s + (std::string)".cpp -lm -O3";
            system(s.data());
            return 0;
        }
    }
    if (flag == 936) {
        if (!f) {
            puts("?????????????");
            puts("");
        }
        puts("kwcmd ???????? ?????windows??????????????code???????锟斤拷???");
        puts("\t?锟斤拷???v0.1.1");
        puts("\t?????keywet06");
        puts("");
        puts("??????????? ??-?? ???? ??/?? ????\\?? ???锟斤拷?");
        puts("\t$ -h ???????? ???????");
        puts("\t$ -c ???????? ????????????锟斤拷??????");
        puts("\t$ -o <C++??????> ???????? ???????C++????????? <C++??????> ?????? ??.cpp??");
        puts("\t$ -r <C++??????> ???????? ???????????C++????????? <C++??????> ?????? ??.cpp??");
    } else if (flag == 437) {
        if (!f) {
            puts("The command syntax is not right.");
            puts("");
        }
        puts("$ ---- A program that can help you to code");
        puts("\tVersion: v0.1.1");
        puts("\tWriter: keywet06");
        puts("");
        puts("Note: '-' in this program is not mixed with '/' and '\\'.");
        puts("\t$ -h ---- help information");
        puts("\t$ -c ---- clear all unnecessary files in this directory");
        puts("\t$ -o <cpp file name> ---- compile a C++ source code where <cpp file name> does not include \".cpp\"");
        puts("\t$ -c <cpp file name> ---- compile and run a C++ source code where <cpp file name> does not include \".cpp\"");
    }
    return 0;
}
inline int op(char *a, char *b) {
    if (strlen(a) != strlen(b)) {
        return 0;
    }
    int len = strlen(a);
    for (int i = 0; i < len; ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}
inline int chcpinit() {
    system("chcp > chcp.tmp");
    freopen("chcp.tmp", "r", stdin);
    std::string s;
    getline(std::cin, s);
    freopen("con", "r", stdin);
    system("del chcp.tmp");
    if (s == (std::string)"???????: 936") {
        return 936;
    }
    return 437;
}