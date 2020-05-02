#include <TinyGPS++.h>

class GpsAPI {
  public:
    TinyGPSPlus gps;
    bool valid = false;
    int foundSatellites = 0;
    double latitude;
    double longtitude;
    int currentSpeed;
    double currentCourse;

    void getAllRequiredData() {
      while (Serial1.available() > 0) {
        if (gps.encode(Serial1.read())) {
          valid = gps.location.isValid();
          foundSatellites = gps.satellites.value();
          latitude = gps.location.lat();
          longtitude = gps.location.lng();
          currentSpeed = gps.speed.kmph();
          currentCourse = gps.course.deg();
        }
      }
    }

    bool isGpsSignalValid() {
      return valid && (foundSatellites > 3);
    }
};

GpsAPI gpsApi;
