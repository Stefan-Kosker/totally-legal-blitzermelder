#include "./DisplayOnTFT.h"
#include "./InternalVoltage.h"
#include "./OilTemperature.h"
#include "./Fuel.h"
#include "./RadarPositionsAPI.h"
#include "./GpsAPI.h"


double referenceVoltage;
int oilTemperature;
int fuelAmount;
int counter = 1;
float value;
bool alert = false;

double oldReferenceVoltage = 0.0;
int oldOilTemperature;
int oldFuelAmount;
unsigned long time;


unsigned long starttime;
unsigned long stoptime;

double tempLat;
double tempLong;

void setup() {
  tftDisplay.initializeDisplay();
  radarPositionsApi.init();
  Serial.begin(9600);
  Serial1.begin(9600); // GPS
}

void loop() {
  gpsApi.getAllRequiredData();
  tftDisplay.showIfGpsIsEngaged(gpsApi.isGpsSignalValid());
  time = millis();

  referenceVoltage = internalVoltageSensor.getInternalReferenceVoltage();
  if (abs(oldReferenceVoltage - referenceVoltage) > 0.3) {
    tftDisplay.updateVoltageValue(oldReferenceVoltage, referenceVoltage);
    oldReferenceVoltage = referenceVoltage;
  }

  if (!alert && (time - oilTemperatureSensor.lastTimeSensorRead) > oilTemperatureSensor.sensorReadInterval) {
    oilTemperatureSensor.lastTimeSensorRead = time;
    oilTemperature = oilTemperatureSensor.getOilTemperature();
    if (abs(oldOilTemperature - oilTemperature) >= 0.5) {
      tftDisplay.updateTemperatureValue(oldOilTemperature, oilTemperature);
      oldOilTemperature = oilTemperature;
    }
  }

  if (!alert && (time - fuelSensor.lastTimeSensorRead) > fuelSensor.sensorReadInterval) {
    fuelSensor.lastTimeSensorRead = time;
    fuelAmount = fuelSensor.getFuelAmount();
    if (abs(oldFuelAmount - fuelAmount) >= 1) {
      tftDisplay.updateFuelValue(oldFuelAmount, fuelAmount);
      oldFuelAmount = fuelAmount;
    }
  }

  if (gpsApi.isGpsSignalValid() && (time - radarPositionsApi.lastTimeCacheCreated) > radarPositionsApi.cacheInterval) {
    radarPositionsApi.lastTimeCacheCreated = time;
    radarPositionsApi.writeClosestRadarIntoCache(gpsApi.longtitude, gpsApi.latitude);
    if (!alert && gpsApi.currentSpeed > 10 && radarPositionsApi.isNextRadarInFrontOfMe(gpsApi.currentCourse) && (radarPositionsApi.radarCache[2] < gpsApi.currentSpeed * 10)) {
      setAlert();
    }
    if (alert && gpsApi.currentSpeed > 10  && (!radarPositionsApi.isNextRadarInFrontOfMe(gpsApi.currentCourse)  || (radarPositionsApi.radarCache[2] > gpsApi.currentSpeed * 10))) {
      disarmAlert();
    }
    if (alert && gpsApi.currentSpeed > 10) {
      tftDisplay.warnUserFromRadar(radarPositionsApi.radarCache[1], radarPositionsApi.radarCache[2]);
    }
  }
}

void setAlert () {
  alert = true;
  tftDisplay.alertMode = true;
  tftDisplay.clearDisplay();
}

void disarmAlert() {
  alert = false;
  tftDisplay.alertMode = false;
  tftDisplay.clearDisplay();
}
