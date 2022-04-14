#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int count = 0;
 const int buzzer = 9;
void setup()
{
Serial.begin(9600);
lcd.begin(16,2);
pinMode(buzzer, OUTPUT);
}

void loop()
{
if(Serial.available())//check if there's incoming data
  {
    count =0; //reset to zero
    while(Serial.available())//keep reading byte by byte from
    {char input=Serial.read();
    Serial.print(input);//print the byte
    count++;
    delay(5);
        
if(input=='false') 
        {
      lcd.setCursor(1,1);
      lcd.print(input);
      tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
        }  

        
       else 
       {
       lcd.setCursor(1,1);
      lcd.print(input);
       } 
}
   
    
    
    }
    Serial.println();

}
