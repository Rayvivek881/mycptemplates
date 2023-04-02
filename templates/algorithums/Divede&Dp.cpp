ll n, k, cur_l, cur_r, curr_ans = 0;
vl dp_before(N, inf), dp_cur(N, inf), lst, freq(N, 0);
void add(int ind) {
    curr_ans += freq[lst[ind]];
    freq[lst[ind]] += 1;
}
void remove(int ind) {
    freq[lst[ind]] -= 1;
    curr_ans -= freq[lst[ind]];
}
ll Cost(int l, int r) {
    while (cur_l > l) add(--cur_l);
    while (cur_l < l) remove(cur_l++);
    while (cur_r < r) add(++cur_r);
    while (cur_r > r) remove(cur_r--);
    return curr_ans;
}
void compute(int l, int r, int optl, int optr) {
    if (l > r) return ;

    int mid = (l + r) >> 1;
    pair<ll, int> best = {LLONG_MAX, -1};

    for (int k = optl; k <= min(mid, optr); k++)
        best = min(best, {(k ? dp_before[k - 1] : 0) + Cost(k, mid), k});

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
void SolveTestCases(int testCase) {
    cin >> n >> k;
    lst.resize(n); cin >> lst;
    freq[lst[0]]++, cur_r = cur_r = 0;
    fora(i, 0, k) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }
    return wrt(dp_before[n - 1]);
}
