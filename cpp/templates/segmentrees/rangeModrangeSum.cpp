#include <bits/stdc++.h>
using namespace std;
template<typename T> // range MOD and range sum
class SegmentBeats {
    T *Tsum, *Tmax, n;
    void margeNode(int ind) {
        Tsum[ind] = Tsum[2 * ind] + Tsum[2 * ind + 1];
        Tmax[ind] = max(Tmax[2 * ind], Tmax[2 * ind + 1]);
    }
    void update_set(int ind, int l, int r, int pos, T val) {
        if (l == r) {
            Tsum[ind] = Tmax[ind] = val;
            return ;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update_set(2 * ind, l, mid, pos, val);
        else update_set(2 * ind + 1, mid + 1, r, pos, val);
        margeNode(ind);
    }
    void update_mod(int ind, int l, int r, int l1, int r1, int x) {
        if (Tmax[ind] < x || r1 < l || r < l1)
            return ;
        if (l == r) {
            Tsum[ind] = Tmax[ind] = (Tmax[ind] % x);
            return ;
        }
        int mid = (l + r) >> 1;
        update_mod(2 * ind, l, mid, l1, r1, x);
        update_mod(2 * ind + 1, mid + 1, r, l1, r1, x);
        margeNode(ind);
    }
    T query(int ind, int l, int r, int l1, int r1) {
        if (r1 < l || r < l1)
            return 0;
        if (l1 <= l && r <= r1)
            return Tsum[ind];
        int mid = (l + r) >> 1;
        return query(2 * ind, l, mid, l1, r1) + query(2 * ind + 1, mid + 1, r, l1, r1);
    }
public:
    SegmentBeats(int size) : n(size) {
        Tsum = new T[4 * (size + 1)];
        Tmax = new T[4 * (size + 1)];
        for (int i = 0; i <= 4 * size; i++)
            Tmax[i] = Tsum[i] = 0;
    }
    void update(int index, int val) {
        update_set(1, 0, n - 1, index, val);
    }
    void update(int l, int r, int x) {
        update_mod(1, 0, n - 1, l, r, x);
    }
    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    SegmentBeats<long long> Tree(n);
    for (int i = 0; i < n; i++) {
        long long value; cin >> value;
        Tree.update(i, value);
    }
    for (int i = 0; i < m; i++) {
        int type, l, r, k, x; cin >> type;
        if (type == 1) {
            cin >> l >> r;
            cout << Tree.query(l - 1, r - 1) << '\n';
        } else if (type == 2) {
            cin >> l >> r >> x;
            Tree.update(l - 1, r - 1, x);
        } else {
            cin >> k >> x;
            Tree.update(k - 1, x);
        }
    }
    return 0;
}
