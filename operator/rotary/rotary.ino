//#include <LiquidCrystal.h>
//
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int in = 8;
const int tickThresh = 120;
bool tick = false;
int ticks = 0;
long lastTickTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(in, INPUT);

//  lcd.begin(16, 2);
}

void loop() {
  if (millis() - lastTickTime > tickThresh && ticks > 0){
    Serial.println(ticks);
//    lcd.print(ticks);
    ticks = 0;
  }
  
  if (digitalRead(in) == LOW){
    if (!tick){
      Serial.println("low");
      ticks++;
      tick = true;
      lastTickTime = millis();
//      Serial.println(lastTickTime);
    }
  } else {
    if (tick){
      Serial.println("high");
      tick = false; 
    }
  }

//  // set the cursor to column 0, line 1
//  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
//  // print the number of seconds since reset:
//  lcd.print(millis() / 1000);

}
