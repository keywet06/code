#include <bits/stdc++.h>
#include <conio.h>
int op(char*, char*);
int main(int n, char* a[]) {
    int f = 0;
    if (n == 2) {
        if (op(a[1], (char*)"clear")) {
            system("rm -rf *.in /s");
            system("rm -rf *.out /s");
            system("rm -rf *.gch /s");
            system("rm -rf *.exe /s");
            system("rm -rf *.ans /s");
            system("rm -rf *.bak /s");
            system("rm -rf *.tmp /s");
            system("rm -rf *.o /s");
            system("rm -rf tmp /s /q");
            return 0;
        }
        if (op(a[1], (char*)"help")) {
            f = 1;
        }
    } else if (n == 3) {
        if (op(a[1], (char*)"run")) {
            std::string s = (std::string)"g++ -o " + (std::string)a[2] + (std::string)" " + (std::string)a[2] + (std::string)".cpp -lm -O3";
            system(s.data());
            printf("Complie is over.\n");
            s = (std::string)a[2];
            system(s.data());
            printf("The program is over.\n");
            while (_kbhit()) {
                getchar();
            }
            printf("Press any key to continue . . .");
            _getch();
            return 0;
        } else if (op(a[1], (char*)"compile")) {
            std::string s = (std::string)"g++ -o " + (std::string)a[2] + (std::string)" " + (std::string)a[2] + (std::string)".cpp -lm -O3";
            system(s.data());
            return 0;
        }
    }
    if (!f) {
        puts("The command syntax is not right.");
        puts("");
    }
    puts("$ ---- A program that can help you to code");
    puts("\tVersion: v0.1.3");
    puts("\tWriter: keywet06");
    puts("");
    puts("Help infomation");
    puts("\t$ help ---- help information");
    puts("\t$ clear ---- clear all unnecessary files in this directory");
    puts("\t$ run <cpp file name> ---- compile a C++ source code where <cpp file name> does not include \".cpp\"");
    puts("\t$ compile <cpp file name> ---- compile and run a C++ source code where <cpp file name> does not include \".cpp\"");
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