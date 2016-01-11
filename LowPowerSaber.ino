/*
Enerlib: easy-to-use wrapper for AVR's Sleep library.
By E.P.G. - 11/2010 - Ver. 1.0.0

When you call any methods for put Arduino in a low
power state, it can only be waked up by triggering
an interruption. If you don't use any interruption,
you must reset Arduino to wake it.
*/

#include <Enerlib.h>


Energy energy;
uint8_t colorState=0; //0- off, 1=red, 2= green, 3= blue
uint8_t redPin=5;
uint8_t greenPin=6;
uint8_t bluePin=9;
uint8_t switchPin=2;


void INT0_ISR(void)
{
 
  
  
  if (energy.WasSleeping())
  {
      //Serial.println("Woken");
     
        
    
  }
  
 
  
}

void setup()
{
  attachInterrupt(0, INT0_ISR, LOW);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(115200);
  /*
  Pin 2 will be the "wake button". Due to uC limitations,
  it needs to be a level interrupt.
  For experienced programmers:
    ATMega's datasheet contains information about the rest of
    wake up sources. The Extended Standby is not implemented.
  */
 // Serial.begin(115200);
 
  //energy.Standby();
 // energy.PowerSave();
 // energy.SleepADC();
 // energy.Idle();      //Least power saving
  
  
}
uint8_t changedColor;

void loop()
{
  if(digitalRead(switchPin)==LOW)
   {
      colorState=colorState+1;
      changedColor=colorState%4;
      Serial.println(colorState);

       if(changedColor==0)
      {
        // state is power down      
      
          digitalWrite(redPin,LOW);
          digitalWrite(greenPin,LOW);
          digitalWrite(bluePin,LOW);
          energy.PowerDown();
      }
      if(changedColor==1)
      {   
          // state is red
          digitalWrite(redPin,HIGH);
          digitalWrite(greenPin,LOW);
          digitalWrite(bluePin,LOW);    
      }      
      if(changedColor==2)
      {   
        //state is green
      
          digitalWrite(redPin,LOW);
          digitalWrite(greenPin,HIGH);
          digitalWrite(bluePin,LOW);
      }
       if(changedColor==3)
      { 
         //state is blue
      
          digitalWrite(redPin,LOW);
          digitalWrite(greenPin,LOW);
          digitalWrite(bluePin,HIGH);
      }  
      delay(1000);
   }
    
}
