#include <bits/stdc++.h>
using namespace std;
template <typename T>
class FenwickTree {
public:
	int n;
	std::vector<T> tree;
	FenwickTree(int size) : n(size + 2), tree(size + 2, 0) {}
	void update(int ind, int delta) {
		for (++ind; ind < n; ind += ind & -ind)
			tree[ind] += delta;
	}
	T prefix_query(int ind) const {
		T ans = 0;
		for (++ind; ind > 0; ind -= ind & -ind)
			ans += tree[ind];
		return ans;
	}
};

template <typename T>
class RangeFenwick {
private:
	int n;
	std::vector<T> tree1, tree2;
	void update(std::vector<T> & tree, int idx, T delta) {
		idx += 1; 
		while (idx <= n) {
			tree[idx] += delta;
			idx += idx & -idx;
		}
	}
	T query(const std::vector<T> & tree, int idx) const {
		T res = 0;
		while (idx > 0) {
			res += tree[idx];
			idx -= idx & -idx;
		}
		return res;
	}
public:
	RangeFenwick(int size) : n(size), tree1(size + 1, 0), tree2(size + 1, 0) {}
	void range_update(int l, int r, T delta) {
		update(tree1, l, delta);
		update(tree1, r + 1, -delta);
		update(tree2, l, delta * l);
		update(tree2, r + 1, -delta * (r + 1));
	}
	int prefix_query(int idx) const {
		idx += 1;
		return query(tree1, idx) * idx - query(tree2, idx);
	}
};

template<typename T>
class Fenwick2D {
  T n, m;
  vector<vector<T>> tree;
public:
  Fenwick2D(T n, T m) : n(n), m(m) {
    tree.resize(n + 1, vector<T>(m + 1, 0));
  }
  void update(T x, T y, T delta) {
    while (x <= n) {
      T y1 = y;
      while (y1 <= m) {
        tree[x][y1] += delta;
        y1 += y1 & -y1;
      }
      x += x & -x;
    }
  }
  
  T query(T x, T y) {
    T result = 0;
    while (x > 0) {
      T y1 = y;
      while (y1 > 0) {
        result += tree[x][y1];
        y1 -= y1 & -y1;
      }
      x -= x & -x;
    }
    return result;
  }
  T rectangle_sum(T x1, T y1, T x2, T y2) {
    x1 += 1, y1 += 1, x2 += 1, y2 += 1;
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
  }
};

int main() {
	FenwickTree<int> ft(10);
	ft.update(1, 1);
	ft.update(2, 2);
	ft.update(3, 3);
	cout << ft.prefix_query(6) << endl;
	return 0;
}