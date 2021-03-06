/***********************************************************
  NES Controller Serial Interface
   David Martinez
   6/14/2013
************************************************************
  INFO    
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
  2       ?  
  3       ? 
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

const int latch = 2;
const int clock = 3;
const int data  = 4;

byte output;

void setup() 
{
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, INPUT);
  
  Serial.begin(115200);
}

void loop() 
{
  /* Prime the controller for clock cycles.*/
  digitalWrite(clock, HIGH);
  digitalWrite(latch, HIGH);
  delayMicroseconds(12);
  digitalWrite(latch, LOW);
  
  /* send button states as one byte */
  output = 0;
  for(byte i = 0; i < 8; i++) 
  {
    digitalWrite(clock, LOW);
    delayMicroseconds(6);
    output += digitalRead(data) << i;
    digitalWrite(clock, HIGH);
    delayMicroseconds(6);
  }
  Serial.write(output);
}
