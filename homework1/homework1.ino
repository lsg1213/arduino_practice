#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);  // (address, column, row)
int ledPin = 13; // 내부 LED 핀
int inputPin = 3; // PIR sensor 핀
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int red = 0;
int green = 0;
int blue = 0;

void setup() {
  pinMode(4, INPUT_PULLUP); 
  // 스위치 핀을 내부 풀업 입력으로
  Serial.begin(9600); // 시리얼 통신 오픈
  lcd.init();
  lcd.backlight();
  pinMode(ledPin, OUTPUT); // 내부 LED 출력 설정
}
int led_switch = 1;
void loop() {
  int ver, hor, sel;
  ver = analogRead(A1); // x축 = 0~1023
  hor = analogRead(A0); // y축 = 0~1023
  sel = digitalRead(4); // 버튼 누르면 LOW, 떼면 HIGH

  lcd.clear();            // 화면 지우기
  lcd.setCursor(0, 0);    // 커서 이동 (column, row)
  lcd.print("X = ");   // 글자 출력
  lcd.print(ver);        // 변수 출력
  lcd.setCursor(0, 1);    // 커서 이동 (column, row)
  lcd.print("Y = ");
  lcd.print(hor);
  Serial.print("X = ");
  Serial.print(ver);
  Serial.print(", Y = ");
  Serial.println(hor);

  if (led_switch) {
    if (ver < 1023 * 2 / 3 && ver >= 1023 / 3 && hor < 1023 * 2 / 3 && hor >= 1023 / 3) {
      analogWrite(redPin, 1023 / 4 / 3);
      analogWrite(greenPin, 1023 / 4 / 3);
      analogWrite(bluePin, 1023 / 4 / 3);
      Serial.println("color change to number 1");
    }else if (ver >= 1023 * 2 / 3 && hor >= 1023 * 2 / 3) {
      analogWrite(redPin, 1023 / 4);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      Serial.println("color change to number 2");
    } else if (ver >= 1023 * 2 / 3 && hor < 1023 * 2 / 3 && hor >= 1023 / 3) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 1023 / 4);
      analogWrite(bluePin, 0);
      Serial.println("color change to number 3");
    } else if (ver >= 1023 * 2 / 3 && hor < 1023 / 3) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 1023 / 4);
      Serial.println("color change to number 4");
    } else if (ver < 1023 * 2 / 3 && ver >= 1023 / 3 && hor >= 1023 * 2 / 3) {
      analogWrite(redPin, 1023 / 4);
      analogWrite(greenPin, 1023 / 4);
      analogWrite(bluePin, 0);
      Serial.println("color change to number 5");
    } else if (ver < 1023 * 2 / 3 && ver >= 1023 / 3 && hor < 1023 / 3) {
      analogWrite(redPin, 1023 / 4);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 1023 / 4);
      Serial.println("color change to number 6");
    } else if (ver < 1023 / 3 && hor >= 1023 * 2 / 3) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 1023 / 4);
      analogWrite(bluePin, 1023 / 4);
      Serial.println("color change to number 7");
    } else if (ver < 1023 / 3 && hor < 1023 * 2 / 3 && hor >= 1023 / 3) {
      analogWrite(redPin, 1023 / 8);
      analogWrite(greenPin, 1023 / 4);
      analogWrite(bluePin, 1023 / 4);
      Serial.println("color change to number 8");
    } else if (ver < 1023 / 3 && hor < 1023 / 3) {
      analogWrite(redPin, 1023 / 8);
      analogWrite(greenPin, 1023 / 8);
      analogWrite(bluePin, 1023 / 4);
      Serial.println("color change to number 9");
    }
  } else {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    Serial.println("LED is off now");
  }
  
  if(sel == HIGH){
    Serial.println("not pressed");
  }
  else{
    Serial.println("PRESSED!");
    if (led_switch) {
      led_switch = 0;
      Serial.println("LED on!");
    }
    else {
      led_switch = 1;
      Serial.println("LED off!");
    }
  }
  delay(100);
}
