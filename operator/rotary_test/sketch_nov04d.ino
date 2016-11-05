String no = "9173972654";

bool printed = false;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < no.length(); i++){
    Serial.print(no[i]);
    delay(1000);
  }
}

void loop() {

}
