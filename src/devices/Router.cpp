#include "shapechangeable-simulation/devices/Router.h"

#include <sys/wait.h>
#include <unistd.h>

#include "shapechangeable-simulation/devices/hardware/Serial.h"

namespace Router {
HardwareSerial Serial;
// _GLOBAL_VARIABLES_BEGIN_ THIS COMMENT SHOULD NOT BE DELETED.
bool waiting_data = false;

// _GLOBAL_VARIABLES_END_ THIS COMMENT SHOULD NOT BE DELETED.
inline void setup(HardwareSerial2& Serial2) {
  // _SETUP_BEGIN_ THIS COMMNET SHOULD NOT BE DELETED.
 Serial.begin(9600); 
  // _SETUP_END_ THIS COMMENT SHOULD NOT BE DELETED.
}
inline void loop(HardwareSerial2& Serial2) {
  while (true) {
    // _LOOP_BEGIN_ THIS COMMNET SHOULD NOT BE DELETED.

  if (Serial2.available() > 0) {
    String recv;
    recv = Serial2.readString();
    if (!waiting_data) {
      if (recv.indexOf("RTS") != -1) {
        Serial2.print("CTS");
        waiting_data = true;
      }
    } else {
      waiting_data = false;
    }
  }
  sleep(3);

    // _LOOP_END_ THIS COMMNET SHOULD NOT BE DELETED.
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
