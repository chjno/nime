class S2S
{
  public:
    S2S(int samp, int func, int pin);
    void state();
  private:
    int _samp;
    int _func;
    int _pin;
    bool _sent0;
    bool _sent1;
};

S2S::S2S(int samp, int func, int pin)
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
      Serial.print('1');
      Serial.print(' ');
      Serial.print(_samp);
      Serial.print(' ');
      Serial.println(_func);
      _sent1 = true;
      _sent0 = false;
    }
  } else {
    if (!_sent0){
      Serial.print('0');
      Serial.print(' ');
      Serial.print(_samp);
      Serial.print(' ');
      Serial.println(_func);
      _sent0 = true;
      _sent1 = false;
    }
  }
}
