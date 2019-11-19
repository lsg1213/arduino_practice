#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h> 

unsigned long previousTime = 0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();  //A5:SCL,A4:SDA,vin:5V,GND:GND
int blueTx=11;   //Tx (보내는핀 설정)
int blueRx=10;   //Rx (받는핀 설정)
int state = 0;  //0: 초기 1: 대기(알람대기) 2: 요리
int pick = 0;
unsigned long startTime = 0;
unsigned long now = 0;
int receipt[6] = {0,0,0,0,0,0};
int numReceipt = 0;
bool boil = false;
SoftwareSerial mySerial(blueTx, blueRx);
unsigned long cookStartTime = 0;

void setting() {
  mySerial.println("시작할 시각을 적어주세요 ex)0800, 1400");
  while(true) {
    while(!mySerial.available());
    startTime = mySerial.parseInt();
    if (startTime / 100 > 24 or startTime < 0 or startTime % 100 > 59) {
      mySerial.println("잘못된 시각을 입력했습니다. 다시 입력해주세요 ex) 0800, 1400");
      continue;
    } else {
      startTime = (startTime / 100 * 60 * 60 * 1000) + (startTime % 100 * 60 * 1000);
      break;
    }
  }
  mySerial.println("물이 끓으면 요리를 시작할까요? 맞으면 1 아니면 0");
  while(true) {
    while(!mySerial.available());
    int sel = mySerial.parseInt();
    if (sel == 1) {
      boil = true;
      break;
    } else if (sel == 0) {
      boil = false;
      break;
    } else {
      mySerial.println("잘못 입력했습니다. 다시 입력해주세요.");
    }
  }
  numReceipt = 1;
  for (int i = 2 ; i <= 5 ; i++) {
    mySerial.print(i);
    mySerial.println("번째 재료를 몇 분 후에 넣을까요? 만약 그만 넣으려면 0을 입력하세요");
    while(!mySerial.available());
    int Time = mySerial.parseInt();
    if (Time > 1000 or Time < 0) {
      mySerial.println("설정한 시간이 너무 크거나 작습니다.\n 다시 입력하세요. 1~1000");
      continue;
    } else if (Time == 0) {
      break;
    }
    receipt[i] = Time;
    numReceipt++;
  }
  mySerial.println("현재 시각을 적어주세요 ex)0800, 1400");
  while(true) {
    while(!mySerial.available());
    now = mySerial.parseInt();
    if (now / 100 > 24 or now < 0 or now % 100 > 59) {
      mySerial.println("잘못된 시각을 입력했습니다. 다시 입력해주세요 ex) 0800, 1400");
      continue;
    } else {
      now = (now / 100 * 60 * 60 * 1000) + (now % 100 * 60 * 1000);
      break;
    }
  }
  startTime = millis() + (startTime - now + 86400000) % 86400000;
  
  mySerial.println("작동을 시작합니다.");
}
void putIngredient() {
  // ----------------------------
  // 위쪽 모터 추가해야함
  // ----------------------------
  // motor1 밀고 당기는 모터
  int motor1_1 = 4;
  int motor1_2 = 5;
  // motor2 숟가락 돌리는 모터
  int motor2_1 = 6;
  int motor2_2 = 7;
  int pushTime = 5200; // ms
  int pullTime = 5200; // ms
  int rotateTime = 2700; // ms
  digitalWrite(motor1_1,HIGH);
  digitalWrite(motor1_2,LOW);
  delay(pushTime);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,HIGH);
  digitalWrite(motor2_2,LOW);
  delay(rotateTime);
  digitalWrite(motor2_1,LOW);
  digitalWrite(motor2_2,LOW);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,HIGH);
  delay(pullTime);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,LOW);
}

bool menu() {
  mySerial.println("┌───┐");
  mySerial.println("│1 세팅│");
  mySerial.println("│2 취소│");
  mySerial.println("└───┘");
  while (true) {
    while (!mySerial.available());
    pick = mySerial.parseInt();
    if (pick == 1 or pick == 2) {
      return false;
    }
    mySerial.println("잘못된 선택입니다. 다시 선택하세요.");
  }

  return true;
}

bool readTemp() {
  Serial.print(mlx.readObjectTempC());
  Serial.println("*C"); //테스팅용, 삭제 요망
  if (mlx.readObjectTempC() > 85.0) {
    return true;
  }
  return false;
}

bool cooking(int num) {
  unsigned int a = receipt[num - numReceipt + 1];
  
  if (a * 60 * 1000 + cookStartTime <= millis()) {
    cookStartTime += a * 60 * 1000;
    mySerial.print(numReceipt);
    mySerial.println("번째 재료를 투하합니다.");
    putIngredient();
    numReceipt--;
  }

  return numReceipt;
}
void reset() {
  state = 0;
  pick = 0;
  startTime = 0;
  now = 0;
  cookStartTime = 0;
  for (int i = 0 ; i < 6 ; i++) receipt[i] = 0;
  numReceipt = 0;
  boil = false;
}
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  mlx.begin();  //mlx모듈을 읽어들이기 시작합니다.
}
void check() {
  Serial.print("세팅 시간:");
  Serial.println(startTime);
  Serial.print("온도:");
  Serial.println(mlx.readObjectTempC());
  Serial.print("현재 조리 번호:");
  Serial.println(numReceipt);
}
void loop() {
  switch(state) {
    case 0:
      menu();
      switch(pick) {
        case 1:
          setting();
          state = 1;
          mySerial.println("대기 상태로 변경됩니다. 취소하시려면 0을 입력해주세요.");
          break;
        case 2:
          reset();
          mySerial.println("초기 상태로 돌아갑니다.");
          return;
        default:
          mySerial.println("예기치 못한 에러 발생");
          Serial.println("예기치 못한 에러 발생");
          break;
      }
    case 1:
      if (mySerial.available()) {
        if (mySerial.parseInt() == 0) {
          reset();
        }
      }
      now = millis();
      if (startTime <= now) {
        mySerial.println("요리를 시작합니다.");
        cookStartTime = millis();
        state = 2;
        break;
      }
      return;
    case 2:
      if (boil) {
        // 온도 읽어오기
        unsigned long currentTime = millis();
        // millis() 함수를 사용하여 현재 시간을 측정하고 저장
        if(currentTime > previousTime + 500){
          // 0.5초마다 읽기
          previousTime = currentTime;
          if(!readTemp()) {
            Serial.println("온도 미달");
            return;
          }
        }
      }
      int num = numReceipt;
      if(!cooking(num)) {
        reset();
        mySerial.println("요리 끝! 맛있게 드세요");
      }
      break;
    default:
      mySerial.println("예기치 못한 에러 발생");
      Serial.println("예기치 못한 에러 발생");
      break;
  }
  
  
//  if (Serial.available() > 0) {
//    int a = Serial.parseInt();
//    if (a == 1) {
//      putIngredient();
//    }
//  }
}
