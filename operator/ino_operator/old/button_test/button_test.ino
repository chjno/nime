const int buttonPin = 13;
const int samp = 1;
const char func = 'P';

bool sent1 = false;
bool sent0 = false;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH){
    if (!sent1){
      Serial.print(samp);
      Serial.print(func);
      Serial.println('1');
      sent1 = true;
      sent0 = false;
    }
  } else {
    if (!sent0){
      Serial.print(samp);
      Serial.print(func);
      Serial.println('0');
      sent0 = true;
      sent1 = false;     
    }
  }
}
