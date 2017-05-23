/**
 * Concertina Midi project
 * The
 */
#include "Arduino.h"
#include <MIDI.h>
#define TUNE_MIN_TIME 2


// main gauche
 //uint8_t pousser[] = {43, 47, 50, 55, 59,  36, 40, 43, 48, 52, 37, 45, 44, 49, 53 };
 //uint8_t tirer[]   = {42, 45, 48, 52, 54,  35, 38, 41, 45, 47, 39, 43, 46, 51, 57 };
 //uint8_t pinButton[] = {A0, A1, A3, A4, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9};

//main droite


// left hand
// uint8_t pinButton[] = {A2,A1,A0,A4,12,11,10,9,8,7,6,5,4,3,2};
// uint8_t pousser[] =   {28,33,37,45,44,24,31,36,40,43,35,38,43,47,50};
// uint8_t tirer[] = {29,34,39,43,46,31,35,38,41,45,38,42,45,48,52};
// int pin_joystick_X = A6;
// int pin_joystick_Y = A7;
//right hand
uint8_t pinButton[] = {A2,A1,A0,A3,A4,11,10,9,8,7,6,5,4,3,2};
uint8_t pousser[] = {49,57,56,61,65,48,52,55,60,64,55,59,62,67,71};
uint8_t tirer[]   = {51,53,58,63,69,47,50,53,57,59,54,57,60,64,66};
int pousseTirerPin = A6;

uint8_t oldStatePousser[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t oldStateTirer[] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

MIDI_CREATE_DEFAULT_INSTANCE();


void setup()
{
  // Configuration de la broche 12 en tant qu'entree numerique.
  MIDI.begin(1);
  Serial.begin(115200);

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

int pousserTirer;
void loop()
{
  pousserTirer = 1;
  //velocity of MIDI notes, must be between 0 and 127
  //higher velocity usually makes MIDI instruments louder
  for (uint8_t i=0; i < 15; i++){
    note(pousserTirer,i,2*12);
  } // fin de la boucle for
}
