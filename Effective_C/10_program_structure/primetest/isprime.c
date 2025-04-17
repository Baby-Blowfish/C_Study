#include "isprime.h"
#include <stdlib.h>

static unsigned long long power(unsigned long long x, unsigned long long y, unsigned long long p)
{
  unsigned long long res = 1;
  x = x % p;
  while(y)
  {
    if(y & 1)
      res = (res * x) % p;
    y = y >> 1;
    x = (x * x) % p;
  }
  return res;
}

static bool miller_rabin_test(unsigned long long d, unsigned long long n)
{
  unsigned long long a = 2 + rand() % (n - 4);
  unsigned long long x = power(a, d, n);

  if(x == 1 || x == n - 1) return true;

  while(d != n - 1)
  {
    x = (x * x) % n;
    d *= 2;

    if(x == 1) return false;
    if(x == n - 1) return true;
  }
  return false;
}

bool is_prime(unsigned long long n, int k)
{
  if(n <= 1 || n == 4) return false;
  if(n <= 3) return true;

  unsigned long long d = n - 1;
  while(d % 2 == 0)
    d /= 2;

  for(int i = 0; i < k; i++)
    if(!miller_rabin_test(d, n))
      return false;
  return true;
}