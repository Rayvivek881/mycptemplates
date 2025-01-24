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
    return (self.query(x2, y2) - self.query(x1 - 1, y2) - self.query(x2, y1 - 1) + self.query(x1 - 1, y1 - 1))