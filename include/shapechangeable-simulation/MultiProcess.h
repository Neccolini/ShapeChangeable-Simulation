#pragma once

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include <atomic>
#include <filesystem>
#include <vector>

#include "Network.h"
#include "devices/Devices.h"

constexpr std::atomic<int> handler_exit_code = 103;

class MultiProcess {
 public:
  std::atomic<int> child_pid;
  std::atomic<int> *children;
  std::atomic<int> children_num;
  MultiProcess(int children_num, std::vector<ROLE>& node_roles,std::vector<std::vector<channel>>& chs);
  // void sigquitHandler(int signal_number);

  template <class Fn>
  pid_t spawnChild(Fn func);
  template <class Fn>
  pid_t spawnChild(Fn func, std::vector<std::pair<int, int>>& ch, int i);
};
