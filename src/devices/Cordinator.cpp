#include "shapechangeable-simulation/devices/Cordinator.h"

#include <sys/wait.h>
#include <unistd.h>

#include "shapechangeable-simulation/devices/hardware/Serial.h"

namespace Cordinator {
using namespace std;
using namespace string_extensions;
HardwareSerial Serial;
// _GLOBAL_VARIABLES_BEGIN_ THIS COMMENT SHOULD NOT BE DELETED.
// _GLOBAL_VARIABLES_END_ THIS COMMENT SHOULD NOT BE DELETED.
inline void setup(HardwareSerial2& Serial2) {
  // _SETUP_BEGIN_ THIS COMMNET SHOULD NOT BE DELETED.
  // _SETUP_END_ THIS COMMENT SHOULD NOT BE DELETED.
}
inline void loop(HardwareSerial2& Serial2) {
  while (true) {
    // _LOOP_BEGIN_ THIS COMMNET SHOULD NOT BE DELETED.
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
