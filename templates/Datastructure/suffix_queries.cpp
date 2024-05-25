#include<bits/stdc++.h>
using namespace std;

template<typename T, class func = function<T(const T &, const T &)>>
class suffix_queries {
  map<T, T> data;
  func myfunc;
public:
  suffix_queries(const func & F) : myfunc(F) {
    data.clear();
  }
  void insert(T a, T b) {
    auto it = data.lower_bound(a);
    if (it != data.end() && myfunc(it->second, b) == it->second) return;
    it = data.insert(it, {a, b}), it->second = b;
    while (next(it) != data.end() && myfunc(it->second, next(it)->second) == it->second)
      data.erase(next(it));
  }
  T query(T a) {
    auto it = data.lower_bound(a);
    return it == data.end() ? -1 : it->second;
  }
};