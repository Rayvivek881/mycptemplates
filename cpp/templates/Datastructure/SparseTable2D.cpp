template<typename T>
  class SparseTable2D { // 0-indexed
  private:
    T n, m;
    vector<vector<vector<vector<T>>>> st;
  public:
    SparseTable2D(const vector<vector<T>> &grid) {
      n = grid.size();
      m = grid[0].size();
      T logN = log2(n) + 5;
      T logM = log2(m) + 5;
      st.resize(n, vector<vector<vector<T>>>(m, vector<vector<T>>(logN, vector<T>(logM))));
      for (T i = 0; i < n; i++) {
        for (T j = 0; j < m; j++) {
          st[i][j][0][0] = grid[i][j];
        }
      }
      for (T l1 = 0; (1 << l1) <= n; l1++) {
        for (T l2 = 0; (1 << l2) <= m; l2++) {
          if (l1 + l2 > 0) {
            for (T i = 0; i + (1 << l1) <= n; i++) {
              for (T j = 0; j + (1 << l2) <= m; j++) {
                if (l1 > 0) {
                  st[i][j][l1][l2] = min(st[i][j][l1 - 1][l2], st[i + (1 << (l1 - 1))][j][l1 - 1][l2]);
                } else {
                  st[i][j][l1][l2] = min(st[i][j][l1][l2 - 1], st[i][j + (1 << (l2 - 1))][l1][l2 - 1]);
                }
              }
            }
          }
        }
      }
    }
    T quary(T x1, T y1, T x2, T y2) {
      T k1 = log2(x2 - x1 + 1);
      T k2 = log2(y2 - y1 + 1);
      T min_val1 = st[x1][y1][k1][k2];
      T min_val2 = st[x2 - (1 << k1) + 1][y1][k1][k2];
      T min_val3 = st[x1][y2 - (1 << k2) + 1][k1][k2];
      T min_val4 = st[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2];
      return min({min_val1, min_val2, min_val3, min_val4});
    }
  };