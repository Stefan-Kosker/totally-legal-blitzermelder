#include <math.h>

class DistanceCalculator {
  private:
    double cosinusResult = 0.0;
  public:
    void calculateCosinusAndCache(double lat1) {
      cosinusResult = cos(lat1 * 0.017444);
    }

    double calculateDistance(double long1, double lat1, double long2, double lat2) {
      double deltaLongInKm = (long1 - long2) * 111.12 * cosinusResult;
      double deltaLatInKm = (lat1 - lat2) * 111.12;
      return deltaLongInKm * deltaLongInKm + deltaLatInKm * deltaLatInKm;
    }

    int calculateBearing(double long1, double lat1, double long2, double lat2) {
      double y = lat2 - lat1;
      double x = (long2 - long1) * cosinusResult;
      double angle = atan2(y, x) * 57.326 ;
      double bearing = 0.0;
      if (angle > 90) {
        bearing = 450 - angle;
      } else {
        bearing = 90 - angle;
      }
      return bearing;
    }

    int calculateBearingDifference(int myMovementBearing, int toRadarBearing) {
      int difference = (toRadarBearing - myMovementBearing) % 360;
      if (difference < -180.0) {
        difference += 360.0;
      }

      if (difference >= 180.0) {
        difference -= 360.0;
      }
      return  abs(difference);
    }
};
DistanceCalculator distanceCalculator;
