class Mux{
  public:
    Mux(int muxNo, int inoPin);
    void read(int);
  private:
    int _muxNo;
    int _inoPin;
    bool _sent0[16];
    bool _sent1[16];
};

Mux::Mux(int muxNo, int inoPin){
  pinMode(inoPin, INPUT);
  _muxNo = muxNo;
  _inoPin = inoPin;
  for (int i = 0; i < 16; i++){
    _sent0[i] = false;
    _sent1[i] = false;
  }
}

void Mux::read(int channel){
  if (digitalRead(_inoPin) == HIGH){
    if (!_sent1[channel]){
      Serial.print('1');
      Serial.print(' ');
      Serial.println(_muxNo * 16 + channel + 1);
//      Serial.print('1');
//      Serial.print(' ');
//      Serial.print(_muxNo);
//      Serial.print(' ');
//      Serial.println(channel);      
      _sent1[channel] = true;
      _sent0[channel] = false;
    }
  } else {
    if (!_sent0[channel]){
      Serial.print('0');
      Serial.print(' ');
      Serial.println(_muxNo * 16 + channel + 1);
//      Serial.print('0');
//      Serial.print(' ');
//      Serial.print(_muxNo);
//      Serial.print(' ');
//      Serial.println(channel);
      _sent0[channel] = true;
      _sent1[channel] = false;
    }
  }
}

