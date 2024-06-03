isprime, prime, SPF = [], [], []

def manipulated_seive(MAXN : int) -> None:
  global isprime, prime, SPF
  isprime, SPF = [1] * (MAXN + 1), [1] * (MAXN + 1)
  isprime[0], isprime[1] = 0, 0
  for i in range(2, MAXN):
    if isprime[i]:
      prime.append(i)
      SPF[i] = i
    j = 0
    while j < len(prime) and i * prime[j] < MAXN and prime[j] <= SPF[i]:
      isprime[i * prime[j]] = 0
      SPF[i * prime[j]] = prime[j]
      j += 1


manipulated_seive(100)

print(SPF)