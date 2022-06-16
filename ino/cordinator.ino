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

int my_id = 0;
int id_count_up = 1;
bool resend = false;
map<int, int> id_tnt;  // random id -> 真のid

void setup() {}
void loop() {
  std::printf("my_id -> %d pid -> %d\n", my_id, getpid());
  if (Serial2.available() > 0) {
    vector<String> req_list = Serial2.readString().split('/');
    for (auto req_str : req_list) {  // 来たパケットを順に処理していく
      if (req_str == "") continue;
      packet req = packet(req_str);
      if (req.dst_id != my_id) continue;  // todo ルーティング
      if (req.msg == "joinrequest") {
        if (id_tnt[req.src_id] == 0) {
          id_tnt[req.src_id] = id_count_up++;
        }
        String msg = "Grant_id ";
        msg += ItoString(id_tnt[req.src_id]);
        int dst_pnt_id = req.pnt_id == -1 ? 0 : req.pnt_id;
        packet rep = packet(msg, req.prv_id, my_id, req.src_id, resend, -1, dst_pnt_id);
        Serial2.print(rep.into_string());
      }
    }
  }
  sleep(4);
  // std::exit(0);
}
