const int outputPins[2] = {A0, A1};
const int inputPins[8] = {2,11,12,21,22,31,32,41};
const int jacks[8] = {31,32,41,50,51,60,61,70};
int sampleState[2] = {200,200};

const byte outputBytes[2] = {
  B00000001,
  B00000010
};

void setup() {
  Serial.begin(9600);
  
  DDRF = B00000011;
  PORTF = B00000000;

  DDRA = B00000000;
  DDRB = B00000000;
  DDRC = B00000000;
  DDRD = B00000000;
  DDRE = B00000000;
  DDRG = B00000000;
  DDRH = B00000000;
  DDRJ = B00000000;
  DDRL = B00000000;
  
  for (int i = 0; i < 8; i++){
    pinMode(inputPins[i], INPUT);
  }
}

void loop() {

  for (int i = 0; i < 2; i++){
    
    bool plugged = false;
    PORTF = outputBytes[i];

    for (int j = 0; j < 8; j++){
      
      if (digitalRead(inputPins[j]) == HIGH){
        if (sampleState[i] != jacks[j]){
          Serial.print(i + 1);
          Serial.print(' ');
          Serial.println(jacks[j]);
          sampleState[i] = jacks[j];
          plugged = true;
        }
      }
    }

    if (!plugged){
      Serial.print(i + 1);
      Serial.print(' ');
      Serial.println(200);
      sampleState[i] = 200;
    }
    
  }

  
  
}
