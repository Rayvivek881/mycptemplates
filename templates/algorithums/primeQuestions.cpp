vector<int> isprime, prime, SPF;
void manipulated_seive(int MAXN) {
  isprime.assign(MAXN, 1), SPF.resize(MAXN);
  isprime[0] = isprime[1] = 0;
  for (int i = 2; i < MAXN; i++) {
    if (isprime[i])
      prime.push_back(i), SPF[i] = i;
    for (int j = 0; j < prime.size() && i * prime[j] < MAXN && prime[j] <= SPF[i]; j++) {
      isprime[i * prime[j]] = false;
      SPF[i * prime[j]] = prime[j];
    }
  }
}
