#include "DisplayOnTFT.h"
#include "InternalVoltage.h"
#include "OilTemperature.h"
#include "Fuel.h"

double referenceVoltage;
double oilTemperatureValue;
double fuelAmount;

void setup() {
  tftDisplay.initializeDisplay();
}

void loop() {
  referenceVoltage = internalVoltage.getInternalReferenceVoltage();
  oilTemperatureValue = oilTemperature.getOilTemperature();
  fuelAmount = fuel.getFuelAmount();

//  lcdDisplay.showInternalVoltage(referenceVoltage);
//  lcdDisplay.showOilTemperature(oilTemperatureValue);
//  lcdDisplay.showFuelAmount(fuelAmount);
//  delay(100);
//  lcdDisplay.clearAll();
}
