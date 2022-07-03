#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int32 = int;
using int64 = long long;
using lint64 = long;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using ulint64 = unsigned long;

namespace Oct {

template <typename Type, size_t Size>
class Pool {
   protected:
    size_t Top;
    Type Data[Size];

   public:
    inline Pool(size_t StartTop = 0, bool Clear = true, int ClearVal = 0, size_t ClearSize = sizeof(Type) * Size) {
        Top = StartTop;
        if (Clear) memset(Data, ClearVal, ClearSize);
    }
    inline Pool(Type InitializeData, size_t ClearNumber = Size, size_t StartTop = 0) {
        Top = StartTop;
        for (int i = 0; i < ClearNumber; ++i) Data[i] = InitializeData;
    }

    inline size_t Now() { return Top; }
    inline size_t New() { return ++Top; }

    inline Type &operator[](size_t i) { return Data[i]; }
};

}  // namespace Oct

const int Z = 100;  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

struct SplayNode;

Oct::Pool<SplayNode, Z> Tr;

struct SplayNodePtr {
    int i;
    inline SplayNodePtr(int ci = 0) : i(ci) {}
    inline SplayNodePtr(SplayNode *cPtr) : i(cPtr - &Tr[0]) {}
    inline operator bool() { return bool(i); }
    inline SplayNode *operator->() { return &Tr[i]; }
    inline SplayNode *Ptr() { return &Tr[i]; }
};

inline bool operator==(SplayNodePtr a, SplayNodePtr b) { return a.i == b.i; }

struct SplayNode {
    SplayNodePtr Fa, Son[2];
    int Sum;
    inline SplayNode(int cFa = 0, int cSonl = 0, int cSonr = 0, int cSum = 1)
        : Fa(cFa), Son({cSonl, cSonr}), Sum(cSum) {}
    inline void PushUp() { Sum = Son[0]->Sum + Son[1]->Sum + 1; }
    inline int GetDir() { return Fa->Son[1] == this; }
    inline void Rotate() {
        int c = GetDir(), d = !c, p = Fa->GetDir();
        if (Fa->Son[c] = Son[d]) Son[d]->Fa = Fa;
        if (Fa = (Son[d] = Fa)->Fa) Fa->Son[p] = this;
        Son[d]->Fa = this;
    }
    inline void Splay() {
        
    }
};

inline SplayNodePtr Tree(int u) { return u; }

struct Solver {
    SplayNodePtr Root;

    inline int GetDir(SplayNodePtr u) { return u->Fa->Son[1] == u; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    return 0;
}