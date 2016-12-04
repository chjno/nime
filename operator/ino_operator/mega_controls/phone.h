class Phone{
  public:
    Phone(int chan, int rotaryPin, int hookPin);
    const int channel = chan;
    bool on();
    int dial();
  private:
    int _rotaryPin;
    int _hookPin;

    const int _tickThresh = 120;
    const int _tickChannel = 120;
    bool _ticked;
    int _ticks;
    long _lastTickTime;
};

Phone::Phone(int rotaryPin, int hookPin){
  pinMode(rotaryPin, INPUT);
  pinMode(hookPin, INPUT);
  _rotaryPin = rotaryPin;
  _hookPin = hookPin;

//  _tickThresh = 120;
  _ticked = false;
  _ticks = 0;
  _lastTickTime = 0;
}

void Phone::on(){
  if (digitalRead(_hookPin) == LOW){
    return false;
  } else {
    return true;
  }
}

int Phone::dial(){
  if (millis() - _lastTickTime > _tickThresh && _ticks > 0){
    _ticks = 0;
    return _ticks;
  }
  
  if (digitalRead(_rotaryPin) == LOW){
    if (!_ticked){
      _ticked = true;
      _lastTickTime = millis();
    }
  } else {
    if (_ticked){
      if (millis() - _lastTickTime > 0){
//        Serial.println(millis() - lastTickTime);
        _ticks++;
        Serial.println(_tickChannel);
      }
      _ticked = false;
    }
  }
}

