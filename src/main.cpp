#include "SparkFunBME280.h"
 //Library allows either I2C or SPI, so include both.
#include "Wire.h"
#include "SPI.h"
#include "Arduino.h"
#include <MIDI.h>
#include "concertina.h"

#define BUTTON_PRESSED 1
#define BUTTON_RELEASED 0
#define DEBUG false

BME280 capteur;
//DEFINING MIDI notes

uint8_t oldStatePousser[] = {0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0};
uint8_t oldStateTirer[] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// main gauche
//                    2     3    4    5    6    7     8   9    10   11   12   14   15  16  17
uint8_t pousser[] = {Gn1, Fn1 , Bn1, As1, Dn2, Fn2, Bb2, Gn2, Eb2, An2, En3, An2, Cn3, 0, Fs2};
uint8_t tirer[] =   {Cn1, En1 , Gn1, An1, Cn2, En2, Cs2, An2, Gs2, Gn2, Dn3, Gn2, Bn2, 0, Dn2};
// Main droite
                  // 3  3   4    5    6    7     8   9    10   11   12   14   15  16  17
// uint8_t pousser[] = {0, 0, Bn2, Ds3, Dn3, Fn3, Ds3, Gn3, As3, An3, En3, An3, Cn4, 0, Fs3};
// uint8_t tirer[]   = {0, 0, Cn3, Cs3, En3, Gn3, Cs3, Gs3, Cs3, Cn3, Gn4, Bn3, Dn4, 0, Gn3};


// for both hands
uint8_t pinButton[] = {2,3,4,5,6,7,8,9,10,11,12,14,15,16,17};

uint8_t initCountSetup = 32;
uint8_t pressureLiveMesure = 4;
float Calib_Pressure = 0;
byte pressureLowLimit = 15;
int oldPressure;


//pressure variables
float Pressure;
int Pressure_Delta;

//timing variables
unsigned long initial_us = 0;
unsigned long final_us = 0;
int curr_velocity = 127;
int velocity = 127;
boolean velocity_active = false;

int prev_velocity = 127;

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
  Calib_Pressure = sumPressureValueSetup / initCountSetup;
  Calib_Pressure = Calib_Pressure;
  oldPressure = 0;

}

void test_curve(int pressure, int Pressure_Delta, int velocity){
  Serial.print(pressure);
  Serial.print(',');
  Serial.print(Pressure_Delta);
  Serial.print(',');
  Serial.println(velocity);
}

int velocity_jason() {
  Pressure = capteur.readFloatPressure();
  //not sure where these numbers come from...
  //the final divisor differs between pulling the bellows out (45) and pushing them in (40)
  if (Pressure <= Calib_Pressure){
    Pressure_Delta = int(float((pow((Calib_Pressure - Pressure),1.4)+280)/48));
  }
  else if (Pressure > Calib_Pressure){
    Pressure_Delta = int(float((pow((Pressure - Calib_Pressure),1.4)+280)/48));
  }
  if (Pressure_Delta > 127){
    Pressure_Delta = 127;
  }

  // setting up minimal pressure to start a sound
  // setting controller to zero once it got to zero
  if (Pressure_Delta < 7){
    curr_velocity = 0;
  }
  else if (Pressure_Delta >= 7) {
    velocity = Pressure_Delta;
    curr_velocity = velocity;
  }
  if(DEBUG){
    test_curve(Pressure, Pressure_Delta, curr_velocity);
  }
  return curr_velocity;
}

int velocity_dmitry(){
  int pressure_low_limit = 10;
  Pressure = capteur.readFloatPressure();
  Pressure_Delta = constrain(abs(Pressure - Calib_Pressure), pressure_low_limit, 127);

  // setting up minimal pressure to start a sound
  if (Pressure_Delta <= pressure_low_limit){
    // we have to get to send message controller to zero once it got to zero
    // maybe setting curr_velocity to 1 will solve the button press -> move problem
    curr_velocity = 1;
    velocity = 0;
  }
  else {
    //we assume the delta has been constrained between 10 and 127,
    //or else this function will not work.
    velocity = int((log(float(Pressure_Delta)/100.0)+4.8)/0.03814);
    velocity_active = true;
  }

  if ((velocity_active) && (curr_velocity != velocity)) {
    curr_velocity = velocity;
    velocity_active = false;
  }
  if(DEBUG){
    test_curve(Pressure, Pressure_Delta, velocity);
  }
  return curr_velocity;
}

int note(uint8_t sens_soufflet, uint8_t index, uint8_t octave, int velocity){//, uint8_t oldStatePousser, uint8_t oldStateTirer
  uint8_t newOctave = 12*octave;
  // velocity = 127;
  digitalWrite(pinButton[index], HIGH);
  uint8_t bouton = digitalRead(pinButton[index]);
  // digitalWrite(pinButton[index], LOW);
  uint8_t noteA = pousser[index];
  uint8_t noteB = tirer[index];

  if(pousser[index] != 0 || tirer[index] != 0){
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
          if(oldStatePousser[index] == BUTTON_RELEASED){
            MIDI.sendNoteOn(noteA + newOctave ,velocity,1);

            oldStatePousser[index] = BUTTON_PRESSED;
            if( oldStateTirer[index] == BUTTON_PRESSED){
              MIDI.sendNoteOff(noteB + newOctave ,0,1);
              oldStateTirer[index] = BUTTON_RELEASED;
            }
          }
        }
        else
        {// on tire sur le soufflet et on appuie sur le bouton
          if(oldStateTirer[index] == 0){
            MIDI.sendNoteOn(noteB + newOctave,velocity,1);
            oldStateTirer[index] = BUTTON_PRESSED;
            if(oldStatePousser[index] == BUTTON_PRESSED){
              MIDI.sendNoteOff(noteA + newOctave,0,1);
              oldStatePousser[index] = BUTTON_RELEASED;
            }
          }
        }
      }
      else
      {
        if(oldStatePousser[index] == BUTTON_PRESSED){
          MIDI.sendNoteOff(noteA + newOctave,0,1);
          oldStatePousser[index] = BUTTON_RELEASED;
        }if( oldStateTirer[index] == BUTTON_PRESSED){
          // on appuie pas sur le bouton ma
          MIDI.sendNoteOff( noteB + newOctave,0,1);
          oldStateTirer[index] = BUTTON_RELEASED;
        }
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
  int expression;

  // Moyenne de pression
  for (size_t i = 0; i < pressureLiveMesure; i++) {
    pressure += capteur.readFloatPressure();
  }
  pressure=pressure/pressureLiveMesure;
  // fin de la moyenne des pressions

  // expression = velocity_dmitry();

  expression = velocity_jason();

  oldPressure = pressure;


  int pousserTirer = 0;
  if(pressure > Calib_Pressure){
    pousserTirer = 1;
  }else{
    pousserTirer = 0;
  }
  uint8_t isButtonPressed = 0;
  for (uint8_t i=0; i < 15; i++){
    if(!DEBUG){
       isButtonPressed += note(pousserTirer,i,3, 127);
       // Only for one hand
       MIDI.sendControlChange(11,expression, 1);


    }
  }
  if(isButtonPressed == 0){
    Calib_Pressure = (Calib_Pressure * 99 + pressure)/100;
  }


}
