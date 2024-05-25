#include<bits/stdc++.h>
using namespace std;

template<typename T, class func = function<T(const T &, const T &)>>
class prifix_queries {
  map<T, T> data;
  func myfunc;
public:
  prifix_queries(const func & F) : myfunc(F) {
    data.clear();
  }
  void insert(T a, T b) {
    auto it = data.lower_bound(a);
    if (it != data.begin() && myfunc(prev(it)->second, b) == prev(it)->second) return;
    it = data.insert(it, {a, b}), it->second = b;
    while (it != data.begin() && myfunc(prev(it)->second, it->second) == prev(it)->second)
      data.erase(prev(it));
  }
  T query(T a) {
    auto it = data.lower_bound(a);
    return it == data.begin() ? -1 : prev(it)->second;
  }
};