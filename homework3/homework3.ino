#include <MsTimer2.h> // 타이머 인터럽트 라이브러리 헤더파일

// variable
int velocity = 0;
bool direct = false;  // true: 정회전, false: 역회전
void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);  //센서 TRIG 핀
  pinMode(3,INPUT);   //센서 ECHO 핀
  MsTimer2::set(500, sensing);
  // 타이머 인터럽트 설정(500ms 마다 flash 함수를 호출)
  MsTimer2::start(); // 타이머 인터럽트 실행
  attachInterrupt(5, rotationChange, RISING);
}

int microsecondsToCentimeters(int microseconds){
  return (double)microseconds / 29.0 / 2.0;
}

void rotationChange() {
  direct = !direct;
}

void sensing() // 인터럽트 발생 시 동작할 함수 
{
  int duration;
  double cm;
  digitalWrite(2,HIGH);    //센서 TRIG 신호 입력
  delayMicroseconds(10);    //10us 유지
  digitalWrite(2,LOW);     //TRIG 신호 off
  
  duration = pulseIn(3,HIGH);  
  //ECHO pin : HIGH-> LOW 간격 측정
  cm = microsecondsToCentimeters(duration);  
  //거리(cm)로 변환
  if (cm <= 10) {
    velocity = 120;
  } else {
    velocity = 255;
  }
  Serial.print(cm);
  Serial.println("cm");
}

void loop() {
  if (direct) {
    analogWrite(8, velocity);
    analogWrite(11, 0);
  } else {
    analogWrite(8, 0);
    analogWrite(11, velocity);
  }
}
