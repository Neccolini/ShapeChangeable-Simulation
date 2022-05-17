#include "shapechangeable-simulation/MultiProcess.h"
#include "shapechangeable-simulation/devices/Devices.h"

MultiProcess::MultiProcess(int children_num, std::vector<ROLE> node_roles) {
    RoleHandler Roles;
    this->children_num = children_num;
    children = reinterpret_cast<std::atomic<int> *>(new int[this->children_num]);
    for (int i = 0; i < this->children_num; i++) {
      children[i] = spawnChild(Roles.role_to_func[node_roles[i]]);
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
template <class Fn, class... A>
pid_t MultiProcess::spawnChild(Fn func, A... args) {
  pid_t ch_pid = fork();
  if (ch_pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (ch_pid > 0) {
    printf("spawn child with pid - %d\n", ch_pid);
    return ch_pid;
  } else {
    // 実行
    func(args...);
    exit(EXIT_FAILURE);
  }
}
