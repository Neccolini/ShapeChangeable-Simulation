#pragma once
#include <sys/wait.h>
#include <unistd.h>

#include "shapechangeable-simulation/devices/hardware/Serial.h"

namespace Cordinator {
HardwareSerial Serial;
static void setup() {}
static void loop() {
  while (true) {
    sleep(10);  // todo
    Serial.println("Cordinator is working");
  }

  _exit(0);
}
}  // namespace Cordinator

namespace Devices {
void Cordinator() {
  Cordinator::setup();
  Cordinator::loop();
}
}  // namespace Devices
