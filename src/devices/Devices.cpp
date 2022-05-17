#include "shapechangeable-simulation/devices/Devices.h"

RoleHandler::RoleHandler() {
  this->role_to_func = {{ROUTER, Devices::Router}, {CORDINATOR, Devices::Cordinator}};
}
