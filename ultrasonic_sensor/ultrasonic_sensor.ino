void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);  //센서 TRIG 핀
  pinMode(3,INPUT);   //센서 ECHO 핀
}
int microsecondsToCentimeters(int microseconds){
  return (double)microseconds / 29.0 / 2.0;
}


void loop() {
  int duration;
  double cm;

  digitalWrite(2,HIGH);    //센서 TRIG 신호 입력
  delayMicroseconds(10);    //10us 유지
  digitalWrite(2,LOW);     //TRIG 신호 off
  
  duration = pulseIn(3,HIGH);  
  //ECHO pin : HIGH-> LOW 간격 측정
  cm = microsecondsToCentimeters(duration);  
  //거리(cm)로 변환
  
  Serial.print(cm);
  Serial.println("cm");
  
  delay(300);  //0.3초 대기 후 다시 측정
}
