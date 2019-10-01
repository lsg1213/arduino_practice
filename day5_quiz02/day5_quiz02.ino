#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 
Servo servo;
int servoPin = 24;

int blueTx=11;   //Tx (보내는핀 설정)
int blueRx=10;   //Rx (받는핀 설정)
LiquidCrystal_I2C lcd(0x27,16,2);  // (address, column, row)

void setup() {
  servo.attach(servoPin);
  lcd.init();
  lcd.backlight();
  pinMode(13, OUTPUT);  //Pin 13을 OUTPUT으로 설정 (LED ON/OFF)
}

 void loop() {
  int potValue = analogRead(A0);    // 포텐셔미터 입력
  int angle = map(potValue, 0, 1023, 0, 180);   // 포텐셔미터의 입력을 회전각으로 변환
  servo.write(angle);    // 서보모터 제어
  

  lcd.clear();            // 화면 지우기
  lcd.setCursor(2, 0);    // 커서 이동 (column, row)
  lcd.print("Servo Motor");   // 글자 출력
  lcd.setCursor(3, 1);    // 커서 이동 (column, row)
  lcd.print("angle : ");
  lcd.print((int)angle);
  delay(100);
 }
