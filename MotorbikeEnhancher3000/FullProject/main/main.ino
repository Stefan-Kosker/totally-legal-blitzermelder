#include "DisplayOnTFT.h"
#include "InternalVoltage.h"
#include "OilTemperature.h"
#include "Fuel.h"
#include "RadarPositions.h"

double referenceVoltage;
double oilTemperature;
int fuelAmount;

double oldReferenceVoltage = 0.0;
double oldOilTemperature;
int oldFuelAmount;
unsigned long time;

void setup() {
  tftDisplay.initializeDisplay();
}

void loop() {
  time = millis();
  referenceVoltage = internalVoltageSensor.getInternalReferenceVoltage();
  if (abs(oldReferenceVoltage - referenceVoltage) > 0.3) {
    tftDisplay.updateVoltageValue(oldReferenceVoltage, referenceVoltage);
    oldReferenceVoltage = referenceVoltage;
  }

  if ((time - oilTemperatureSensor.lastTimeSensorRead) > oilTemperatureSensor.sensorReadInterval) {
    oilTemperatureSensor.lastTimeSensorRead = time;
    oilTemperature = oilTemperatureSensor.getOilTemperature();
    if (abs(oldOilTemperature - oilTemperature) >= 0.5) {
      tftDisplay.updateTemperatureValue(oldOilTemperature, oilTemperature);
      oldOilTemperature = oilTemperature;
    }
  }

  if ((time - fuelSensor.lastTimeSensorRead) > fuelSensor.sensorReadInterval) {
    fuelSensor.lastTimeSensorRead = time;
    fuelAmount = fuelSensor.getFuelAmount();
    if (abs(oldFuelAmount - fuelAmount) >= 1) {
      tftDisplay.updateFuelValue(oldFuelAmount, fuelAmount);
      oldFuelAmount = fuelAmount;
    }
  }
}
