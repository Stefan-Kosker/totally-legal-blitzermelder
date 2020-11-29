class Fuel {
  private:
    double referenceResistance = 47;
    InternalVoltage internalVoltage;

    int convertFuelResistanceToFuel(double fuelResistance) {
      double fuelAmount;
      if(fuelResistance < 55) {
        fuelAmount = 0.000002 *  pow(fuelResistance, 3) - 0.00002 *  pow(fuelResistance, 2) - 0.0046 * fuelResistance + 1.0447; 
      }
      if(fuelResistance >= 55 && fuelResistance < 100) {
        fuelAmount = 0.0002 *  pow(fuelResistance, 2) - 0.0378 * fuelResistance + 1.9952;
      }
      if(fuelResistance >= 100) {
        fuelAmount = 0.1;
      }
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
