#include "shapechangeable-simulation/devices/Router.h"

#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

#include "shapechangeable-simulation/devices/hardware/Serial.h"

namespace Router {
HardwareSerial Serial;
void setup(HardwareSerial2& Serial2) {
  // here
  Serial.begin(9600);
}
void loop(HardwareSerial2& Serial2) {
  while (true) {
    if (Serial2.available() > 0) {
      String recv;
      recv = Serial2.readString();
      if (int idx = recv.indexOf("RTS") != -1) {
        Serial2.print("CTS");
      } else {
        Serial.println(recv);
      }
    }
    sleep(2);
  }
}
}  // namespace Router

namespace Devices {
void Router(std::vector<std::pair<int, int>>& ch) {
  HardwareSerial2 Serial2 = HardwareSerial2(ch);
  Router::setup(Serial2);
  Router::loop(Serial2);
}
}  // namespace Devices
