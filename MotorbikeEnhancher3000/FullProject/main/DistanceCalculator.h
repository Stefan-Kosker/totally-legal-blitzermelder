class DistanceCalculator {
  public:
    double calculateDistance(double long1, double lat1, double long2, double lat2){
      double deltaLongInKm = (long1-long2)* 111.12 * cos((lat1+lat2)/2 * 0.017444);
      double deltaLatInKm = (lat1-lat2) * 111.12;
      return sqrt(deltaLongInKm * deltaLongInKm + deltaLatInKm * deltaLatInKm);
    }
};
DistanceCalculator distanceCalculator;
