#include <SPI.h>
#include <RF24.h>
#include "Temperature.h"

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PP123"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;               // Mise au format "byte array" du nom du tunnel
const char message[] = "Coucou";     // Message à transmettre à l'autre NRF24 (32 caractères maxi, avec cette librairie)
int val = 0;

void setup() {
  radio.begin();                      // Initialisation du module NRF24
  radio.openWritingPipe(adresse);     // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);      // Sélection d'un niveau "MINIMAL" pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.stopListening(); 
  TEMP_setup();                       // Arrêt de l'écoute du NRF24 (signifiant qu'on va émettre, et non recevoir, ici)
}


void loop() {
  val = TEMP_mes();
  Serial.println(val);
  radio.write(&val, sizeof(val));     // Envoi de notre message
  delay(1000);                        // … toutes les secondes !
}