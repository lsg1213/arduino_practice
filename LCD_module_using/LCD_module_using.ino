#include <DHT11.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int pin=2;    // 연결한 아두이노 디지털 핀 번호
DHT11 dht11(pin); 

LiquidCrystal_I2C lcd(0x27,16,2);  // (address, column, row)

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0) {
    // 온습도 출력
    lcd.clear();            // 화면 지우기
    lcd.setCursor(0, 0);    // 커서 이동 (column, row)
    lcd.print("Temp = ");   // 글자 출력
    lcd.print(temp);        // 변수 출력
    lcd.setCursor(0, 1);    // 커서 이동 (column, row)
    lcd.print("Humi = ");
    lcd.print(humi);
  } else {
    // 에러 메시지 출력
    lcd.clear();
    lcd.setCursor(0, 0);    // move to (column, row)
    lcd.print("Error = ");
    lcd.print(err);
  }
  delay(DHT11_RETRY_DELAY); // delay for reread
}
