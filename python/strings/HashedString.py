class HashedString:
  M, B, pow = 1e9 + 9, 9973, [1]
  
  def __init__(self, s):
    self.p_hash = [0] * (len(s) + 1)
    while len(self.pow) <= len(s):
      self.pow.append((self.pow[-1] * self.B) % self.M)
    
    for i in range(len(s)):
      self.p_hash[i + 1] = (self.p_hash[i] * self.B + ord(s[i])) % self.M

  def get_hash(self, start, end):
    raw_val = (self.p_hash[end + 1] - (self.p_hash[start] * self.pow[end - start + 1])) % self.M
    return (raw_val + self.M) % self.M
