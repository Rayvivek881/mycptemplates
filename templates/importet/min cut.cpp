#include <bits/stdc++.h>
using namespace std;
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);

int n, m;
vector<vector<int>> capacity, adj, Graph;

int maxFlowBFS(int s, int t, vector<int> &parent) {
  fill(parent.begin(), parent.end(), -1);
  parent[s] = -2;
  queue<pair<int, int>> q;
  q.push({s, numeric_limits<int>::max()});
  while (!q.empty()) {
    auto [cur, flow] = q.front();
    q.pop();
    for (int next : adj[cur]) {
      if (parent[next] == -1 && capacity[cur][next]) {
        parent[next] = cur;
        int new_flow = min(flow, capacity[cur][next]);
        if (next == t)
          return new_flow;
        q.push({next, new_flow});
      }
    }
  }
  return 0;
}

int maxflow(int s, int t) {
  int flow = 0, new_flow;
  vector<int> parent(n + 1);
  while (new_flow = maxFlowBFS(s, t, parent)) {
    flow += new_flow;
    int cur = t;
    while (cur != s) {
      int prev = parent[cur];
      capacity[prev][cur] -= new_flow;
      capacity[cur][prev] += new_flow;
      cur = prev;
    }
  }
  return flow;
}
int main(int argc, char const *argv[]) {
  boost;
  cin >> n >> m;
  capacity.assign(n + 5, vector<int>(n + 5, 0));
  Graph = capacity;
  adj.resize(n + 5);
  for (int i = 0; i < m; i += 1) {
    int u, v, c; cin >> u >> v;
    capacity[u][v] += 1, capacity[v][u] += 1;
    if (Graph[u][v] == 0) {
      adj[u].push_back(v);
      adj[v].push_back(u);
      Graph[u][v] = Graph[v][u] = 1;
    }
  }
  maxflow(1, n);
  vector<int> visited(n + 5);
  function<void(int, int)> reacheable = [&](int node, int par)->void {
    visited[node] = 1;
    for (auto & child : adj[node]) {
      if (visited[child] == 0 && capacity[node][child] > 0)
        reacheable(child, node);
    }
  };
  reacheable(1, 0);
  vector<pair<int, int>> result;
  for (int i = 1; i <= n; i += 1) {
    for (int j = 1; j <= n; j += 1) {
      if (visited[i] == 1 && visited[j] == 0 && Graph[i][j])
        result.push_back({i, j});
    }
  }
  cout << result.size() << '\n';
  for (auto [a, b] : result) {
    cout << a << ' ' << b << '\n';
  }
  return 0;
}
