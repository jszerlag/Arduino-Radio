/*
 -----
- The TEA5767 maximum supply voltage is 5V.  Be sure your Arduino is not sourcing more than 5V

- TEA5756 module:

Top view:
+-10--9--8--7--6-+
|  +------+  ++  |
|  | TEA  |  ||  |
|  | 5767 |  ||  |
|  +------+  ++  |
+--1--2--3--4--5-+

1 ----> Arduino SDA
2 ----> Arduino SCL
3 ----> GND
5 ----> +5V
6 ----> GND
7 ----> Audio out (right channel)
8 ----> Audio out (left channel)
10 ---> Antenna

 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * Arduino SDA PIN A5
 * Arduino SCL PIN A4
 * ends to +5V and ground
 * UP SEARCH (A0)
 * DOWN SEARCH (A1)
 * ALL RESISTOR ARE 10K AND PUSH BUTTON IN PULL DOWN MODE
 */

#include <Wire.h>                               
#include <TEA5767Radio.h>                       
#include <LiquidCrystal.h>                      
                                               
                                                
TEA5767Radio radio = TEA5767Radio();            
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);              
float frequency = 0;                            
int fUP = A0;                                   
int fDOWN = A1;                                
int count = 0;                                   


void setup()
{
  delay(1000);
  Wire.begin();
  frequency = 88.1;                       //starting frequency
  radio.setFrequency(frequency);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("FM: ");
  lcd.setCursor(0, 1);
  lcd.print(frequency);
}

void loop()
{
  
  if(digitalRead(fUP))                      
  {
    count=0;
    while (digitalRead(fUP))
    {
      count++;
      if(count > 0 && count <= 6)          
      {
        frequency += 0.1;
        frequencyUpdate();
        delay(200);
      }
      else if (count > 6 && count <= 2)   
      {
        frequency += 0.1;
        frequencyUpdate();
        delay(80);
      }
      else                                
      {
        frequency += 0.1;
        frequencyUpdate();
        delay(5);
      }
    }

  }
  
  
  
   if(digitalRead(fDOWN))                   
   {
     count = 0;
    while (digitalRead(fDOWN))            
    {
      count--;
      if(count < 0 && count >= -6)
      {
        frequency -= 0.1;
        frequencyUpdate();
        delay(200);
      }
      else if (count < -6 && count >= -12)
      {
        frequency -= 0.1;
        frequencyUpdate();
        delay(80);
      }
      else                                 
      {
        frequency -= 0.1;
        frequencyUpdate();
        delay(5);
      }
    }
   }  
  
}


void frequencyUpdate()                    //this function changes the frequency of the station, is called by preset and frequency up/down conditions.
{
  frequency = constrain(frequency, 87.5, 108.5);
  lcd.setCursor(0,0);
  lcd.print("ESTACION DE FM:");
  lcd.setCursor(0,1);
  lcd.print(frequency);
  radio.setFrequency(frequency);
}

