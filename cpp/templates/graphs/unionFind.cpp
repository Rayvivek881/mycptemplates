#include <bits/stdc++.h>
using namespace std;
template <typename T>
class UnionFind {
public:
  int components;
  vector<T> parent, rank;
  UnionFind(int size) : components(size) {
    parent.resize(size + 1);
    rank.assign(size + 1, 0);
    for (int i = 0; i <= size; i++)
      parent[i] = i;
  }
  T find(T x) {
    if (parent[x] != x)
      parent[x] = find(parent[x]);
    return parent[x];
  }
  bool same(T a, T b) {
    return this->find(a) == this->find(b);
  }
  int size() { return components; }
  void Union(T a, T b) {
    a = find(a), b = find(b);
    if (a == b) return;
    components--;
    if (rank[a] < rank[b])
      parent[a] = b;
    else if (rank[a] > rank[b])
      parent[b] = a;
    else
      parent[b] = a, rank[a]++;
  }
};
int main(int argc, char const *argv[])
{
  int n, q;
  cin >> n >> q;
  UnionFind<int> obj(n);
  for (int i = 0; i < q; i++)
  {
    int f, a, b;
    cin >> f;
    cin >> a >> b;
    if (f == 1)
      obj.Union(a, b);
    else
      cout << (obj.find(a) == obj.find(b)) << endl;
  }
  return 0;
}
