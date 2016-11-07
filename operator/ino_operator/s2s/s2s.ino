#include "S2S.h"

S2S loop1(1,'L',8);
S2S rec1(1,'R',12);
S2S play1(1,'P',13);

void setup() {
  Serial.begin(9600);

}

void loop() {
  rec1.state();
  loop1.state();
  play1.state();
}
