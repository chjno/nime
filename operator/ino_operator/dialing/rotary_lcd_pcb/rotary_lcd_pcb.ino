#include "LCD.h"

LCD lcd1(8, 9, 10, 11, 12, 13);

const int _rotaryPin = A0;
const int _hookPin = A2;

// on vars
bool _plugged = false;

// dial vars
const int _tickChannel = 120;
const int _tickThresh = 120;

bool _ticked;
int _ticks = 0;
long _lastTickTime = 0;



void setup() {
  Serial.begin(9600);
  pinMode(_rotaryPin, INPUT);
}

void loop() {
  if (on()){
    int num = dial();
    if (num > 0){

      // send to twilio
      Serial.println(num);
      lcd1.printNum(num);
    }
  } else {
    lcd1.reset();
  }
}

bool on(){
  if (digitalRead(_hookPin) == LOW){
    if (_plugged){
      _plugged = false;
      return false;
    }
  } else {
    if (!_plugged){
      _plugged = true;
      return true;  
    }
  }
}

int dial(){
  if (digitalRead(_rotaryPin) == LOW){
    if (!_ticked){
      _ticked = true;
      _lastTickTime = millis();
    }
  } else {
    if (_ticked){
      _ticked = false;
      if (millis() - _lastTickTime > 10){
//        troubleshoot ticks
//        Serial.println(millis() - lastTickTime);
        _ticks++;

        // send to max
        Serial.println(_tickChannel);
      }
    }
  }

  if (millis() - _lastTickTime > _tickThresh && _ticks > 0){
    int ticks = _ticks;
    _ticks = 0;
    return ticks;
  } else {
    return 0;
  }
}

