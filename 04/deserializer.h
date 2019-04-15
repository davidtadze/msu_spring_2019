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

  template <class... ArgsT>
  Error operator()(ArgsT&... args) {
    return process(args...);
  }

 private:
  std::istream& in_;

  bool is_number(const std::string& s) {
    return !s.empty()
           && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
  }

  Error process(bool& val) {
    std::string text;
    in_ >> text;

    if (text == "true") {
      val = true;
    }
    else if (text == "false")
      val = false;
    else
      //std::cout << "oops!!" << std::endl;
      //std::cout << "text = " << text << std::endl;
      return Error::CorruptedArchive;

    return Error::NoError;
  }

  Error process(uint64_t& val) {
    std::string text;
    in_ >> text;

    if (is_number(text)) {
      val = std::stoi(text);
    }
    else
      return Error::CorruptedArchive;

    return Error::NoError;
  }

  template <class T, class... Args>
  Error process(T&& val, Args&&... args) {
    Error err = process(val);
    if(err == Error::NoError)
      err = process(std::forward<Args>(args)...);

    return err;
  }
};

#endif //INC_04_DESERIALIZER_H_
