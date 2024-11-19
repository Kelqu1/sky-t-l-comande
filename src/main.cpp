#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t RECV_PIN = 21; // Remplacez par votre numéro de broche
IRrecv irrecv(RECV_PIN);
decode_results results;

// Déclaration des codes infrarouges
uint32_t Tableau[] = {
    0xE318261B, 0x511DBB, 0xEE886D7F, 0x52A3D41F, 0xD7E84B1B, 0x20FE4DBB, 0xF076C13B,
    0xA3C8EDDB, 0xE5CFBD7F, 0xC101E57B, 0xFF9867, 0xFFB04F, 0x9716BE3F, 0x3D9AE3F7,
    0x6182021B, 0x8C22657B, 0x488F3CBB, 0x449E79F, 0x32C6FDF7, 0x1BC0157B, 0x3EC3FC1B
};

void setup() {
    Serial.begin(115200);
    irrecv.enableIRIn();  // Démarrer le récepteur IR
    Serial.println("Récepteur IR prêt");
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.println("Signal reçu !");
        // Vérification des codes
        if (results.value == Tableau[0]) {
            Serial.println("Touche CH- appuie ");
        } else if (results.value == Tableau[1]) {
            Serial.println("Touche CH appuie");
        } else if (results.value == Tableau[2]) {
            Serial.println("Touche CH+ appuie");
        } else if (results.value == Tableau[3]) {
            Serial.println("Touche |<< appuie");
        } else if (results.value == Tableau[4]) {
            Serial.println("Touche >>| appuie");
        } else if (results.value == Tableau[5]) {
            Serial.println("Touche >|| appuie");
        } else if (results.value == Tableau[6]) {
            Serial.println("Touche - appuie");
        } else if (results.value == Tableau[7]) {
            Serial.println("Touche + appuie");
        } else if (results.value == Tableau[8]) {
            Serial.println("Touche EQ appuie");
        } else if (results.value == Tableau[9]) {
            Serial.println("Touche 0 appuie");
        } else if (results.value == Tableau[10]) {
            Serial.println("Touche 100+ appuie");
        } else if (results.value == Tableau[11]) {
            Serial.println("Touche 200+ appuie");
        } else if (results.value == Tableau[12]) {
            Serial.println("Touche 1 appuie");
        } else if (results.value == Tableau[13]) {
            Serial.println("Touche 2 appuie");
        } else if (results.value == Tableau[14]) {
            Serial.println("Touche 3 appuie");
        } else if (results.value == Tableau[15]) {
            Serial.println("Touche 4 appuie");
        } else if (results.value == Tableau[16]) {
            Serial.println("Touche 5 appuie");
        } else if (results.value == Tableau[17]) {
            Serial.println("Touche 6 appuie");
        } else if (results.value == Tableau[18]) {
            Serial.println("Touche 7 appuie");
        } else if (results.value == Tableau[19]) {
            Serial.println("Touche 8 appuie");
        } else if (results.value == Tableau[20]) {
            Serial.println("Touche 9 appuie");
        }
        irrecv.resume();  // Reprendre la réception pour le prochain signal
    }
}