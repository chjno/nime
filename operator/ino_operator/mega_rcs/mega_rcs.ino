const int outputPins[10] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9};
const int inputPins[50] = {2,3,4,5,6,7,8,9,10,11,12,A13,14,15,16,17,18,19,A14,A15,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};

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
  
//  for (int i = 0; i < sizeof(inputPins); i++){
//    pinMode(inputPins[i], INPUT);
//  }
}

void loop() {
  for (int i = 0; i < 10; i++){
    if (i < 8){
      PORTK = B00000000;
      PORTF = outputBytes[i];
    } else {
      PORTF = B00000000;
      PORTK = outputBytes[i];
    }

    for (int j = 0; j < 50; j++){
//      if ((j != 11) && (j != 18) && (j != 19)){
        if (digitalRead(inputPins[j]) == HIGH){
          Serial.println(String(j + 2));
        }
//      }
    }
  }
}
