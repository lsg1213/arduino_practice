#include <Servo.h> 

Servo servo;
int servoPin = 24;

void setup() {
  servo.attach(servoPin);
}

void loop() {
  int potValue = analogRead(A0);    // 포텐셔미터 입력
  int angle = map(potValue, 0, 1023, 0, 180);   // 포텐셔미터의 입력을 회전각으로 변환
  servo.write(angle);    // 서보모터 제어
  delay(100);
}
