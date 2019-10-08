void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  attachInterrupt(1, blink, CHANGE);
// D3 핀에 인터럽트 설정
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}

void blink() 
// ISR: 인터럽트가 발생할 때 실행되는 함수
{
  int button = digitalRead(3);
  digitalWrite(2, button);
}
