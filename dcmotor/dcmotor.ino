void setup() {
  Serial.begin(9600);
//  pinMode(8, OUTPUT);
//  pinMode(9, OUTPUT);
}

void loop() {
  //- Forward 방향으로 2초 회전 후 2초 정지
  Serial.println("Forward");
//  digitalWrite(8, HIGH);  digitalWrite(9, LOW);
  analogWrite(8, 255);
  analogWrite(9, 0);
  delay(2000);
//  digitalWrite(8, LOW);  digitalWrite(9, LOW);
  analogWrite(8, 0);
  analogWrite(9, 0);
  delay(2000);
  
  //- Backward 방향으로 2초 회전 후 2초 정지
  Serial.println("Backward");
  analogWrite(8, 0);
  analogWrite(9, 255);
  delay(2000);
  analogWrite(8, 0);
  analogWrite(9, 0);
  delay(2000);
}
