#include <bits/stdc++.h>
using namespace std;
#define boost ios_base::sync_with_stdio(false), cin.tie(nullptr);
template <typename T, class func = function<T(const T &, const T &)>>
class segmentTree {
public:
  T *Tree, *lst;
  int n;
  func myfunc;
  segmentTree(void){};
  void init(int size, T arr[], const func &F) {
    myfunc = F, n = size;
    Tree = new T[4 * size];
    lst = new T[size];
    for (int i = 0; i < size; i++)
      lst[i] = arr[i];
    buildTree(1, 0, size - 1);
  };
  void buildTree(int ind, int l, int r) {
    if (l == r) {
      Tree[ind] = lst[l];
      return;
    }
    int mid = (l + r) >> 1;
    buildTree(2 * ind, l, mid);
    buildTree(2 * ind + 1, mid + 1, r);
    Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
  }
  void updateUtil(int ind, int l, int r, int pos, T val) {
    if (l == r) {
      lst[pos] = val;
      Tree[ind] = val;
      return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
      updateUtil(2 * ind, l, mid, pos, val);
    else
      updateUtil(2 * ind + 1, mid + 1, r, pos, val);
    Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
  }
  T quaryUtil(int ind, int l, int r, int start, int end) {
    if (l >= start && r <= end)
      return Tree[ind];
    int mid = (l + r) >> 1;
    if (start > mid)
      return quaryUtil(2 * ind + 1, mid + 1, r, start, end);
    else if (end <= mid)
      return quaryUtil(2 * ind, l, mid, start, end);
    else {
      T a = quaryUtil(2 * ind + 1, mid + 1, r, mid + 1, end);
      T b = quaryUtil(2 * ind, l, mid, start, mid);
      return myfunc(a, b);
    }
  }
  void update(int pos, T val) {
    updateUtil(1, 0, n - 1, pos, val);
    return;
  }
  T quary(int l, int r) {
    T ans = quaryUtil(1, 0, n - 1, l, r);
    return ans;
  }
};
template <typename T, class func = function<T(const T &, const T &)>>
class spashTable
{
public:
  int n, Log;
  func myfunc;
  T **Table, *arr;
  spashTable(void) {}
  void init(vector<T> &lst, const func &F) {
    n = lst.size(), Log = ceil(log2((int)lst.size())) + 5;
    arr = new T[n + 1];
    Table = new T *[n + 1];
    for (int i = 0; i < n; i++) {
      Table[i] = new T[Log];
      arr[i] = lst[i], Table[i][0] = i;
    }
    myfunc = F;
    buildTable();
  }
  void buildTable() {
    for (int j = 1; j <= Log; j++) {
      for (int i = 0; (i + (1 << j) - 1) < n; i++)
        Table[i][j] = myfunc(Table[i][j - 1], Table[i + (1 << (j - 1))][j - 1]);
    }
  }
  T query(int l, int r) {
    int j = log2(r - l + 1);
    return myfunc(Table[l][j], Table[r - (1 << j) + 1][j]);
  }
};
struct element {
  int value, leader, index;
};
template <typename T, class func = function<T(const T &, const T &)>>
class HeavyLight {
  T *level, *subSize, n, ind = 0, lead = 0, Time = 0;
  vector<T> *Graph, dp, lst;
  T *NodeValues, *decompArr, *inTime, *outTime, *parent;
  func myfunc;
  struct element *Nodeimf;
  spashTable<T> lcaTable;
  segmentTree<T> myTree;
  
  int firstMinIndex(int i, int j) {
    return (lst[i] <= lst[j]) ? i : j;
  };
public:
  HeavyLight() {  };
  HeavyLight(int n, vector<T> Tree[], T Values[], const func &F) {
    init(int n, vector<T> Tree[], T Values[], const func &F);
  }
  void init(int n, vector<T> Tree[], T Values[], const func &F) {
    this->n = n, this->myfunc = F;
    level = new T[n + 1];
    parent = new T[n + 1];
    decompArr = new T[n + 1];
    NodeValues = new T[n + 1];
    Nodeimf = new struct element[n + 1];
    subSize = new T[n + 1];
    Graph = new vector<T>[n + 1];
    inTime = new T[n + 1];
    outTime = new T[n + 1];
    for (int i = 0; i <= n; i++) {
      level[i] = 0, subSize[i] = 0, parent[i] = 0;
      Graph[i] = Tree[i], NodeValues[i] = Values[i];
    }
    PreDFS(1, 0);
    Decomposition(1, 0);
    myTree.init(ind, decompArr, myfunc);
    lst.resize(dp.size());
    for (int i = 0; i < dp.size(); i++)
      lst[i] = level[dp[i]];
    lcaTable.init(lst, firstMinIndex);
  }
  void PreDFS(T node, T par = 0) {
    dp.push_back(node);
    inTime[node] = Time++, parent[node] = par;
    for (auto &child : Graph[node]) {
      if (child == par)
        continue;
      level[child] = level[node] + 1;
      PreDFS(child, node);
      subSize[node] += subSize[child];
      dp.push_back(node), outTime[node] = Time++;
    }
    subSize[node] += 1;
  }
  void Decomposition(T node, T par) {
    decompArr[ind] = (NodeValues[node]);
    Nodeimf[node] = {NodeValues[node], lead, ind++};
    T maxnode = -1, maxweight = 0;
    for (T &child : Graph[node]) {
      if (child == par)
        continue;
      if (subSize[child] > maxweight)
        maxweight = subSize[child], maxnode = child;
    }
    if (maxnode != -1)
      Decomposition(maxnode, node);
    for (T &child : Graph[node]) {
      if (child == par || child == maxnode)
        continue;
      lead = child;
      Decomposition(child, node);
    }
  }
  T queryUtill(T node, T granpa) {
    if (Nodeimf[node].leader == Nodeimf[granpa].leader)
      return myTree.quary(Nodeimf[granpa].index, Nodeimf[node].index);
    T ans = myTree.quary(Nodeimf[Nodeimf[node].leader].index, Nodeimf[node].index);
    node = parent[Nodeimf[node].leader];
    return myfunc(ans, queryUtill(node, granpa));
  }
  void update(T node, T val) {
    myTree.update(Nodeimf[node].index, val);
    Nodeimf[node].value = val;
  }
  int getLCA(int u, int v) {
    return dp[lcaTable.query(inTime[u], inTime[v])];
  }
  T query(T u, T v) {
    if (inTime[u] >= inTime[v])
      swap(u, v);
    T granpa = getLCA(u, v);
    T ans1 = queryUtill(u, granpa), ans2 = queryUtill(v, granpa);
    return myfunc(ans1, ans2);
  }
};
int main(int argc, char const *argv[])
{
  boost;
  int n, u, v, q, ind = 0;
  cin >> n >> q;
  int values[n + 1], answers[q];
  for (int i = 1; i < n + 1; i++)
    cin >> values[i];
  vector<int> graph[n + 1];
  for (int i = 0; i < n - 1; i++)
  {
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  HeavyLight<int> cphard(n, graph, values, [&](int a, int b){ return max(a, b); });
  while (q--)
  {
    int flage, pos, val, a, b;
    cin >> flage;
    cin >> pos >> val;
    if (flage == 1)
      cphard.update(pos, val);
    else
      answers[ind++] = (cphard.query(pos, val));
  }
  for (int i = 0; i < ind; i++)
    cout << answers[i] << " ";
  return 0;
}