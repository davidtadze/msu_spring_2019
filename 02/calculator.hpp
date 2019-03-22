//
// Created by David Davitadze on 21/03/2019.
//

#ifndef MSU_SPRING_2019_02_CALCULATOR_H_
#define MSU_SPRING_2019_02_CALCULATOR_H_

#include <string>

namespace dt {

class Calculator {
 private:
  std::string expr_;
  int cur_pos = 0;

  // grammar:
  // grammar ::= summation\0
  // summation ::= multiplication{[+-]+multiplication}*
  // multiplication ::= number{[*/]number}*
  // number ::= -[0-9]+

  int get_grammar();
  int get_summation();
  int get_multiplication();
  int get_number();

  void move_pos();

 public:
  int evaluate(const std::string& expr);
};

}  // namespace dt

#endif //MSU_SPRING_2019_02_CALCULATOR_H_
