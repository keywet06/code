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
    inline void Del(Type ClearData = Type()) { Data[Top--] = ClearData; }

    inline Type &operator[](size_t i) { return Data[i]; }
};

}  // namespace Oct

const int Z = 100;  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

struct SplayNode;

extern Oct::Pool<SplayNode, Z> Tr;

struct SplayNode {
    struct Ptr {
        int i;
        inline Ptr(int ci = 0) : i(ci) {}
        inline Ptr(SplayNode *cPtr) : i(cPtr - &Tr[0]) {}
        inline operator bool() { return bool(i); }
        inline SplayNode *operator->() { return &Tr[i]; }
        inline explicit operator SplayNode *() { return &Tr[i]; }
        inline bool operator==(Ptr b) { return i == b.i; }
        inline SplayNode &operator&() { return Tr[i]; }
    };
    Ptr Fa, Son[2];
    int Sum, Val;
    inline SplayNode(int cVal = 0, int cFa = 0, int cSonl = 0, int cSonr = 0, int cSum = 1)
        : Fa(cFa), Son({cSonl, cSonr}), Sum(cSum) {}
    inline void PushUp() { Sum = Son[0]->Sum + Son[1]->Sum + 1; }
    inline int GetDir() { return Fa->Son[1] == this; }
    inline void Rotate() {
        int c = GetDir(), d = !c, p = Fa->GetDir();
        if (Fa->Son[c] = Son[d]) Son[d]->Fa = Fa;
        if (Fa = (Son[d] = Fa)->Fa) Fa->Son[p] = this;
        Son[d]->Fa = this;
        Son[d]->PushUp(), PushUp();
    }
    inline void Splay() {
        PushUp();
        for (; Fa; Rotate()) {
            if (Fa->Fa) GetDir() == Fa->GetDir() ? Fa->Rotate() : Rotate();
        }
    }
};

Oct::Pool<SplayNode, Z> Tr;

struct Solver {
    SplayNode::Ptr Root;
    inline void Splay(SplayNode::Ptr u) { u->Splay(), Root = u; }
    inline SplayNode::Ptr InsertNode(int x) {
        SplayNode::Ptr u = Tr.New();
        &u = SplayNode(x);
        if (!Root) return Root = u;
        SplayNode::Ptr c = Root;
        while (true) {
            int Dir = x > c->Val;
            if (c->Son[Dir]) {
                c = c->Son[Dir];
            } else {
                c->Son[Dir] = u;
                break;
            }
        }
        return Splay(u), u;
    }
    inline int Insert(int x) {
        auto u = InsertNode(-x);
        int Ans = u->Son[1]->Sum + 1;
        if (!u->Son[0]) return (Root = u->Son[1])->Fa = 0, Tr.Del(), Ans;
        for (u = u->Son[0]; u->Son[1];) u = u->Son[1];
        u->Son[1] = Root->Son[1], (Root = Root->Son[0])->Fa = 0;
        if (u->Son[1]) u->Son[1]->Fa = u, Splay(u->Son[1]);
        return Splay(u->Son[1]), Tr.Del(), Ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    return 0;
}