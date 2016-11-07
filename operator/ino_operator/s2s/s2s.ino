#include "S2S.h"

// 1 == record
// 2 == play
// 3 == loop

S2S rec1(1,1,12);
S2S play1(1,2,13);
S2S loop1(1,3,8);

void setup() {
  Serial.begin(9600);

}

void loop() {
  rec1.state();
  loop1.state();
  play1.state();
}
