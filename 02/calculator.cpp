//
// Created by David Davitadze on 21/03/2019.
//

#include <exception>

#include "calculator.hpp"

using namespace dt;

int Calculator::get_grammar() {
  if(expr_[cur_pos] == ' ') move_pos();
  int val = get_summation();
  if(expr_[cur_pos] == ' ') move_pos();

  // 0xDEADBEEF as indicator of incorrect number
  if(  expr_.begin() + cur_pos != expr_.end()
    || val == 0xDEADBEEF) throw std::runtime_error("couldn't interpret input");

  return val;
}

int Calculator::get_summation() {
  // check for correct number after operand
  // this is needed for cases like +2 (should be incorrect)
  int val_a = get_multiplication();
  if(val_a == 0xDEADBEEF) return val_a;

  while(expr_[cur_pos] == '+' || expr_[cur_pos] == '-') {
    int op = expr_[cur_pos];
    move_pos();

    // check for correct number after operand
    // this is needed for cases like 4++4 or 2+ (should be incorrect)
    int val_b = get_multiplication();
    if(val_b == 0xDEADBEEF) return val_b;

    if(op == '+') {
      val_a += val_b;
    } else {
      val_a -= val_b;
    }
  }

  return val_a;
}

int Calculator::get_multiplication() {
  // check for correct number after operand
  // this is needed for cases like /2 (should be incorrect)
  int val_a = get_number();
  if(val_a == 0xDEADBEEF) return val_a;

  while(expr_[cur_pos] == '*' || expr_[cur_pos] == '/') {
    int op = expr_[cur_pos];
    move_pos();

    // check for correct number after operand
    // this is needed for cases like 4**4 or 2/ (should be incorrect)
    int val_b = get_number();
    if(val_b == 0xDEADBEEF) return val_b;

    if(op == '*') {
      val_a *= val_b;
    } else {
      if(val_b == 0) return 0xDEADBEEF;
      val_a /= val_b;
    }
  }

  return val_a;
}

int Calculator::get_number() {
  int val = 0xDEADBEEF;
  bool is_number = false;

  // check for negative number
  int k = 1;
  while(expr_[cur_pos] == '-') {
    k = -1 * k;
    move_pos();
  }

  while(std::isdigit(expr_[cur_pos])) {
    if(!is_number) {
      is_number = true;
      val = 0;
    }

    val = val*10 + expr_[cur_pos] - '0';
    ++cur_pos;
  }
  if(expr_[cur_pos] == ' ') move_pos();

  return val * k;
}

void Calculator::move_pos() {
  ++cur_pos;
  while(expr_[cur_pos] == ' ') {
    ++cur_pos;
  }
}

int Calculator::evaluate(const std::string& expr) {
  expr_ = expr;
  cur_pos = 0;
  return get_grammar();
}