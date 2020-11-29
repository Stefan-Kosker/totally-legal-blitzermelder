void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogFuelValue = 0;
  analogReference(DEFAULT);
  analogFuelValue = analogRead(A2);
  analogFuelValue = analogRead(A2);
  analogFuelValue = analogRead(A2);
  double referenceResistance = 47;
  double referenceVoltage = 5.0;
  double fuelVoltage = ((double)analogFuelValue / 1023.0) * referenceVoltage;
  double fuelResistance = (fuelVoltage * referenceResistance) / (referenceVoltage - fuelVoltage);
  Serial.print(millis());
  Serial.print(";");
  Serial.print(fuelResistance);
  Serial.println("");
}
