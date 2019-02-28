/***********************************************************
  NES Controller USB Controller Interface
   David Martinez
   6/14/2013
************************************************************
     
      -----
    /   (7)|
  /        |
  |(1)  (6)|
  |        |
  |(2)  (5)|
  |        |
  |(3)  (4)|
   --------


  Pinout
  ==================================
  Pin     Description    Arduino Pin
  ===     ===========    ===========
  1       +5v            5v
  2       -  
  3       - 
  4       Serial out     4  
  5       Latch          2                  
  6       Clock          3                    
  7       Ground         GND  
  
  
  Button Cycles
  =======================
  Bit     Button Reported
  ===     ===============
  1       A
  2       B
  3       Select
  4       Start
  5       Up on joypad
  6       Down on joypad
  7       Left on joypad
  8       Right on joypad
*/

#include <UnoJoy.h>

const byte latch = 2;
const byte clock = 3;
const byte data  = 4;

byte output;

dataForController_t controller;

void setup() 
{
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data,  INPUT);
  
  setupUnoJoy();
  controller = getBlankDataForController();
}

void loop()
{
  /* Prime the controller for clock cycles.*/
  bitWrite(PORTD, clock, HIGH);
  bitWrite(PORTD, latch, HIGH);
  delayMicroseconds(12);
  bitWrite(PORTD, latch, LOW);
  
  /* Form button status into byte */
  output = 0;
  for(byte i = 0; i < 8; i++) 
  {
    bitWrite(PORTD, clock, LOW);
    delayMicroseconds(6);
    output |= !bitRead(PIND, data) << i;
    bitWrite(PORTD, clock, HIGH);
    delayMicroseconds(6);
  }
  
  /* Send controller data */
  controller.circleOn    = output & 1 ? 1 : 0;
  controller.crossOn     = output & 2 ? 1 : 0;
  controller.selectOn    = output & 4 ? 1 : 0;
  controller.startOn     = output & 8 ? 1 : 0;
  controller.dpadUpOn    = output & 16 ? 1 : 0;
  controller.dpadDownOn  = output & 32 ? 1 : 0;
  controller.dpadLeftOn  = output & 64 ? 1 : 0;
  controller.dpadRightOn = output & 128 ? 1 : 0;
  
  setControllerData(controller);
}
