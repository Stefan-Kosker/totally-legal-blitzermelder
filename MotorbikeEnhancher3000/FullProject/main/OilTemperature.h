class OilTemperature {
  private:

    int referenceResistance = 10000;
    int analogTemperatureValue = 0;
    double temperatureVoltage;
    double temperatureResistance;
    double referenceVoltage;
    InternalVoltage internalVoltage;

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
      int temperature =  -35.22 * (log(temperatureResistance) / 0.43429) + 251.42;
      return temperature;
    }

  public:
    unsigned long lastTimeSensorRead = 0;
    int sensorReadInterval = 10000;

    double getOilTemperature() {
      return convertOilTemperatureResistanceToCelcius(getOilTemperatureResistance());
    }
};

OilTemperature oilTemperatureSensor;
