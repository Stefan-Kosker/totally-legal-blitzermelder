#include "DisplayOnTFT.h"
#include "InternalVoltage.h"
#include "OilTemperature.h"
#include "Fuel.h"

double referenceVoltage;
double oilTemperature;
int fuelAmount;

double oldReferenceVoltage = 0.0;
double oldOilTemperature;
int oldFuelAmount;

void setup() {
  tftDisplay.initializeDisplay();
}

void loop() {
  referenceVoltage = internalVoltageSensor.getInternalReferenceVoltage();
  if(abs(oldReferenceVoltage - referenceVoltage) > 0.3) {
    tftDisplay.updateVoltageValue(oldReferenceVoltage, referenceVoltage);
    oldReferenceVoltage = referenceVoltage;
  }

  oilTemperature = oilTemperatureSensor.getOilTemperature();
  if(abs(oldOilTemperature - oilTemperature) >= 1.0) {
    tftDisplay.updateTemperatureValue(oldOilTemperature, oilTemperature);
    oldOilTemperature = oilTemperature;
  }
  
  fuelAmount = fuelSensor.getFuelAmount();
  if(abs(oldFuelAmount - fuelAmount) >= 1) {
    tftDisplay.updateFuelValue(oldFuelAmount, fuelAmount);
    oldFuelAmount = fuelAmount;
  }
}
