#include <LiquidCrystal.h>

class LCD{
  public:
    LCD(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6);
    void printNum(int);
    void reset();
  private:
    LiquidCrystal _lcd;
    int _lcdCounter;
};

LCD::LCD(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6)
  : _lcd(pin1,pin2,pin3,pin4,pin5,pin6)
{
  _lcdCounter = 0;
  _lcd.begin(16, 2);
}

void LCD::printNum(int number){
  if (_lcdCounter == 3 || _lcdCounter == 6){
    _lcd.print('-');
  } else if (_lcdCounter == 10){
    _lcd.setCursor(0, 1);
  } else if (_lcdCounter > 25){
    _lcd.setCursor(0, 1);
    _lcd.print("                ");
    _lcd.setCursor(0, 1);
    _lcdCounter = 10;
  }
  _lcd.print(number);
  _lcdCounter++;
}

void LCD::reset(){
  _lcd.clear();
  _lcdCounter = 0;
}

