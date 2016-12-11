class Phone{
  public:
    Phone(int chan, int rotaryPin, int hookPin);
    int channel;
    bool hung;
    bool on();
    int dial();
  private:
    int _rotaryPin;
    int _hookPin;

//    bool _plugged = false;

    const int _tickChannel = 120;
    const int _tickThresh = 200;
    bool _ticked;
    int _ticks = 0;
    long _lastTickTime = 0;
};

Phone::Phone(int chan, int rotaryPin, int hookPin){
  hung = true;
  channel = chan;
  pinMode(rotaryPin, INPUT);
  pinMode(hookPin, INPUT);
  _rotaryPin = rotaryPin;
  _hookPin = hookPin;
}

bool Phone::on(){
  if (digitalRead(_hookPin) == LOW){
//    if (_plugged){
//      _plugged = false;
      return false;
//    }
  } else {
//    if (!_plugged){
//      _plugged = true;
      return true;  
//    }
  }
}

int Phone::dial(){
  if (digitalRead(_rotaryPin) == LOW){
    if (!_ticked){
      _ticked = true;
      _lastTickTime = millis();
    }
  } else {
    if (_ticked){
      _ticked = false;
      if (millis() - _lastTickTime > 10){
//        troubleshoot ticks
//        Serial.println(millis() - _lastTickTime);
        _ticks++;

        // send to max
//        Serial.println(_tickChannel);
        return _tickChannel;
      }
    }
  }

  if (millis() - _lastTickTime > _tickThresh && _ticks > 0){
    int ticks = _ticks;
    _ticks = 0;
    return ticks;
  } else {
    return 0;
  }
}
