#include "SparkFunBME280.h"
//Library allows either I2C or SPI, so include both.
#include "Wire.h"
#include "SPI.h"
#include "Arduino.h"
#include <MIDI.h>
#define TUNE_MIN_TIME 2
#define DEBUG false

BME280 capteur;
//DEFINING MIDI notes
uint8_t Cn1 = 0;
uint8_t Cs1 = 1;
uint8_t Dn1 = 2;
uint8_t Ds1 = 3;
uint8_t En1 = 4;
uint8_t Fn1 = 5;
uint8_t Fs1 = 6;
uint8_t Gn1 = 7;
uint8_t Gs1 = 8;
uint8_t An1 = 9;
uint8_t As1 = 10;
uint8_t Bn1 = 11;

uint8_t Cn2 = 0 + 12;
uint8_t Cs2 = 1 + 12;
uint8_t Dn2 = 2 + 12;
uint8_t Ds2 = 3 + 12;
uint8_t En2 = 4 + 12;
uint8_t Fn2 = 5 + 12;
uint8_t Fs2 = 6 + 12;
uint8_t Gs2 = 8 + 12;
uint8_t An2 = 9 + 12;
uint8_t Gn2 = 7 + 12;
uint8_t As2 = 10 + 12;
uint8_t Bn2 = 11 + 12;

uint8_t Cn3 = 0 + 24;
uint8_t Cs3 = 1 + 24;
uint8_t Dn3 = 2 + 24;
uint8_t Ds3 = 3 + 24;
uint8_t En3 = 4 + 24;
uint8_t Fn3 = 5 + 24;
uint8_t Fs3 = 6 + 24;
uint8_t Gs3 = 8 + 24;
uint8_t An3 = 9 + 24;
uint8_t Gn3 = 7 + 24;
uint8_t As3 = 10 + 24;
uint8_t Bn3 = 11 + 24;

uint8_t Eb1 = As1;
uint8_t Bb1 = Ds1;
uint8_t Eb2 = As2;
uint8_t Bb2 = Ds2;
uint8_t Eb3 = As3;
uint8_t Bb3 = Ds3;




uint8_t oldStatePousser[] = {0,0,0,0,0 ,0,0,0,0,0, 0,0,0,0,0};
uint8_t oldStateTirer[] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// main gauche
//                    2     3    4    5    6    7     8   9    10   11   12   14   15  16  17
// uint8_t pousser[] = {Gn1, Fn1 , Bn1, Bb1, Dn1, Fn1, Eb1, Gn1, Bb1, An1, En2, An1, Cn2, 0, Fs1};
// uint8_t tirer[] =   {Cn1, En1 , Gn1, An1, Cn1, En1, Cs1, An1, Gs1, Gn1, Dn2, Gn1, Bn1, 0, Dn1};
// Main droite
                  // 2  3   4    5    6    7     8   9    10   11   12   14   15  16  17
uint8_t pousser[] = {0, 0, Bn1, Cs2, Dn2, Fn2, Ds2, Gn2, As2, An2, En3, An2, Cn3, 0, Fs2};
uint8_t tirer[]   = {0, 0, Cn2, Ds2, En2, Gn2, Cs2, Gs2, Cs2, Cn2, Gn3, Bn2, Dn3, 0, Gn2};


// for both hands
uint8_t pinButton[] = {2,3,4,5,6,7,8,9,10,11,12,14,15,16,17};

uint8_t initCountSetup = 32;
uint8_t pressure_live_mesure = 4;
float standardValuePressure = 0;
byte pressure_low_limit = 1;



MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

void setup() {
  // Configuration de la broche 12 en tant qu'entree numerique.
  MIDI.begin(1);
  // normal use
  if(DEBUG){
     Serial.begin(9600);
  }else{
     Serial.begin(115200);
  }
  // for testing function
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
  pinMode(11,INPUT);
  digitalWrite(11,HIGH);
  pinMode(12,INPUT);
  digitalWrite(12,HIGH);
  pinMode(13,INPUT);
  digitalWrite(13,HIGH);
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

  pinMode(A5,INPUT);
  digitalWrite(A5,HIGH);
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
int note_test(uint8_t sens_soufflet, uint8_t index, uint8_t octave, uint8_t velocity){
  uint8_t bouton = digitalRead(pinButton[index]);
  Serial.println(velocity);
  return 0;

}
int note(uint8_t sens_soufflet, uint8_t index, uint8_t octave, int velocity){//, uint8_t oldStatePousser, uint8_t oldStateTirer
  uint8_t newOctave = 12*octave;
  // velocity = 127;
  digitalWrite(pinButton[index], HIGH);
  delayMicroseconds(300);
  uint8_t bouton = digitalRead(pinButton[index]);
  digitalWrite(pinButton[index], LOW);
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
          MIDI.sendNoteOn(noteA + newOctave ,velocity,1);

          oldStatePousser[index] = TUNE_MIN_TIME;
          if( oldStateTirer[index] == 1){
            MIDI.sendNoteOff(noteB + newOctave ,0,1);
            oldStateTirer[index] = 0;
          }
        }
      }
      else
      {// on tire sur le soufflet et on appuie sur le bouton
        if(oldStateTirer[index] == 0){
          MIDI.sendNoteOn(noteB + newOctave,velocity,1);
          oldStateTirer[index] = TUNE_MIN_TIME;
          if(oldStatePousser[index] == 1){
            MIDI.sendNoteOff(noteA + newOctave,0,1);
            oldStatePousser[index] = 0;
          }
        }
      }
    }
    else
    {
      if(oldStatePousser[index] == 1){
        MIDI.sendNoteOff(noteA + newOctave,0,1);
        oldStatePousser[index] = 0;
      }if( oldStateTirer[index] == 1){
        // on appuie pas sur le bouton ma
        MIDI.sendNoteOff( noteB + newOctave,0,1);
        oldStateTirer[index] = 0;
      }
    }
  }
  if ( bouton == LOW ) {
    return 1;
  }else{
    return 0;
  }
}

void loop() {
  float pressure=0;
  for (size_t i = 0; i < pressure_live_mesure; i++) {
    pressure += capteur.readFloatPressure();
  }
  pressure=pressure/pressure_live_mesure;


  float p_offset = abs(standardValuePressure - pressure);
  // todo faire la moyenne de 5 mesures de pression
  if(p_offset > pressure_low_limit){
    int volume = int((log(float(p_offset) / 100) + 2) * 23);
    int pousserTirer = 0;

    if(pressure > standardValuePressure){
      pousserTirer = 1;
    }else{
      pousserTirer = 0;
    }
    uint8_t isButtonPressed = 0;
    for (uint8_t i=0; i < 15; i++){
      if(DEBUG){
         note_test(pousserTirer,i,4, volume);
      }else{
         isButtonPressed += note(pousserTirer,i,4, volume);
      }
    }
    if(isButtonPressed == 0){
      standardValuePressure = (standardValuePressure * 99 + pressure)/100;
    }
    // MIDI.sendControlChange(7,volume, 1);
  }


}
