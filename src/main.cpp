#include "SparkFunBME280.h"
//Library allows either I2C or SPI, so include both.
#include "Wire.h"
#include "SPI.h"

BME280 capteur;
int nbCaptureInit = 10;
float pressionBasicValue=0;

uint8_t pinButton[] = {2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3,A6,A7};
                     //2,3,4,5,6,7,8,9,10,11,12,14,15,16,17
int8_t buttonTabSize = 18;
uint8_t pousser[] = {49,57,56,61,65,48,52,55,60,64,55,59,62,67,71};
uint8_t tirer[]   = {51,53,58,63,69,47,50,53,57,59,54,57,60,64,66};

uint8_t oldStatePousser[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t oldStateTirer[] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//MIDI_CREATE_DEFAULT_INSTANCE();


void setup() {
  for (size_t i = 0; i < buttonTabSize; i++) {
    pinMode(pinButton[i],INPUT);
    digitalWrite(pinButton[i],HIGH);
  }
  Serial.begin(9600);
  while (!Serial) {
    // Attente de l'ouverture du port série pour Arduino LEONARDO
  }
  //configuration du capteur
  capteur.settings.commInterface = I2C_MODE;
  capteur.settings.I2CAddress = 0x76;
  capteur.settings.runMode = 3;
  capteur.settings.tStandby = 0;
  capteur.settings.filter = 0;
  capteur.settings.tempOverSample = 1 ;
  capteur.settings.pressOverSample = 1;
  capteur.settings.humidOverSample = 1;

  Serial.println("Starting BME280... ");
  delay(10);  // attente de la mise en route du capteur. 2 ms minimum
  // chargement de la configuration du capteur
  capteur.begin();
  for (size_t i = 0; i < nbCaptureInit; i++) {
    /* code */
    pressionBasicValue += capteur.readFloatPressure();
    delay(20);
  }
  pressionBasicValue = pressionBasicValue/nbCaptureInit;
}

void loop() {
  float value = capteur.readFloatPressure();
  float differencial = value-pressionBasicValue;
  // boucle de lecture des touches
  for (size_t i = 0; i < buttonTabSize; i++) {
    uint8_t bouton = digitalRead(pinButton[i]);
    if(bouton == LOW){
      Serial.println("====================================================================");
      Serial.print("-> ");
      Serial.print(pinButton[i]);
      Serial.println("");
      if(differencial < -10.0){
        Serial.println("-> Tirer\n");
      }else if(differencial > 10.0){
        Serial.println("-> Pousser\n");
      }else{
        Serial.print("-> ");
        Serial.print(differencial, 3);
        Serial.println("");
      }
    }


  }


}
