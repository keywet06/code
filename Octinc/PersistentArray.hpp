#ifndef OCTINC_PERSISTENTARRAY_HPP
#  define OCTINC_PERSISTENTARRAY_HPP
#  ifndef BITS_STDCPP_H
#    define BITS_STDCPP_H
#    include <bits/stdc++.h>
#  endif
#  if __cplusplus < 201103L && !defined(nullptr)
#    define nullptr NULL
#  endif
namespace Octinc {
template <typename ValueType, size_t length>
  class PersistentArray {
   protected:
    class Node {
       public:
        Node *lson, *rson;
        ValueType value;
        Node();
    };
    std::vector<Node *> version;
    Node *NewNode(Node *&);
    ValueType &query(Node *, size_t, size_t, size_t);
   public:
    PersistentArray();
    ~PersistentArray();
    void clear();
    Node *NewVersion();
    Node *NewVersion(size_t);
    ValueType &operator[](size_t);
    ValueType &operator()(size_t, size_t);
    size_t getVersion();
};
} // namespace Octinc
namespace Octinc {
template <typename ValueType, size_t length>
  inline PersistentArray<ValueType, length>::Node::Node() {
    this->lson = this->rson = nullptr;
}
template <typename ValueType, size_t length>
  inline typename PersistentArray<ValueType, length>::Node
  *PersistentArray<ValueType, length>::NewVersion() {
    this->version.push_back(new Node);
    return &(*(this->version[this->version.size() - 1]) =
      *(this->version[this->version.size() - 2]));
}
template <typename ValueType, size_t length>
  inline typename PersistentArray<ValueType, length>::Node
  *PersistentArray<ValueType, length>::NewVersion(size_t v) {
    this->version.push_back(new Node);
    return &(*this->version[this->version.size() - 1] = *this->version[v]);
}
template <typename ValueType, size_t length>
  inline typename PersistentArray<ValueType, length>::Node
  *PersistentArray<ValueType, length>::NewNode(Node *&v) {
    return v ? v = &(*(new Node) = *v) : v = new Node;
}
template <typename ValueType, size_t length>
  inline ValueType &PersistentArray<ValueType, length>::query
  (Node *v, size_t x, size_t l, size_t r) {
    return l == r ? v->value : (x <= l + r >> 1 ?
      query(this->NewNode(v->lson), x, l, l + r >> 1) :
      query(this->NewNode(v->rson), x, (l + r >> 1) + 1, r));
}
template <typename ValueType, size_t length>
  inline PersistentArray<ValueType, length>::PersistentArray() {
    version.push_back(new Node);
}
template <typename ValueType, size_t length>
  inline PersistentArray<ValueType, length>::~PersistentArray() {
    this->clear();
}
template <typename ValueType, size_t length>
  inline void PersistentArray<ValueType, length>::clear() {
    std::set<Node *> set;
    std::queue<Node *> queue;
    for (size_t i = this->version.size() - 1; ~i; --i) {
        set.insert(this->version[i]);
        queue.push(this->version[i]);
    }
    this->version.clear();
    while (!queue.empty()) {
        Node *v = queue.front();
        queue.pop();
        if (v->lson && !set.count(v->lson)) {
            set.insert(v->lson);
            queue.push(v->lson);
        }
        if (v->rson && !set.count(v->rson)) {
            set.insert(v->rson);
            queue.push(v->rson);
        }
        delete v;
    }
}
template <typename ValueType, size_t length>
  inline ValueType &PersistentArray<ValueType, length>::operator[](size_t x) {
    ValueType &tmp = this->query(this->NewVersion(), x, 0, length - 1);
    return tmp;
}
template <typename ValueType, size_t length>
  inline ValueType &PersistentArray<ValueType, length>::operator()(size_t x, size_t y) {
    ValueType &tmp = this->query(this->NewVersion(x), y, 0, length - 1);
    return tmp;
}
template <typename ValueType, size_t length>
  inline size_t PersistentArray<ValueType, length>::getVersion() {
    return this->version.size() - 1;
}
} // namespace Octinc
#endif
