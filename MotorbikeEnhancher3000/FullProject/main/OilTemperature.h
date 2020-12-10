class OilTemperature {
  private:

    int referenceResistance = 10000;
    int analogTemperatureValue = 0;
    double temperatureVoltage;
    double temperatureResistance;
    double referenceVoltage;
    InternalVoltage internalVoltage;

    double ressistanceTemperatureTable[40] = {
      7721.35,  // -15 °C
      5720.88,  // -10 °C
      4284.03,  // -5 °C
      3240.18,  // 0 °C
      2473.60,  // 5 °C
      1905.87,  // 10 °C
      1486.65,  // 15 °C
      1168.64,  // 20 °C
      926.71,   // 25 °C
      739.98,   // 30 °C
      594.90,   // 35 °C
      481.53,   // 40 °C
      392.57,   // 45 °C
      322.17,   // 50 °C
      266.19,   // 55 °C
      221.17,   // 60 °C
      184.72,   // 65 °C
      155.29,   // 70 °C
      131.38,   // 75 °C
      112.08,   // 80 °C
      96.40,    // 85 °C
      82.96,    // 90 °C
      71.44,    // 95 °C
      61.92,    // 100 °C
      54.01,    // 105 °C
      47.24,    // 110 °C
      41.42,    // 115 °C
      36.51,    // 120 °C
      32.38,    // 125 °C
      28.81,    // 130 °C
      25.70,    // 135 °C
      23.00,    // 140 °C
      20.66,    // 145 °C
      18.59,    // 150 °C
      16.74,    // 155 °C
      15.11,    // 160 °C
      13.66,    // 165 °C
      12.38,    // 170 °C
      11.25,    // 175 °C
      10.24     // 180 °C
    };

    double getOilTemperatureResistance() {
      analogReference(DEFAULT);
      analogTemperatureValue = analogRead(A1);
      analogTemperatureValue = analogRead(A1);
      analogTemperatureValue = analogRead(A1);
      referenceVoltage = internalVoltage.getInternalReferenceVoltage();
      temperatureVoltage = ((double)analogTemperatureValue / 1023.0) * referenceVoltage;
      temperatureResistance =  (- referenceVoltage * referenceResistance / (temperatureVoltage - referenceVoltage)) - referenceResistance;
      return temperatureResistance;
    }

    int convertOilTemperatureResistanceToCelcius(double temperatureResistance) {
      double difference;
      double minimumDifference = 99999;
      int minimumIndex = 0;
      for (int i = 0; i < sizeof ressistanceTemperatureTable / sizeof ressistanceTemperatureTable[0]; i++) {
        difference = abs(temperatureResistance - ressistanceTemperatureTable[i]);
        if ( difference < minimumDifference ) {
        minimumDifference = difference;
        minimumIndex = i;
      } else {
        break;
      }
    }
    return (minimumIndex * 5) - 15;
    }

  public:
    unsigned long lastTimeSensorRead = 0;
    int sensorReadInterval = 10000;

    double getOilTemperature() {
      return convertOilTemperatureResistanceToCelcius(getOilTemperatureResistance());
    }
};

OilTemperature oilTemperatureSensor;
