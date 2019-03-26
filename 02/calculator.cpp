//
// Created by David Davitadze on 21/03/2019.
//

#include <stdexcept>

#include "calculator.hpp"

using namespace dt;

int Calculator::get_grammar() {
  if(expr_[cur_pos] == ' ') move_pos();
  int val = get_summation();
  if(expr_[cur_pos] == ' ') move_pos();

  if(  expr_.begin() + cur_pos != expr_.end()) throw std::runtime_error{"couldn't interpret input"};

  return val;
}

int Calculator::get_summation() {
  int val_a = get_multiplication();

  while(expr_[cur_pos] == '+' || expr_[cur_pos] == '-') {
    int op = expr_[cur_pos];
    move_pos();

    int val_b = get_multiplication();

    if(op == '+') {
      val_a += val_b;
    } else {
      val_a -= val_b;
    }
  }

  return val_a;
}

int Calculator::get_multiplication() {
  int val_a = get_number();

  while(expr_[cur_pos] == '*' || expr_[cur_pos] == '/') {
    int op = expr_[cur_pos];
    move_pos();

    int val_b = get_number();

    if(op == '*') {
      val_a *= val_b;
    } else {
      if(val_b == 0) throw std::runtime_error{"division by zero"};
      val_a /= val_b;
    }
  }

  return val_a;
}

int Calculator::get_number() {
  int val = 0;
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
    }

    val = val*10 + expr_[cur_pos] - '0';
    ++cur_pos;
  }
  if(!is_number) throw std::runtime_error{"not a number"};
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