#include <iostream>
#include <algorithm>
#include <iterator>

#include "numbers.dat"

int IntSqrt(int x) {
  if (x == 0 || x == 1)
    return x;

  int left = 1,
      right = x/2,
      ans = -1;

  while(left <= right) {
    int mid = (left + right) / 2;

    if(mid * mid == x)
      return mid;

    if (mid * mid < x) {
      left = mid + 1;
      ans = mid;
    } else
      right = mid-1;
  }

  return ans;
}

bool IsPrime(int x) {
  if(x == 1) return false;

  int top = IntSqrt(x);
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
    auto reversed_right_pos = std::find(std::rbegin(Data), std::rend(Data), right_element);

    if(left_pos  == std::end(Data) || reversed_right_pos == std::rend(Data)) {
      std::cout << 0 << std::endl;
      continue;
    }
    auto right_pos = reversed_right_pos.base() - 1;

    int num_of_primes = 0;
    for(auto j = left_pos; j <= right_pos; ++j) {
      if(IsPrime( Data[std::distance(Data, j)] ))
        ++num_of_primes;
    }

    std::cout << num_of_primes << std::endl;
  }

  return 0;
}
