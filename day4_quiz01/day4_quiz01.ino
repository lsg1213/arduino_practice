#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);  // (address, column, row)

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(2,OUTPUT);  //센서 TRIG 핀
  pinMode(3,INPUT);   //센서 ECHO 핀
}
int microsecondsToCentimeters(int microseconds){
  return microseconds / 29.0 / 2.0;
}
void loop() {
  int err;
  float temp, humi;
  int duration;
  int cm;

  digitalWrite(2,HIGH);    //센서 TRIG 신호 입력
  delayMicroseconds(10);    //10us 유지
  digitalWrite(2,LOW);     //TRIG 신호 off
  duration = pulseIn(3,HIGH);  
  //ECHO pin : HIGH-> LOW 간격 측정
  cm = microsecondsToCentimeters(duration);  
  //거리(cm)로 변환
  
  Serial.print(cm);
  

  // 온습도 출력
  lcd.clear();            // 화면 지우기
  lcd.setCursor(0, 0);    // 커서 이동 (column, row)
  lcd.print("UltraSonicSensor");   // 글자 출력
  lcd.setCursor(0, 1);    // 커서 이동 (column, row)
  lcd.print("Distance = ");
  lcd.print(cm);
  lcd.print("cm");
  delay(1000); // delay for reread
}
