class packet {
 public:
  int prv_id;
  int src_id;
  int dst_id;
  bool resend;
  int pnt_id;
  int trg_pnt_id;
  String msg;
  packet(String msg, int prv_id, int src_id, int dst_id, bool resend, int pnt_id, int trg_pnt_id = -1) {
    this->msg = msg;
    this->prv_id = prv_id;
    this->src_id = src_id;
    this->dst_id = dst_id;
    this->resend = resend;
    this->pnt_id = pnt_id;
    this->trg_pnt_id = trg_pnt_id;
  }
  packet(String raw_msg) {
    std::vector<String> list = raw_msg.split(',');
    this->prv_id = list[0].toInt();
    this->src_id = list[1].toInt();
    this->dst_id = list[2].toInt();
    this->pnt_id = list[3].toInt();
    this->resend = list[4] == String("true") ? true : false;
    this->msg = list[5];
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
    ret += "/";
    return ret;
  }
};

const int CORDINATOR_ID = 0;
bool joined = false;
bool resend = false;
int my_id;
int pnt_id;
map<int, int> dst_mp;  // 目的のid -> その方向の隣接ノードid

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
      if (p.dst_id != my_id) continue;  // todo ルーティング
      vector<String> msg_list = p.msg.split(' ');
      if (msg_list[0] == String("Grant_id")) {  // 参加要求の返事 真IDの取得
        my_id = msg_list[1].toInt();
        joined = true;
      } else if (msg_list[0] == String("")) {
      }
    }
  }
  sleep(3);
}
