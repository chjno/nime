#include <Switch2Serial.h>

Switch2Serial loop1(1,'L',8);
Switch2Serial rec1(1,'R',12);
Switch2Serial play1(1,'P',13);

void setup() {
  Serial.begin(9600);

}

void loop() {
  rec1.state();
  loop1.state();
  play1.state();
}
