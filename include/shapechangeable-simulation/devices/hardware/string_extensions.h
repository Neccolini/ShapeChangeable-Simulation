#pragma once

#include <iostream>
#include <string>

namespace string_extensions {
using namespace std;

struct string : std::string {
  using std::string::string;

 public:
  void print() { std::cout << *this << std::endl; }
  int indexOf(std::string s) {
    for (int i = 0; i < this->size() - s.size() + 1, i < this->size(); i++) {
      if (this->substr(i, s.size()) == s) {
        return i;
      }
    }
    return -1;
  }
};
}  // namespace string_extensions
