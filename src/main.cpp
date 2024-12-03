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
    static int angle_inclinaison = 0; // Position actuelle du servo inclinaison
    static int angle_direction = 0;  // Position actuelle du servo directionnel

    if (code == Tableau[13]) { // Touche 2 : inclinaison +15°
        if (angle_inclinaison <= 170) { // Empêche de dépasser 180°
            angle_inclinaison += 10;
            Servo_inclinaison.write(angle_inclinaison);
            Serial.print("Inclinaison augmentée à : ");
            Serial.println(angle_inclinaison);
        } else {
            Serial.println("Inclinaison déjà au maximum (180°).");
        }
    } else if (code == Tableau[15]) { // Touche 4 : direction +15°
        if (angle_direction <= 170) { // Empêche de dépasser 180°
            angle_direction += 10;
            Servo_dir.write(angle_direction);
            Serial.print("Direction augmentée à : ");
            Serial.println(angle_direction);
        } else {
            Serial.println("Direction déjà au maximum (180°).");
        }
    } else if (code == Tableau[17]) { // Touche 6 : direction -15°
        if (angle_direction >= 10) { // Empêche de descendre sous 0°
            angle_direction -= 10;
            Servo_dir.write(angle_direction);
            Serial.print("Direction diminuée à : ");
            Serial.println(angle_direction);
        } else {
            Serial.println("Direction déjà au minimum (0°).");
        }
    } else if (code == Tableau[19]) { // Touche 8 : inclinaison -15°
        if (angle_inclinaison >= 10) { // Empêche de descendre sous 0°
            angle_inclinaison -= 10;
            Servo_inclinaison.write(angle_inclinaison);
            Serial.print("Inclinaison diminuée à : ");
            Serial.println(angle_inclinaison);
        } else {
            Serial.println("Inclinaison déjà au minimum (0°).");
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
