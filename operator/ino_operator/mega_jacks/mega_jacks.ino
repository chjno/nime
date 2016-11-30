const int outputPins[10] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9};
const int inputPins[4] = {2,11,12,21};
//const int inputPins[50] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
int sampleState[10] = {31,32,33,34,35,36,37,38,39,40};
bool sent0[10];
bool sent1[10];

const byte outputBytes[10] = {
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

void setup() {
  Serial.begin(9600);
  Serial1.end();
  Serial2.end();
  Serial3.end();

  DDRF = B11111111;
  DDRK = B00000011;

  DDRA = B00000000;
  DDRB = B00000000;
  DDRC = B00000000;
  DDRD = B00000000;
  DDRE = B00000000;
  DDRG = B00000000;
  DDRH = B00000000;
  DDRJ = B00000000;
  DDRL = B00000000;

  for (int i = 0; i < 10; i++){
    sent0[i] = false;
    sent1[i] = false;
  }
  
//  for (int i = 0; i < sizeof(inputPins); i++){
//    pinMode(inputPins[i], INPUT);
//  }
}

void loop() {
  
  for (int i = 0; i < sizeof(outputPins); i++){
    
    if (i < 8){
      PORTK = B00000000;
      PORTF = outputBytes[i];
    } else {
      PORTF = B00000000;
      PORTK = outputBytes[i];
    }

    for (int j = 0; j < sizeof(inputPins); j++){
      
        if (digitalRead(inputPins[j]) == HIGH){
//          if (!sent1[i]){
          if (j + 41 != sampleState[i]){
            Serial.print(String(i + 1));
            Serial.print(' ');
            Serial.println(String(j + 41));
            sampleState[i] = j + 41;
//            sent1[i] = true;
//            sent0[i] = false;
          }
          
        } else {
//          if (!sent0[i]){
          if (j + 31 != sampleState[i]){
            Serial.print(String(i + 1));
            Serial.print(' ');
            Serial.println(String(i + 31)); // if not using normal plugs
            sampleState[i] = j + 31;
//            sent0[i] = true;
//            sent1[i] = false;
          }
       }   
    }
  }
}

