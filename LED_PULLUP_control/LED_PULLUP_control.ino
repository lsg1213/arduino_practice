#define SWITCH1_PIN 40

void setup() {
  pinMode(SWITCH1_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(SWITCH1_PIN) == LOW) {
    Serial.println("ON(LOW)");
  }else {
    Serial.println("OFF(HIGH)");
  }
  delay(500);
}
