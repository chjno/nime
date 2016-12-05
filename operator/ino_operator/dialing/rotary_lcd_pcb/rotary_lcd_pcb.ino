#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
const int _rotaryPin = A0;
const int _hookPin = A2;

// lcd vars
int _lcdCounter = 0;

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

  lcd.begin(16, 2);
}

void loop() {
  if (on()){
    int num = dial();
    if (num > 0){

      // send to twilio
      Serial.println(num);
      lcdDisplay(num); 
    }
  } else {
    lcd.clear();
  }
}

void lcdDisplay(int number){
  if (_lcdCounter == 3 || _lcdCounter == 6){
        lcd.print('-');
      } else if (_lcdCounter == 10){
        lcd.setCursor(0, 1);
      } else if (_lcdCounter > 25){
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        _lcdCounter = 10;
      }
      lcd.print(number);
      _lcdCounter++;
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

