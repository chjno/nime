#include <LiquidCrystal.h>

LiquidCrystal lcd1(8, 9, 10, 11, 12, 13);
LiquidCrystal lcd2(A10, A11, A12, A13, A14, A15);

Phone phone1(100, A0, A2);
Phone phone2(101, A1, A3);

bool sent1[32];

//int phone1Dialed;
//int phone2Dialed;

void setup() {
  Serial.begin(9600);
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);

  DDRA = B00000000;
  DDRC = B00000000;
  DDRD = B00000000;
  DDRG = B00000000;
  DDRL = B00000000;
  DDRB = B00000000;

  for (int i = 0; i < 32; i++){
    sent1[i] = false;
  }
}

void loop() {
  controlStates();

  checkRotary(phone1);
  checkRotary(phone2);
}

void controlStates(){
  for (int i = 0; i < 32; i++){
    if (digitalRead(i + 22) == HIGH){
      if (!sent1[i]){
        Serial.print('1');
        Serial.print(' ');
        Serial.println(i);
        sent1[i] = true;
      }
      
    } else {
      if (sent1[i]){
        Serial.print('0');
        Serial.print(' ');
        Serial.println(i);
        sent1[i] = false;
      }
    }
  }
}

void checkRotary(whichPhone){
  if (whichPhone.on()){
    int number = whichPhone.dial();
    lcd.print(number);
    Serial.print(whichPhone.channel);
    Serial.print(' ');
    Serial.println(number);
    // send to twilio?
  }
}

