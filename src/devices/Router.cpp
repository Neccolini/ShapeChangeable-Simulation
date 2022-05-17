#pragma once
#include "shapechangeable-simulation/devices/Router.h"

#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

#include "shapechangeable-simulation/devices/hardware/Serial.h"

namespace Router {
HardwareSerial Serial;
static void setup() {}
static void loop() {
  while (true) {
    sleep(20);  // todo
    Serial.println("Router is working");
  }

  _exit(0);
}
}  // namespace Router

namespace Devices {
void Router() {
  Router::setup();
  Router::loop();
}
}  // namespace Devices
