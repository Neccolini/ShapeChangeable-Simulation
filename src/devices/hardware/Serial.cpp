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
  /*
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
  */
}

void HardwareSerial2::print(String s) {
  String ss = String(SERIAL_STRING_BEGIN);
  ss += s;
  ss += String(SERIAL_STRING_END);
  const char* cs = ss.c_str();
  int n = strlen(cs);
  for (auto p : this->ch) {
    for (int i = 0; i < n; i++) {
      write(p.w, cs + i, 1);
    }
  }
}
void HardwareSerial2::println(String s) {
  s += "\n";
  String ss = String(SERIAL_STRING_BEGIN);
  ss += s;
  ss += String(SERIAL_STRING_END);

  const char* cs = s.c_str();
  int n = strlen(cs);
  for (auto p : this->ch) {
    for (int i = 0; i < n; i++) {
      write(p.w, cs + i, 1);
    }
  }

  /*
    char buf[ss.size() + 1];
    sprintf(buf, ss.c_str());
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
      std::string rs = std::string(read_buf);
      std::string one_msg;
      // std::printf("all: %s\n", rs.c_str());
      while (rs.find(SERIAL_STRING_BEGIN) != -1) {
        if (rs.find(SERIAL_STRING_END) != -1) {
          int idx = rs.find(SERIAL_STRING_BEGIN) + strlen(SERIAL_STRING_BEGIN);
          int idx_end = rs.find(SERIAL_STRING_END);
          // std::printf("%d %d\n", idx, idx_end);
          if (idx >= idx_end) break;
          one_msg = rs.substr(idx, idx_end - idx);
          this->buff += one_msg;
          rs = rs.substr(idx_end);
        } else
          break;
      }
    }
    write(fd.w, "\n", 1); // for linux?
  }
  this->total_bytes += this->buff.size();
  return (int)this->buff.size();
}

String HardwareSerial2::readString() {
  String ret = this->buff;
  this->buff.clear();
  return ret;
}
void HardwareSerial2::begin(int rate) { return; }
