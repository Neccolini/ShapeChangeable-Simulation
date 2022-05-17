#include <cstdio>
#include <fstream>
#include <iostream>

#include "json.hpp"
#include "shapechangeable-simulation/MultiProcess.h"
#include "shapechangeable-simulation/Network.h"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s <simulation source file>\n", argv[0]);
    _exit(1);
  }
  FILE* fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("error file %s not found\n", argv[1]);
    _exit(1);
  }
  // todo jsonファイルの場合とcsv形式の場合に対応したい
  // jsonの場合
  json j = json::parse(fp);
  fclose(fp);

  if (j["channel_info"] == nullptr || j["node_num"] == nullptr || j["channel_num"] == nullptr || j["roles"] == nullptr) {
    printf("the format of json file is incorrect.\n");
    _exit(1);
  }
  // todo 形式に関するassertionを設ける
  SimFile s = {
    .size = j["node_num"],
    .channel_num = j["channel_num"],
    .graph = j["channel_info"],
    .node_roles = j["roles"],
  };
  Network network = Network(s);
  MultiProcess mp = MultiProcess(s.size, network.node_roles);
  return 0;
}
