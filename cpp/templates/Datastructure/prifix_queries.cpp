#include<bits/stdc++.h>
using namespace std;

template<typename T, class func = function<T(const T &, const T &)>>
class prefix_queries {
  map<T, T> data;
  func myfunc;
public:
  prefix_queries(const func & F) : myfunc(F) {
    data.clear();
  }
  void insert(T a, T b) {
    auto it = data.upper_bound(a);
    if (it != data.begin() && myfunc(prev(it)->second, b) == prev(it)->second) return;
    it = data.insert(it, {a, b}), it->second = b;
    while (next(it) != data.end() && myfunc(it->second, next(it)->second) == it->second)
      data.erase(next(it));
  }
  T query(T a) {
    auto it = data.upper_bound(a);
    return it == data.begin() ? 0 : prev(it)->second;
  }
};