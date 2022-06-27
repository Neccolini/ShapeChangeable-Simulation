class packet {
 public:
  int prv_id;
  int prv_prv_id;
  int src_id;
  int dst_id;
  bool resend;
  int pnt_id;
  int nbr_dst_id;
  String msg;
  packet(String msg, int prv_id, int src_id, int dst_id, bool resend, int pnt_id, int prv_prv_id = -1, int nbr_dst_id = -1) {
    this->msg = msg;
    this->prv_id = prv_id;
    this->src_id = src_id;
    this->dst_id = dst_id;
    this->resend = resend;
    this->pnt_id = pnt_id;
    this->prv_prv_id = prv_prv_id;
    this->nbr_dst_id = nbr_dst_id;
  }
  packet(String raw_msg) {
    std::vector<String> list = raw_msg.split(',');
    this->prv_id = list[0].toInt();
    this->src_id = list[1].toInt();
    this->dst_id = list[2].toInt();
    this->pnt_id = list[3].toInt();
    this->resend = list[4] == String("true") ? true : false;
    this->msg = list[5];
    this->prv_prv_id = list[6].toInt();
    this->nbr_dst_id = list[7].toInt();
  }
  String into_string() {
    String ret = "/";
    ret += ItoString(this->prv_id);
    ret += ",";
    ret += ItoString(this->src_id);
    ret += ",";
    ret += ItoString(this->dst_id);
    ret += ",";
    ret += ItoString(this->pnt_id);
    ret += ",";
    ret += String(this->resend ? "true" : "false");
    ret += ",";
    ret += this->msg;
    ret += ",";
    ret += ItoString(this->prv_prv_id);
    ret += ",";
    ret += ItoString(this->nbr_dst_id);
    ret += "/";
    return ret;
  }
};

int my_id = 0;
int id_count_up = 1;
bool resend = false;
map<int, int> random_id_table;  // random id -> 真のid
map<int, int> dst_id_table;     // 目的のid -> その方向の隣接ノードid
inline bool update_table(int key_id, int val_id, map<int, int> table) { table[key_id] = val_id; }
inline bool table_find(int id, map<int, int> table) {
  if (table.find(id) == table.end()) {
    return false;
  } else {
    return true;
  }
}

void setup() {}
void loop() {
  // std::printf("my_id -> %d pid -> %d\n", my_id, getpid());
  if (Serial2.available() > 0) {
    vector<String> req_list = Serial2.readString().split('/');
    for (auto req_str : req_list) {  // 来たパケットを順に処理していく
      if (req_str == "") continue;
      packet p = packet(req_str);
      if (p.prv_prv_id == my_id) continue;  // 自分が送信したパケットは受け取らない
      if (p.dst_id != my_id && (p.nbr_dst_id == my_id || p.nbr_dst_id == -1)) {  // ルーティング
        dst_id_table[p.src_id] = p.prv_id;
        int nbr_dst_id = table_find(p.dst_id, dst_id_table) ? dst_id_table[p.dst_id] : -1;
        Serial2.print(packet(p.msg, my_id, p.src_id, p.dst_id, p.resend, p.pnt_id, p.prv_id, nbr_dst_id).into_string());
        // std::printf("myid: %d, routing: %s\n",my_id, packet(p.msg, my_id, p.src_id, p.dst_id, p.resend, p.pnt_id, p.prv_id, nbr_dst_id).into_string().c_str());
        continue;
      }
      if (p.msg == "joinrequest") {  // 参加要求に対し，真のidを返す
        if (!table_find(p.src_id, random_id_table)) {
          random_id_table[p.src_id] = id_count_up++;
          // std::printf("assigned %d to %d\n", random_id_table[p.src_id], p.src_id);
        }
        // std::printf("assigned %d to %d\n", random_id_table[p.src_id], p.src_id);
        String msg = "Grant_id ";
        msg += ItoString(random_id_table[p.src_id]);
        int dst_pnt_id = p.pnt_id == -1 ? 0 : p.pnt_id;
        packet rep = packet(msg, my_id, my_id, p.src_id, resend, -1, dst_pnt_id);
        Serial2.print(rep.into_string());
      }
    }
  }
  sleep(2);
  // std::exit(0);
}
