#include<bits/stdc++.h>
using namespace std;
template <typename T>
class UnionFind {
public:
  int Components;
  vector<T> parent, rank, Arr;
  UnionFind(int size) : Components(size) {
    parent.resize(size), rank.assign(size, 0);
    Arr.assign(size, 0);
    for (int i = 0; i < size; i++)
      parent[i] = Arr[i] = i;
  }
  T find(T x) {
    if (parent[x] != x)
      parent[x] = find(parent[x]);
    return parent[x];
  }
  int getValue(T a) { return Arr[find(a)]; }
  void Union(T a, T b, T value) {
    T aset = find(a), bset = find(b), curr;
    if (aset == bset) return;
    Components--;
    if (rank[aset] < rank[bset])
      curr = parent[aset] = bset;
    else if (rank[aset] > rank[bset])
      curr = parent[bset] = aset;
    else curr = parent[bset] = aset, rank[aset]++;
    Arr[curr] = value;
  }
};
int main(int argc, char const *argv[]) {
  int n, q, x; cin >> n >> q;
  vector<vector<int>> Graph(n + 1);
  vector<vector<pair<int, int>>> queries(n + 1);
  vector<int> result(q), visited(n + 1, 0);
  UnionFind<int> LCA(n + 1);
  for (int i = 2; i <= n; i += 1) {
    cin >> x;
    Graph[x].push_back(i);
    Graph[i].push_back(x);
  }
  for (int i = 0; i < q; i += 1) {
    int u, v; cin >> u >> v;
    queries[u].push_back({v, i});
    queries[v].push_back({u, i});
  }
  function<void(int, int)> answer = [&](int u, int par)->void {
    visited[u] = 1;
    for (auto & child : Graph[u]) {
      if (child == par)
        continue;
      answer(child, u);
      LCA.Union(u, child, u);
    }
    for (auto [v, ind] : queries[u]) {
      if (visited[v] == 1)
        result[ind] = LCA.getValue(v);
    }
  };
  answer(1, 0);
  for (int i = 0; i < q; i += 1) cout << result[i] << '\n';
  return 0;
}