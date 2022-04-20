#include <usbhid.h>
#include <usbhub.h>
#include <hiduniversal.h>
#include <hidboot.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // pour télécharger la librairie: croquis - include library - manage libraries - LiquidCrystal_I2C.h de Frank de Brabander
LiquidCrystal_I2C lcd(0x27,16,2); //écran LCD 0x27 avec 16 colonnes et 2 lignes (ligne 0 et ligne 1)
String dataa;
int buzzer = 8 ;
int i;
class MyParser : public HIDReportParser {
  public:
    MyParser();
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
  protected:
    uint8_t KeyToAscii(bool upper, uint8_t mod, uint8_t key);
    virtual void OnKeyScanned(bool upper, uint8_t mod, uint8_t key);
    virtual void OnScanFinished();
};
 
MyParser::MyParser() {}
 
void MyParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  // If error or empty, return
  if (buf[2] == 1 || buf[2] == 0) return;
 
  for (uint8_t i = 7; i >= 2; i--) {
    // If empty, skip
    if (buf[i] == 0) continue;
 
    // If enter signal emitted, scan finished
    if (buf[i] == UHS_HID_BOOT_KEY_ENTER) {
      OnScanFinished();
    }
 
    // If not, continue normally
    else {
      // If bit position not in 2, it's uppercase words
      OnKeyScanned(i > 2, buf, buf[i]);
    }
 
    return;
  }
}
 
uint8_t MyParser::KeyToAscii(bool upper, uint8_t mod, uint8_t key) {
  // Letters
  if (VALUE_WITHIN(key, 0x04, 0x1d)) {
    if (upper) return (key - 4 + 'A');
    else return (key - 4 + 'a');
  }
 
  // Numbers
  else if (VALUE_WITHIN(key, 0x1e, 0x27)) {
    return ((key == UHS_HID_BOOT_KEY_ZERO) ? '0' : key - 0x1e + '1');
  }
 
  return 0;
}
 
void MyParser::OnKeyScanned(bool upper, uint8_t mod, uint8_t key) {
  uint8_t ascii = KeyToAscii(upper, mod, key);
  Serial.print((char)ascii);
}
 
void MyParser::OnScanFinished() {
  Serial.println("");
}
 
USB          Usb;
USBHub       Hub(&Usb);
HIDUniversal Hid(&Usb);
MyParser     Parser;
 
void setup() {
  Serial.begin( 9600 );
 
  if (Usb.Init() == -1) {
    Serial.println("OSC did not start.");
  }
 
  delay( 200 );
 
  Hid.SetReportParser(0, &Parser);
  pinMode (buzzer, OUTPUT) ;
 // digitalWrite (buzzer, LOW) ;
  lcd.init(); //initialisation de l'écran LCD
  lcd.cursor_on();
  lcd.blink_on();
  lcd.backlight();
  lcd.setCursor(5,0); // écriture du texte sur la ligne 1 colonne 5 (centré)
  lcd.print("Welcome!");
  lcd.cursor_off();
lcd.blink_off();
}
 
void loop() {
      Usb.Task();
  if (Serial.available()){ 
     
    //Si un message a été reçu  faire ceci
    // data=Serial.read(); 
     dataa=Serial.readString(); 
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
     if (dataa==NULL)
     {
     // digitalWrite(PIN_LED1,LOW);
     // digitalWrite(PIN_LED2,LOW);
     }
     else if(dataa=="false false") //si le caractère lu est égale à 1
    {
     // digitalWrite(PIN_LED1,HIGH);
     // digitalWrite(PIN_LED2,LOW); // alumer la lampe 
       //envoyer le nouvel état de la lampe
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CIN introuvable");
      digitalWrite (buzzer, LOW) ; //send tone
      delay (2000) ;
      digitalWrite (buzzer, HIGH) ; //no tone
      
      
     }
     else if (dataa!="false false")
     {
     // digitalWrite(PIN_LED2,HIGH);
     // digitalWrite(PIN_LED1,LOW);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print(dataa);
      }
      if (dataa!=NULL)
      {
       Serial.println(dataa);
      }
    }  
}
