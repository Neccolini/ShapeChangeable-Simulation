#pragma once

#include <stdio.h>
#include <unistd.h>

#include <vector>

#include "devices/Devices.h"

#define MAX_NODES 100
#define MAX_CHANNEL 8

struct SimFile {
  int size;
  int channel_num;  // 一ノード当たりのチャネル数
  std::vector<std::vector<int>> graph;
  std::vector<std::string> node_roles;
};

struct channel {
  int read, write;
};

class Network {
 public:
  Network(SimFile s);
  int pp[2 * MAX_NODES * MAX_CHANNEL][2];  // todo 動的確保にする
  // std::vector<std::vector<channel>> chs;
  std::vector<ROLE> node_roles;
  std::vector<std::vector<channel>> chs;
};
