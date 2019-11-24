#include <bits/stdc++.h>
namespace Octinc {
template <typename DataType = std::nullptr_t, typename ValueType = int,
  typename ValueGreater = std::greater<ValueType> >
  class Splay {
   public:
    class Point;
   public:
    class Point {
       public:
        Point *fa;
        Point *son[2];
        int size = 0, num = 0;
        ValueType val;
        DataType data;
        Point();
        Point(ValueType, DataType);
        ~Point();
    };
};
} // namespace Octinc
namespace Octinc {
template <typename DataType, typename ValueType, typename ValueGreater>
  Splay<DataType, ValueType, ValueGreater>::Point::Point() {
    this->fa = this->son[0] = this->son[2] = nullptr;
    this->size = this->data = 0;
}
template <typename DataType, typename ValueType, typename ValueGreater>
  Splay<DataType, ValueType, ValueGreater>::Point::Point
  (ValueType val, DataType data) {
    this->fa = this->son[0] = this->son[2] = nullptr;
    this->size = this->data = 0;
    this->val = val;
    this->data = data;
}
template <typename DataType, typename ValueType, typename ValueGreater>
  Splay<DataType, ValueType, ValueGreater>::Point::~Point() {
    this->fa = this->son[0] = this->son[2] = nullptr;
    this->size = this->data = 0;
}
} // namespcae Octinc
Octinc::Splay Splay;
int main() {

    return 0;
}