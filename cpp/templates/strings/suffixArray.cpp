#include <bits/stdc++.h>
using namespace std;
vector<int> suffix_array_construction(string s) {
  s += "$";
  int n = s.size(), alphabet = 256, classes = 1;
  vector<int> SArr(n), rank(n), cnt(max(alphabet, n), 0);
  for (int i = 0; i < n; i++) cnt[s[i]]++;
  for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; i++) SArr[--cnt[s[i]]] = i;
  rank[SArr[0]] = 0;
  for (int i = 1; i < n; i++) 
    rank[SArr[i]] = (classes += (s[SArr[i]] != s[SArr[i - 1]])) - 1;
  vector<int> NSArr(n), Nrank(n);
  for (int k = 0; (1 << k) < n; ++k) {
    for (int i = 0; i < n; i++)
      NSArr[i] = (SArr[i] - (1 << k) + n) % n;
    fill(cnt.begin(), cnt.begin() + classes, 0);
    for (int i = 0; i < n; i++) cnt[rank[NSArr[i]]]++;
    for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) SArr[--cnt[rank[NSArr[i]]]] = NSArr[i];
    Nrank[SArr[0]] = 0, classes = 1;
    for (int i = 1; i < n; i++) {
      pair<int, int> a = {rank[SArr[i]], rank[(SArr[i] + (1 << k)) % n]}, 
        b = {rank[SArr[i - 1]], rank[(SArr[i - 1] + (1 << k)) % n]};
      Nrank[SArr[i]] = (classes += (a != b)) - 1;
    }
    rank.swap(Nrank);
  }
  return vector<int>(SArr.begin() + 1, SArr.end());
}
vector<int> lcp_construction(string const& s, vector<int> const& suffix_array) {
  int n = s.size(), k = 0;
  vector<int> rank(n, 0);
  for (int i = 0; i < n; i++) rank[suffix_array[i]] = i;
  vector<int> lcp(n-1, 0);
  for (int i = 0; i < n; i++) {
    if (rank[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = suffix_array[rank[i] + 1];
    while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
    lcp[rank[i]] = k;
    if (k > 0) k--;
  }
  return lcp;
}
int main(int argc, char const *argv[]) {
  string str1 = "banana";
  vector<int> lst = suffix_array_construction(str1);
  for (int i = 0; i < lst.size(); i++) cout << lst[i] << " ";
  cout << endl;
  vector<int> temp = lcp_construction(str1, lst);
  for (int i = 0; i < temp.size(); i++) cout << temp[i] << " ";
  return 0;
}