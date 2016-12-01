#include "Mux.h"

Mux mux0(0,6);
Mux mux1(1,7);

const byte addresses[16] = {
  B00000000,  // 1
  B00001000,  // 2
  B00000100,  // 3
  B00001100,  // 4
  B00000010,  // 5
  B00001010,  // 6
  B00000110,  // 7
  B00001110,  // 8
  B00000001,  // 9
  B00001001,  // 10
  B00000101,  // 11
  B00001101,  // 12
  B00000011,  // 13
  B00001011,  // 14
  B00000111,  // 15
  B00001111   // 16
};

void setup() {
  Serial.begin(9600);
  DDRB = B00001111;   // address pins 8 9 10 11
}

void loop() {
  for (int i = 0; i < sizeof(addresses); i++){
    PORTB = addresses[i];
    mux0.read(i);
    mux1.read(i);
  }
}

