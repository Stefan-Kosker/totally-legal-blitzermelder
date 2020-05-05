#include <TinyGPS++.h>

class GpsAPI {
  private:
    unsigned long lastDataTime = 0;
    unsigned long lastCourseTime = 0;

    void debounceInvalidSignal() {
      if (millis() - lastDataTime > 5000) {
        valid = 0;
      }
    }

    void debounceNoSignal() {
      if (millis() - lastDataTime > 5000) {
        valid = 2;
      }
    }

  public:
    TinyGPSPlus gps;
    int valid = 0;
    int foundSatellites = 0;
    double latitude;
    double longtitude;
    int currentSpeed;
    int currentCourse;

    void getAllRequiredData() {
      if (Serial1.available() == 0) {
        debounceNoSignal();
      }
      while (Serial1.available() > 0) {
        if (gps.encode(Serial1.read())) {
          valid = gps.location.isValid();
          foundSatellites = gps.satellites.value();
          latitude = gps.location.lat();
          longtitude = gps.location.lng();
          currentSpeed = gps.speed.kmph();
          if (millis() - lastCourseTime > 1000) {
            lastCourseTime = millis();
            currentCourse = gps.course.deg();
            Serial.println("Speed: " + String(currentSpeed) + " currentCourse: " + String(currentCourse));
          }
          lastDataTime = millis();
        } else {
          debounceInvalidSignal();
        }
      }
    }

    // 0 = GPS Device ok but no valid signal, 1 = Valid Signal, 2 = GPS Device Dead
    int isGpsSignalValid() {
      if (valid == 1 && foundSatellites < 3) {
        valid = 0;
      }
      return valid;
    }
};

GpsAPI gpsApi;
