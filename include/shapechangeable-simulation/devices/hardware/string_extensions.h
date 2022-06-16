#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace string_extensions {
using namespace std;

struct string : std::string {
  using std::string::string;

 public:
  void print() { std::cout << *this << std::endl; }
  int indexOf(string s) {
    for (int i = 0; i < this->size() - s.size() + 1, i < this->size(); i++) {
      if (this->substr(i, s.size()) == s) {
        return i;
      }
    }
    return -1;
  }
  vector<string> split(char sep = ' ') {
    string s = *this;
    vector<string> elems;
    string item;
    for (auto ch : s) {
      if (ch == sep) {
        if (!item.empty()) elems.push_back(item);
        item.clear();
      } else {
        item += ch;
      }
    }
    if (!item.empty()) elems.push_back(item);
    return elems;
  }
  int toInt() {
    int ret = 0;
    string s = *this;
    int n = s.length();
    int digit = 1;
    if (s[0] == '-') {
      for (int i = 0; i < n - 1; i++) {
        char d = s[n - i - 1];
        ret += (int)(d - '0') * digit;
        digit *= 10;
      }
      ret = -ret;
    } else {
      for (int i = 0; i < n; i++) {
        char d = s[n - i - 1];
        ret += (d - '0') * digit;
        digit *= 10;
      }
    }
    return ret;
  }
};
}  // namespace string_extensions

string_extensions::string ItoString(int x);
