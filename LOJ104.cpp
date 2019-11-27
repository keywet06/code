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
        int size, num;
        ValueType value;
        DataType data;
       public:
        Point();
        Point(ValueType, DataType);
        ~Point();
        
    };
   public:
    Point *root = nullptr;
   private:
    void clearByPoint(Point *);
   public:
    Splay();
    ~Splay();
    void clear();
    int fason(Point *);
    void rotate(Point *);
    void insert(ValueType, DataType = nullptr);
};
} // namespace Octinc
namespace Octinc {
template <typename DataType, typename ValueType, typename ValueGreater>
  Splay<DataType, ValueType, ValueGreater>::Point::Point() {
    this->fa = this->son[0] = this->son[2] = nullptr;
    this->size = this->num = 1;
    this->value = NULL;
    this->data = nullptr;
}
template <typename DataType, typename ValueType, typename ValueGreater>
  Splay<DataType, ValueType, ValueGreater>::Point::Point
  (ValueType value, DataType data) {
    this->fa = this->son[0] = this->son[2] = nullptr;
    this->size = this->num = 1;
    this->value = value;
    this->data = data;
}
template <typename DataType, typename ValueType, typename ValueGreater>
  Splay<DataType, ValueType, ValueGreater>::Point::~Point() {
    this->fa = this->son[0] = this->son[2] = nullptr;
    this->size = this->num = 0;
}
template <typename DataType, typename ValueType, typename ValueGreater>
  void Splay<DataType, ValueType, ValueGreater>::clearByPoint
  (Splay<DataType, ValueType, ValueGreater>::Point *v) {
    if (v->son[0]) {
        this->clearByPoint(v->son[0]);
    }
    if (this->son[1]) {
        v->clearByPoint(v->son[1]);
    }
    delete v;
}
template <typename DataType, typename ValueType, typename ValueGreater>
  Splay<DataType, ValueType, ValueGreater>::Splay() {
    this->root = nullptr;
}
template <typename DataType, typename ValueType, typename ValueGreater>
  Splay<DataType, ValueType, ValueGreater>::~Splay() {
    this->clear();
}
template <typename DataType, typename ValueType, typename ValueGreater>
  void Splay<DataType, ValueType, ValueGreater>::clear() {
    this->clearByPoint(this->root);
    this->root = nullptr;
}
template <typename DataType, typename ValueType, typename ValueGreater>
  void Splay<DataType, ValueType, ValueGreater>::insert
  (ValueType value, DataType data) {
    if (!this->root) {
        this->root = new Point(value, data);
        return;
    }
    Point now = this->root;
    while (1) {
        if (ValueGreater(value, now->value)) {
            if (!now->son[0]) {
                break;
            }
            now = now->son[0];
        } else if (ValueGreater(now->value, value)) {
            if (!now->son[1]) {
                break;
            }
            now = now->son[1];
        } else {
            ++now->num;
            ++now->size;
            return;
        }
    }
    now->son[ValueGreater(value, now->value)] = new Point(value, data);
    now = now->son[ValueGreater(value, now->value)];
    this->splay(now);
}
} // namespcae Octinc
Octinc::Splay Splay;
int main() {
    
    return 0;
}