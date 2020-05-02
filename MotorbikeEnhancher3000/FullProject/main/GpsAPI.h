#include <TinyGPS++.h>

class GpsAPI {
  private:
    unsigned long lastDataTime = 0;

    void debounceInvalidSignal() {
      if (millis() - lastDataTime > 5000) {
        valid = false;
      }
    }

  public:
    TinyGPSPlus gps;
    bool valid = false;
    int foundSatellites = 0;
    double latitude;
    double longtitude;
    int currentSpeed;
    double currentCourse;

    void getAllRequiredData() {
      if(Serial1.available() == 0) {
        debounceInvalidSignal();
      }
      while (Serial1.available() > 0) {
        if (gps.encode(Serial1.read())) {
          valid = gps.location.isValid();
          foundSatellites = gps.satellites.value();
          latitude = gps.location.lat();
          longtitude = gps.location.lng();
          currentSpeed = gps.speed.kmph();
          currentCourse = gps.course.deg();
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
