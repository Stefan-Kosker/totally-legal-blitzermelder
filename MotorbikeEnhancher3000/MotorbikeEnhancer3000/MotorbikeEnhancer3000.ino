#include <TFT.h>
#include <SPI.h>


#define cs   10
#define dc   9
#define rst  8
#define flashy 3

bool draw = false;

TFT TFTscreen = TFT(cs, dc, rst);

void setup() {
  
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  pinMode(flashy, OUTPUT);
}

void loop() {
  if(draw == false) {
    TFTscreen.stroke(255, 0, 0); // set the stroke color to red
    TFTscreen.line(0, 10, TFTscreen.width(), 10); // draw a line across the screen
    
    TFTscreen.noStroke(); // don't draw a line around the next rectangle
    TFTscreen.fill(0,255,0); // set the fill color to green
    TFTscreen.rect(0,20,TFTscreen.width(),10); //draw a rectangle across the screen
  
    TFTscreen.fill(0,0,255); // set the fill color to blue
    TFTscreen.stroke(255,255,255); // outline the rectangle with a white line
    TFTscreen.rect(0,45,TFTscreen.width(),45); // draw a fat rectangle  
  
    draw = true;
  }

  digitalWrite(flashy, HIGH);
  delay(1000);
  digitalWrite(flashy, LOW);
  delay(1000);
  
}
