#pragma once

#include <stdio.h>
#include <unistd.h>

#include <vector>

#include "devices/Devices.h"

#define MAX_NODES 2000
#define MAX_CHANNEL 10

struct SimFile {
  int size;
  int channel_num;  // 一ノード当たりのチャネル数
  std::vector<std::vector<int>> graph;
  std::vector<std::string> node_roles;
};

struct channel {
  int node_a, node_b;
  int channel_no;  // 割り当てられたチャネル番号
};

class Network {
 public:
  Network(SimFile s);
  int pp[MAX_NODES * MAX_CHANNEL][2];  // todo 動的確保にする
  std::vector<std::vector<channel>> chs;
  std::vector<ROLE> node_roles;
};
