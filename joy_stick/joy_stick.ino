void setup() {
  pinMode(4, INPUT_PULLUP); 
  // 스위치 핀을 내부 풀업 입력으로
  Serial.begin(9600); // 시리얼 통신 오픈
}

void loop() {
  int ver, hor, sel;
  ver = analogRead(A1); // x축 = 0~1023
  hor = analogRead(A0); // y축 = 0~1023
  sel = digitalRead(4); // 버튼 누르면 LOW, 떼면 HIGH

  Serial.print("X = ");
  Serial.print(ver);
  Serial.print(", Y = ");
  Serial.print(hor);
  Serial.print(", Button = ");

  if(sel == HIGH){
    Serial.println("not pressed");
  }
  else{
    Serial.println("PRESSED!");
  }
  delay(100);
}
