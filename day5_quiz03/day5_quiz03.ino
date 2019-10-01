#include <SoftwareSerial.h>
//시리얼통신 라이브러리 호출
 
int blueTx=11;   //Tx (보내는핀 설정)at
int blueRx=10;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  
//시리얼 통신을 위한 객체선언

void setup() {
  //Serial.begin(9600);
  mySerial.begin(9600); //블루투스 시리얼
  pinMode(2,OUTPUT);  //센서 TRIG 핀
  pinMode(3,INPUT);   //센서 ECHO 핀
}

String mode = "";
void loop() {
  int duration, cm;

  digitalWrite(2,HIGH);    //센서 TRIG 신호 입력
  delayMicroseconds(10);    //10us 유지
  digitalWrite(2,LOW);     //TRIG 신호 off
  
  duration = pulseIn(3,HIGH);  
  //ECHO pin : HIGH-> LOW 간격 측정
  cm = microsecondsToCentimeters(duration);  
  //거리(cm)로 변환
  if (mySerial.available()) {
    mode += mySerial.read();
  }
  
  mySerial.print(cm);
  mySerial.print("cm\n");
  cm = 0;
  
  if (mode == "red") {
    
  } else if (mode == "green") {
    
  } else if (mode == "blue") {
    
  }
  delay(300);  //0.3초 대기 후 다시 측정 
}


int microsecondsToCentimeters(int microseconds){
  return microseconds / 29 / 2;
}
