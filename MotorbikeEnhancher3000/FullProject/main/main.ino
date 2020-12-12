#include "./DisplayOnTFT.h"
#include "./InternalVoltage.h"
#include "./OilTemperature.h"
#include "./Fuel.h"
#include "./RadarPositionsAPI.h"
#include "./GpsAPI.h"


double referenceVoltage;
int oilTemperature;
int fuelAmount;
float value;

double oldReferenceVoltage = 0.0;
int oldOilTemperature = -100;
int oldFuelAmount = - 100;
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
  time = millis();


  gpsApi.getAllRequiredData();
  if (time - tftDisplay.lastTimeGPSStatus > tftDisplay.GPSStatusInterval) {
    tftDisplay.lastTimeGPSStatus = time;
    tftDisplay.showIfGpsIsEngaged(gpsApi.isGpsSignalValid());
  }


  referenceVoltage = internalVoltageSensor.getInternalReferenceVoltage();
  if (abs(oldReferenceVoltage - referenceVoltage) > 0.09) {
    if (!tftDisplay.alertMode) {
      tftDisplay.updateVoltageValue(oldReferenceVoltage, referenceVoltage);
    }
    oldReferenceVoltage = referenceVoltage;
  }

  if (!tftDisplay.alertMode && (time - oilTemperatureSensor.lastTimeSensorRead) > oilTemperatureSensor.sensorReadInterval) {
    oilTemperatureSensor.lastTimeSensorRead = time;
    oilTemperature = oilTemperatureSensor.getOilTemperature();
    if (abs(oldOilTemperature - oilTemperature) >= 0.5) {
      tftDisplay.updateTemperatureValue(oldOilTemperature, oilTemperature);
      oldOilTemperature = oilTemperature;
    }
  }


  if (!tftDisplay.alertMode && (time - fuelSensor.lastTimeSensorRead) > fuelSensor.sensorReadInterval) {
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
    if (!tftDisplay.alertMode && gpsApi.currentSpeed > 10 && radarPositionsApi.isNextRadarInFrontOfMe(gpsApi.currentCourse) && (radarPositionsApi.radarCache[2] < gpsApi.currentSpeed * 10)) {
      setAlert();
    }
    if (tftDisplay.alertMode && gpsApi.currentSpeed > 10  && (!radarPositionsApi.isNextRadarInFrontOfMe(gpsApi.currentCourse)  || (radarPositionsApi.radarCache[2] > gpsApi.currentSpeed * 10)) || gpsApi.currentSpeed < 10 ) {
      disarmAlert();
    }
    if (tftDisplay.alertMode && gpsApi.currentSpeed > 10) {
      tftDisplay.warnUserFromRadar(radarPositionsApi.radarCache[1], radarPositionsApi.radarCache[2]);
    }
  }
}

void setAlert () {
  tftDisplay.alertMode = true;
  tftDisplay.clearDisplay();
}

void disarmAlert() {
  tftDisplay.alertMode = false;
  tftDisplay.clearDisplay();
}
