class Fuel {
  private:
    double referenceResistance = 47;
    InternalVoltage internalVoltage;

    int convertFuelResistanceToFuel(double fuelResistance) {
      double fuelAmount;
      fuelAmount = 1.061143 - 0.01630667 * fuelResistance + 0.00005695241 * pow(fuelResistance, 2);
      return (int)(fuelAmount * 100);
    }

    double getFuelResistance() {
      int analogFuelValue = 0;
      analogReference(DEFAULT);
      analogFuelValue = analogRead(A2);
      analogFuelValue = analogRead(A2);
      analogFuelValue = analogRead(A2);
      double referenceVoltage = internalVoltage.getInternalReferenceVoltage();
      double fuelVoltage = ((double)analogFuelValue / 1023.0) * referenceVoltage;
      double fuelResistance = (fuelVoltage * referenceResistance) / (referenceVoltage - fuelVoltage);
      return fuelResistance;
    }

  public:
    unsigned long lastTimeSensorRead = 0;
    int sensorReadInterval = 5000;
    double getFuelAmount() {
      return convertFuelResistanceToFuel(getFuelResistance());
    }
};

Fuel fuelSensor;
