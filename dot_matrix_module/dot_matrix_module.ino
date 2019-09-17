#include "LedControlMS.h"

#define NBR_MTX 1  // 연결된 LED 매트릭스 모듈의 갯수
LedControl lc=LedControl(12,11,10, NBR_MTX);

String displayChar = "1234567890abcdefghijklmnopqrstuvwxyz";
int stringCounter=0;
/* we always wait a bit between updates of the display */
unsigned long delaytime=300;


byte iconHeart[8]={
           B00100100,
           B01011010,
           B10000001,
           B10000001,
           B01000010,
           B00100100,
           B00011000,
           B00000000};

void scrollLeft(char ch){
  int pos =lc.getCharArrayPosition(ch);
  for (int scroll =0; scroll<6; scroll++) {
     for (int i=scroll; i<6;i++) {
        lc.setRow(0,i-scroll, alphabetBitmap[pos][i]);
    } 
    delay(300);
    lc.clearDisplay(0);
  }
}

void scrollRight(char ch){
  int pos =lc.getCharArrayPosition(ch);
  for (int scroll =0; scroll<8; scroll++) {
     for (int i=0; i<6;i++) {
        if (scroll+i<8) lc.setRow(0, scroll+i, alphabetBitmap[pos][i]);
    } 
    delay(300);
    lc.clearDisplay(0);
  }
}
void setup() {
    /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  stringCounter=0; 
  for (int i=0; i< NBR_MTX; i++){ 
    lc.shutdown(i,false); // 매트릭스 모듈 초기화
  /* Set the brightness to a medium values */
    lc.setIntensity(i,1); // LED 밝기 조절
  /* and clear the display */
    lc.clearDisplay(i); // 모든 LED를 끔
  }
}

void loop() {
   // LED 1개씩 제어
  // setLed(int addr, int row, int col, boolean state)
//  lc.setLed(0,0,0,true);  // 0번 모듈, (0, 0) on
//  delay(1000);
//  lc.setLed(0,0,7,true);
//  delay(1000);
//  lc.setLed(0,7,0,true);
//  delay(1000);
//  lc.setLed(0,7,7,true);
//  delay(1000);
//  lc.setLed(0,0,0,false);  // 0번 모듈, (0, 0) off
//  delay(1000);
//  lc.setLed(0,0,7,false);
//  delay(1000);
//  lc.setLed(0,7,0,false);
//  delay(1000);
//  lc.setLed(0,7,7,false);
//  delay(5000); 


  // 행(세로) LED 8개 제어
//  lc.setRow(0,1,0x0C);  // 0번 모듈, 1 행
//  delay(1000);
//  lc.clearDisplay(0);
//  lc.setRow(0,1,0xC0);
//  delay(5000);
//  lc.clearDisplay(0);

  // 열(가로) LED  8개 제어
//  lc.setColumn(0,7,iconHeart[0]);
//  lc.setColumn(0,6,iconHeart[1]);
//  lc.setColumn(0,5,iconHeart[2]);
//  lc.setColumn(0,4,iconHeart[3]);
//  lc.setColumn(0,3,iconHeart[4]);
//  lc.setColumn(0,2,iconHeart[5]);
//  lc.setColumn(0,1,iconHeart[6]);
//  lc.setColumn(0,0,iconHeart[7]);
//  delay(50000);
//  lc.clearDisplay(0);

 // 문자열 출력
//  lc.writeString(0,"GIVE ME A");
//  delay(5000);
//  lc.clearAll();

  
  // 문자 스크롤
//  scrollLeft('O');
//  delay(3000);
//  lc.clearAll();
//  scrollRight('O');
//  delay(3000);
//  lc.clearAll();

  char ch= displayChar[stringCounter];
  stringCounter++;
  if (stringCounter>35) stringCounter=0;
  lc.displayChar(0, lc.getCharArrayPosition(ch));
  delay(1000);
  lc.clearAll();
  delay(200);


}
