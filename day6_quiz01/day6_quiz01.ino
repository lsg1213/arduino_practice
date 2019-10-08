void setup() {
  Serial.begin(9600);
}
int menu = 0;
void loop() {
  
  if (Serial.available() > 0) {
    menu = Serial.parseInt();
  }
  switch(menu) {
    case 5:
      analogWrite(8,0);
      analogWrite(9,0);
      break;
    case 6:
      analogWrite(8,120);
      analogWrite(9,0);
      break;
    case 7:
      analogWrite(8,255);
      analogWrite(9,0);
      break;
    case 3:
      analogWrite(8,0);
      analogWrite(9,120);
      break;
    case 4:
      analogWrite(8,0);
      analogWrite(9,255);
      break;
    default:
      break;
  }
}
