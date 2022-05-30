#pragma once

#include <string.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "string_extensions.h"

#define r first
#define w second
#define TEST
#define totalN 256
#define SERIAL_STRING_BEGIN "SERIAL_STRING_BEGIN"
#define SERIAL_STRING_END "SERIAL_STRING_END"

typedef string_extensions::string String;

class HardwareSerial {
 public:
  void print(String s);
  void print(char* s);
  void println(String s);
  void println(char* s);
  template <class... A>
  void printf(String s, A... args);
  template <class... A>
  void printf(char* s, A... args);
  void begin(int rate);
};

// 通信
class HardwareSerial2 {
 private:
  String buff;
  unsigned long total_bytes = 0;

 public:
  HardwareSerial2(std::vector<std::pair<int, int>>& ch);
  std::vector<std::pair<int, int>> ch;

  void print(String s);
  void println(String s);
  template <class... A>
  void printf(String s, A... args);
  int available();
  String readString();
  void begin(int rate);
};
