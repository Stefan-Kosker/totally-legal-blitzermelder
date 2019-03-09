#include "DisplayOnLCD.h"
#include "InternalVoltage.h"
#include "OilTemperature.h"
#include "Fuel.h"

double referenceVoltage;
double oilTemperatureValue;
double fuelAmount;

void setup() {
  lcd.begin(20, 4);
}

void loop() {
  referenceVoltage = internalVoltage.getInternalReferenceVoltage();
  oilTemperatureValue = oilTemperature.getOilTemperature();
  fuelAmount = fuel.getFuelAmount();

  lcdDisplay.showInternalVoltage(referenceVoltage);
  lcdDisplay.showOilTemperature(oilTemperatureValue);
  lcdDisplay.showFuelAmount(fuelAmountü);
  delay(100);
  lcdDisplay.clearAll();
}
