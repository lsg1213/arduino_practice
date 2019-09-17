int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int buttonPin = 4;
int potPin = A0;
int red = 0;
int green = 0;
int blue = 0;
int mode = 0;



void setup(){
  // put your setup code here, to run once :
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);//
  
}

void loop(){
  
  //버튼 핀 읽기
  if(digitalRead(buttonPin)==LOW){
    mode=mode+1; //RGB 모드 바꾸기
    if(mode>2){
      mode = 0;
    }
  }
// 포텐셔미터 읽기 (10bits, 0~1023);
  int potValue = analogRead(potPin);
// RGB LED 색변화
if(mode == 0){
  red = potValue/4;
  analogWrite(redPin, red);
} else if(mode == 1){
  green = potValue/4;
  analogWrite(greenPin, green);
} else{
  blue = potValue/4;
  analogWrite(bluePin, blue);
}
Serial.println(potValue);
Serial.println(mode);
delay(50);
}
