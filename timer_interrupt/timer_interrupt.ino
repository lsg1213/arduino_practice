#include <MsTimer2.h> // 타이머 인터럽트 라이브러리 헤더파일

void flash() // 인터럽트 발생 시 동작할 함수 
{
  static boolean output = HIGH;
  digitalWrite(13, output);
  output = !output;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  MsTimer2::set(15, flash);
  // 타이머 인터럽트 설정(500ms 마다 flash 함수를 호출)
  MsTimer2::start(); // 타이머 인터럽트 실행
}

void loop() {
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  delay(1000);
}
