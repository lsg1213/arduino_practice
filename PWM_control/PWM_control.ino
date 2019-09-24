void setup() {
  analogReference(DEFAULT);
  Serial.begin(9600);

}

void loop() {
  int val;

  analogRead(10);
  val = analogRead(10);
  analogWrite(13, val/4);

  Serial.println(5.0*double(val)/1023.0);

}
