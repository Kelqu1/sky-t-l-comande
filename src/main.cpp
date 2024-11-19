#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t RECV_PIN = 21; // Remplacez par votre numéro de broche

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
    Serial.begin(115200);
    irrecv.enableIRIn();  // Démarrer le récepteur IR
    Serial.println("Récepteur IR prêt");
    int Tableau[0xE318261B,0x511DBB,0xEE886D7F,0x52A3D41F,0xD7E84B1B,0x20FE4DBB,0xF076C13B,0xA3C8EDDB,0xE5CFBD7F,0xC101E57B,0xFF9867,0xFFB04F,0x9716BE3F,0x3D9AE3F7,0x6182021B,0x8C22657B,0x488F3CBB,0x449E79F,0x32C6FDF7,0x1BC0157B,0x3EC3FC1B];//bouton CH-1 =1 et CH = en hexa
}//                 CH-        CH       CH+       |<<        >>|          >||       -           +          EQ          0      +100     +200        1          2          3         4          5          6          7          8

void loop() {
    if (irrecv.decode(&results)) {
        Serial.println("Signal reçu !");
        // Affiche les données en format décimal et hexadécimal
        Serial.printf("Code décimal : %ld\n", results.value);
        Serial.printf("Code hexadécimal : 0x%X\n", results.value);
        irrecv.resume();  // Reprendre la réception pour le prochain signal
    }
}
