#include "shapechangeable-simulation/devices/Cordinator.h"

#include <sys/wait.h>
#include <unistd.h>

#include "shapechangeable-simulation/devices/hardware/Serial.h"

namespace Cordinator {
HardwareSerial Serial;
// _GLOBAL_VARIABLES_BEGIN_ THIS COMMENT SHOULD NOT BE DELETED.
bool can_send = false;

// _GLOBAL_VARIABLES_END_ THIS COMMENT SHOULD NOT BE DELETED.
inline void setup(HardwareSerial2& Serial2) {
  // _SETUP_BEGIN_ THIS COMMNET SHOULD NOT BE DELETED.
 Serial.begin(9600); 
  // _SETUP_END_ THIS COMMENT SHOULD NOT BE DELETED.
}
inline void loop(HardwareSerial2& Serial2) {
  while (true) {
    // _LOOP_BEGIN_ THIS COMMNET SHOULD NOT BE DELETED.

  if (!can_send) {
    String req = "RTS";
    Serial2.print(req);
  }
  if (Serial2.available() > 0) {
    String rep = Serial2.readString();
    if (rep.indexOf("CTS") != -1) {
      can_send = true;
      String data = "this is a data.";
      Serial2.print(data);
    }
  }
  sleep(3);

    // _LOOP_END_ THIS COMMNET SHOULD NOT BE DELETED.
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
