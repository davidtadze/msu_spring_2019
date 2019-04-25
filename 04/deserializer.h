//
// Created by David Davitadze on 04/04/2019.
//

#ifndef INC_04_DESERIALIZER_H_
#define INC_04_DESERIALIZER_H_

#include <iostream>

#include "error.h"

class Deserializer {
  static constexpr char Separator = ' ';
 public:
  explicit Deserializer(std::istream& in)
      : in_(in) {}

  template <class T>
  Error load(T& object) {
    return object.serialize(*this);
  }

  template<class... Args>
  Error operator()(Args&&... args) {
    return process(std::forward<Args>(args)...);
  }

 private:
  std::istream& in_;

  template <class T, class... Args>
  Error process(T&& val, Args&&... args) {
    if(process(std::forward<T>(val)) == Error::CorruptedArchive) return Error::CorruptedArchive;
    return process(std::forward<Args>(args)...);
  }

  bool is_number(const std::string& s) {
    return !s.empty()
           && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
  }

  Error process(bool& val) {
    std::string text;
    in_ >> text;

    if (text == "true")
      val = true;
    else if (text == "false")
      val = false;
    else
      return Error::CorruptedArchive;

    return Error::NoError;
  }

  Error process(uint64_t& val) {
    std::string text;
    in_ >> text;

    if (is_number(text))
      val = std::stoi(text);
    else
      return Error::CorruptedArchive;

    return Error::NoError;
  }
};

#endif //INC_04_DESERIALIZER_H_
