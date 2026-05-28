#include <vector>
#include <cmath>
using namespace std;

class SparseTable2D {
public:
  int n, m, logN, logM;
  vector<vector<vector<vector<int>>>> st;
  SparseTable2D(const vector<vector<int>> &grid) {
    n = grid.size(), m = grid[0].size();
    logN = log2(n) + 1, logM = log2(m) + 1;
    st.assign(logN, vector<vector<vector<int>>>(logM, vector<vector<int>>(n, vector<int>(m))));

    // Initialize table
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        st[0][0][i][j] = grid[i][j];

    // Precompute along columns
    for (int k = 1; (1 << k) <= n; k++)
      for (int i = 0; i + (1 << k) <= n; i++)
        for (int j = 0; j < m; j++)
          st[k][0][i][j] = min(st[k - 1][0][i][j], st[k - 1][0][i + (1 << (k - 1))][j]);

    // Precompute along rows
    for (int l = 1; (1 << l) <= m; l++)
      for (int k = 0; (1 << k) <= n; k++)
        for (int i = 0; i + (1 << k) <= n; i++)
          for (int j = 0; j + (1 << l) <= m; j++) {
            st[k][l][i][j] = min(st[k][l - 1][i][j], st[k][l - 1][i][j + (1 << (l - 1))]);
          }
  }

  int query(int x1, int y1, int x2, int y2) {
    int k = log2(x2 - x1 + 1), l = log2(y2 - y1 + 1);
    int min1 = min(st[k][l][x1][y1], st[k][l][x1][y2 - (1 << l) + 1]);
    int min2 = min(st[k][l][x2 - (1 << k) + 1][y1], st[k][l][x2 - (1 << k) + 1][y2 - (1 << l) + 1]);
    return min(min1, min2);
  }
};
