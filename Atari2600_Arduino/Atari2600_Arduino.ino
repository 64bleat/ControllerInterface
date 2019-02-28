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
  
  Serial Output
  ================
  Bit  Description
  ===  ===========
  1    Up
  2    Down
  3    Left
  4    Right
  5    Button
  6    x
  7    x
  8    x
*/

byte output;

void setup()
{
  /* Pins 3-7 */
  for(byte i = 3; i <= 7; i++)
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
 for(byte i = 0; i < 5; i++)
   output += !digitalRead(i + 3) << i;
   
 //output += 1 << 5;

 Serial.write(output);
}
