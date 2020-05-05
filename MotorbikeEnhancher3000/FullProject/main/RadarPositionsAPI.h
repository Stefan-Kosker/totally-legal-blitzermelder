#include "RadarPositions.h"
#include "DistanceCalculator.h"
#define CacheDimension 4
#define DesiredRangeInKm 5

class RadarPositionsAPI {
  private:
    int loopLimit = sizeof(radarPositions1) / sizeof(radarPositions1[0]);
    double radarLong;
    double radarLat;
    double distanceToRadar;
    int distanceToRadarInMeters;

    int createIdForRadar(int arrayIndex, int firstDimension) {
      return arrayIndex * 10000 + firstDimension;
    }

    double readFromMemory(int arrayIndex, int firstDimension, int secondDimension) {
      const uint_farptr_t radarPositions1base = pgm_get_far_address(radarPositions1);
      const uint_farptr_t radarPositions2base = pgm_get_far_address(radarPositions2);
      const uint_farptr_t radarPositions3base = pgm_get_far_address(radarPositions3);
      const uint16_t entriesPerRow = sizeof(radarPositions1[0]) / sizeof(radarPositions1[0][0]);

      if (arrayIndex == 1) {
        return pgm_read_float_far(radarPositions1base + sizeof(float) * (firstDimension * entriesPerRow + secondDimension));
      }
      if (arrayIndex == 2) {
        return pgm_read_float_far(radarPositions2base + sizeof(float) * (firstDimension * entriesPerRow + secondDimension));
      }
      if (arrayIndex == 3) {
        return pgm_read_float_far(radarPositions3base + sizeof(float) * (firstDimension * entriesPerRow + secondDimension));
      }
      return 0.0;
    }

  public:
    unsigned int radarCache[CacheDimension]; // id, speedLimit, distance, directionToTheRadar
    unsigned long lastTimeCacheCreated = 0;
    int cacheInterval = 2000;
    unsigned long lastTimeCacheRefreshed = 0;
    int cacheRefreshInterval = 50;

    void init() {
      for (int i = 0; i < CacheDimension; ++i) {
        radarCache[i] = 0;
      }
    }

    bool isNextRadarInFrontOfMe(int currentCourse) {
      return (distanceCalculator.calculateBearingDifference(currentCourse, radarCache[3]) < 90);
    }

    void writeClosestRadarIntoCache(double currentPositionLong, double currentPositionLat) {
      double closestRange = 9999.99;
      int closestRadarId = 0;
      double closestLong = 0.0;
      double closestLat = 0.0;

      lastTimeCacheRefreshed = lastTimeCacheCreated;
      distanceCalculator.calculateCosinusAndCache(currentPositionLat);
      for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < loopLimit; ++j) {
          radarLong = readFromMemory(i, j, 1);
          radarLat = readFromMemory(i, j, 0);
          distanceToRadar = distanceCalculator.calculateDistance(currentPositionLong, currentPositionLat, radarLong , radarLat);
          if (distanceToRadar < closestRange) {
            closestRange = distanceToRadar;
            closestRadarId = createIdForRadar(i, j);
            closestLong = radarLong;
            closestLat = radarLat;
          }
        }
      }
      radarCache[0] = closestRadarId;
      radarCache[1] = readFromMemory( closestRadarId / 10000, closestRadarId % 10000, 2);
      radarCache[2] = (int)(sqrt(closestRange) * 1000);
      radarCache[3] = distanceCalculator.calculateBearing(currentPositionLong, currentPositionLat, closestLong , closestLat);
    }
};

RadarPositionsAPI radarPositionsApi;
