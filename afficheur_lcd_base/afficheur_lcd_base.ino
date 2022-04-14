#include <Wire.h>
#include <LiquidCrystal_I2C.h> // pour télécharger la librairie: croquis - include library - manage libraries - LiquidCrystal_I2C.h de Frank de Brabander
LiquidCrystal_I2C lcd(0x27,16,2); //écran LCD 0x27 avec 16 colonnes et 2 lignes (ligne 0 et ligne 1)
char data;
void setup()
{
  Serial.begin(9600);
lcd.init(); //initialisation de l'écran LCD
lcd.cursor_on();
lcd.blink_on();
lcd.backlight();
lcd.setCursor(5,0); // écriture du texte sur la ligne 1 colonne 5 (centré)
lcd.print("Welcome!"); // texte "hello" sur ligne 1 colonne 5
lcd.setCursor(1,1); // écriture du texte sur la ligne 2 colonne 7 (centré)
lcd.print("WaterProof"); // texte "ok" sur ligne 2 colonne 7
lcd.cursor_off();
lcd.blink_off();

}


void loop() {
  if (Serial.available()){     
  
      data=Serial.read();  
       if(data=='1') 
        {
          lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("En marche");
      
      
        }  

        
       else if(data=='0')
       {
        lcd.clear();
       lcd.setCursor(4,1);
      lcd.print("En panne");
     
       }   
      } 
}
