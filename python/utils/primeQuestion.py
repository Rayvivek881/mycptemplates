def manipulated_sieve(MAXN):
  isprime, prime, SPF = [1] * MAXN, [], [0] * MAXN 
  isprime[0] = isprime[1] = 0
  
  for i in range(2, MAXN):
    if isprime[i]:
      prime.append(i)
      SPF[i] = i
    for p in prime:
      if i * p >= MAXN or p > SPF[i]:
        break
      isprime[i * p], SPF[i * p] = False, p
  
  return isprime, prime, SPF

# Example usage:
MAXN = 10000000
isprime, prime, SPF = manipulated_sieve(MAXN)