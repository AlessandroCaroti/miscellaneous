#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <stdint.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


//      ./segmented_sieve 180000000 10000000 998 grandi.txt       tra 1.8*10^8 e 1.0*10^7
//      ./segmented_sieve 99000     6000     300 piccoli.txt


/// Set your CPU's L1 data cache size (in bytes) here
const int64_t L1D_CACHE_SIZE = 32768;
int perc;

void segmented_sieve(int64_t limit, int64_t toPrintStart, char* fileName)
{
  int64_t sqrt = (int64_t) std::sqrt(limit);
  int64_t segment_size = std::max(sqrt, L1D_CACHE_SIZE);
  int64_t count = (limit < 2) ? 0 : 1;

  // we sieve primes >= 3
  int64_t i = 3;
  int64_t n = 3;
  int64_t s = 3;

  std::vector<char> sieve(segment_size);
  std::vector<char> is_prime(sqrt + 1, true);
  std::vector<int64_t> primes;
  std::vector<int64_t> multiples;

  std::ofstream myfile;
  myfile.open (fileName);
  if(!myfile.is_open()){
     std::cerr << "Unable to open file";
     exit(-1);
  }

  for (int64_t low = 0; low <= limit; low += segment_size)
  {
    std::fill(sieve.begin(), sieve.end(), true);

    // current segment = [low, high]
    int64_t high = low + segment_size - 1;
    high = std::min(high, limit);

    // generate sieving primes using simple sieve of Eratosthenes
    for (; i * i <= high; i += 2)
      if (is_prime[i])
        for (int64_t j = i * i; j <= sqrt; j += i)
          is_prime[j] = false;

    // initialize sieving primes for segmented sieve
    for (; s * s <= high; s += 2)
    {
      if (is_prime[s])
      {
           primes.push_back(s);
        multiples.push_back(s * s - low);
      }
    }

    // sieve the current segment
    for (std::size_t i = 0; i < primes.size(); i++)
    {
      int64_t j = multiples[i];
      for (int64_t k = primes[i] * 2; j < segment_size; j += k)
        sieve[j] = false;
      multiples[i] = j - segment_size;
    }
	
    for (; n <= high; n += 2)
      if (sieve[n - low] && n>toPrintStart && (rand() % 1000 )>perc){ // n is a prime
            myfile << n << " ";
            count++;
      };
  }
   myfile.close();
   std::cout << count << " primes found." << std::endl;
}

/// Usage: ./segmented_sieve n
/// @param n  Sieve the primes up to n.
///
int main(int argc, char** argv)
{
  srand (time(NULL));
  if (argc >= 5){
    perc = std::atoi(argv[3]);
    segmented_sieve(std::atoll(argv[1]), std::atoll(argv[2]), argv[4]);
  }
  else
    return -1;

  return 0;
}