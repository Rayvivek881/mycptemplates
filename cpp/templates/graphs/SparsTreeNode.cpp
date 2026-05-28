#include<bits/stdc++.h>
using namespace std;
template <typename T, class func = function<T(const T&, const T&)>>
class SparseTree {
  int n, _log, _timer = 0;
  func merge;

  vector<T> val;
  vector<int> tin, tout;
  vector<vector<T>> table;
  vector<vector<int>> tree, up;
private:
  void dfs(int v, int p) {
    tin[v] = _timer++;
    up[v][0] = p;
    table[v][0] = val[v];
    for (int i = 1; i < _log; i++) {
      up[v][i] = up[up[v][i - 1]][i - 1];
      table[v][i] = merge(table[v][i - 1], table[up[v][i - 1]][i - 1]);
    }
    for (int to : tree[v]) {
      if (to != p)
        dfs(to, v);
    }
    tout[v] = _timer++;
  }
  bool isAncestor(int u, int v) {
    if (v == 0) return false;
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }
  int lca(int u, int v) {
    if (isAncestor(u, v)) return u;
    if (isAncestor(v, u)) return v;

    for (int i = _log - 1; i >= 0; i--) {
      if (!isAncestor(up[u][i], v))
        u = up[u][i];
    }

    return up[u][0];
  }

public:
  SparseTree(int n, vector<vector<int>>& g, vector<T>& arr, func f) : n(n), tree(g), val(arr), merge(f) {
    _log = ceil(log2(n)) + 3;
    up.assign(n + 1, vector<int>(_log));
    table.assign(n + 1, vector<T>(_log));
    tin.resize(n + 1), tout = tin;
    dfs(1, 0);
  }
  T query(int u, int v) {
    int L = lca(u, v);
    T ans = val[L];
    auto climb = [&](int &x) {
      for (int i = _log - 1; i >= 0; i--) {
        if (!isAncestor(up[x][i], L)) {
          ans = merge(ans, table[x][i]);
          x = up[x][i];
        }
      }
    };

    climb(u);
    climb(v);
    return ans;
  }
};
int main(int argc, char const *argv[])
{
	int n; cin >> n;
	vector<vector<int>> Graph(n + 1);
  vector<int> arr(n + 1);

	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		Graph[u].push_back(v);
		Graph[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) cin >> arr[i];
	SparseTree<int> myDsa(n, Graph, arr, [&](int a, int b) { return max(a, b); });
	cout << myDsa.query(3, 7);
	return 0;
}
