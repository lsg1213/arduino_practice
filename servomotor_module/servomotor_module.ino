#include <Servo.h> 
Servo servo;
 
void setup() 
{ 
  // 24번 핀으로 500~1500us가 0~180도에 해당하도록 함
  // 500, 2500은 RC 서보 모터 모델마다 다름
  servo.attach(24, 500, 1500); 
  //1000,1500 으로 변경해보기
} 

void loop() 
{ 
  int pos;
  
  for(pos = 0; pos <= 180; pos += 1) {
    servo.write(pos);
    delay(15);
  }
  delay(15);
  for(pos = 180; pos>=0; pos-=1) {                                
    servo.write(pos);
    delay(15);
  } 
} 
