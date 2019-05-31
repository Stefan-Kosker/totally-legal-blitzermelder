#include "DisplayOnTFT.h"
#include "InternalVoltage.h"
#include "OilTemperature.h"
#include "Fuel.h"
#include "RadarPositions.h"


double referenceVoltage;
double oilTemperature;
int fuelAmount;
int counter = 1;
float value;

double oldReferenceVoltage = 0.0;
double oldOilTemperature;
int oldFuelAmount;
unsigned long time;

void setup() {
  tftDisplay.initializeDisplay();
  Serial.begin(9600);
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
  Serial.println(counter);
  switch (counter) {
    case 1:
      value = readFromMemory(1, 0, 0);
      Serial.println(value, 6);
      counter++;
      break;

    case 2:
      value = readFromMemory(2, 0, 0);
      Serial.println(value, 6);
      counter++;
      break;
    case 3:
      counter = 1;
      value = readFromMemory(3, 0, 0);
      Serial.println(value, 6);
      break;
  }
  delay(1000);
}

double readFromMemory(int arrayIndex, int firstDimension, int secondDimension) {
  if (arrayIndex == 1) {
    return pgm_read_float_far(pgm_get_far_address(radarPositions1[firstDimension][secondDimension]));
  }
  if (arrayIndex == 2) {
    return pgm_read_float_far(pgm_get_far_address(radarPositions2[firstDimension][secondDimension]));
  }
  if (arrayIndex == 3) {
    return pgm_read_float_far(pgm_get_far_address(radarPositions3[firstDimension][secondDimension]));
  }
}
