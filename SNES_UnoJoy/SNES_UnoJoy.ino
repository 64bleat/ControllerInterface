/***********************************************************
  SNES Controller USB Controller Interface
   David Martinez
   6/14/2013
************************************************************
  INFO http://www.gamefaqs.com/snes/916396-snes/faqs/5395
 
   ----------------------------- ---------------------
  |                             |                      \
  | (1)     (2)     (3)     (4) |   (5)     (6)     (7) )
  |                             |                      /
   ----------------------------- ---------------------


  Pinout
  ==================================
  Pin     Description    Arduino Pin
  ===     ===========    ===========
  1       +5v            5v
  2       Data clock     3   
  3       Data latch     2  
  4       Serial out     4  
  5       ?                   
  6       ?                    
  7       Ground         GND  
  
  
  Button Cycles
  =======================
  Bit     Button Reported
  ===     ===============
  1       B
  2       Y
  3       Select
  4       Start
  5       Up on joypad
  6       Down on joypad
  7       Left on joypad
  8       Right on joypad
  9       A
  10      X
  11      L
  12      R
  13      none (always high)
  14      none (always high)
  15      none (always high)
  16      none (always high)
*/

#include <UnoJoy.h>

const int latch = 2;
const int clock = 3;
const int data  = 4;

unsigned int output;

dataForController_t controller;

void setup() 
{
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, INPUT);
  
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
  for(byte i = 0; i < 12; i++) 
  {
    bitWrite(PORTD, clock, LOW);
    delayMicroseconds(6);
    output |= (int)!bitRead(PIND, data) << i;
    bitWrite(PORTD, clock, HIGH);
    delayMicroseconds(6);
  }
  
  /* Send controller data */
  controller.crossOn     = output & 1 ? 1 : 0;
  controller.squareOn    = output & 2 ? 1 : 0;
  controller.selectOn    = output & 4 ? 1 : 0;
  controller.startOn     = output & 8 ? 1 : 0;
  controller.dpadUpOn    = output & 16 ? 1 : 0;
  controller.dpadDownOn  = output & 32 ? 1 : 0;
  controller.dpadLeftOn  = output & 64 ? 1 : 0;
  controller.dpadRightOn = output & 128 ? 1 : 0;
  controller.circleOn    = output & 256 ? 1 : 0;
  controller.triangleOn  = output & 512 ? 1 : 0;
  controller.l1On        = output & 1024 ? 1 : 0;
  controller.r1On        = output & 2048 ? 1 : 0;
  
  setControllerData(controller);
}
