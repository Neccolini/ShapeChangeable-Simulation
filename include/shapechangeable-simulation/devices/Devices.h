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
  std::map<ROLE, void (*)(std::vector<std::pair<int, int>>& ch)> role_to_func;
  RoleHandler();
};
