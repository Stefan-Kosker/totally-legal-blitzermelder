#include "./DisplayOnTFT.h"
#include "./InternalVoltage.h"
#include "./OilTemperature.h"
#include "./Fuel.h"
#include "./RadarPositionsAPI.h"
#include "./GpsAPI.h"


double referenceVoltage;
double oilTemperature;
int fuelAmount;
int counter = 1;
float value;
bool alert = false;

double oldReferenceVoltage = 0.0;
double oldOilTemperature;
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

  if (alert || (time - radarPositionsApi.lastTimeCacheCreated) > radarPositionsApi.cacheInterval) {
    double currentPosLong = random(8473970, 8473979) / 1000000.0;
    double currentPosLat =  random(49069340, 49069349) / 1000000.0;
    int currentSpeed = 400;
    if (millis() > 20000) {
      currentSpeed = 50;
    }

    gpsApi.showAll();


    radarPositionsApi.lastTimeCacheCreated = time;
    radarPositionsApi.writeClosestRadarIntoCache(currentPosLong, currentPosLat);
    if ( currentSpeed > 10 && !alert && (radarPositionsApi.radarCache[2] < currentSpeed * 10)) {
      setAlert();
    }
    if (currentSpeed > 10 && alert && (radarPositionsApi.radarCache[2] > currentSpeed * 10)) {
      disarmAlert();
    }
    if (alert && currentSpeed > 10) {
      tftDisplay.warnUserFromRadar(radarPositionsApi.radarCache[1], radarPositionsApi.radarCache[2]);
    }
  }
  delay(100);
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
