#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    mutable ll m, c, p;
    bool operator<(const Line& other) const {
        return m < other.m;
    }
    bool operator<(ll x) const {
        return p < x;
    }
};

struct DynamicHull : multiset<Line, less<>> {
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) {
        if (b < 0) a *= -1, b *= -1;
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = inf;
            return false;
        }
        if (x->m == y->m)
            x->p = (x->c > y->c ? inf : -inf);
        else
            x->p = div(y->c - x->c, x->m - y->m);
        return x->p >= y->p;
    }

    void add(ll m, ll c) {
        auto z = insert({m, c, 0});
        auto y = z++;
        auto x = y;

        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }

    ll query(ll x) {
        auto l = *lower_bound(x);
        return l.m * x + l.c;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    DynamicHull hull;
    while (n--) {
        ll t, a, b;
        cin >> t >> a;
        if (t == 1) {
            cin >> b;
            hull.add(a, b);
        } else {
            cout << hull.query(a) << "\n";
        }
    }
}