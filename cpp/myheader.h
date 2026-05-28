#include<iostream>
#include<algorithm>
#include<functional>
#include<numeric>
#include<cstdint>
#include<vector>
#include<cstring>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include <forward_list>
#include<queue>
#include<cmath>
#include<sstream>

struct element {
  int l, r;
  bool operator()(const element & lhs, const element & rhs) const {
    return lhs.r < rhs.r;
  }
};

using namespace std;

#define LOCAL;

#ifdef LOCAL
  #include <ext/pb_ds/assoc_container.hpp>
  #include <ext/pb_ds/tree_policy.hpp>
  using namespace __gnu_pbds;
  template <typename T>
  using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
  template <typename T>
  using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
#endif

namespace dbg {
  template <typename T, typename = void> struct is_iterable : false_type {};
  template <typename T>
  struct is_iterable<T, void_t<decltype(begin(declval<T&>())), decltype(end(declval<T&>()))>> : true_type {};

  template <typename T, typename = void> struct is_pair : false_type {};
  template <typename T1, typename T2> struct is_pair<pair<T1, T2>> : true_type {};

  template <typename T, typename = void> struct is_tuple : false_type {};
  template <typename... Ts> struct is_tuple<tuple<Ts...>> : true_type {};

  template <typename T> struct is_string_like : false_type {};
  template <> struct is_string_like<string> : true_type {};
  template <> struct is_string_like<const char*> : true_type {};
  template <> struct is_string_like<char*> : true_type {};
  template <size_t N> struct is_string_like<char[N]> : true_type {};

  template <typename T> struct container_name { static string get() { return "container"; } };
  template <typename T, typename A> struct container_name<vector<T, A>> { static string get() { return "vector"; } };
  template <typename T, size_t N> struct container_name<array<T, N>> { static string get() { return "array"; } };
  template <typename T, typename A> struct container_name<deque<T, A>> { static string get() { return "deque"; } };
  template <typename T, typename A> struct container_name<list<T, A>> { static string get() { return "list"; } };
  template <typename T, typename A> struct container_name<forward_list<T, A>> { static string get() { return "forward_list"; } };
  template <typename T, typename C, typename A> struct container_name<set<T, C, A>> { static string get() { return "set"; } };
  template <typename T, typename C, typename A> struct container_name<multiset<T, C, A>> { static string get() { return "multiset"; } };
  template <typename T, typename H, typename E, typename A> struct container_name<unordered_set<T, H, E, A>> { static string get() { return "unordered_set"; } };
  template <typename T, typename H, typename E, typename A> struct container_name<unordered_multiset<T, H, E, A>> { static string get() { return "unordered_multiset"; } };
  template <typename K, typename V, typename C, typename A> struct container_name<map<K, V, C, A>> { static string get() { return "map"; } };
  template <typename K, typename V, typename C, typename A> struct container_name<multimap<K, V, C, A>> { static string get() { return "multimap"; } };
  template <typename K, typename V, typename H, typename E, typename A> struct container_name<unordered_map<K, V, H, E, A>> { static string get() { return "unordered_map"; } };
  template <typename K, typename V, typename H, typename E, typename A> struct container_name<unordered_multimap<K, V, H, E, A>> { static string get() { return "unordered_multimap"; } };
  template <typename T, typename C> struct container_name<stack<T, C>> { static string get() { return "stack"; } };
  template <typename T, typename C> struct container_name<queue<T, C>> { static string get() { return "queue"; } };
  template <typename T, typename C, typename Cmp> struct container_name<priority_queue<T, C, Cmp>> { static string get() { return "priority_queue"; } };
  template <> struct container_name<string> { static string get() { return "string"; } };
  template <typename T1, typename T2> struct container_name<pair<T1, T2>> { static string get() { return "pair"; } };
  template <typename... Ts> struct container_name<tuple<Ts...>> { static string get() { return "tuple"; } };

  #ifdef LOCAL
  template <typename T> struct container_name<ordered_set<T>> { static string get() { return "ordered_set"; } };
  template <typename T> struct container_name<ordered_multiset<T>> { static string get() { return "ordered_multiset"; } };
  #endif

  template <typename T> struct brackets { static string open() { return "["; } static string close() { return "]"; } };
  template <typename T, typename A> struct brackets<vector<T, A>> { static string open() { return "["; } static string close() { return "]"; } };
  template <typename T, size_t N> struct brackets<array<T, N>> { static string open() { return "["; } static string close() { return "]"; } };
  template <typename T, typename A> struct brackets<deque<T, A>> { static string open() { return "["; } static string close() { return "]"; } };
  template <typename T, typename A> struct brackets<list<T, A>> { static string open() { return "["; } static string close() { return "]"; } };
  template <typename T, typename A> struct brackets<forward_list<T, A>> { static string open() { return "["; } static string close() { return "]"; } };
  template <typename T, typename C, typename A> struct brackets<set<T, C, A>> { static string open() { return "{"; } static string close() { return "}"; } };
  template <typename T, typename C, typename A> struct brackets<multiset<T, C, A>> { static string open() { return "{"; } static string close() { return "}"; } };
  template <typename T, typename H, typename E, typename A> struct brackets<unordered_set<T, H, E, A>> { static string open() { return "{"; } static string close() { return "}"; } };
  template <typename T, typename H, typename E, typename A> struct brackets<unordered_multiset<T, H, E, A>> { static string open() { return "{"; } static string close() { return "}"; } };
  template <typename K, typename V, typename C, typename A> struct brackets<map<K, V, C, A>> { static string open() { return "{"; } static string close() { return "}"; } };
  template <typename K, typename V, typename C, typename A> struct brackets<multimap<K, V, C, A>> { static string open() { return "{"; } static string close() { return "}"; } };
  template <typename K, typename V, typename H, typename E, typename A> struct brackets<unordered_map<K, V, H, E, A>> { static string open() { return "{"; } static string close() { return "}"; } };
  template <typename K, typename V, typename H, typename E, typename A> struct brackets<unordered_multimap<K, V, H, E, A>> { static string open() { return "{"; } static string close() { return "}"; } };

  #ifdef LOCAL
  template <typename T> struct brackets<ordered_set<T>> { static string open() { return "{"; } static string close() { return "}"; } };
  template <typename T> struct brackets<ordered_multiset<T>> { static string open() { return "{"; } static string close() { return "}"; } };
  #endif

  template <typename T> string format(const T& x);

  template <typename T1, typename T2>
  string format_pair(const pair<T1, T2>& p) {
    return "(" + format(p.first) + ", " + format(p.second) + ")";
  }

  template <typename Tuple, size_t... Is>
  string format_tuple_impl(const Tuple& t, index_sequence<Is...>) {
    string parts[] = { format(get<Is>(t))... };
    string out = "(";
    for (size_t i = 0; i < sizeof...(Is); ++i) {
      if (i) out += ", ";
      out += parts[i];
    }
    out += ")";
    return out;
  }

  template <typename... Ts>
  string format_tuple(const tuple<Ts...>& t) {
    return format_tuple_impl(t, index_sequence_for<Ts...>{});
  }

  template <typename T>
  string format_iterable(const T& c) {
    string out = brackets<T>::open();
    bool first = true;
    for (const auto& v : c) {
      if (!first) out += ", ";
      out += format(v);
      first = false;
    }
    out += brackets<T>::close();
    return out;
  }

  template <typename T, typename C>
  string format_stack(stack<T, C> s) {
    vector<T> v;
    while (!s.empty()) { v.push_back(s.top()); s.pop(); }
    reverse(v.begin(), v.end());
    string out = "stack[bottom> ";
    for (size_t i = 0; i < v.size(); ++i) {
      if (i) out += ", ";
      out += format(v[i]);
    }
    out += " <top]";
    return out;
  }

  template <typename T, typename C>
  string format_queue(queue<T, C> q) {
    string out = "queue[front> ";
    bool first = true;
    while (!q.empty()) {
      if (!first) out += ", ";
      out += format(q.front());
      q.pop();
      first = false;
    }
    out += " <back]";
    return out;
  }

  template <typename T, typename C, typename Cmp>
  string format_pq(priority_queue<T, C, Cmp> pq) {
    string out = "priority_queue[top> ";
    bool first = true;
    while (!pq.empty()) {
      if (!first) out += ", ";
      out += format(pq.top());
      pq.pop();
      first = false;
    }
    out += "]";
    return out;
  }

  inline string i128_to_string(__int128 v) {
    if (v == 0) return "0";
    bool neg = v < 0;
    string s;
    __int128 u = neg ? -v : v;
    while (u) { s += char('0' + int(u % 10)); u /= 10; }
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    return s;
  }

  inline string u128_to_string(unsigned __int128 v) {
    if (v == 0) return "0";
    string s;
    while (v) { s += char('0' + int(v % 10)); v /= 10; }
    reverse(s.begin(), s.end());
    return s;
  }

  template <typename T>
  string format(const T& x) {
    if constexpr (is_string_like<T>::value) {
      ostringstream oss; oss << x; return oss.str();
    } else if constexpr (is_same_v<T, char>) {
      return string(1, x);
    } else if constexpr (is_same_v<T, bool>) {
      return x ? "true" : "false";
    } else if constexpr (is_same_v<T, __int128>) {
      return i128_to_string(x);
    } else if constexpr (is_same_v<T, unsigned __int128>) {
      return u128_to_string(x);
    } else if constexpr (is_floating_point_v<T>) {
      ostringstream oss;
      oss << setprecision(numeric_limits<T>::max_digits10) << x;
      return oss.str();
    } else if constexpr (is_pair<T>::value) {
      return format_pair(x);
    } else if constexpr (is_tuple<T>::value) {
      return format_tuple(x);
    } else if constexpr (is_iterable<T>::value) {
      return container_name<T>::get() + format_iterable(x);
    } else {
      ostringstream oss; oss << x; return oss.str();
    }
  }

  template <size_t N>
  string format(const bitset<N>& b) {
    return "bitset<" + to_string(N) + ">{" + b.to_string() + "}";
  }

  template <typename T, size_t N>
  string format(const T (&arr)[N]) {
    if constexpr (is_same_v<remove_cv_t<T>, char>) {
      ostringstream oss; oss << arr; return oss.str();
    } else {
      string out = "array[";
      for (size_t i = 0; i < N; ++i) {
        if (i) out += ", ";
        out += format(arr[i]);
      }
      out += "]";
      return out;
    }
  }

  template <typename T>
  string format(const optional<T>& o) {
    return o ? "some(" + format(*o) + ")" : string("nullopt");
  }

  inline string format(nullptr_t) { return "nullptr"; }

  template <typename T, typename C>
  string format(const stack<T, C>& s) { return format_stack(s); }

  template <typename T, typename C>
  string format(const queue<T, C>& q) { return format_queue(q); }

  template <typename T, typename C, typename Cmp>
  string format(const priority_queue<T, C, Cmp>& pq) { return format_pq(pq); }

  template <typename T>
  void print_one(const string& name, const T& val) {
    cerr << name << " = " << format(val);
  }

  template <typename T, typename C>
  void print_one(const string& name, const stack<T, C>& s) {
    cerr << name << " = " << format(s);
  }

  template <typename T, typename C>
  void print_one(const string& name, const queue<T, C>& q) {
    cerr << name << " = " << format(q);
  }

  template <typename T, typename C, typename Cmp>
  void print_one(const string& name, const priority_queue<T, C, Cmp>& pq) {
    cerr << name << " = " << format(pq);
  }

  template <size_t N>
  void print_one(const string& name, const bitset<N>& b) {
    cerr << name << " = " << format(b);
  }

  template <typename T, size_t N>
  void print_one(const string& name, const T (&arr)[N]) {
    cerr << name << " = " << format(arr);
  }

  inline vector<string> split_names(const string& s) {
    vector<string> out;
    string cur;
    int depth = 0;
    for (char c : s) {
      if (c == '(' || c == '[' || c == '{' || c == '<') depth++;
      else if (c == ')' || c == ']' || c == '}' || c == '>') depth--;
      if (c == ',' && depth == 0) {
        size_t a = cur.find_first_not_of(" \t");
        size_t b = cur.find_last_not_of(" \t");
        out.push_back(a == string::npos ? "" : cur.substr(a, b - a + 1));
        cur.clear();
      } else {
        cur += c;
      }
    }
    if (!cur.empty()) {
      size_t a = cur.find_first_not_of(" \t");
      size_t b = cur.find_last_not_of(" \t");
      out.push_back(a == string::npos ? "" : cur.substr(a, b - a + 1));
    }
    return out;
  }

  inline void debug_out(const vector<string>&, size_t) { cerr << endl; }

  template <typename T, typename... Rest>
  void debug_out(const vector<string>& names, size_t idx, const T& first, const Rest&... rest) {
    if (idx) cerr << " | ";
    print_one(names[idx], first);
    debug_out(names, idx + 1, rest...);
  }
};

#ifdef LOCAL
  #define debug(...) do { \
    cerr << "[DEBUG][L" << __LINE__ << "] "; \
    dbg::debug_out(dbg::split_names(#__VA_ARGS__), 0, __VA_ARGS__); \
  } while (0)
#else
  #define debug(...) ((void)0)
#endif