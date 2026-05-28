#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
vector<ll> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

bool is_prime(ll n) {
  if (n < 2)
    return false;

  for (auto p : small_primes) {
    if (n % p == 0)
      return n == p;
  }

  ll d = n - 1;
  int r = 0;
  while ((d & 1) == 0) {
    d >>= 1;
    r++;
  }

  for (auto a : bases) {
    if (a % n == 0)
      return true;

    __int128 x = 1, base = a % n;
    ll exp = d;

    while (exp) {
      if (exp & 1)
        x = (x * base) % n;
      base = (base * base) % n;
      exp >>= 1;
    }

    if (x == 1 || x == n - 1)
      continue;

    bool composite = true;
    for (int i = 0; i < r - 1; i++) {
      x = (x * x) % n;
      if (x == n - 1) {
        composite = false;
        break;
      }
    }

    if (composite)
      return false;
  }

  return true;
}