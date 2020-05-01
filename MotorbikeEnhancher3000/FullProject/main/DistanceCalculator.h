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
};
DistanceCalculator distanceCalculator;
