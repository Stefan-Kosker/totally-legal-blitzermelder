#include "DisplayOnTFT.h"
#include "InternalVoltage.h"
#include "OilTemperature.h"
#include "Fuel.h"
#include "RadarPositions.h"
#include "DistanceCalculator.h"


double referenceVoltage;
double oilTemperature;
int fuelAmount;
int counter = 1;
float value;

double oldReferenceVoltage = 0.0;
double oldOilTemperature;
int oldFuelAmount;
unsigned long time;


unsigned long starttime;
unsigned long stoptime;

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

  double currentPosLong = 8.473979;
  double currentPosLat =  49.069344;
  int loopLimit = sizeof(radarPositions1) / sizeof(radarPositions1[0]);

  Serial.println(readFromMemory(1, 0, 0));

  //Serial.println(distanceCalculator.calculateDistance(currentPosLong, currentPosLat, 8.427868, 49.090272), 6);
  starttime = millis();
  for (int i = 1; i < 4; i++) {
    for (int j = 0; j < loopLimit; j++) {
      value = distanceCalculator.calculateDistance(currentPosLong, currentPosLat, readFromMemory(i, j, 1), readFromMemory(i, j, 0));
    }
  }
  stoptime = millis();
  Serial.println(stoptime - starttime, 6);
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
