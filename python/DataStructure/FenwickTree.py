class FenwickTree:
  def __init__(self, n):
    self.n, self.tree = n + 2, [0] * (n + 2)
  
  def add(self, ind, x):
    ind += 1
    while ind <= self.n:
      self.tree[ind] += x
      ind += (ind & -ind)
  
  def prefix_sum(self, ind):
    ind, res = ind + 1, 0
    while ind > 0:
      res += self.tree[ind]
      ind -= (ind & -ind)
    return res

  
class RangeFenwick:
  def __init__(self, size):
    self.n = size
    self.tree1 = [0] * (self.n + 1) 
    self.tree2 = [0] * (self.n + 1) 

  def _update(self, tree, idx, delta):
    idx += 1
    while idx <= self.n:
      tree[idx] += delta
      idx += idx & -idx

  def _query(self, tree, idx):
    idx, res = idx + 1, 0
    while idx > 0:
      res += tree[idx]
      idx -= idx & -idx
    return res

  def update(self, l, r, delta):
    self._update(self.tree1, l, delta)
    self._update(self.tree1, r + 1, -delta)
    self._update(self.tree2, l, delta * l)
    self._update(self.tree2, r + 1, -delta * (r + 1))

  def prefix_query(self, idx):
    return self._query(self.tree1, idx) * (idx + 1) - self._query(self.tree2, idx)
  
class Fenwick2D:
  def __init__(self, n, m):
    self.n, self.m = n, m
    self.tree = [[0] * (m + 1) for _ in range(n + 1)]

  def update(self, x, y, delta):
    xi = x
    while xi <= self.n:
      yi = y
      while yi <= self.m:
        self.tree[xi][yi] += delta
        yi += yi & -yi
      xi += xi & -xi

  def query(self, x, y):
    result, xi = 0, x
    while xi > 0:
      yi = y
      while yi > 0:
        result += self.tree[xi][yi]
        yi -= yi & -yi
      xi -= xi & -xi
    return result

  def rectangle_sum(self, x1, y1, x2, y2):
    return self.query(x2, y2) - self.query(x1 - 1, y2) - self.query(x2, y1 - 1) + self.query(x1 - 1, y1 - 1)
