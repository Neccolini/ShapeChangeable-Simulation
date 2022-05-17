#include "shapechangeable-simulation/devices/hardware/Serial.h"

void HardwareSerial::print(std::string s) {
   std::printf(s.c_str());
}
void HardwareSerial::print(char* s) {
   std::printf(s);
}
void HardwareSerial::println(std::string s) {
    std::puts(s.c_str());
}
void HardwareSerial::println(char* s) {
    std::puts(s);
}
template<class... A>
void HardwareSerial::printf(std::string s, A... args) {
    std::printf(s.c_str(), args...);
}
template<class... A>
void HardwareSerial::printf(char* s, A... args) {
    std::printf(s, args...);
}

HardwareSerial2::HardwareSerial2(int channel) {
    HardwareSerial2::channel = channel;
}

void HardwareSerial2::print(std::string s) {
   
}
void HardwareSerial2::println(std::string s) {
    std::puts(s.c_str());
}
template<class... A>
void HardwareSerial2::printf(std::string s, A... args) {
    std::printf(s.c_str(), args...);
}
