#include "shapechangeable-simulation/Network.h"

#include <string>

Network::Network(SimFile s) {
  if (s.size > MAX_NODES) {
    printf("error: too many nodes\n");
    _exit(0);
  }
  this->chs.resize(s.size);
  for (std::string role : s.node_roles) {
    if (role == std::string("ROUTER")) {
      this->node_roles.emplace_back(ROUTER);
    } else if (role == std::string("CORDINATOR")) {
      this->node_roles.emplace_back(CORDINATOR);
    }
  }
  for(int i = 0; i < 2 * s.size * s.channel_num; i++) {
    pipe(this->pp[i]);
  }
  int pp_idx = 0;
  for (int node_a = 0; node_a < s.graph.size(); node_a++) {
    for (int node_b : s.graph[node_a]) {
      // node_aとnode_bをつなぐ
      int channel1 = pp_idx, channel2 = pp_idx + 1;
      // std::printf("pipe between `%d` and `%d` is `%d, %d`\n", node_a, node_b, pp[pp_idx][0], pp[pp_idx][1]);
      this->chs[node_b].emplace_back(channel{.read = pp[pp_idx][0], .write = pp[pp_idx+1][1]});
      // std::printf("pipe between `%d` and `%d` is `%d, %d`\n", node_b, node_a, pp[pp_idx+1][0], pp[pp_idx+1][1]);
      this->chs[node_a].emplace_back(channel{.read = pp[pp_idx+1][0], .write = pp[pp_idx][1]});
      pp_idx += 2;
    }
  }
}
