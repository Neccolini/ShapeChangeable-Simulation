#include "shapechangeable-simulation/Network.h"

Network::Network(SimFile s) {
  if (s.size > MAX_NODES) {
    printf("error: too many nodes\n");
    _exit(0);
  }
  this->chs.resize(s.size);
  for (std::string role : s.node_roles) {
    if(role == std::string("ROUTER")) {
      this->node_roles.emplace_back(ROUTER);
    } else if(role == std::string("CORDINATOR")) {
      this->node_roles.emplace_back(CORDINATOR);
    }
  }
  int pp_idx = 0;
  for (int node_a = 0; node_a < s.graph.size(); node_a++) {
    for (int node_b : s.graph[node_a]) {
      // node_aとnode_bをつなぐ
      pipe(pp[pp_idx]);
      this->chs[node_a].emplace_back(channel{.node_a = node_a, .node_b = node_b, .channel_no = pp_idx});
    }
  }
}
