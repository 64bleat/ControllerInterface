/***********************************************************
  SNES Controller Serial Interface
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
  digitalWrite(latch, LOW);
  digitalWrite(clock, HIGH);
  digitalWrite(latch, HIGH);
  delayMicroseconds(12);
  digitalWrite(latch, LOW);
  
  /* send cycles as bytes */
  for(byte j = 0; j < 2; j++)
  {
    output = 0;
    for(byte i = 0; i < 8; i++) 
    {
      digitalWrite(clock, LOW);
      delayMicroseconds(6);
      output += digitalRead(data) << i;
      digitalWrite(clock, HIGH);
      delayMicroseconds(6);
    }
    Serial.write(~output);
  }
  
  /* Allignment byte */
  Serial.write((byte)255);
}
