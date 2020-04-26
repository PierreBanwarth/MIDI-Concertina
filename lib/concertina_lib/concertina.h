#ifndef __CONCERTINA_H__
#define __CONCERTINA_H__
#include "Arduino.h"
#include <MIDI.h>


enum
{
  //DEFINING MIDI notes
  Cn1 = 0,
  Cs1 = 1,
  Dn1 = 2,
  Ds1 = 3,
  En1 = 4,
  Fn1 = 5,
  Fs1 = 6,
  Gn1 = 7,
  Gs1 = 8,
  An1 = 9,
  As1 = 10,
  Bn1 = 11,

  Cn2 = 0 + 12,
  Cs2 = 1 + 12,
  Dn2 = 2 + 12,
  Ds2 = 3 + 12,
  En2 = 4 + 12,
  Fn2 = 5 + 12,
  Fs2 = 6 + 12,
  Gn2 = 7 + 12,
  Gs2 = 8 + 12,
  An2 = 9 + 12,
  As2 = 10 + 12,
  Bn2 = 11 + 12,

  Cn3 = 0 + 24,
  Cs3 = 1 + 24,
  Dn3 = 2 + 24,
  Ds3 = 3 + 24,
  En3 = 4 + 24,
  Fn3 = 5 + 24,
  Fs3 = 6 + 24,
  Gn3 = 7 + 24,
  Gs3 = 8 + 24,
  An3 = 9 + 24,
  As3 = 10 + 24,
  Bn3 = 11 + 24,

  Cn4 = 0 + 36,
  Cs4 = 1 + 36,
  Dn4 = 2 + 36,
  Ds4 = 3 + 36,
  En4 = 4 + 36,
  Fn4 = 5 + 36,
  Fs4 = 6 + 36,
  Gn4 = 7 + 36,
  Gs4 = 8 + 36,
  An4 = 9 + 36,
  As4 = 10 + 36,
  Bn4 = 11 + 36,
  
  Eb1 = As1,
  Bb1 = Ds1,
  Eb2 = As2,
  Bb2 = Ds2,
  Eb3 = As3,
  Bb3 = Ds3,
};



#endif
