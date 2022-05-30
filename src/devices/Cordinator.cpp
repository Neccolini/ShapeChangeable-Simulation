#include "shapechangeable-simulation/devices/Cordinator.h"

#include <sys/wait.h>
#include <unistd.h>

#include "shapechangeable-simulation/devices/hardware/Serial.h"

namespace Cordinator {
HardwareSerial Serial;
bool can_send = false;
inline void setup(HardwareSerial2& Serial2) {
  // here
  Serial.begin(9600);
}
inline void loop(HardwareSerial2& Serial2) {
  while (true) {
    if (!can_send) {
      String req = "RTS";
      Serial2.print(req);
    }
    if (Serial2.available() > 0) {
      String rep = Serial2.readString();
      std::printf("Cordinator received: %s\n", rep.c_str());
      if (rep.indexOf("CTS") != -1) {
        can_send = true;
        Serial2.print("this is a data.");
      }
    }
    sleep(1);
  }
}
}  // namespace Cordinator

namespace Devices {
void Cordinator(std::vector<std::pair<int, int>>& ch) {
  HardwareSerial2 Serial2 = HardwareSerial2(ch);
  Cordinator::setup(Serial2);
  Cordinator::loop(Serial2);
}
}  // namespace Devices
