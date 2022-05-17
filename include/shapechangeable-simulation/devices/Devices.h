#pragma once
#include <map>

#include "Cordinator.h"
#include "Router.h"

enum ROLE {
  ROUTER,
  CORDINATOR,
  END_DEVICE,
};

class RoleHandler {
 public:
  std::map<ROLE, void (*)()> role_to_func;
  RoleHandler();
};

extern RoleHandler Roles;
