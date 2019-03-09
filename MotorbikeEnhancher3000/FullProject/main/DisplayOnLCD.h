#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

class DisplayOnLCD {
  public:

    void showInternalVoltage(double text) {
      lcd.setCursor(0, 0); //Ab hier kann das I2C LCD Modul genau wie das einfache LCD Modul programmiert werden.
      lcd.print("Spannung: ");
      lcd.print(text);
      lcd.print(" V");
    }
    void showOilTemperature(double text) {
      lcd.setCursor(0, 1); //Ab hier kann das I2C LCD Modul genau wie das einfache LCD Modul programmiert werden.
      lcd.print("Temperatur: ");
      lcd.print(text);
      lcd.print(" C");
    }
    void showFuelAmount(double text){
      lcd.setCursor(0,2);
      lcd.print("Sprit: ");
      lcd.print(text);
    }

    void clearAll() {
      lcd.clear();
    }
};

DisplayOnLCD lcdDisplay;

