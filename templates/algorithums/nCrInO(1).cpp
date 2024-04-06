#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 1e9 + 7, N = 1e6 + 10;
ll factorialNumInverse[N + 1], naturalNumInverse[N + 1], fact[N + 1];

void nCrPreComputation() {
  naturalNumInverse[0] = naturalNumInverse[1] = fact[0] = 1;
  factorialNumInverse[0] = factorialNumInverse[1] = fact[1] = 1;
  for (int i =  2; i < N; i += 1) {
    naturalNumInverse[i] = naturalNumInverse[MOD % i] * (MOD - MOD / i) % MOD;
    factorialNumInverse[i] = (naturalNumInverse[i] * factorialNumInverse[i - 1]) % MOD;
		fact[i] = (fact[i - 1] * i) % MOD;
	}
}
ll nCrMod(ll n, ll r) {
	if (n < 0 || r > n) return 0;
  return ((fact[n] * factorialNumInverse[r]) % MOD * factorialNumInverse[n - r]) % MOD;
}