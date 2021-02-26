#include <TFT.h>
#include <SPI.h>
#include "EmbeddedImages.h"
#include "FrontendVariables.h"



#define cs   10
#define dc   9
#define rst  8
#define displayLight 3

TFT TFTscreen = TFT(cs, dc, rst);


class DisplayOnTFT {

  public:
    bool alertMode = false;
    unsigned long lastTimeGPSStatus;
    int GPSStatusInterval = 1000;

    void initializeDisplay() {
      pinMode(displayLight, OUTPUT);
      TFTscreen.begin();
      TFTscreen.setRotation(3);
      clearDisplay();
      digitalWrite(displayLight, HIGH);
    }

    void clearDisplay() {
      if (alertMode) {
        TFTscreen.background(AlertBackgroundColor_R, AlertBackgroundColor_G, AlertBackgroundColor_B);
        TFTscreen.setTextSize(5);
      } else {
        TFTscreen.background(NormalBackgroundColor_R, NormalBackgroundColor_G, NormalBackgroundColor_B);
        TFTscreen.setTextSize(2);
        drawImagesInitially(InitialIconColor);
      }

    }

    void updateFuelValue(int oldFuelValue, int fuelValue) {
      removeText(String(oldFuelValue) + "%", TEXTMARGINLEFT , POS1 + TEXTMARGINTOP);
      addText(String(fuelValue) + "%" , TEXTMARGINLEFT , POS1 + TEXTMARGINTOP);
    }

    void updateVoltageValue(double oldVoltageValue, double voltageValue) {
      removeText(String(oldVoltageValue, 1) + "V", TEXTMARGINLEFT , POS2 + TEXTMARGINTOP);
      addText(String(voltageValue, 1) + "V" , TEXTMARGINLEFT , POS2 + TEXTMARGINTOP);
    }

    void updateTemperatureValue(int oldTemperatureValue, int temperatureValue) {
      removeText(String(oldTemperatureValue) + "C", TEXTMARGINLEFT , POS3 + TEXTMARGINTOP);
      addText(String(temperatureValue) + "C", TEXTMARGINLEFT , POS3 + TEXTMARGINTOP);
    }

    void warnUserFromRadar(int speedLimit, int distanceToRadar) {
      distanceToRadar = makeDistanceValueFasterToComprehend(distanceToRadar);
      removeText("\x0F:" + String(oldSpeedLimit), ALERTTEXTMARGINLEFT, ALERTTEXTMARGINTOP);
      addText("\x0F:" + String(speedLimit), ALERTTEXTMARGINLEFT, ALERTTEXTMARGINTOP);
      removeText(String(oldDistanceToRadar) + "m", ALERTTEXTMARGINLEFT, ALERTTEXTMARGINTOP + ALERTTEXTMARGINBETWEEN);
      addText(String(distanceToRadar) + "m", ALERTTEXTMARGINLEFT, ALERTTEXTMARGINTOP + ALERTTEXTMARGINBETWEEN);
      oldSpeedLimit = speedLimit;
      oldDistanceToRadar = distanceToRadar;
    }

    void showIfGpsIsEngaged(int gpsStatus) {
      if (!alertMode) {
        removeText("X", GpsEngagedIconMargin, PADDING);
        removeText("\x03", GpsEngagedIconMargin, PADDING);
        if (gpsStatus == 1) {
          applyWriteCommand("\x03", GpsEngagedIconMargin, PADDING, 0, 255, 0);
        }
        if (gpsStatus == 2) {
          applyWriteCommand("X", GpsEngagedIconMargin, PADDING, 0, 255, 0);
        }
      }
    }

  private:

    int oldSpeedLimit  = 0;
    int oldDistanceToRadar = 0;

    int makeDistanceValueFasterToComprehend(int distanceValue) {
      if (distanceValue > 100) {
        distanceValue = distanceValue / 100;
        return distanceValue * 100;
      } else {
        distanceValue = distanceValue / 10;
        return distanceValue * 10;
      }
    }

    void applyWriteCommand(String text, int x, int y, int8_t color_r, int8_t color_g, int8_t color_b) {
      char _text[text.length() + 1];
      text.toCharArray(_text, text.length() + 1);
      _text[text.length()] = '\0'; // In case 'toCharArray' doesn't add the null terminator.

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
