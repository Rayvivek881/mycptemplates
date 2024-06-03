#include<bits/stdc++.h>
using namespace std;
int n, k, m;
struct Node {
  int num, k, weight;
  Node() {}
  Node(int num, int k, int weight) {
    this->k = k, this->num = num;
    this->weight = weight;
  }
  bool operator()(const Node & lhs, const Node & rhs) const {
    return lhs.weight > rhs.weight;
  }
};
vector<vector<vector<Node>>> Graph;
void kLavelDiastra(int source, vector<vector<int>> & dist) {
  priority_queue<Node, vector<Node>, Node> que;
  que.push(Node(source, 0, 0));
  while (que.size() != 0) {
    auto & [u, ku, currWeight] = que.top();
    que.pop(), dist[u][ku] = min(dist[u][ku], currWeight);
    for (auto & [v, kv, weight] : Graph[u][ku]) {
      if (currWeight + weight < dist[v][kv]) {
        dist[v][kv] = currWeight + weight;
        que.push(Node(v, kv, dist[v][kv]));
      }
    }
  } 
}
int main(int argc, char const *argv[]) {
  cin >> n >> m >> k;
  Graph.assign(n + 5, vector<vector<Node>>(k + 5));
  for (int i = 0; i < m; i += 1) {
    int u, v, weight;
    cin >> u >> v >> weight;
    for (int j = 0; j <= k; j += 1) {
      Graph[u][j].push_back(Node(v, j, weight));
      Graph[u][j].push_back(Node(v, j + 1, 0));
    }
  }
  vector<vector<int>> dist(n + 5, vector<int>(k + 5, INT32_MAX));
  kLavelDiastra(1, dist);
  return 0;
}