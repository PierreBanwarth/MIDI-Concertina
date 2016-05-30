/**
 * Concertina Midi project
 * The
 */
#include "Arduino.h"
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  MIDI.begin(1);
  Serial.begin(115200);
  
  // Hairlesse serial baudrate Set 
  // now we need to setup each input Pins
  
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
  pinMode(A5,INPUT);
  digitalWrite(A5,HIGH);
  //  Set MIDI baud rate:

}
// need to read if a button was ever pressed or not 
uint8_t oldStatePousser[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t oldStateTirer[] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void note(uint8_t bouton, uint8_t sens_soufflet, uint8_t noteA, uint8_t noteB, uint8_t index, uint8_t octave){//, uint8_t oldStatePousser, uint8_t oldStateTirer
  uint8_t velocity = 100;
  //velocity of MIDI notes, must be between 0 and 127
 // maybe i need to change the velocity value.
 //higher velocity usually makes MIDI instruments louder
  if ( bouton == LOW ) {
    if(sens_soufflet == LOW ){// we are pushing
      if(oldStatePousser[index] == 0){
        // the note was not pushed before
        // so play A note and save state
        MIDI.sendNoteOn(noteA + octave ,velocity,1);
        oldStatePousser[index] = 1;
        // this part is needed in case of air flow change stop the BoteA and edit old state
        if( oldStateTirer[index] == 1){
          MIDI.sendNoteOff(noteB + octave ,0,1);
          oldStateTirer[index] = 0;
        }
      }
    }
    else
    {// we pull
      if(oldStateTirer[index] == 0){
        // and the note was not pulled before
        // so we play noteB and save state.
        MIDI.sendNoteOn(noteB + octave,velocity,1);
        oldStateTirer[index] = 1;
        //This part is need in case of air flow change to stop the old NoteA and edit old state
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
      // So we cut off the note and we set the old position to off
      MIDI.sendNoteOff(noteA + octave,0,1);
      oldStatePousser[index] = 0;
    }if( oldStateTirer[index] == 1){
      // So we cut off the note and we set the old position to off
      MIDI.sendNoteOff( noteB + octave,0,1);
      oldStateTirer[index] = 0;
    }
  }
}
// Right hand note config
//
// {23,26,31,25,38,12,19,24,28,31,16,21,25,33,32}
// {26,30,33,36,40,19,23,26,29,33,17,22,27,31,34}
//
//  Left hand note config
//
// {43, 47, 50, 55, 59,  36, 40, 43, 48, 52, 37, 45, 44, 49, 53 }
// {42, 45, 48, 52, 54,  35, 38, 41, 45, 47, 39, 43, 46, 51, 57 }
void loop()
{
  int  etatButton[]= {digitalRead(2),digitalRead(3), digitalRead(4),digitalRead(5),digitalRead(6), digitalRead(7),digitalRead(8), digitalRead(9), digitalRead(10), digitalRead(11), digitalRead(12), digitalRead(A0), digitalRead(A1), digitalRead(A2), digitalRead(A3)};
  //int etatButton[]= {digitalRead(A0), digitalRead(A1), digitalRead(A2),digitalRead(A3), digitalRead(A4),digitalRead(12),digitalRead(13), digitalRead(2),digitalRead(3), digitalRead(4), digitalRead(5), digitalRead(6), digitalRead(7), digitalRead(8), digitalRead(9)};
  
  uint8_t pousser[] ={43, 47, 50, 55, 59,  36, 40, 43, 48, 52, 37, 45, 44, 49, 53 };
  uint8_t tirer[]   = {42, 45, 48, 52, 54,  35, 38, 41, 45, 47, 39, 43, 46, 51, 57 };
  uint8_t poussertirer = digitalRead(A4);
  //velocity of MIDI notes, must be between 0 and 127
  //higher velocity usually makes MIDI instruments louder
  for (uint8_t i=0; i < 15; i++){
    note( etatButton[i],poussertirer, pousser[i], tirer[i],i,2*12);//,oldStatePousser[i],oldStateTirer[i]
  } // fin de la boucle for
}
