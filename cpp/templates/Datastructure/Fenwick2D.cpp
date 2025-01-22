template<typename T>
  class Fenwick2D { // 1-indexed
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
      return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
  };