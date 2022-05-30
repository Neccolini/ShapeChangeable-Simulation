#include "shapechangeable-simulation/devices/Router.h"

#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

#include "shapechangeable-simulation/devices/hardware/Serial.h"

namespace Router {
HardwareSerial Serial;
bool waiting_data = false;
void setup(HardwareSerial2& Serial2) {
  // here
  Serial.begin(9600);
}
void loop(HardwareSerial2& Serial2) {
  while (true) {
    if (Serial2.available() > 0) {
      String recv;
      recv = Serial2.readString();
      std::printf("Router recieved: %s\n", recv.c_str());
      if (!waiting_data) {
        if (recv.indexOf("RTS") != -1) {
          Serial2.print("CTS");
          waiting_data = true;
        }
      } else {
        waiting_data = false;
      }
    }
    sleep(1);
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
