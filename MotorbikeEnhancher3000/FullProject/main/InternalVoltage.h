class InternalVoltage {
  private:

    int analogReferenceValue = 0;
    double referenceVoltage = 4.3;
    double referenceResistanceR1 = 1000;
    double referenceResistanceR2 = 4700;

  public:
    double getInternalReferenceVoltage() {
//      analogReference(INTERNAL1V1);
//      analogReferenceValue = analogRead(A0);
//      analogReferenceValue = analogRead(A0);
//      analogReferenceValue = analogRead(A0);
//      referenceVoltage = double(analogReferenceValue) / 1023.0 * 1.1;
//      referenceVoltage = referenceVoltage * (referenceResistanceR1 + referenceResistanceR2) / referenceResistanceR1;
      return referenceVoltage;
    }

};

InternalVoltage internalVoltageSensor;
