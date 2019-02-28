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
  7    
  8    GND          Ground
  9    8            Button 2
  
  Serial Output
  ================
  Bit  Description
  ===  ===========
  1    Up
  2    Down
  3    Left
  4    Right
  5    Button1
  6    Button2
  7    x
  8    x
*/

byte output;

void setup()
{
  /* Pins 3-8 */
  for(byte i = 3; i <= 8; i++)
  {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH); 
  }

  Serial.begin(115200);
}

void loop()
{
 output = 0;
 
 /* Assign each button to a bit */
 for(byte i = 0; i < 6; i++)
   output += !digitalRead(i + 3) << i;

 Serial.write(output);
}
