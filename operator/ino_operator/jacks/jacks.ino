const int inputPinNo = 50;
const int sampNo = 10;

const int inputPins[inputPinNo] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,52,53,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
const int outputPins[sampNo] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9};

bool sent1[sampNo];

const byte outputBytes[sampNo] = {
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
  B00000001,
  B00000010
};

void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < inputPinNo; i++){
    pinMode(inputPins[i], INPUT);
  }
  
//  DDRF = B11111111;
//  DDRK = B00000011;
//  PORTF = B00000000;
//  PORTK = B00000000;

  for (int j = 0; j < sampNo; j++){
    pinMode(outputPins[j], OUTPUT);
    digitalWrite(outputPins[j], LOW);
    sent1[j] = false;
  }

}

void loop() {

  if (Serial.available() > 0){
    resetFunc();
  }
  
  for (int i = 0; i < sampNo; i++){

    if (i == 0){
      digitalWrite(outputPins[sampNo - 1], LOW);
    } else {
      digitalWrite(outputPins[i - 1], LOW);
    }
    
    digitalWrite(outputPins[i], HIGH);
    
//    if (i < 8){
//      PORTF = outputBytes[i];
//      PORTK = B00000000;
//    } else {
//      PORTF = B00000000;
//      PORTK = outputBytes[i];
//    }

    bool plugged = false;

    for (int j = 0; j < inputPinNo; j++){
      
      if (digitalRead(inputPins[j]) == HIGH){
        plugged = true;
        
        if (!sent1[i]){
          plugged = true;
          sent1[i] = true;
          
          Serial.print(i + 1);
          Serial.print(' ');
          Serial.println(j);
        }
      }
    }
    if (!plugged && sent1[i]){
      sent1[i] = false;
      Serial.print(i + 1);
      Serial.print(' ');
      Serial.println(200);
    }
  }
}

