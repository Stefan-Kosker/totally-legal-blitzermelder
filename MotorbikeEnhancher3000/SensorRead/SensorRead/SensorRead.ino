int analogReferenceValue;
double referenceVoltage;
double referenceResistanceR1 = 1000;
double referenceResistanceR2 = 4700;

void setup() {
 Serial.begin(9600);
}

void loop() {
  analogReference(INTERNAL1V1);
  analogReferenceValue = analogRead(A0);
  analogReferenceValue = analogRead(A0);
  analogReferenceValue = analogRead(A0);
  referenceVoltage = double(analogReferenceValue) / 1023.0 * 1.1;
  referenceVoltage = referenceVoltage * (referenceResistanceR1 + referenceResistanceR2) / referenceResistanceR1;
  Serial.println(referenceVoltage);
}
