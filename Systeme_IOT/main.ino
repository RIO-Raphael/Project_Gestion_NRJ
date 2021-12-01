#include <SPI.h>
#include <RF24.h>
#include "Temperature.h"
#include "LowPower.h"

#define pinCE           7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN          8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel          "PP123"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre
#define TIME_SLEEP_MS   5000  
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
  // Triggers a TIME_SLEEP_MS ms sleep (the device will be woken up only by the registered wakeup sources and by internal RTC)
  // The power consumption of the chip will drop consistently
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
}

void loop() {
  val = TEMP_mes();
  Serial.println(val);
  radio.write(&val, sizeof(val));     // Envoi de notre message
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
}