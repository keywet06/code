#include <bits/stdc++.h>
int op(char*, char*);
int main(int n, char* a[]) {
    int f;
    if (n == 2) {
        if (op(a[1], "clear")) {
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
        if (op(a[1], "-h")) {
            f = 1;
        }
    } else if (n == 3) {
        if (op(a[1], "-c")) {
            std::string s = "g++ -o ";
            s = s + (std::string)a[2];
            s = s + (std::string)" ";
            s = s + (std::string)a[2];
            s = s + (std::string)".cpp -lm";
            system(s.data());
            return 0;
        }
    }
    system("chcp > chcp.tmp");
    freopen("chcp.tmp", "r", stdin);
    std::string s;
    getline(std::cin, s);
    freopen("con", "r", stdin);
    system("del chcp.tmp");
    if (s == (std::string)"�����ҳ: 936") {
        if (!f) {
            puts("�����﷨����ȷ��");
            puts("");
        }
        puts("kwcmd �������� һ����windows�����¿��ٰ�����code�������г���");
        puts("\t�汾�ţ�v0.1.0");
        puts("\t���ߣ�keywet06");
        puts("");
        puts("ע�⣺�������� ��-�� ���� ��/�� ����\\�� ���á�");
        puts("\t$ -h �������� ������Ϣ");
        puts("\t$ clear �������� �����Ŀ¼�����ж����ļ�");
        puts("\t$ -c <C++Դ�ļ���> �������� ����һ��C++Դ���룬���� <C++Դ�ļ���> ������ ��.cpp��");
    } else {
        if (!f) {
            puts("The command syntax is not right.");
            puts("");
        }
        puts("$ ---- A program that can help you to code");
        puts("\tWriter: keywet06");
        puts("");
        puts("Note: '-' in this program is not mixed with '/' and '\\'.");
        puts("\t$ -h ---- help information");
        puts("\t$ clear ---- clear all unnecessary files in this directory");
        puts("\t$ -c <cpp file name> ---- compile a C++ source code where <cpp file name> does not include \".cpp\"");
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