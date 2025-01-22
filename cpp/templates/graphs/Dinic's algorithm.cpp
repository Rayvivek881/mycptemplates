#include <bits/stdc++.h>
#define ll long long
using namespace std;

template<typename T>
struct FlowEdge {
  int v, u;
  T cap, flow = 0;
  FlowEdge(int v, int u, T cap) : v(v), u(u), cap(cap) {}
};

template<typename T>
struct Dinic {
  const T flow_inf = numeric_limits<T>::max();
  vector<FlowEdge<T>> edges;
  vector<vector<int>> adj;
  int n, m = 0, s, t;
  vector<int> level, ptr;
  queue<int> q;

  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }

  void add_edge(int v, int u, T cap) {
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
  }

  bool bfs() {
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : adj[v]) {
        if ((edges[id].cap - edges[id].flow < 1) || (level[edges[id].u] != -1))
          continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    }
    return level[t] != -1;
  }

  T dfs(int v, T pushed) {
    if (pushed == 0 || v == t)
      return pushed;
    for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
      int id = adj[v][cid], u = edges[id].u;
      if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
        continue;
      T tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr, edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }

  T flow() {
    T f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      q.push(s);
      if (!bfs())
        break;
      fill(ptr.begin(), ptr.end(), 0);
      while (T pushed = dfs(s, flow_inf)) {
        f += pushed;
      }
    }
    return f;
  }
};

int main(int argc, char const *argv[]) {
  int n, m; cin >> n >> m;
  Dinic<ll> obj(n + 1, 1, n);
  for (int i = 0; i < m; i += 1) {
    int u, v, cap; cin >> u >> v >> cap;
    obj.add_edge(u, v, cap);
  }
  cout << obj.flow() << '\n';
  return 0;
}
