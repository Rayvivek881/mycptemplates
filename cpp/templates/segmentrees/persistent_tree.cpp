#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct seg_node {
  T val;
  seg_node() {}
  seg_node operator+(const seg_node & other) {
    seg_node res;

    return res;
  }
  seg_node(T curr) {
    
  }
};
template<typename T>
class persistent_tree {
  int n;
  vector<T> Arr;
  vector<vector<seg_node<T>>> tree;
  void build (int ind, int l, int r) {
    if (l == r) {
      tree[ind].push_back(seg_node<T>(Arr[l]));
      return ;
    }
    int mid = (l + r) >> 1;
    build(ind << 1, l, mid);
    build(ind << 1 | 1, mid + 1, r);
    tree[ind].push_back(tree[ind << 1].back() + tree[ind << 1 | 1].back());
  }
  void update(int ind, int l, int r, int pos, T value) {
    if (l == r) {
      Arr[l] = value;
      tree[ind].push_back(seg_node<T>(value));
      return ;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
      update(ind << 1, l, mid, pos, value);
    } else update(ind << 1 | 1, mid + 1, r, pos, value);
    tree[ind].push_back(tree[ind << 1].back() + tree[ind << 1 | 1].back());
  }
  seg_node<T> query(int ind, int l, int r, int start, int end, int version) {
    if (l >= start && r <= end) {
      return tree[ind][min(version, (int)tree[ind].size()) - 1];
    }
    int mid = (l + r) >> 1;
    if (end <= mid) {
      return query(ind << 1, l, mid, start, end, version);
    } else if (start > mid) {
      return query(ind << 1 | 1, mid + 1, r, start, end, version);
    }
    return query(ind << 1, l, mid, start, end, version) + query(ind << 1 | 1, mid + 1, r, start, end, version);
  }
public:
  persistent_tree() {}
  persistent_tree(int n, vector<T> lst) {
    init(n, lst);
  }
  void init(int n, vector<T> lst) {
    this->n = n, Arr = lst;
    tree.resize(4 * n);
    build(1, 0, n - 1);
  }
  void update(int pos, T value) {
    update(1, 0, n - 1, pos, value);
  }
  seg_node<T> query(int start, int end, int version) {
    return query(1, 0, n - 1, start, end, version);
  }
};