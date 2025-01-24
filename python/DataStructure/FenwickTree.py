class FenwickTree:
  def __init__(self, n):
    self.n = n + 2
    self.tree = [0] * (n + 2)
  
  def add(self, ind, x):
    ind += 1
    while ind < self.n:
      self.tree[ind] += x
      ind += (ind & -ind)
  
  def prefix_sum(self, ind):
    ind, res = ind + 1, 0
    while ind > 0:
      res += self.tree[ind]
      ind -= (ind & -ind)
    return res
  
