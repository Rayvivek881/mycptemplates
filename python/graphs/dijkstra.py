import heapq
from collections import deque
from typing import List

def dijkstra(graph: List[List], start: int) -> List:
  n = len(graph)
  dist = [float('inf')] * n
  dist[start], heap = 0, [(0, start)]
  while len(heap) > 0:
    d, u = heapq.heappop(heap)
    if d > dist[u]:
      continue
    for v, w in graph[u]:
      if dist[u] + w < dist[v]:
        dist[v] = dist[u] + w
        heapq.heappush(heap, (dist[v], v))
  return dist


def bfs(graph: List[List], start: int) -> List:
  n = len(graph)
  dist = [float('inf')] * n
  dist[start], queue = 0, deque([start])
  while len(queue) > 0:
    u = queue.popleft()
    for v, w in graph[u]:
      if dist[u] + w < dist[v]:
        dist[v] = dist[u] + w
        queue.append(v)
  return dist