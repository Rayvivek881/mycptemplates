class UnionFind:
  def __init__(self, n):
    self.rank, self.components = [0] * n, n
    self.parent = list(range(n))

  def find(self, a):
    while self.parent[a] != a:
      self.parent[a] = self.parent[self.parent[a]]
      a = self.parent[a]
    
    return self.parent[a]

  def join(self, a, b):
    a, b = self.find(a), self.find(b)
    if a == b: return

    self.components -= 1
    self.rank[a] += (self.rank[a] == self.rank[b])
    if self.rank[a] < self.rank[b]:
      self.parent[a] = b
    else: self.parent[b] = a

  def __len__(self):
    return self.components
  
  