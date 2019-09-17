void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val;

  analogRead(10);
  val = analogRead(10); // A10
  analogWrite(13, val/4); // 13번 포트(LED), val/4만큼 전압

  Serial.println(5.0*double(val)/1023.0);
}
