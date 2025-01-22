#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);

int n, m;
vector<vector<ll>> capacity;
vector<vector<int>> adj;

ll maxFlowBFS(int s, int t, vector<int> &parent) {
  fill(parent.begin(), parent.end(), -1);
  parent[s] = -2;
  queue<pair<int, ll>> q;
  q.push({s, numeric_limits<ll>::max()});
  while (!q.empty()) {
    auto [cur, flow] = q.front();
    q.pop();
    for (int next : adj[cur]) {
      if (parent[next] == -1 && capacity[cur][next]) {
        parent[next] = cur;
        ll new_flow = min(flow, capacity[cur][next]);
        if (next == t)
          return new_flow;
        q.push({next, new_flow});
      }
    }
  }
  return 0;
}

ll maxflow(int s, int t) {
  ll flow = 0, new_flow;
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
  capacity.assign(n + 5, vector<ll>(n + 5, 0));
  adj.resize(n + 5);
  for (int i = 0; i < m; i += 1) {
    ll u, v, c; cin >> u >> v >> c;
    capacity[u][v] += c;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  cout << maxflow(1, n) << endl;
  return 0;
}
