int ledPin = 13; // 내부 LED 핀
int inputPin = 3; // PIR sensor 핀
int redPin = 9;
int bluePin = 11;
int red = 0;
int blue = 0;


void setup() {
  Serial.begin(9600); // 시리얼 통신 오픈
  pinMode(ledPin, OUTPUT); // 내부 LED 출력 설정
  pinMode(inputPin, INPUT_PULLUP);//
}

void loop() {
  int motion = digitalRead(inputPin);
  int potValue = 1023;
  if(motion==HIGH){
    digitalWrite(13, HIGH);
    Serial.println("Detected");
    red = potValue/4;
    analogWrite(redPin, red);
    analogWrite(bluePin, 0);
  }
  else{
    digitalWrite(13, LOW);
    Serial.println("Not Detected");
    blue = potValue/4;
    analogWrite(bluePin, blue);
    analogWrite(redPin, 0);
  }
  delay(100);
}
