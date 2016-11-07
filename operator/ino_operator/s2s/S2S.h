class S2S
{
  public:
    S2S(int samp, char func, int pin);
    void state();
  private:
    int _samp;
    char _func;
    int _pin;
    bool _sent0;
    bool _sent1;
};

S2S::S2S(int samp, char func, int pin)
{
  pinMode(pin, INPUT);
  _samp = samp;
  _func = func;
  _pin = pin;
  _sent0 = false;
  _sent1 = false;
}

void S2S::state()
{
  if (digitalRead(_pin) == HIGH){
    if (!_sent1){
      Serial.print(_samp);
      Serial.print(_func);
      Serial.println('1');
      _sent1 = true;
      _sent0 = false;
    }
  } else {
    if (!_sent0){
      Serial.print(_samp);
      Serial.print(_func);
      Serial.println('0');
      _sent0 = true;
      _sent1 = false;
    }
  }
}
