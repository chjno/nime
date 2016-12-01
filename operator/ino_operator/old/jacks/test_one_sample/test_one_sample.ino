const int inputPinNo = 50;
const int inputPins[inputPinNo] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,52,53,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};

const int outputPin = A0;
bool sent1 = false;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < inputPinNo; i++){
    pinMode(inputPins[i], INPUT);
  }

  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, HIGH);
}

void loop() {
  
  bool plugged = false;

  for (int j = 0; j < inputPinNo; j++){
    
    if (digitalRead(inputPins[j]) == HIGH){
      plugged = true;
      
      if (!sent1){
        sent1 = true;
        Serial.print(1);
        Serial.print(' ');
        Serial.println(j);
      }
    }
  }
  
  if (!plugged && sent1){
    sent1 = false;
    Serial.print(1);
    Serial.print(' ');
    Serial.println(200);
  }
}

