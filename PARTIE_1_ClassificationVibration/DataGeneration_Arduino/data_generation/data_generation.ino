#include <Arduino_LSM9DS1.h>

void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (!IMU.begin()) {
        Serial.println("Erreur!");
        while (1);
    }
    Serial.println("IMU prêt !");
}

void loop() {
    float ax, ay, az;  
    float gx, gy, gz;  

    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
        IMU.readAcceleration(ax, ay, az);
        IMU.readGyroscope(gx, gy, gz);

        Serial.print(ax); Serial.print(",");
        Serial.print(ay); Serial.print(",");
        Serial.print(az); Serial.print(",");
        Serial.print(gx); Serial.print(",");
        Serial.print(gy); Serial.print(",");
        Serial.print(gz); Serial.print(",");
        Serial.println("0");  // Label

        delay(100);
    }
}
