#include <iostream>

#include "calculator.hpp"

int main(int argc, char* argv[]) {
  if(argc != 2){
    std::cout << "error" <<std::endl;
    return 1;
  }

  std::string expr(argv[1]);
  //std::string expr;
  //std::getline(std::cin, expr);

  try {
    dt::Calculator calculator;
    std::cout << calculator.evaluate(expr) << std::endl;
  } catch (const std::runtime_error& error) {
    // should print 'error' to pass tests
    std::cout << "error" << std::endl;
    return 1;
  }

  return 0;
}