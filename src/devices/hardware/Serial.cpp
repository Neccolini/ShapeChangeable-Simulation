#include "shapechangeable-simulation/devices/hardware/Serial.h"

void HardwareSerial::print(String s) { std::printf(s.c_str()); }
void HardwareSerial::print(char* s) { std::printf(s); }
void HardwareSerial::println(String s) { std::puts(s.c_str()); }
void HardwareSerial::println(char* s) { std::puts(s); }
template <class... A>
void HardwareSerial::printf(String s, A... args) {
  std::printf(s.c_str(), args...);
}
template <class... A>
void HardwareSerial::printf(char* s, A... args) {
  std::printf(s, args...);
}
void HardwareSerial::begin(int rate) { return; }

HardwareSerial2::HardwareSerial2(std::vector<std::pair<int, int>>& ch) {
  this->ch = ch;

  for (auto fd : this->ch) {
    std::printf("%d %d\n", fd.w, fd.r);
    if (fd.w % 2)
      close(fd.w + 1);
    else
      close(fd.w - 1);
    if (fd.r % 2)
      close(fd.r + 1);
    else
      close(fd.r - 1);
  }
}

void HardwareSerial2::print(String s) {
  const char* cs = s.c_str();
  int n = strlen(cs);
  for (auto p : this->ch) {
    for (int i = 0; i < n; i++) {
      write(p.w, cs + i, 1);
    }
  }
}
void HardwareSerial2::println(String s) {
  s += "\n";
  const char* cs = s.c_str();
  int n = strlen(cs);
  for (auto p : this->ch) {
    for (int i = 0; i < n; i++) {
      write(p.w, cs + i, 1);
    }
  }
  /*
  s += "\n";
  char buf[256];
  sprintf(buf, s.c_str());
  for (auto p : this->ch) {
    write(p.w, buf, strlen(buf) + 1);
  }
  */
}

template <class... A>
void HardwareSerial2::printf(String s, A... args) {
  std::printf(s.c_str(), args...);  // todo not implemented フォーマット化された文字列の取り出し
}

int HardwareSerial2::available() {
  this->buff.clear();
  char read_buf[1025];
  for (auto fd : this->ch) {
    write(fd.w, "\n", 1);
    if (read(fd.r, read_buf, 1024) > 0) {
      this->buff += String(read_buf);
    }
  }

  /*
  char buf[2];
  for (auto p : this->ch) {
    puts("OK1");
    while (read(0, buf, 1) > 0) {
      this->buff += String(buf);
      std::printf("%s\n", buff);
    }
    puts("OK2");
  }
  */
  this->total_bytes += this->buff.size();
  return (int)this->buff.size();
}

String HardwareSerial2::readString() {
  String ret = this->buff;
  this->buff.clear();
  return ret;
}
void HardwareSerial2::begin(int rate) { return; }
