#include "Arduino.h"
#include <MIDI.h>
#include "SparkFunBME280.h"
//
// MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);
// BME280 capteur;
//
// BME280 initPressureSensor(){
//   capteur.settings.commInterface = I2C_MODE;
//   capteur.settings.I2CAddress = 0x76;
//   capteur.settings.runMode = 3;
//   capteur.settings.tStandby = 0;
//   capteur.settings.filter = 0;
//   capteur.settings.tempOverSample = 1 ;
//   capteur.settings.pressOverSample = 1;
//   capteur.settings.humidOverSample = 1;
//   return capteur;
// }
//
// float computePressure(int pressureCount){
//   float pressure = 0;
//   for (size_t i = 0; i < pressureCount; i++) {
//     pressure += capteur.readFloatPressure();
//   }
//   return pressure / pressureCount;
// }
//
// int velocity_computation(float Pressure, float Calib_Pressure, float velocity, float curr_velocity) {
//   size_t pressureCount = 4;
//   float Pressure_Delta;
//   // make a test to avoid mistakes and jumps in pressure;
//   Pressure_Delta = abs(Pressure - Calib_Pressure);
//   Pressure_Delta = int((log(float(Pressure_Delta) / 80) + 2) * 19)+40;
//   // TUTO Pressure_Delta = int(0.000014*pow(Pressure_Delta-162,3) + 0.01*Pressure_Delta)+99;
//   //NIELS  int((log(float(p_offset) / 55) + 6) * 27) ;
//   if (Pressure_Delta > 127){
//     Pressure_Delta = 127;
//   }
//   if(Pressure_Delta < 20){
//     Pressure_Delta = 20;
//   }
//   // setting up minimal pressure to start a sound
//   // setting controller to zero once it got to zero
//   if (Pressure_Delta < 7){
//     curr_velocity = 0;
//   }
//
//   else if (Pressure_Delta >= 7) {
//     velocity = Pressure_Delta;
//     curr_velocity = velocity;
//   }
//   return curr_velocity;
// }
