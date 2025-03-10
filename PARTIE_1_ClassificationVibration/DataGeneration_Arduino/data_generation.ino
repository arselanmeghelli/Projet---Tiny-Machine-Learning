#include <Arduino_LSM9DS1.h>

void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (!IMU.begin()) {
        Serial.println("Erreur : Impossible d'initialiser l'IMU !");
        while (1);
    }
    Serial.println("IMU prêt !");
}

void loop() {
    float x, y, z;

    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(x, y, z);
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(",");
        Serial.print(z);
        Serial.print(",");
        Serial.println("1");  // Changer l'étiquette selon la vibration
    }

    delay(100);
}
