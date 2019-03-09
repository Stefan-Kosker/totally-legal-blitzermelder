class OilTemperature {
  private:

    int referenceResistance = 10000;
    int analogTemperatureValue = 0;
    double temperatureVoltage;
    double temperatureResistance;
    double referenceVoltage; 
    InternalVoltage internalVoltage;

    double getOilTemperatureRessistance() {
      analogReference(DEFAULT);
      analogTemperatureValue = analogRead(A1);
      analogTemperatureValue = analogRead(A1);
      analogTemperatureValue = analogRead(A1);
      referenceVoltage = internalVoltage.getInternalReferenceVoltage();
      temperatureVoltage = ((double)analogTemperatureValue / 1023.0) * referenceVoltage;
      temperatureResistance = (temperatureVoltage * referenceResistance) / (referenceVoltage - temperatureVoltage);
      return temperatureResistance;
    }

    double convertOilTemperatureResistanceToCelcius(double temperatureResistance) {
      int temperature = 1 / (0.001759284 + 0.000251684 * log(temperatureResistance) + 0.000000082 * pow(log(temperatureResistance), 3));
      temperature = temperature - 273;
      return temperature;
    }

  public:

    double getOilTemperature() {
      return convertOilTemperatureResistanceToCelcius(getOilTemperatureRessistance());
    }

};

OilTemperature oilTemperature;

