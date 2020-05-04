#include <TinyGPS++.h>

class GpsAPI {
  private:
    unsigned long lastDataTime = 0;
    unsigned long lastCourseTime = 0;
    double lastLong = 0.0;
    double lastLat = 0.0;

    void debounceInvalidSignal() {
      if (millis() - lastDataTime > 5000) {
        valid = false;
      }
    }

    int calculateCourse(double longtitude, double latitude) {
      int result = distanceCalculator.calculateBearing(lastLong, lastLat, longtitude, latitude);
      lastLong = longtitude;
      lastLat = latitude;
      return result;
    }

  public:
    TinyGPSPlus gps;
    bool valid = false;
    int foundSatellites = 0;
    double latitude;
    double longtitude;
    int currentSpeed;
    int currentCourse;

    void getAllRequiredData() {
      if (Serial1.available() == 0) {
        debounceInvalidSignal();
      }
      while (Serial1.available() > 0) {
        if (gps.encode(Serial1.read())) {
          valid = gps.location.isValid();
          foundSatellites = gps.satellites.value();
          latitude = gps.location.lat();
          longtitude = gps.location.lng();
          currentSpeed = gps.speed.kmph();
          if (millis() - lastCourseTime > 1500) {
            lastCourseTime = millis();
            currentCourse = calculateCourse(longtitude, latitude);
            Serial.println("Speed: " + String(currentSpeed) + " currentCourse: " + String(currentCourse) + " GPS Course: " + String(gps.course.deg()));
          }
          lastDataTime = millis();
        } else {
          debounceInvalidSignal();
        }
      }
    }

    bool isGpsSignalValid() {
      return valid && (foundSatellites > 3);
    }
};

GpsAPI gpsApi;
