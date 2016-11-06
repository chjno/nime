const int tickThresh = 120;

#include <LiquidCrystal.h>

//  // set the cursor to column 0, line 1
//  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
//  // print the number of seconds since reset:
//  lcd.print(millis() / 1000);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int dialPin = 8;
const int hookPin = 9;

bool tick = false;
int ticks = 0;
long lastTickTime = 0;
bool onHook = false;

void setup() {
  Serial.begin(9600);
  pinMode(dialPin, INPUT);

  lcd.begin(16, 2);
}

void loop() {
  
  hook();
  if (!onHook){
    if (Serial.available()){
      Serial.read();
      lcd.clear();
    }
    dial();
  }

}

void dial(){
  if (millis() - lastTickTime > tickThresh && ticks > 0){
    Serial.print(ticks);
    lcd.print(ticks);
    ticks = 0;
  }
  
  if (digitalRead(dialPin) == LOW){
    if (!tick){
//      Serial.println("low");
      ticks++;
      tick = true;
      lastTickTime = millis();
//      Serial.println(lastTickTime);
    }
  } else {
    if (tick){
//      Serial.println("high");
      tick = false; 
    }
  }
}

bool hook(){
  if (digitalRead(hookPin) == LOW){
    if (onHook){
      onHook = false;
    }
  } else {
    if (!onHook){
      Serial.print('.');
      lcd.clear();
      onHook = true;
    }
  }
}

