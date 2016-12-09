#include "LCD.h"
#include "Phone.h"

bool sent1[32];
bool adjust = false;
const int adjustNo = 10;
int adjustPins[adjustNo] = {1,3,5,7,9,11,13,15,17,19};

LCD lcd[2] = {
  LCD(8, 9, 10, 11, 12, 13),
  LCD(A10, A11, A12, A13, A14, A15)
};

Phone phone[2] = {
  Phone(100, A0, A2),
  Phone(101, A1, A3)
};

void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 22; i < 54; i++){
    pinMode(i, INPUT);
  }

  for (int j = 0; j < 32; j++){
    sent1[j] = false;
  }
}

void loop() {

  if (Serial.available() > 0){
    resetFunc();
  }

  controlStates();
  
  for (int i = 0; i < 2; i++){
    
    if (phone[i].on()){
      if (phone[i].hung){
        phone[i].hung = false;
        Serial.print(phone[i].channel);
        Serial.print(' ');
        Serial.println('[');
      }
      
      int num = phone[i].dial();
      if (adjust){
        if (num > 0 && num < 11){
          
          // send adjusts to max
          Serial.print(phone[i].channel);
          Serial.print(' ');
          Serial.println(num + 10);
        }

      // not adjust
      } else {
        
        // send ticks to max
        if (num == 120){
          Serial.println(num);

        // send digits to twilio
        } else if (num > 0){

          Serial.print(phone[i].channel);
          Serial.print(' ');
          Serial.println(num);

          // print to LCD
          if (num > 9){
            lcd[i].printNum(0);
          } else {
            lcd[i].printNum(num);
          }
        }
      }
      
    } else {

      // hang up
      if (!phone[i].hung){
        phone[i].hung = true;
        Serial.print(phone[i].channel);
        Serial.print(' ');
        Serial.println(']');
        lcd[i].reset();
      }

      if (adjust){
        int num = phone[i].dial();
        if (num > 0 && num < 11){
          
          // send adjusts to max
          Serial.print(phone[i].channel);
          Serial.print(' ');
          Serial.println(num + 10);
        }
      }
      
    }
    
  }
  
}

const int micNo = 2;
const int micPins[micNo] = {};
//const int micChannels[micNo] = {200, 201};
//bool micSent1[2] = {false, false};
const int micChannel = 200;
bool micSent1 = false;

void controlStates(){

  bool mic1 = false;
//  bool mic2 = false;

  for (int k = 0; k < 2; k++){
    if (digitalRead(micPins[k]) == HIGH){
      if (!micSent1){
//      if (!micSent1[k]){
//        Serial.print(micChannels[k]);
        Serial.print(200);
        Serial.print(' ');
        Serial.println('1');
//        micSent1[k] = true;
        micSent1 = true;
      }
      mic1 = true;
      return;
    } else {
      if (micSent1){
//      if (!micSent1[k]){
//        Serial.print(micChannels[k]);
        Serial.print(200);
        Serial.print(' ');
        Serial.println('0');
//        micSent1[k] = true;
        micSent1 = false;
      }
    }
  }


  adjust = false;
  
  for (int i = 0; i < 32; i++){
    if (digitalRead(i + 22) == HIGH){
      
      if (!adjust){
        for (int j = 0; j < adjustNo; j++){
          if (i == adjustPins[j]){
            adjust = true;
            break;
          }
        }
      }

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

