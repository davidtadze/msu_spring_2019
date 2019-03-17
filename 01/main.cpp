#include <iostream>
#include <math.h>
#include <algorithm>

#include "numbers.dat"

bool isPrime(int x) {
  if(x == 1) return false;

  int top = sqrt(x);
  for (int i = 2; i <= top; ++i) {
    if(x % i == 0)
      return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  if(argc % 2 != 1 || argc == 1)
    return -1;

  for (int i = 1; i < argc; i+=2) {
    int left_element = std::atoi(argv[i]);
    int right_element = std::atoi(argv[i+1]);

    auto left_pos  = std::find(std::begin(Data), std::end(Data), left_element );
    auto right_pos = std::find(std::begin(Data), std::end(Data), right_element);

    if(left_pos  == std::end(Data) || right_pos == std::end(Data)) {
      std::cout << 0 << std::endl;
      continue;
    }

    int num_of_primes = 0;
    for(auto j = left_pos; j <= right_pos; ++j) {
      if(isPrime( Data[std::distance(Data, j)] ))
        ++num_of_primes;
    }

    std::cout << num_of_primes << std::endl;
  }

  return 0;
}
