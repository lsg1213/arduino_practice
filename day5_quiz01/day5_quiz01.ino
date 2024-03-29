#include <SoftwareSerial.h> 
//시리얼 통신 라이브러리 호출
 
int blueTx=11;   //Tx (보내는핀 설정)
int blueRx=10;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  
//시리얼 통신을 위한 객체선언
String myString=""; // 받는 문자열
 
void setup() {
  Serial.begin(9600);    
  mySerial.begin(9600); //블루투스 시리얼
}
 
String s="";
void loop() {
  while(Serial.available()) {
    char k = (char)Serial.read();
    s+= k;
    delay(5);
  }
  while(mySerial.available()) 
  {
    char myChar = (char)mySerial.read();  //mySerial int 값을 char 형식으로 변환
    myString+=myChar;   //수신되는 문자를 myString에 모두 붙임 (1바이트씩 전송되는 것을 연결)
    delay(5);           //수신 문자열 끊김 방지
  }
  if(!s.equals("")){
    mySerial.print(s);
    s="";
  }
  if(!myString.equals(""))  //myString 값이 있다면
  {
    Serial.println(myString); //시리얼모니터에 myString값 출력
    myString="";  //myString 변수값 초기화
  }
}
