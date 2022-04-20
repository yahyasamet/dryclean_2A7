#include <Wire.h>
#include <LiquidCrystal_I2C.h> // pour télécharger la librairie: croquis - include library - manage libraries - LiquidCrystal_I2C.h de Frank de Brabander
LiquidCrystal_I2C lcd(0x27,16,2); //écran LCD 0x27 avec 16 colonnes et 2 lignes (ligne 0 et ligne 1)
char data;
#include<Servo.h>

//Define the pins of the color sensor
#define s0 8 //S0 pin of the sensor on Arduino pin#2
#define s1 9 //S1 pin of the sensor on Arduino pin#3
#define s2 10 //S2 pin of the sensor on Arduino pin#4
#define s3 11 //S3 pin of the sensor on Arduino pin#5
#define sensorOut 12 //Output pin of the sensor on Arduino pin#6


//Variable to save the data coming from the sensorOut
int frequency = 0;
int i=0;
char nb_pieces;
// Variable to save the color
byte identifiedColor = 0;

//Declaring Servos

Servo feedingServo;
Servo decisionServo;

//Declaring general delays
byte smallDelay_ms = 5;
byte mediumDelay_ms = 30;
byte bigDelay_ms = 3000;
byte veryBigDelay_ms = 4000;


//Delcaring position of the feederServo
byte pos1FeederServo = 180;
byte pos2FeederServo = 100;
byte pos3FeederServo = 0;

//Delcaring position of the decisionServo
byte decisionServo_RED = 30;
byte decisionServo_BLUE = 65;
byte decisionServo_GREEN = 105;
byte decisionServo_YELLOW = 138;
byte decisionServo_PURPLE = 170;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);//initialisation du buzzeur
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
//Set the pins of the Color Sensor
  pinMode (s0, OUTPUT);
  pinMode (s1, OUTPUT);
  pinMode (s2, OUTPUT);
  pinMode (s3, OUTPUT);
  pinMode (sensorOut, INPUT);

  /* The pins S0 & S1 works for the frequency scaling
      L - L = Power Down
      L - H = 2%
      H - L = 20%
      H - H = 100%
  */
  //Using at 100%
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  //Attaching the Servos
  feedingServo.attach (6);
  decisionServo.attach(5);

  //Set the serial communication in bytes per second
  feedingServo.write (180);

}


void loop() {
  if (Serial.available()){    
 
      data=Serial.read();  
     
       while(data=='1' )
        {
         
          lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("En marche");
       //Write "steps" of 1 degree to the servo until pos2 (Sensor position)
       i++;
  for (int i = pos1FeederServo; i > pos2FeederServo ; i--) {

    feedingServo.write (i);
    delay (mediumDelay_ms);

  }//close for loop

  //Delay to stabilize readings
  delay(4000);
    if(getTheColor()==5 )
    {
      i--;
      //nb_pieces=i;   
      Serial.print(i); 
      i=0;
      data=3;
    }
  //We launch the Function getTheColor
  identifiedColor = getTheColor();

  //Switch Case to decide wich color are we reading
  /*********IMPORTANT********
   * Please calibrate your Servos and the TCS3200 sensor before uploading this program,
   * Depending on mechanical installation the positions of the servos may change
   * Also the TCS3200 can give you different readings compared to mines
   * because of the ambient lighting (light changes in general)
   */
  switch (identifiedColor) {

    //Case for Red
    case 1:
      decisionServo.write (decisionServo_RED);
      break;

    //Case for Orange
    case 2:
      decisionServo.write (decisionServo_BLUE);
      break;

    //Case for Green
    case 3:
      decisionServo.write (decisionServo_GREEN);
      break;

    //Case for Yellow
    case 4:
      decisionServo.write (decisionServo_YELLOW);
      break;
      case 5:
       lcd.clear();
       lcd.setCursor(4,1);
        lcd.print("Termine");
         tone (13, 600); // allume le buzzer actif arduino
         delay(500);
         tone(13, 900); // allume le buzzer actif arduino
         delay(500);
         noTone(13);  // désactiver le buzzer actif arduino
         delay(500);
      break;


  }// close Switch Case

  //Delay to exit position
  delay(bigDelay_ms);

  //Move Feeding servo to exit position
  for (int i = pos2FeederServo; i > pos3FeederServo; i--) {

    feedingServo.write (i);
    delay (mediumDelay_ms);

  }//Close for loop - Servo to Exit Position

  //Delay to return servo
  delay(bigDelay_ms);


  //Return the Feeding Servo to initial position
  for (int i = pos3FeederServo; i < pos1FeederServo ; i++) {

    feedingServo.write (i);
    delay (smallDelay_ms);
  }//Close for loop - Servo initial Position


  //Return the Value to 0
  identifiedColor = 0;

  //Delay to begin again
  delay (veryBigDelay_ms);
         
       
        }  

       
       if(data=='0')
       {
        lcd.clear();
       lcd.setCursor(4,1);
      lcd.print("En panne");
     
       }
        if(data=='2')
       {
        lcd.clear();
       lcd.setCursor(4,1);
      lcd.print("Etteinte");
     
       }
               if(data=='3')
       {
          lcd.clear();
          lcd.setCursor(4,1);
          lcd.print("Termine");
          
       }      
      }
}
int getTheColor() {


  //---Read RED values... S2 LOW - S3 LOW---
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  frequency = pulseIn(sensorOut, LOW);

  int redValue = frequency;

  /*Serial.print("R=");
  Serial.print(redValue);
  Serial.print("  ");

  delay(200);*/

  //---Read Green values ... S2 LOW - S3 HIGH---
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(sensorOut, LOW);

  int greenValue = frequency;
/*
  Serial.print("G=");
  Serial.print(greenValue);
  Serial.print("  ");

  delay(200);*/


  //---Read Blue values ... S2 HIGH - S3 LOW---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  frequency = pulseIn(sensorOut, LOW);

  int blueValue = frequency ;

 /* Serial.print("B=");
  Serial.print(blueValue);
  Serial.print("  ");

  delay(200);*/


    //---Read Clear values ... S2 HIGH - S3 HIGH---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(sensorOut, LOW);

  int clearValue = frequency ;

 /* Serial.print("C=");
  Serial.print(clearValue);
  Serial.println("  ");

  delay(200);*/


  //////////Parameters for Red//////////
if (redValue<13 & redValue>8 & clearValue<21 & clearValue>=17 ) {
   // Serial.println("Red");
    identifiedColor = 1; // Red
  }

  //////////Parameters for Orange//////////
  if (redValue<18 & redValue>13  & clearValue<21 & clearValue>=12) {
    //Serial.println("BLUE");
    identifiedColor = 2; // BLUE
  }


  //////////Parameters for Green//////////
  if (redValue<11 & redValue>7 & clearValue<16 & clearValue>13 ) {
    //Serial.println("PINK");
    identifiedColor = 3; // PINK
  }

  //////////Parameters for Yellow//////////
  if (redValue<12 & redValue>6 & clearValue<14 & clearValue>9 ) {
    //Serial.println("Yellow");
    identifiedColor = 4; // Yellow
  }
  if (redValue<=22 & redValue>=19 & greenValue<=19 & greenValue>=16 & blueValue<=7 & blueValue>=5  & clearValue<=23 & clearValue>=15 ) {
   // Serial.println("Terminé");
    identifiedColor = 5; // Terminé
  }

  //--- Return the value found---
  return identifiedColor;

}//Close Function getTheColor
