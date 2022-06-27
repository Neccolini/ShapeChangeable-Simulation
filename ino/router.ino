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

const int CORDINATOR_ID = 0;
bool joined = false;
bool resend = false;
int my_id;
int pnt_id;
map<int, int> dst_id_table;  // 目的のid -> その方向の隣接ノードid
bool update_table(int dst_id, int nbr_id) { dst_id_table[dst_id] = nbr_id; }
bool table_find(int dst_id) {
  if (dst_id_table.find(dst_id) == dst_id_table.end()) {
    return false;
  } else {
    return true;
  }
}
void setup() {
  random_device rnd;
  int random_value = rnd();
  random_value = random_value < 0 ? -random_value : random_value;
  my_id = random_value < 10000 ? random_value + 10000 : random_value;
}

void loop() {
  std::printf("my_id -> %d pid -> %d\n", my_id, getpid());
  if (!joined) {
    // コーディネータに対し参加要求を送る
    packet join_request = packet(String("joinrequest"), my_id, my_id, CORDINATOR_ID, resend, -1);
    // Serial.println(join_request.into_string());
    Serial2.print(join_request.into_string());
  }
  if (Serial2.available() > 0) {
    vector<String> pkt_list = Serial2.readString().split('/');
    for (auto pkt : pkt_list) {
      if (pkt == "") continue;
      packet p = packet(pkt);
      if (p.prv_prv_id == my_id) continue;  // 自分が送ったパケットは受け取らない

      if (p.dst_id != my_id && (p.nbr_dst_id == my_id || p.nbr_dst_id == -1)) {  // ルーティング
        update_table(p.src_id, p.prv_id);                                        // todo どのタイミングでどうやってテーブル更新する?
        int nbr_dst_id = table_find(p.dst_id) ? dst_id_table[p.dst_id] : -1;
        Serial2.print(packet(p.msg, my_id, p.src_id, p.dst_id, p.resend, p.pnt_id, p.prv_id, nbr_dst_id).into_string());
        // std::printf("myid: %d, routing: %s\n",my_id, packet(p.msg, my_id, p.src_id, p.dst_id, p.resend, p.pnt_id, p.prv_id, nbr_dst_id).into_string().c_str());
        continue;
      }

      if (p.dst_id == my_id) {  // 自分宛てだった場合
        vector<String> msg_list = p.msg.split(' ');
        if (msg_list[0] == String("Grant_id") && !joined) {  // 真IDの取得
          update_table(p.src_id, p.prv_id);                  // todo どのタイミングでどうやってテーブル更新する?
          my_id = msg_list[1].toInt();
          std::printf("myid: %d, message %s received from %d\n", my_id, p.msg.c_str(), p.src_id);
          pnt_id = p.prv_id;
          joined = true;
        } else {
          std::printf("myid: %d message %s received from %d\n", my_id, p.msg.c_str(), p.src_id);
        }
      }
    }
  }
  if (joined) {
    int dst_id = 1;
    if (dst_id != my_id) {
      int nbr_dst_id = table_find(dst_id) ? dst_id_table[dst_id] : -1;
      packet test_p = packet("test", my_id, my_id, 1, false, pnt_id, -1, nbr_dst_id);
      std::printf("myid: %d, sending msg to %d\n", my_id, dst_id);
      Serial2.print(test_p.into_string());
    }
  }
  sleep(1);
}
