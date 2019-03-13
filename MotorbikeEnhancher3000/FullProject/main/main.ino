#include "DisplayOnTFT.h"
#include "InternalVoltage.h"
#include "OilTemperature.h"
#include "Fuel.h"

double referenceVoltage;
double oilTemperature;
double fuelAmount;

double oldReferenceVoltage;
double oldOilTemperature;
double oldFuelAmount;

void setup() {
  tftDisplay.initializeDisplay();
}

void loop() {
  referenceVoltage = internalVoltageSensor.getInternalReferenceVoltage();
  oilTemperature = oilTemperatureSensor.getOilTemperature();
  fuelAmount = fuelSensor.getFuelAmount();

//  lcdDisplay.showInternalVoltage(referenceVoltage);
//  lcdDisplay.showOilTemperature(oilTemperature);
//  lcdDisplay.showFuelAmount(fuelAmount);
//  delay(100);
//  lcdDisplay.clearAll();
}
