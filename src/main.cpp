#include "SparkFunBME280.h"
//Library allows either I2C or SPI, so include both.
#include "Wire.h"
#include "SPI.h"
#include "Arduino.h"
#include <MIDI.h>
#define TUNE_MIN_TIME 2

BME280 capteur;
uint8_t oldStatePousser[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t oldStateTirer[] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t pousser[] = {49,57,56,61,65,48,52,55,60,64,55,59,62,67,71};
uint8_t tirer[]   = {51,53,58,63,69,47,50,53,57,59,54,57,60,64,66};
uint8_t pinButton[] = {A2,A1,A0,A3,A4,11,10,9,8,7,6,5,4,3,2};
uint8_t initCountSetup = 20;
float standardValuePressure = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(2,INPUT);
  digitalWrite(2,HIGH);
  pinMode(3,INPUT);
  digitalWrite(3,HIGH);
  pinMode(4,INPUT);
  digitalWrite(4,HIGH);
  pinMode(5,INPUT);
  digitalWrite(5,HIGH);
  pinMode(6,INPUT);
  digitalWrite(6,HIGH);
  pinMode(7,INPUT);
  digitalWrite(7,HIGH);
  pinMode(8,INPUT);
  digitalWrite(8,HIGH);
  pinMode(9,INPUT);
  digitalWrite(9,HIGH);
  pinMode(10,INPUT);
  digitalWrite(10,HIGH);
  pinMode(13,INPUT);
  digitalWrite(13,HIGH);
  pinMode(11,INPUT);
  digitalWrite(11,HIGH);
  pinMode(12,INPUT);
  digitalWrite(12,HIGH);
  pinMode(A0,INPUT);
  digitalWrite(A0,HIGH);
  pinMode(A1,INPUT);
  digitalWrite(A1,HIGH);
  pinMode(A2,INPUT);
  digitalWrite(A2,HIGH);
  pinMode(A3,INPUT);
  digitalWrite(A3,HIGH);
  pinMode(A4,INPUT);
  digitalWrite(A4,HIGH);
  pinMode(A6,INPUT);
  digitalWrite(A6,HIGH);

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
  float sumPressureValueSetup = 0.0;
  for (size_t i = 0; i < initCountSetup; i++) {
    sumPressureValueSetup += capteur.readFloatPressure();
    delay(10);
  }
  standardValuePressure = sumPressureValueSetup / initCountSetup;


}
void note_test(uint8_t sens_soufflet, uint8_t index, uint8_t octave){
  uint8_t bouton = digitalRead(pinButton[index]);
  if(bouton == LOW){
    Serial.println("--------------------------------");
    Serial.print("");
    if(sens_soufflet == 1){
      Serial.print("push :");
      Serial.print(pousser[index]);

    }
    else{
      Serial.print("pull :");
      Serial.print(tirer[index]);
    }
  }

}
void note(uint8_t sens_soufflet, uint8_t index, uint8_t octave){//, uint8_t oldStatePousser, uint8_t oldStateTirer
  uint8_t velocity = 100;//velocity of MIDI notes, must be between 0 and 127
  uint8_t bouton = digitalRead(pinButton[index]);
  uint8_t noteA = pousser[index];
  uint8_t noteB = tirer[index];

  if(oldStatePousser[index] > 1) { //Tune started too recently to be changed
    oldStatePousser[index]--;
  }
  else if(oldStateTirer[index] > 1) { //Tune started too recently to be changed
    oldStateTirer[index]--;
  } else {

    //higher velocity usually makes MIDI instruments louder
    if ( bouton == LOW ) {
      if(sens_soufflet == LOW ){
        // on pousse sur le bouton et sur le soufflet
        if(oldStatePousser[index] == 0){
          MIDI.sendNoteOn(noteA + octave ,velocity,1);
          oldStatePousser[index] = TUNE_MIN_TIME;
          if( oldStateTirer[index] == 1){
            MIDI.sendNoteOff(noteB + octave ,0,1);
            oldStateTirer[index] = 0;
          }
        }
      }
      else
      {// on tire sur le soufflet et on appuie sur le bouton
        if(oldStateTirer[index] == 0){
          MIDI.sendNoteOn(noteB + octave,velocity,1);
          oldStateTirer[index] = TUNE_MIN_TIME;
          if(oldStatePousser[index] == 1){
            MIDI.sendNoteOff(noteA + octave,0,1);
            oldStatePousser[index] = 0;
          }
        }
      }
    }
    else
    {
      if(oldStatePousser[index] == 1){
        MIDI.sendNoteOff(noteA + octave,0,1);
        oldStatePousser[index] = 0;
      }if( oldStateTirer[index] == 1){
        // on appuie pas sur le bouton ma
        MIDI.sendNoteOff( noteB + octave,0,1);
        oldStateTirer[index] = 0;
      }
    }
  }
}

void loop() {
  float pressure = capteur.readFloatPressure();
  int pousserTirer = 0;
  if(pressure > standardValuePressure){
    pousserTirer = 1;
  }else{
    pousserTirer = 0;
  }
  for (uint8_t i=0; i < 15; i++){
    note_test(pousserTirer,i,2*12);
  }
}
