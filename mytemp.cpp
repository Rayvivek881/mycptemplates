#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#pragma GCC optimize("O1")
#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#else
#include "myheader.h"
#endif
// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
using namespace std;
void input() {return;}
template<typename T1, typename... T2>
	void input(T1 & x, T2&... args){((cin >> x), input(args...));}
void wrt() { cout << "\n"; return;}
template<typename T1, typename... T2>
	void wrt(T1 x, T2... args){((cout << x << ' '), wrt(args...));}
template<typename T> void inlst(T & lst, int x, int y)
	{ for(int i = x ; i < y; i++ ) cin >> lst[i]; }
template<typename T1, typename T2> istream & operator>>(istream & in, pair<T1, T2> & val)
	{ in >> val.first >> val.second; return in; }
template<typename T> istream & operator>>(istream & in, vector<T> & lst)
	{ for (auto & e : lst) in >> e; return in; }
template<typename T> void prlst(T & lst, int x, int y)
	{ for(int i = x ; i < y; i++ ) cout << lst[i] << " "[i < (y - 1)]; wrt(); }
// template<typename T> using Indexed_set = 
//   tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template<typename T> using Indexed_multiset = 
//   tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template<typename Key, typename T> using Indexed_map =
//   tree<Key, T, less<Key>, rb_tree_tag, tree_order_statistics_node_update>;
// template<typename T> using pques = priority_queue<T, vector<T>, greater<T>>;
// template<typename T> using pqueg = priority_queue<T>;
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define precision(n) cout.precision(n);
#define ll long long
#define pb push_back
#define fi first
#define se second
#define tests int test; cin >> test; while(test--)
#define ub(lst, val) (upper_bound(all(lst), val) - lst.begin())
#define lb(lst, val) (lower_bound(all(lst), val) - lst.begin())
#define fora(i, x, y) for (ll i = x; i < y; ++i)
#define ford(i, x, y) for (ll i = x; i >= y; --i)
#define all(lst) lst.begin(), lst.end()
#define rall(lst) lst.rbegin(), lst.rend()
#define _ceil(a, b) ((a + b - 1) / (b))
#define _sum(lst) accumulate(all(lst), 0ll)
#define cntval(lst, val) count(all(lst), val)
#define lcn(lst, val) (find(all(lst), val) - lst.begin())
#define sortlst(lst) sort(lst.begin(), lst.end())
#define sorted(lst) is_sorted(lst.begin(), lst.end())
#define rsortlst(lst) sort(lst.rbegin(), lst.rend())
#define sortarr(x, n) sort(x, x + n)
#define sz(lst) (int)lst.size()
typedef pair<long long, long long> pl;
typedef pair<int, int> pi;
typedef vector<long long> vl;
typedef vector<int> vi;
typedef vector<vector<long long>> vovl;
typedef vector<vector<int>> vovi;
typedef vector<string> vs;
typedef map<int, int> mi;
typedef map<long long, long long> ml;
typedef set<long long> sl;
typedef set<int> si;
const ll inf = INT32_MAX, MOD = 1e9 + 7, N = 3e5 + 10;
/*---------------------------------------FUNCT---------------------------------------- */
ll _lcm(ll a, ll b) { return (a * b) / __gcd(a, b); }
ll  min(ll a, ll b) { return std :: min(a, b); }
ll  max(ll a, ll b) { return std :: max(a, b); }
ll _nurm(ll & x) { while (x < 0) x += MOD; return x = (x + MOD) % MOD; }
ll _bits(ll x) { ll cnt = 0; while(x > 0) { cnt++; x >>= 1; } return cnt; }
ll _setbits(ll x) { ll cnt = 0; while(x > 0) { cnt += (x & 1); x >>= 1; } return cnt; }
ll _add(ll x, ll y) { x %= MOD, y %= MOD; return (x + y) % MOD; }
ll _sub(ll x, ll y) { x %= MOD, y %= MOD; return (x - y + MOD) % MOD; }
ll _mul(ll x, ll y) { x %= MOD, y %= MOD; return (x * 1ll * y) % MOD; }
ll _pow(ll x, ll y) { if (y == 0) return 1; else if (y % 2 == 0){
ll _tmp =_pow(x, y / 2); return _mul(_tmp, _tmp); } else return _mul(x, _pow(x, y - 1)); }
ll _inv(ll p) { return _pow(p, MOD - 2); }
ll _div(ll x, ll y) { x %= MOD, y %= MOD; return _mul(x, _inv(y)); }
/*---------------------------------------Code---------------------------------------- */
void SolveTestCases(int testCase) {
	wrt("hello", "World");
}
int main(int argc, char const *argv[]) {
	boost;
	int testCase = 1;
	cin >> testCase;
	for (int test = 0; test < testCase; test++)
		SolveTestCases(test);
	return 0;
}