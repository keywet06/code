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
        this->Tu();
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
}
#endif