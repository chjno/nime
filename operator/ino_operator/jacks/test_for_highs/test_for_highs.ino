const int inputPinNo = 50;
const int inputPins[inputPinNo] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};


void setup() {
  Serial.begin(9600);

//  DDRF = B11111111;
//  DDRK = B00000011;
//
//  DDRA = B00000000;
//  DDRB = B00000000;
//  DDRC = B00000000;
//  DDRD = B00000000;
//  DDRE = B00000000;
//  DDRG = B00000000;
//  DDRH = B00000000;
//  DDRJ = B00000000;
//  DDRL = B00000000;
  
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);

  for (int i = 0; i < inputPinNo; i++){
    pinMode(inputPins[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < inputPinNo; i++){
    if (digitalRead(inputPins[i]) == HIGH){
      Serial.println(inputPins[i]);
    }
  }

}
