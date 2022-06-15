bool waiting_data = false;
void setup() { Serial.begin(9600); }

void loop() {
  if (Serial2.available() > 0) {
    String recv;
    recv = Serial2.readString();
    if (!waiting_data) {
      if (recv.indexOf("RTS") != -1) {
        Serial2.print("CTS");
        waiting_data = true;
      }
    } else {
      waiting_data = false;
    }
  }
  sleep(3);
}
