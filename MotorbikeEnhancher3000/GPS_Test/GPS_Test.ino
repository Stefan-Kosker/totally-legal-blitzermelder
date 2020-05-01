#include <TinyGPS++.h>
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}
void loop() {
  while (Serial1.available() > 0) {
    if (gps.encode(Serial1.read())) {
      Serial.print("Valid= ");
      Serial.print(gps.location.isValid());
      Serial.print(" Latitude= ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= ");
      Serial.println(gps.location.lng(), 6);
      Serial.print("Time= ");
      Serial.println(String(gps.time.hour() + 2) + ':' + String(gps.time.minute()) + ':' + String(gps.time.second()));
      Serial.print(" Speed= ");
      Serial.println(gps.speed.kmph());
      Serial.print(" Satellites ");
      Serial.println(gps.satellites.value());
    }
  }
}
