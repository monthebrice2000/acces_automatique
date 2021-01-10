#include <SPI.h>
#include <MFRC522.h>
//#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Keypad.h>
 

#define SS_PIN 10  //D10:pin of tag reader SDA
#define RST_PIN 9 //D9:pin of tag reader RST
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String accessGranted [2] = {"310988016", "19612012715"};  //RFID serial numbers to grant access to
int accessGrantedSize = 2;                                //The number of serial numbers
#define beep_pin 8

#define LCD_COLS 20
#define LCD_ROWS 4
#define LCD_I2C_ADDRESS 0x20
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, LCD_COLS, LCD_ROWS); //declaration des ports du LCD sur les broches de l'arduino => initialisation de l'afficheur avec les ports 

Servo lockServo ;
int lockPos = 15;               //Locked position limit
int unlockPos = 75;             //Unlocked position limit
boolean locked = true;

//constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;

//the number of tests
int number_of_test=1;
int multiple_time=0;

//Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//connexion to the arduino board
byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {A1, A2, A3, A4 };

//create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


 
void setup() 
{
  //setup serial monitor
  Serial.begin(9600);

  //setup lcd with backlight and initialize
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode( 13, OUTPUT );
  digitalWrite( 13, LOW );
  pinMode( 10, OUTPUT );
  digitalWrite( 10, LOW );
   
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  lockServo.attach( A0);
  lockServo.write(lockPos);

}
void loop() 
{
  while( locked == false ){
     delay(5000);
     lcd.setCursor(0, 0);
     lcd.print("closed door");
     delay(500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("closed door");
     delay(500);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("closed door");
     delay(500);
     lcd.clear(); 
  }
  lcd.setCursor(0, 0);
  lcd.print("Put your card to");
  lcd.setCursor(0, 1);
  lcd.print("the reader......");
  delay(2000);
  lcd.clear();
  lcd.setCursor( 0 , 0 );
  lcd.print( "ENTER PASSWORD:");
  delay(300);

  int cursor_value=0;
  String value="";
  char customKey;
  int waiting_time=0; 
  if(number_of_test<5){
    while(cursor_value<5){
      //get key value if pressed
      customKey = customKeypad.getKey();
      if (customKey){
        cursor_value++;
        value+=customKey;
        lcd.setCursor(cursor_value,1);
        lcd.print( "*" );
        Serial.print(customKey);
      }
    }
    checkAccess_with_keypad ( value );
  }else{
    multiple_time++;
    number_of_test=0;
    waiting_time=multiple_time*5;
    lcd.setCursor( 4, 0 );
    lcd.print("RETRY AFTER ");
    lcd.setCursor( 0, 1 );
    lcd.print(waiting_time);
    lcd.setCursor( 3, 1 );
    lcd.print("SECONDS!!");
    delay(waiting_time*1000);
    lcd.clear();
   }

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  Serial.println ( content );
  checkAccess_with_rfid ( content );
  mfrc522.PICC_HaltA(); 

}

void checkAccess_with_rfid (String temp)    //Function to check if an identified tag is registered to allow access
{
  boolean granted = false;
  for (int i=0; i <= (accessGrantedSize-1); i++)    //Runs through all tag ID numbers registered in the array
  {
    if(accessGranted[i] == temp)            //If a tag is found then open/close the lock
    {
      Serial.println ("Access Granted");
      granted = true;
      grantedHandler( locked );
      lcd.clear();
      lcd.print("ACCESS PERMITTED!!");
      digitalWrite( 10, HIGH );
      delay( 500 );
      digitalWrite( 10, LOW );
      delay( 500 );
      digitalWrite( 10, HIGH );
      delay( 500 );
      digitalWrite( 10, LOW );
      delay( 500 );
      digitalWrite( 10, HIGH );
      delay( 500 );
      digitalWrite( 10, LOW );
      delay(1000);
      lcd.clear();
    }
  }
  if (granted == false)     //If the tag is not found
  {
    Serial.println ("Access Denied");
    lcd.clear();
    lcd.print("ACCESS DENIED!!");
      Serial.println("ACCESS DENIED!!");
      digitalWrite( 13, HIGH );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay( 500 );
      digitalWrite( 13, HIGH );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay( 500 );
      digitalWrite( 13, HIGH );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay(1000);
      lcd.clear();
  }
}

void checkAccess_with_keypad (String value)    //Function to check if an identified password is registered to allow access
{
    boolean granted = false;
    if(value!="01010"){
      number_of_test++;
      lcd.clear();
      lcd.print("ACCESS DENIED!!");
      Serial.println("ACCESS DENIED!!");
      digitalWrite( 13, HIGH );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay( 500 );
      digitalWrite( 13, HIGH );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay( 500 );
      digitalWrite( 13, HIGH );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay(1000);
      lcd.clear();
    }
    else{
      granted = true;
      grantedHandler( locked );
      lcd.clear();
      lcd.print("ACCESS PERMITTED!!");
      digitalWrite( 10, HIGH );
      delay( 500 );
      digitalWrite( 10, LOW );
      delay( 500 );
      digitalWrite( 10, HIGH );
      delay( 500 );
      digitalWrite( 10, LOW );
      delay( 500 );
      digitalWrite( 10, HIGH );
      delay( 500 );
      digitalWrite( 10, LOW );
      delay(1000);
      lcd.clear();
    }
} 

void grantedHandler( boolean locked ){
    if (locked == true)         //If the lock is closed then open it
      {
          lockServo.write(unlockPos);
          locked = false;
      }
      else if (locked == false)   //If the lock is open then close it
      {
          lockServo.write(lockPos);
          locked = true;
      }
}
