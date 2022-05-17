#pragma once

#include <string>

class HardwareSerial {
 public:
  void print(std::string s);
  void print(char* s);
  void println(std::string s);
  void println(char* s);
  template <class... A>
  void printf(std::string s, A... args);
  template <class... A>
  void printf(char* s, A... args);
};

// 通信
class HardwareSerial2 {
 private:
  HardwareSerial2(int channel);
  int channel;

 public:
  void print(std::string s);
  void println(std::string s);
  template <class... A>
  void printf(std::string s, A... args);
};
