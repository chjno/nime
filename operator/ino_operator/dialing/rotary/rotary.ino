const int tickThresh = 120;
const int dialPin = 8;

bool tick = false;
int ticks = 0;
long lastTickTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(dialPin, INPUT);
}

void loop() {
  dial();
}

void dial(){
  if (millis() - lastTickTime > tickThresh && ticks > 0){
    Serial.println(ticks);
    ticks = 0;
  }
  
  if (digitalRead(dialPin) == LOW){
    if (!tick){
      tick = true;
      lastTickTime = millis();
    }
  } else {
    if (tick){
      if (millis() - lastTickTime > 0){
//        Serial.println(millis() - lastTickTime);
        ticks++;
      }
      tick = false;
    }
  }
}

