import math
from typing import List, Callable, Any

class SparseTable:
  def __init__(self, arr: List[Any], func: Callable[[Any, Any], Any]):
    self.n = len(arr)
    self.func = func
    self.log = math.ceil(math.log2(self.n)) + 5
    self.table = self._build_table(arr)

  def _build_table(self, arr: List[Any]) -> List[List[Any]]:
    table = [[0] * self.log for _ in range(self.n)]
    for i in range(self.n):
      table[i][0] = arr[i]
    for j in range(1, self.log):
      for i in range(self.n - (1 << j) + 1):
        table[i][j] = self.func(table[i][j - 1], table[i + (1 << (j - 1))][j - 1])
    return table

  def query(self, left: int, right: int) -> Any:
    j = math.floor(math.log2(right - left + 1))
    return self.func(self.table[left][j], self.table[right - (1 << j) + 1][j])

  

st = SparseTable([1, 3, 2, 7, 9, 11, 3, 5], max)
print(st.query(1, 4))  # Output: 2
print(st.query(3, 7))  # Output: 3