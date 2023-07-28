class IndexMange {
  vector<int> indexes;
  vector<bool> visited;
public:
  IndexMange(int n = 0) {
    indexes.resize(n), visited.assign(n, 1);
    for (int i = 0; i < n; i += 1)
      indexes[i] = i;
    random_shuffle(begin(indexes), end(indexes));
  }
  bool isAvalible(int ind) { 
    return ind < visited.size() && visited[ind]; 
  }
  int getInd() {
    swap(indexes.back(), indexes[rand() % indexes.size()]);
    int result = indexes.back();
    visited[result] = 0, indexes.pop_back();
    return result;
  }
  void addInd(int ind) {
    if (ind < visited.size() && visited[ind] == 0)
      indexes.push_back(ind);
    visited[ind] = 1;
  }
};