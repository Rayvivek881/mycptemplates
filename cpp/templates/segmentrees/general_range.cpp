#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct range_node {
  T lazy;
  bool is_lazy;
  range_node() { }
  range_node operator+(const range_node & other) {
    range_node res;

    return res;
  }
  void apply_lazy() {
    this->is_lazy = false;
  }
  void update_lazy(T value) {
    this->is_lazy = true;

  }
  range_node(T value) {

  }
};
template<typename T, typename Node = range_node<T>>
class general_range {
  int n;
  vector<T> Arr;
  vector<Node> tree;
  void build (int ind, int l, int r) {
    if (l == r) {
      tree[ind] = Node(Arr[l]);
      return ;
    }
    int mid = (l + r) >> 1;
    build(ind << 1, l, mid);
    build(ind << 1 | 1, mid + 1, r);
    tree[ind] = tree[ind << 1] + tree[ind << 1 | 1];
  }
  void push(int ind, int l, int r) {
    if (tree[ind].is_lazy) {
      if (l != r) {
        tree[ind << 1].update_lazy(tree[ind].lazy);
        tree[ind << 1 | 1].update_lazy(tree[ind].lazy);
      }
      tree[ind].apply_lazy();
    }
  }
  void update(int ind, int l, int r, int start, int end, T value) {
    if (l >= start && r <= end)
      tree[ind].update_lazy(value);
    push(ind, l, r);
    if (l > end || r < start || (l >= start && r <= end)) return ;
    int mid = (l + r) >> 1;
    update(ind << 1, l, mid, start, end, value);
    update(ind << 1 | 1, mid + 1, r, start, end, value);
    tree[ind] = tree[ind << 1] + tree[ind << 1 | 1];
  }
  Node query(int ind, int l, int r, int start, int end) {
    push(ind, l, r);
    if (l >= start && r <= end) return tree[ind];
    int mid = (l + r) >> 1;
    if (end <= mid) {
      return query(ind << 1, l, mid, start, end);
    } else if (start > mid) {
      return query(ind << 1 | 1, mid + 1, r, start, end);
    }
    return query(ind << 1, l, mid, start, end) + query(ind << 1 | 1, mid + 1, r, start, end);
  }
public:
  general_range(int n, vector<T> lst) {
    init(n, lst);
  }
  void init(int n, vector<T> lst) {
    this->n = n, Arr = lst;
    tree.resize(4 * (n + 1));
    build(1, 0, n - 1);
  }
  void update(int l, int r, T value) {
    update(1, 0, n - 1, l, r, value);
  }
  Node query(int start, int end) {
    return query(1, 0, n - 1, start, end);
  }
};