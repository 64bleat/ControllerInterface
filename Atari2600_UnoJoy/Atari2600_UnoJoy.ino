/*************************************
  Atari 2600 Serial Interface
  David Martinez
  6/14/2013
  ************************************
  For use with Atari2600 or C64 Joysticks
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
  6    7            Button
  7    
  8    GND          Ground
  9
*/

#include <UnoJoy.h>

dataForController_t controller;

void setup()
{
  /* Pins 3-7 */
  for(byte i = 3; i <= 7; i++)
  {
    pinMode(i, INPUT);
    bitWrite(PORTD, i, HIGH);
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
  
  setControllerData(controller);
}
