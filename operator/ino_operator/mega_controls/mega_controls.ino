bool sent0[32];
bool sent1[32];

void setup() {
  Serial.begin(9600);

  DDRA = B00000000;
  DDRC = B00000000;
  DDRD = B00000000;
  DDRG = B00000000;
  DDRL = B00000000;
  DDRB = B00000000;

  for (int i = 0; i < 32; i++){
    sent0[i] = false;
    sent1[i] = false;
  }
}

void loop() {
  
  for (int i = 0; i < 32; i++){
    if (digitalRead(i + 22) == HIGH){
      if (!sent1[i]){
        Serial.print('1');
        Serial.print(' ');
        Serial.println(i);
        sent1[i] = true;
        sent0[i] = false;
      }
      
    } else {
      if (!sent0[i]){
        Serial.print('0');
        Serial.print(' ');
        Serial.println(i);
        sent0[i] = true;
        sent1[i] = false;
      }
    }
  }

}
