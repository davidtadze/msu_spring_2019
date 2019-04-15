//
// Created by David Davitadze on 04/04/2019.
//

#ifndef INC_04_SERIALIZER_H_
#define INC_04_SERIALIZER_H_

#include <iostream>

#include "error.h"

class Serializer {
    static constexpr char Separator = ' ';
public:
  explicit Serializer(std::ostream& out)
    : out_(out) {}

  template <class T>
  Error save(T& object) {
    return object.serialize(*this);
  }

  template <class... ArgsT>
  Error operator()(ArgsT... args) {
    return process(args...);
  }

private:
  std::ostream& out_;

  template <class T>
  Error process(T&& val) {
    return Error::CorruptedArchive;
  }

  Error process(bool& val) {
    std::string text;

    if (val)
      text = "true";
    else
      text = "false";

    out_ << text << Separator;
    return Error::NoError;
  }

  Error process(uint64_t& val) {
    std::string text(std::to_string(val));

    out_ << text << Separator;
    return Error::NoError;
  }

  template <class T, class... Args>
  Error process(T&& val, Args&&... args) {
    const Error err = process(val);
    if(err == Error::NoError)
      process(std::forward<Args>(args)...);
    else
      return Error::CorruptedArchive;

    return Error::NoError;
  }
};

#endif //INC_04_SERIALIZER_H_
