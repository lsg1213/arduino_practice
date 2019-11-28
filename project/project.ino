#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h> 

/*
 Arduino Mario Bros Tunes
 With Piezo Buzzer and PWM
 
 Connect the positive side of the Buzzer to pin 3,
 then the negative side to a 1k ohm resistor. Connect
 the other side of the 1 k ohm resistor to
 ground(GND) pin on the Arduino.
 
 by: Dipto Pratyaksa
 last updated: 31/3/13
 */
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 9
#define inductor 3  //inductor led 제어핀

unsigned long previousTime = 0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();  //A5:SCL,A4:SDA,vin:5V,GND:GND
int blueTx = 11;   //Tx (보내는핀 설정)
int blueRx = 10;   //Rx (받는핀 설정)
int state = 0;  //0: 초기 1: 대기(알람대기) 2: 요리
int pick = 0;
unsigned long startTime = 0;
unsigned long now = 0;
struct Receipt {
  int receipt[6] = {0,0,0,0,0,0};
  int fire[6] = {0,0,0,0,0,0};
}Receipt;
int receipt[6] = { 0, 0, 0, 0, 0, 0 };
int numReceipt = 0;
int num = 0;
bool alarmState = false;
bool boil = false;
SoftwareSerial mySerial(blueTx, blueRx);
unsigned long cookStartTime = 0;

int melody[] = {
NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0,
NOTE_G7, 0, 0, 0,
NOTE_G6, 0, 0, 0,

NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6,
    NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0,
    NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0 };
//Mario main them tempo
int tempo[] = { 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, };
//Underworld melody
int underworld_melody[] = {
NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
NOTE_AS3, NOTE_AS4, 0, 0,
NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
NOTE_AS3, NOTE_AS4, 0, 0,
NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
NOTE_DS3, NOTE_DS4, 0, 0,
NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
NOTE_DS3, NOTE_DS4, 0, 0, NOTE_DS4, NOTE_CS4, NOTE_D4,
NOTE_CS4, NOTE_DS4,
NOTE_DS4, NOTE_GS3,
NOTE_G3, NOTE_CS4,
NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
NOTE_GS4, NOTE_DS4, NOTE_B3,
NOTE_AS3, NOTE_A3, NOTE_GS3, 0, 0, 0 };
//Underwolrd tempo
int underworld_tempo[] = { 12, 12, 12, 12, 12, 12, 6, 3, 12, 12, 12, 12, 12, 12,
    6, 3, 12, 12, 12, 12, 12, 12, 6, 3, 12, 12, 12, 12, 12, 12, 6, 6, 18,
    18, 18, 6, 6, 6, 6, 6, 6, 18, 18, 18, 18, 18, 18, 10, 10, 10, 10, 10,
    10, 3, 3, 3 };
int song = 0;

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];

      buzz(melodyPin, underworld_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
      if (!alarmState) {
        return;
      }
      if (mySerial.available()) {
        while (true) {
          if (!mySerial.parseInt()) {
            alarmState = false;
            return;
          }
        }
      }
    }

  } else {

    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
      if (!alarmState) {
        return;
      }
      if (mySerial.available()) {
        while (true) {
          if (!mySerial.parseInt()) {
            alarmState = false;
            return;
          }
        }
      }
    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}
bool inductorSet(int strong) {
  // 0: 끄기, 1: 약, 2: 중, 3: 강
  switch(strong) {
    case 0:
    analogWrite(inductor,0);
    break;
    case 1:
    analogWrite(inductor,255/strong);
    break;
    case 2:
    analogWrite(inductor,255/strong);
    break;
    case 3:
    analogWrite(inductor,255/strong);
    break;
    default:
    return false;
  }
  return true;
}
bool recommendReceipt() {
  mySerial.println("1.된장찌개");
  mySerial.println("2.김치찌개");
  mySerial.println("3.콩나물국");
  mySerial.println("0.뒤로가기");

  // 각 요리 레시피 입력하기!
  while (true) {re
    while (!mySerial.available())
      ;
    switch (mySerial.parseInt()) {
    case 1:
      boil = false;
      mySerial.println("1번 재료함:볶은쇠고기90g, 표고버섯15g, 된장85g");
      mySerial.println("2번 재료함:재료X");
      mySerial.println("3번 재료함:두부250g, 고춧가루2.2g");
      mySerial.println("4번 재료함:청고추15g, 홍고추20g, 파20g");
      receipt[2] = 4; //센불
      receipt[3] = 10;  //중불
      receipt[4] = 2;
      numReceipt = 4;
      mySerial.println("진행 하시겠습니까? 진행하면 1, 아니면 0을 입력해주세요");
      while (!mySerial.available())
        ;
      switch (mySerial.parseInt()) {
      case 0:
        reset();
        return true;
      case 1:
        break;
      default:
        mySerial.println("잘못 입력했습니다. 다시 입력해주세요.");
        break;
      }
      break;
    case 2:
      boil = true;
      mySerial.println("1번 재료함:고춧가루2.2g");
      mySerial.println("2번 재료함:참기름13g,볶은돼지고기150g");
      mySerial.println("3번 재료함:볶은김치280g");
      mySerial.println("4번 재료함:재료X");
      mySerial.println("5번 재료함:소금2g,두부150g,파20g");
      receipt[2] = 0;
      receipt[3] = 6; //센불
      receipt[4] = 30;  //중불
      receipt[5] = 2;
      numReceipt = 5;
      mySerial.println("진행 하시겠습니까? 진행하면 1, 아니면 0을 입력해주세요");
      while (!mySerial.available())
        ;
      switch (mySerial.parseInt()) {
      case 0:
        reset();
        return true;
      case 1:
        break;
      default:
        mySerial.println("잘못 입력했습니다. 다시 입력해주세요.");
        break;
      }
      break;
    case 3:
      boil = false;
      mySerial.println("1번 재료함:참기름 1큰술,콩나물 250g");
      mySerial.println("2번 재료함:콩나물 250g");
      mySerial.println("3번 재료함:파1/2대,다진 마늘 1작은술,국간장 2큰술,소금 약간");
      receipt[2] = 0;
      receipt[3] = 25;  //중불
      numReceipt = 3;
      mySerial.println("진행 하시겠습니까? 진행하면 1, 아니면 0을 입력해주세요");
      while (!mySerial.available())
        ;
      switch (mySerial.parseInt()) {
      case 0:
        reset();
        return true;
      case 1:
        break;
      default:
        mySerial.println("잘못 입력했습니다. 다시 입력해주세요.");
        break;
      }
      break;
    case 0:
      //reset
      return true;
    default:
      mySerial.println("잘못된 입력입니다. 다시 입력해주세요.");
    }
  }
  return false;
}
void timeSetting() {
  mySerial.println("일어날 시각을 적어주세요 ex)0800, 1400");
  while (true) {
    while (!mySerial.available())
      ;
    startTime = mySerial.parseInt();
    if (startTime / 100 > 24 or startTime < 0 or startTime % 100 > 59) {
      mySerial.println("잘못된 시각을 입력했습니다. 다시 입력해주세요 ex) 0800, 1400");
      continue;
    } else {
      startTime = (startTime / 100 * 60 * 60 * 1000)
          + (startTime % 100 * 60 * 1000);
      break;
    }
  }
  mySerial.println("현재 시각을 적어주세요 ex)0800, 1400");
  while (true) {
    while (!mySerial.available())
      ;
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
}
void setting() {

  mySerial.println("물이 끓으면 요리를 시작할까요? 맞으면 1 아니면 0");
  while (true) {
    while (!mySerial.available())
      ;
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
  for (int i = 2; i <= 5; i++) {
    mySerial.print(i);
    mySerial.println("번째 재료를 몇 분 후에 넣을까요? 만약 그만 넣으려면 -1을 입력하세요");
    while (!mySerial.available())
      ;
    int Time = mySerial.parseInt();
    if (Time > 1000 or Time < -1) {
      mySerial.println("설정한 시간이 너무 크거나 작습니다.\n 다시 입력하세요. 0~1000");
      continue;
    } else if (Time == -1) {
      break;
    }
    receipt[i] = Time;
    numReceipt++;
  }
  num = numReceipt;
  for (int i = 1; i <= numReceipt; i++) {
    mySerial.print(i);
    mySerial.print("번째 재료는 ");
    mySerial.print(receipt[i]);
    mySerial.println("분뒤에 투하");
  }
  timeSetting();

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
  int pushTime = 5000; // ms
  int pullTime = 5000; // ms
  int rotateTime = 2700; // ms
  digitalWrite(motor1_1, HIGH);
  digitalWrite(motor1_2, LOW);
  delay(pushTime);
  digitalWrite(motor1_1, LOW);
  digitalWrite(motor1_2, LOW);
  digitalWrite(motor2_1, HIGH);
  digitalWrite(motor2_2, LOW);
  delay(rotateTime / 2);
  digitalWrite(motor2_1, LOW);
  digitalWrite(motor2_2, LOW);
  delay(1000);
  digitalWrite(motor2_1, HIGH);
  digitalWrite(motor2_2, LOW);
  delay(rotateTime / 2);
  digitalWrite(motor2_1, LOW);
  digitalWrite(motor2_2, LOW);
  digitalWrite(motor1_1, LOW);
  digitalWrite(motor1_2, HIGH);
  delay(pullTime);
  digitalWrite(motor1_1, LOW);
  digitalWrite(motor1_2, LOW);
}

bool menu() {
  mySerial.println("┌───┐");
  mySerial.println("│1 세팅│");
  mySerial.println("│2 취소│");
  mySerial.println("│3 추천│");
  mySerial.println("└───┘");
  while (true) {
    while (!mySerial.available())
      ;
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
    Serial.println(a);
    check();
    cookStartTime += a * 60 * 1000;
    mySerial.print(num - numReceipt + 1);
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
  num = 0;
  now = 0;
  cookStartTime = 0;
  if (!inductorSet(0)) {
    mySerial.println("인덕터 초기화에 문제가 생겼습니다.");
    return;
  }
  for (int i = 0; i < 6; i++)
    receipt[i] = 0;
  numReceipt = 0;
  boil = false;
}
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(9, OUTPUT); //buzzer
  mlx.begin();  //mlx모듈을 읽어들이기 시작합니다.
}
void check() {
  Serial.print("세팅 시간:");
  Serial.println(startTime);
  Serial.print("온도:");
  Serial.println(mlx.readObjectTempC());
  Serial.print("현재 조리 번호:");
  Serial.println(numReceipt);
  Serial.print("cookStartTime:");
  Serial.println(cookStartTime);
}
void loop() {
  switch (state) {
  case 0:
    menu();
    switch (pick) {
    case 1:
      setting();
      state = 1;
      mySerial.println("대기 상태로 변경됩니다. 취소하시려면 0을 입력해주세요.");
      alarmState = true;
      break;
    case 2:
      reset();
      mySerial.println("초기 상태로 돌아갑니다.");
      return;
    case 3:
      if (recommendReceipt()) {
        reset();
        return;
      }
      timeSetting();
      break;
    default:
      mySerial.println("예기치 못한 에러 발생");
      Serial.println("예기치 못한 에러 발생");
      break;
    }
  case 1:
    if (mySerial.available()) {
      if (mySerial.parseInt() == 0) {
        reset();
        return;
      }
    }
    now = millis();
    if (startTime <= now) {
      mySerial.println("기상 시간입니다. 알람을 끄려면 0을 눌러주세요");
      while (alarmState) {
        sing(1);
        if (!alarmState) {
          break;
        }
        sing(1);
        if (!alarmState) {
          break;
        }
        sing(2);
      }
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
      if (currentTime > previousTime + 500) {
        // 0.5초마다 읽기
        previousTime = currentTime;
        if (!readTemp()) {
          Serial.println("온도 미달");
          return;
        }
      }
    }

    if (!cooking(num)) {
      reset();
      mySerial.println("요리 끝! 맛있게 드세요");
    }
    break;
  default:
    mySerial.println("예기치 못한 에러 발생");
    Serial.println("예기치 못한 에러 발생");
    break;
  }
}
