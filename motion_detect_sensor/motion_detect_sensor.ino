int ledPin = 13; // 내부 LED 핀
int inputPin = 3; // PIR sensor 핀

void setup() {
  Serial.begin(9600); // 시리얼 통신 오픈
  pinMode(ledPin, OUTPUT); // 내부 LED 출력 설정
  pinMode(inputPin, INPUT); // PIR 센서핀 입력 설정
}

void loop() {
  int motion = digitalRead(inputPin);
  Serial.print("motion : ");
  Serial.println(motion);

  if(motion==HIGH){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
  delay(100);
}
