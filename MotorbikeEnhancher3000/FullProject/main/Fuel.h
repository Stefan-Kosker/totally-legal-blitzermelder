class Fuel {
  private:
    double referenceResistance = 47;
    InternalVoltage internalVoltage;

    double convertFuelResistanceToFuel(double fuelResistance) {
      double fuelAmount;
      fuelAmount = 1.061143 - 0.01630667 * fuelResistance + 0.00005695241 * pow(fuelResistance, 2);
      return fuelAmount;
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
    double getFuelAmount() {
      return convertFuelResistanceToFuel(getFuelResistance());
    }
};

Fuel fuelSensor;
