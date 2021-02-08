#include <SPI.h>
#include <MFRC522.h>
//#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Keypad.h>
#include <Stepper.h>
 
#define STEPS 20
Stepper stepper(STEPS, 7, 8, 9, 10);
 

#define SS_PIN 10  //D10:pin of tag reader SDA
#define RST_PIN 9 //D9:pin of tag reader RST
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String accessGranted [2] = {" 40 64 50 49", " 5B 4F AA 0D"};  //RFID serial numbers to grant access to
int accessGrantedSize = 2;                                //The number of serial numbers
int buzzer = 11;
#define beep_pin 8

#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_I2C_ADDRESS 0x27
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
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = { 3, 2, 1, 0};

//create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


 
void setup() 
{
  //setup serial monitor
  Serial.begin(9600);
  lcd.init();
  //setup lcd with backlight and initialize
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode( 5, OUTPUT ); // led verte 
  digitalWrite(5, LOW);
  pinMode( 6, OUTPUT ); //led rouge
  digitalWrite(6, LOW);
   
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //lockServo.attach( A0);
  //lockServo.write(lockPos);

}

int direction_ = -1, speed_ = 0;

void loop() 
{
//  while( locked == false ){
//     delay(5000);
//     lcd.setCursor(0, 0);
//     lcd.print("closed door");
//     delay(500);
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("closed door");
//     delay(500);
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("closed door");
//     delay(500);
//     lcd.clear(); 
//  }
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
     Serial.print (mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  Serial.println ( content );
  checkAccess_with_rfid ( content );
  //mfrc522.PICC_HaltA(); 
  
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

  

}

void checkAccess_with_rfid (String temp)    //Function to check if an identified tag is registered to allow access
{
  boolean granted = false;
  for (int i=0; i <= (accessGrantedSize-1); i++)    //Runs through all tag ID numbers registered in the array
  {
    if(accessGranted[i].equals( temp ) )            //If a tag is found then open/close the lock
    {
      Serial.println ("Access Granted");
      granted = true;
      grantedHandler();
      lcd.clear();
      lcd.print("ACCESS PERMITTED!!");
      digitalWrite( 4, HIGH );
      delay( 500 );
      digitalWrite( 4, LOW );
      delay( 500 );
      digitalWrite( 4, HIGH );
      delay( 500 );
      digitalWrite( 4, LOW );
      delay( 500 );
      digitalWrite( 4, HIGH );
      delay( 500 );
      digitalWrite( 4, LOW );
      delay(1000);
      lcd.clear();
    }
  }
  if (granted == false)     //If the tag is not found
  {
    Serial.println ("Access Denied");
    lcd.clear();
    lcd.print("ACCESS DENIED!!");
    deniedHandler();
      Serial.println("ACCESS DENIED!!");
      digitalWrite( 5, HIGH );
      delay( 500 );
      digitalWrite( 5, LOW );
      delay( 500 );
      digitalWrite( 5, HIGH );
      delay( 500 );
      digitalWrite( 5, LOW );
      delay( 500 );
      digitalWrite( 5, HIGH );
      delay( 500 );
      digitalWrite( 5, LOW );
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
      deniedHandler();
      lcd.print("ACCESS DENIED!!");
      Serial.println("ACCESS DENIED!!");
      digitalWrite( 5, HIGH );
      delay( 500 );
      digitalWrite( 5, LOW );
      delay( 500 );
      digitalWrite( 5, HIGH );
      delay( 500 );
      digitalWrite( 5, LOW );
      delay( 500 );
      digitalWrite( 5, HIGH );
      delay( 500 );
      digitalWrite( 5, LOW );
      delay(1000);
      lcd.clear();
    }
    else{
      granted = true;
      grantedHandler();
      lcd.clear();
      lcd.print("ACCESS PERMITTED!!");
      digitalWrite( 4, HIGH );
      delay( 500 );
      digitalWrite( 4, LOW );
      delay( 500 );
      digitalWrite( 4, HIGH );
      delay( 500 );
      digitalWrite( 4, LOW );
      delay( 500 );
      digitalWrite( 4, HIGH );
      delay( 500 );
      digitalWrite( 4, LOW );
      delay(1000);
      lcd.clear();
    }
} 

void grantedHandler(){
  speed_ = 1000;
  stepper.setSpeed(speed_);  
  // move the stepper motor
  stepper.step(direction_);

  tone(buzzer, 450 );
  delay(200);
  noTone(buzzer);
  delay(200);
}

void deniedHandler(){
  tone(buzzer, 450 );
  delay(200);
  noTone(buzzer);
  delay(300);

  tone(buzzer, 450 );
  delay(200);
  noTone(buzzer);
  delay(300);

  tone(buzzer, 450 );
  delay(200);
  noTone(buzzer);
  delay(300);
  
}
