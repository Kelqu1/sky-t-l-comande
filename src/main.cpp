#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <ESP32Servo.h>

const uint16_t RECV_PIN = 21; // Broche pour le récepteur IR
IRrecv irrecv(RECV_PIN);
decode_results results;

// Déclaration des codes infrarouges
uint32_t Tableau[] = {
    0xE318261B, 0x511DBB, 0xEE886D7F, 0x52A3D41F, 0xD7E84B1B, 0x20FE4DBB, 0xF076C13B,
    0xA3C8EDDB, 0xE5CFBD7F, 0xC101E57B, 0xFF9867, 0xFFB04F, 0x9716BE3F, 0x3D9AE3F7,
    0x6182021B, 0x8C22657B, 0x488F3CBB, 0x449E79F, 0x32C6FDF7, 0x1BC0157B, 0x3EC3FC1B,
    0xFFFFFFFF,
};

// Initialisation des servomoteurs
Servo Servo_inclinaison; // Inclinaison
Servo Servo_dir;         // Direction
const int servo_incl_Pin = 32; // Broche GPIO pour le servo d'inclinaison
const int servo_dir_Pin = 33;  // Broche GPIO pour le servo directionnel

void handleIRSignal(uint32_t code) {
    if (code == Tableau[13]) { // Touche 2
        Serial.println("Touche 2 appuyée : Servo inclinaison tourne de 0° à 180°");
        for (int angle = 0; angle <= 180; angle++) {
            Servo_inclinaison.write(angle);
            delay(15);
        }
    } else if (code == Tableau[15]) { // Touche 4
        Serial.println("Touche 4 appuyée : Servo inclinaison tourne de 0° à 180°");
        for (int angle = 0; angle <= 180; angle++) {
            Servo_dir.write(angle);
            delay(15);
        }
    } else if (code == Tableau[17]) { // Touche 2
        Serial.println("Touche 6 appuyée : Servo directionnel tourne de 180° à 0°");
        for (int angle = 180; angle >= 0; angle--) {
            Servo_dir.write(angle);
            delay(15);
        }
    } else if (code == Tableau[19]) { // Touche 2
        Serial.println("Touche 8 appuyée : Servo directionnel tourne de 180° à 0°");
        for (int angle = 180; angle >= 0; angle--) {
            Servo_inclinaison.write(angle);
            delay(15);
        }
    } else {
        Serial.println("Code non mappé ou inutilisé.");
    }
}

void setup() {
    Serial.begin(115200);
    irrecv.enableIRIn();  // Démarrage du récepteur IR
    Serial.println("Récepteur IR prêt");

    // Initialisation des servomoteurs
    Servo_inclinaison.attach(servo_incl_Pin);
    Servo_dir.attach(servo_dir_Pin);
    Serial.println("Servomoteurs prêts !");
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.println("Signal reçu !");
        handleIRSignal(results.value); // Gestion des actions selon le signal IR
        irrecv.resume();  // Reprendre la réception pour le prochain signal
    }
}
