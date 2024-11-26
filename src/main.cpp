#include <ESP32Servo.h>

Servo myServo; // Crée un objet Servo

const int servoPin = 33; // Broche GPIO pour le contrôle du servo
int angle = 0;           // Angle initial du servomoteur

void setup() {
  Serial.begin(115200);

  // Attache le servomoteur à la broche servoPin
  myServo.attach(servoPin);
  Serial.println("Servometeur pret!");
}

void loop() {
  // Balayer l'angle de 0 à 180 degrés
  for (angle = 0; angle <= 180; angle++) {
    myServo.write(angle);        // Déplace le servo à l'angle défini
    delay(15);                   // Attendez un peu pour permettre au servo de bouger
  }
  // Balayer l'angle de 180 à 0 degrés
  for (angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}
