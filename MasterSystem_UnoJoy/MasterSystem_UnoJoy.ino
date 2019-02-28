/*************************************
  Master System Serial Interface
  David Martinez
  6/15/2013
  ************************************
  For use with Sega Master System controllers.
     _____________________
     \(5) (4) (3) (2) (1)/
      \ (9) (8) (7) (6) /
      
  Atari Joystick Pinout
  =============================
  Pin  Arduino pin  Description
  ===  ===========  ===========
  1    3            Up
  2    4            Down
  3    5            Left
  4    6            Right
  5    
  6    7            Button 1
  7                 Select?
  8    GND          Ground
  9    8            Button 2
*/

#include <UnoJoy.h>

dataForController_t controller;

void setup()
{
  /* Pins 3-8 */
  for(byte i = 3; i <= 8; i++)
  {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH); 
  }

  setupUnoJoy();
  controller = getBlankDataForController();
}

void loop()
{
  controller.dpadUpOn    = bitRead(PIND, 3);
  controller.dpadDownOn  = bitRead(PIND, 4);
  controller.dpadLeftOn  = bitRead(PIND, 5);
  controller.dpadRightOn = bitRead(PIND, 6);
  controller.crossOn     = bitRead(PIND, 7);
  controller.circleOn    = bitRead(PIND, 8);
  
  setControllerData(controller);
}
