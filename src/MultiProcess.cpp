#include "shapechangeable-simulation/MultiProcess.h"

#include <string.h>
#include <sys/types.h>
#include <unistd.h>
MultiProcess::MultiProcess(int children_num, std::vector<ROLE>& node_roles, std::vector<std::vector<channel>>& chs) {
  RoleHandler Roles;
  this->children_num = children_num;
  children = reinterpret_cast<std::atomic<int>*>(new int[this->children_num]);

  for (int i = 0; i < this->children_num; i++) {
    std::vector<std::pair<int, int>> vp;
    for (auto c : chs[i]) {
      vp.emplace_back(std::pair(c.read, c.write));
    }
    children[i] = spawnChild(Roles.role_to_func[node_roles[i]], vp, i);
  }
}
/*
void MultiProcess::sigquitHandler(int signal_number) {
for (int i = 0; i < this->children_num; ++i) {
  kill(this->children[i], SIGTERM);
  printf("killed child process: %d\n", children[i]);
}
while ((child_pid = wait(nullptr)) > 0)
  ;
_exit(handler_exit_code);
}
*/
template <class Fn>
pid_t MultiProcess::spawnChild(Fn func) {
  pid_t ch_pid = fork();
  if (ch_pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (ch_pid > 0) {
    printf("spawn child with pid - %d\n", ch_pid);
    return ch_pid;
  } else {
    // 実行
    func();
    exit(EXIT_FAILURE);
  }
}
template <class Fn>
pid_t MultiProcess::spawnChild(Fn func, std::vector<std::pair<int, int>>& ch, int i) {
  pid_t ch_pid = fork();
  if (ch_pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (ch_pid > 0) {
    printf("spawn child with pid - %d\n", ch_pid);
    return ch_pid;
  } else {
    func(ch);
    exit(EXIT_FAILURE);
  }
}
