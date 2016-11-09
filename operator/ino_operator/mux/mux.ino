byte addresses[2] = {B00000000, B00001110};

const int mux1 = 7;
const int mux2 = 6;

void setup() {
  Serial.begin(9600);
  DDRB = B00001111;
  pinMode(mux1, INPUT);
}

void loop() {
//  PORTB = B00000000;
  PORTB = addresses[0];
  Serial.print("PIN 0: ");
  Serial.println(digitalRead(mux1));
  Serial.print("PIN 17: ");
  Serial.println(digitalRead(mux2));
//  PORTB = B00001110;
  PORTB = addresses[1];
  Serial.print("PIN 7: ");
  Serial.println(digitalRead(mux1));
}
