void setup() {
  Serial.begin(9600);
  
}

void putIngredient() {
  // motor1 밀고 당기는 모터
  int motor1_1 = 4;
  int motor1_2 = 5;
  // motor2 숟가락 돌리는 모터
  int motor2_1 = 6;
  int motor2_2 = 7;
  int pushTime = 4800; // ms
  int pullTime = 4800; // ms
  int rotateTime = 2700; // ms
  
  digitalWrite(motor1_1,HIGH);
  digitalWrite(motor1_2,LOW);
  delay(pushTime);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,HIGH);
  digitalWrite(motor2_2,LOW);
  delay(rotateTime);
  digitalWrite(motor2_1,LOW);
  digitalWrite(motor2_2,LOW);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,HIGH);
  delay(pullTime);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int a = Serial.parseInt();
    if (a == 1) {
      putIngredient();
    }
  }
}
