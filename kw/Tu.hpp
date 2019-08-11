#ifndef KW_TU_HPP
#define KW_TU_HPP
// Head files
#ifndef STD_BITS_STDCPP_H
#define STD_BITS_STDCPP_H
#include <bits/stdc++.h>
#endif
// Class Definition
namespace kw {
    template<int PointNum, int EdgeNum, typename DataType> class Tu;
}
// Class Realization & Function Definition
namespace kw {
    template<int PointNum, int EdgeNum, typename DataType> class Tu {
        // Class Definition
        private:
            class edge;
        public:
            typedef edge* iterator;
        // Variable Definition
        private:
            edge ed[EdgeNum + 1];
            iterator cnt;
            iterator head[PointNum + 1];
        // Class Realization & Function Definition
        private:
            class edge {
                // Variable Definition
                public:
                    int to;
                    iterator next;
                    DataType data;
            };
        public:
            Tu();
            void clear();
            iterator GetHead(int);
            void insert(int, int, DataType);
            void addedge(int, int, DataType);
            void delinsert(int, int);
            void deledge(int, int);
            iterator GetIt(int, int);
    };
}
// Function Realization
namespace kw {
    template<int PointNum, int EdgeNum, typename DataType> inline Tu<PointNum, EdgeNum, DataType>::Tu() {
        memset(this->head, 0, sizeof(this->head));
        memset(this->ed, 0, sizeof(this->ed));
        this->cnt = this->ed;
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::clear() {
        memset(this->head, 0, sizeof(this->head));
        memset(this->ed, 0, sizeof(this->ed));
        this->cnt = this->ed;
    }
    template<int PointNum, int EdgeNum, typename DataType> inline typename Tu<PointNum, EdgeNum, DataType>::iterator Tu<PointNum, EdgeNum, DataType>::GetHead(int x) {
        return this->head[x];
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::insert(int x, int y, DataType z) {
        ++this->cnt;
        this->cnt->next = this->head[x];
        this->head[x] = this->cnt;
        this->cnt->to = y;
        this->cnt->data = z;
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::addedge(int x, int y, DataType z) {
        this->insert(x, y, z);
        this->insert(y, x, z);
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::delinsert(int x, int y) {
        while (this->GetHead(x) && this->GetHead(x)->to == y) {
            this->head[x] = this->GetHead(x)->next;
        }
        typename Tu<PointNum, EdgeNum, DataType>::iterator its = this->GetHead(x);
        for (typename Tu<PointNum, EdgeNum, DataType>::iterator it = this->GetHead(x); it;) {
            while (it && it->to == y) {
                its->next = it->next;
                it = it->next;
            }
            its = it;
            if (it) {
                it = it->next;
            }
        }
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::deledge(int x, int y) {
        this->delinsert(x, y);
        this->delinsert(y, x);
    }
    template<int PointNum, int EdgeNum, typename DataType> inline typename Tu<PointNum, EdgeNum, DataType>::iterator Tu<PointNum, EdgeNum, DataType>::GetIt(int x, int y) {
        typename Tu<PointNum, EdgeNum, DataType>::iterator it = 0;
        for (it = this->GetHead(x); it; it = it->next) {
            if (it->to == y) {
                return it;
            }
        }
        return it;
    }
}
#endif