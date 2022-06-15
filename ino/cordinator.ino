bool can_send = false;
void setup() { Serial.begin(9600); }

void loop() {
  if (!can_send) {
    String req = "RTS";
    Serial2.print(req);
  }
  if (Serial2.available() > 0) {
    String rep = Serial2.readString();
    if (rep.indexOf("CTS") != -1) {
      can_send = true;
      String data = "this is a data.";
      Serial2.print(data);
    }
  }
  sleep(3);
}
