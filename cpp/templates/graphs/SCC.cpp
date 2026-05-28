#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;
vector<vector<int>> graph(N);

class SCC {
  vector<vector<int>> sccs;
  vector<bool> inStack;
  vector<int> st, disc, low, Ids;
  int n, timer = 0;
  void dfs(int u) {
    disc[u] = low[u] = ++timer;
    st.push_back(u), inStack[u] = true;
    
    for (int v : graph[u]) {
      if (disc[v] == 0) {
        dfs(v);
        low[u] = min(low[u], low[v]);
      }
      else if (inStack[v]) {
        low[u] = min(low[u], disc[v]);
      }
    }
    if (low[u] == disc[u]) {
      vector<int> scc;
      int node;
      do {
        node = st.back();
        st.pop_back();
        inStack[node] = false, scc.push_back(node);
      } while (node != u);
      sccs.push_back(scc);
    }
  }
public:
  int size() const { return (int)sccs.size(); }
  int getId(int u) const { return Ids[u]; }
  void init(int n) {
    this->n = n, this->timer = 0;
    inStack.assign(n + 1, 0);
    st.clear(), sccs.clear();
    disc.assign(n + 1, 0), low.assign(n + 1, 0);
    Ids.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) {
      if (disc[i] == 0)
        dfs(i);
    }

    for (int ind = 0; ind < sccs.size(); ind += 1) {
      for (int curr : sccs[ind]) {
        Ids[curr] = ind + 1;
      }
    } 
  }
  vector<vector<int>> updated_dag() {
    vector<vector<int>> result(this->size() + 1);
    vector<unordered_set<int>> exist(this->size() + 1);
    for (int u = 1; u <= n; u++) {
      for (int v : graph[u]) {
        int a = Ids[u], b = Ids[v];
        if (a != b && !exist[a].count(b)) {
          exist[a].insert(b);
          result[a].push_back(b);
        }
      }
    }
    return result;
  }
};