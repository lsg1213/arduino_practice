
#define LED1_PIN 22
#define LED2_PIN 32

void setLed12(int cmd) {
  if(cmd == 0) {
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
  } else if (cmd == 1) {
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
  }
}
void setup() {
  pinMode(LED1_PIN,OUTPUT);
  pinMode(LED2_PIN,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int cmd;

  if (Serial.available() > 0) {
    cmd = Serial.parseInt();

    if (Serial.read() == '\n') {
      setLed12(cmd);
    }
  }
}
