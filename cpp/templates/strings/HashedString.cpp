#include <bits/stdc++.h>
using namespace std;

#define ll long long
class HashedString {
  private:
	static const ll M = 1e9 + 9, B = 9973;
	static vector<ll> pow;
	vector<ll> p_hash;
  public:
	HashedString(const string &s) : p_hash(s.size() + 1) {
    if (pow.size() == 0) pow.push_back(1);
		while (pow.size() < s.size()) { 
      pow.push_back((pow.back() * B) % M); 
    }
		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}
	ll getHash(int start, int end) {
		ll raw_val = (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
		return (raw_val % M + M) % M;
	}
};