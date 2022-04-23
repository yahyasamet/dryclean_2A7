
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
 String x;
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

String NUID_dec, NUID_hex;
String RKey;

Servo lockServo;                //Servo for locking mechanism
int lockPos = 10;               //Locked position limit
int unlockPos = 45;             //Unlocked position limit
boolean locked = true;

int redLEDPin = 5;
int greenLEDPin = 6;

void setup() { 
Serial.begin(9600);
SPI.begin(); // Init SPI bus
rfid.PCD_Init(); // Init MFRC522 
//Define Key
for (byte i = 0; i < 6; i++) {
key.keyByte[i] = 0xFF;
}
RKey = String(key.keyByte[0], HEX) + " "
           +String(key.keyByte[1], HEX) + " "
           +String(key.keyByte[2], HEX) + " " 
           +String(key.keyByte[3], HEX) + " "
           +String(key.keyByte[4], HEX) + " "
           +String(key.keyByte[5], HEX);
RKey.toUpperCase();

pinMode(redLEDPin, OUTPUT);     //LED startup sequence
  pinMode(greenLEDPin, OUTPUT);
lockServo.attach(3);
}

void loop() {

// Reset the loop if no new card present on the sensor/reader.
if ( ! rfid.PICC_IsNewCardPresent()) return;

// Verify if the NUID has been readed
if ( ! rfid.PICC_ReadCardSerial()) return;

//Serial.print(F("PICC type: "));
MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
//Serial.println(rfid.PICC_GetTypeName(piccType));

/* 
// Check is the PICC of Classic MIFARE type
if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
}*/

NUID_dec = String(rfid.uid.uidByte[0])+String(rfid.uid.uidByte[1])+String(rfid.uid.uidByte[2])+String(rfid.uid.uidByte[3]);
//Serial.print("NUID Tag (DEC): "); 
Serial.println(NUID_dec); 

NUID_hex = String(rfid.uid.uidByte[0], HEX) + " "
           +String(rfid.uid.uidByte[1], HEX) + " "
           +String(rfid.uid.uidByte[2], HEX) + " " 
           +String(rfid.uid.uidByte[3], HEX);
NUID_hex.toUpperCase();
//Serial.print("NUID Tag (HEX): "); 
//Serial.println(NUID_hex);

for (byte i = 0; i < 4; i++) {
nuidPICC[i] = rfid.uid.uidByte[i];
}
  
       x=Serial.readString(); 
       

if (compareNUID(nuidPICC, 67, 247, 82, 148)) 
    {//Serial.println("Welcome manager");
      if ((locked == true) && (x=="1"))       //If the lock is closed then open it
      {
          lockServo.write(lockPos);
          locked = false;
           //Serial.println("Door unlocked");
          digitalWrite(greenLEDPin, HIGH);
          delay(200);
          digitalWrite(greenLEDPin, LOW);
           delay(200);
           digitalWrite(greenLEDPin, HIGH);
           delay(200);
           digitalWrite(greenLEDPin, LOW);
      }
      else if ((locked == false)&& (x=="1"))   //If the lock is open then close it
      { 
        
          lockServo.write(unlockPos);
          locked = true;
         // Serial.println("Door locked");
          digitalWrite(redLEDPin, HIGH);
          delay(200);
          digitalWrite(redLEDPin, LOW);
          delay(200);
           digitalWrite(redLEDPin, HIGH);
          delay(200);
          digitalWrite(redLEDPin, LOW);
      }
     
    }
else if (compareNUID(nuidPICC, 83, 133, 106, 25)) 
    {//Serial.println("Welcome storekeeper"); 
      if ((locked == true)   && (x=="1")  )   //If the lock is closed then open it
      {
          lockServo.write(lockPos);
          locked = false;
          // Serial.println("Door unlocked");
          digitalWrite(greenLEDPin, HIGH);
          delay(200);
          digitalWrite(greenLEDPin, LOW);
           delay(200);
           digitalWrite(greenLEDPin, HIGH);
           delay(200);
           digitalWrite(greenLEDPin, LOW);
      }
      else if ((locked == false) && (x=="1")  ) //If the lock is open then close it
      { 
        
          lockServo.write(unlockPos);
          locked = true;
          //Serial.println("Door locked");
          digitalWrite(redLEDPin, HIGH);
          delay(200);
          digitalWrite(redLEDPin, LOW);
          delay(200);
           digitalWrite(redLEDPin, HIGH);
          delay(200);
          digitalWrite(redLEDPin, LOW);
      }
     
    }

 else if (compareNUID(nuidPICC, 124, 75, 96, 73)) 
    {//Serial.println("Welcome cashier"); 
      if( (locked == true)    &&  (x=="1") )     //If the lock is closed then open it
      {
          lockServo.write(lockPos);
          locked = false;
           //Serial.println("Door unlocked");
          digitalWrite(greenLEDPin, HIGH);
          delay(200);
          digitalWrite(greenLEDPin, LOW);
           delay(200);
           digitalWrite(greenLEDPin, HIGH);
           delay(200);
           digitalWrite(greenLEDPin, LOW);
      }
      else if( (locked == false) && (x=="1") )   //If the lock is open then close it
      { 
        
          lockServo.write(unlockPos);
          locked = true;
          //Serial.println("Door locked");
          digitalWrite(redLEDPin, HIGH);
          delay(200);
          digitalWrite(redLEDPin, LOW);
          delay(200);
           digitalWrite(redLEDPin, HIGH);
          delay(200);
          digitalWrite(redLEDPin, LOW);
      }
     
    }   
else 
     {if ((locked == false)  && (x=="0") )  //If the lock is open then close it
      {
          lockServo.write(unlockPos);
          locked = true;
      }
     // Serial.println("Access Denied");
      digitalWrite(redLEDPin, HIGH);
      delay(200);
      digitalWrite(redLEDPin, LOW);
      delay(200);
       digitalWrite(redLEDPin, HIGH);
      delay(200);
      digitalWrite(redLEDPin, LOW);
     } 

//Serial.println();

// Halt PICC
rfid.PICC_HaltA();

// Stop encryption on PCD
rfid.PCD_StopCrypto1();
}

boolean compareNUID(byte x[4], byte x0, byte x1, byte x2, byte x3)
{
if (x[0] == x0 && x[1] == x1 && x[2] == x2 && x[3] == x3)
return true; 
else return false;
}
