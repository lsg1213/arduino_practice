#include <Servo.h> 
#include <SoftwareSerial.h>
Servo servo;

int blueTx=11;   //Tx (보내는핀 설정)at
int blueRx=10;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  
//시리얼 통신을 위한 객체선언
String myString=""; // 받는 문자열

void setup() {
  mySerial.begin(9600); //블루투스 시리얼
  mySerial.println("Enter the up of down");
  mySerial.println("up = angle + 15");
  mySerial.println("down = angle - 15");
}

int angle = 90;
void loop() {
  int pos;
  while(mySerial.available()) 
  {
    char myChar = (char)mySerial.read();  //mySerial int 값을 char 형식으로 변환
    myString+=myChar;   //수신되는 문자를 myString에 모두 붙임 (1바이트씩 전송되는 것을 연결)
    delay(5);           //수신 문자열 끊김 방지
  }
  if (!myString.equals("")) {
    mySerial.print("Input value: ");
    mySerial.println(myString);
    if (myString != "up" && myString != "down") {
      myString = "";
      mySerial.println("wrong operation!!");
    }
    else if (myString == "up") {
      servo.attach(24, 500, 1500);
      myString = "";
      for(pos = 0; pos < 15; pos += 1) {
        servo.write(angle++);
        delay(15);
      }
      mySerial.print("+15 ");
      mySerial.println(angle);
      servo.detach();
    } else if (myString == "down") {
      servo.attach(24, 500, 1500);
      myString = "";
      for(pos = 15; pos>0; pos-=1) {                                
        servo.write(angle--);
        delay(15);
      }
      mySerial.print("-15 ");
      mySerial.println(angle);
      servo.detach();
    }
  }
  delay(100);
}
