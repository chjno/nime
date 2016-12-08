#include "LCD.h"
#include "Phone.h"

bool sent1[32];
bool adjust = false;

LCD lcd[2] = {
  LCD(8, 9, 10, 11, 12, 13),
  LCD(A10, A11, A12, A13, A14, A15)
};

Phone phone[2] = {
  Phone(100, A0, A2),
  Phone(101, A1, A3)
};

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

void controlStates(){
  
  adjust = false;
  
  for (int i = 0; i < 32; i++){
    if (digitalRead(i + 22) == HIGH){
      
      if (!adjust){
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9 || i == 11 || i == 13 || i == 15 || i == 17 || i == 19){
          adjust = true;
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

