#include <TFT.h>
#include <SPI.h>
#include "EmbeddedImages.h"
#include "FrontendVariables.h"



#define cs   10
#define dc   9
#define rst  8
#define displayLight 3

TFT TFTscreen = TFT(cs, dc, rst);
bool alertMode = false;

class DisplayOnTFT {

  public:
    void initializeDisplay() {
      pinMode(displayLight, OUTPUT);
      digitalWrite(displayLight, HIGH);
      TFTscreen.begin();
      TFTscreen.background(NormalBackgroundColor_R, NormalBackgroundColor_G, NormalBackgroundColor_B);
      TFTscreen.setTextSize(2);
      drawImagesInitially(InitialIconColor);
    }

    void updateFuelValue(double oldFuelValue, double fuelValue) {
      removeText(String(oldFuelValue,0) + "%", TEXTMARGINLEFT , POS1 + TEXTMARGINTOP);
      addText(String(fuelValue,0) + "%" , TEXTMARGINLEFT , POS1 + TEXTMARGINTOP);
    }

    void updateVoltageValue(double oldVoltageValue, double voltageValue) {
      removeText(String(oldVoltageValue, 1) +"V", TEXTMARGINLEFT , POS2 + TEXTMARGINTOP);
      addText(String(voltageValue, 1) + "V" , TEXTMARGINLEFT , POS2 + TEXTMARGINTOP);
    }

    void updateTemperatureValue(double oldTemperatureValue, double temperatureValue) {
      removeText(String(oldTemperatureValue, 1) + "C", TEXTMARGINLEFT , POS3 + TEXTMARGINTOP);
      addText(String(temperatureValue, 1) + "C", TEXTMARGINLEFT , POS3 + TEXTMARGINTOP);
    }

  private:

    void applyWriteCommand(String text, int x, int y, int8_t color_r, int8_t color_g, int8_t color_b) {
      char _text[sizeof(text)];
      text.toCharArray(_text, sizeof(_text));

      TFTscreen.stroke(color_r, color_g, color_b);
      TFTscreen.text(_text, x, y);
    }

    void removeText(String text, int x, int y) {
      if (alertMode) {
        applyWriteCommand(text, x, y, AlertBackgroundColor_R, AlertBackgroundColor_G, AlertBackgroundColor_B);
      } else {
        applyWriteCommand(text, x, y, NormalBackgroundColor_R, NormalBackgroundColor_G, NormalBackgroundColor_B);
      }
    }

    void addText(String text, int x, int y) {
      if (alertMode) {
        applyWriteCommand(text, x, y, AlertTextColor_R, AlertTextColor_G, AlertTextColor_B);
      } else {
        applyWriteCommand(text, x, y, NormalTextColor_R, NormalTextColor_G, NormalTextColor_B);
      }
    }

    void drawImagesInitially(int16_t color) {
      drawFuelIcon(color);
      drawBatteryIcon(color);
      drawOilTemperatureIcon(color);
    }

    void drawFuelIcon(int16_t color) {
      TFTscreen.drawBitmap(PADDING, PADDING + POS1, fuelImage, IMGWIDTH, IMGHEIGHT, color);
    }
    void drawBatteryIcon(int16_t color) {
      TFTscreen.drawBitmap(PADDING, PADDING + POS2, batteryImage, IMGWIDTH, IMGHEIGHT, color);
    }
    void drawOilTemperatureIcon(int16_t color) {
      TFTscreen.drawBitmap(PADDING, PADDING + POS3, oilTemperatureImage, IMGWIDTH, IMGHEIGHT, color);
    }
};

DisplayOnTFT tftDisplay;
