#include <bits/stdc++.h>
using namespace std;
void Dijkstra(vector<pair<int, int>> adj[], vector<int> &ans, int src) {
	typedef pair<int, int> dpi;
	priority_queue<dpi, vector<dpi>, greater<dpi>> que;
	que.push({0, src}), ans[src] = 0;
	while (!que.empty()) {
		int u = que.top().second;
		que.pop();
		for (auto child : adj[u]) {
			int v = child.first, weight = child.second;
			if (ans[v] > ans[u] + weight) {
				ans[v] = ans[u] + weight;
				que.push({ans[v], v});
			}
		}
	}
}
bool spfa(int s, vector<int> & dist, vector<vector<pair<int, int>>> adj) {
	int n = adj.size();
	vector<int> cnt(n, 0), inqueue(n, false);
	queue<int> q;
	dist[s] = 0;
	q.push(s);
	inqueue[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop(), inqueue[v] = false;
		for (auto edge : adj[v]) {
			auto [to, len] = edge;
			if (dist[v] + len < dist[to]) {
				dist[to] = dist[v] + len;
				if (!inqueue[to]) {
					q.push(to);
					inqueue[to] = true, cnt[to]++;
					if (cnt[to] > n)
						return false;
				}
			}
		}
	}
	return true;
}
int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> adj[n];
	vector<int> ans(n, INT32_MAX);
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	Dijkstra(adj, ans, 0);
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	return 0;
}
