unsigned long previousTime = 0;
// LED의 상태를 변경한 시간
boolean isOn = false;
// LED의 상태를 알려주는 변수

void setup(){
  pinMode(13, OUTPUT);
// 13번 내부 LED 핀을 출력으로 설정
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
// 시리얼 모니터 사용을 위한 설정
}

void loop(){
  unsigned long currentTime = millis();
// millis() 함수를 사용하여 현재 시간을 측정하고 저장
  
  if(currentTime > previousTime + 1000){
// 1초가 경과하면
    if(isOn) // isOn 값이 true이면
   {
      digitalWrite(13, HIGH);
      Serial.println("ON");
    }
    else // isOn 값이 false이면
    {
      digitalWrite(13, LOW);
      Serial.println("OFF");
    }
    isOn = !isOn; // 다음 동작을 위한 LED 상태 변경
    previousTime = currentTime; 
  }
  Serial.println(currentTime); 

  int button = digitalRead(3);
  digitalWrite(2, button);
  delay(10);
}
