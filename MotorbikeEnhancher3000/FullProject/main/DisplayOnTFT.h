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
  private:


  public:
    void initializeDisplay() {
      pinMode(displayLight, OUTPUT);
      digitalWrite(displayLight, HIGH);
      TFTscreen.begin();
      TFTscreen.background(0, 0, 0);
      TFTscreen.setTextSize(2);
      drawImagesInitially();
    }

  private:
    void drawImagesInitially() {
      drawFuel(ST7735_GREEN);
      drawBattery(ST7735_GREEN);
      drawOilTemperature(ST7735_GREEN);
    }

    void drawFuel(int16_t color) {
      TFTscreen.drawBitmap(PADDING, PADDING + POS1, fuelImage, IMGWIDTH, IMGHEIGHT, color);
    }
    void drawBattery(int16_t color) {
      TFTscreen.drawBitmap(PADDING, PADDING + POS2, batteryImage, IMGWIDTH, IMGHEIGHT, color);
    }
    void drawOilTemperature(int16_t color) {
      TFTscreen.drawBitmap(PADDING, PADDING + POS1, oilTemperatureImage, IMGWIDTH, IMGHEIGHT, color);
    }

    void writeText(String text, int x, int y, int8_t color_r, int8_t color_g, int8_t color_b){
      char _text[sizeof(text)];
      text.toCharArray(_text, sizeof(_text));
      
      TFTscreen.stroke(color_r, color_g, color_b);
      TFTscreen.text(_text, x, y);
    }

};

DisplayOnTFT tftDisplay;
