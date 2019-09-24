#include <DHT11.h>
int pin=2;    // 연결한 아두이노 디지털 핀 번호
DHT11 dht11(pin); 
 //라이브러리 사용을 위한 변수 선언



void setup() {
   Serial.begin(9600);
}

void loop() {
  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0) {
  //온·습도 값을 반복해서 읽음
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  } else {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
  delay(DHT11_RETRY_DELAY); //delay for reread (1000ms)

}
