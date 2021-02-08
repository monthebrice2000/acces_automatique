#include <Servo.h>

#include <Wire.h>
#include <LiquidCrystal.h>

// Include the keypad library
#include <Keypad.h>

//declaration des ports du LCD sur les broches de l'arduino
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//initialisation de l'afficheur avec les ports
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo servo ;

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
byte colPins[COLS] = {A1, A2, A3, A4};

//create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


void setup()
{
  //setup serial monitor
  Serial.begin(9600);

  //setup lcd with backlight and initialize
  lcd.begin(16, 2);
  pinMode( 13, OUTPUT );
  digitalWrite( 13, LOW );
  pinMode( 10, OUTPUT );
  digitalWrite( 10, LOW );
  servo.attach( A0 );
  servo.write( 0 );
  
}


void loop()
{
  lcd.setCursor( 1 , 0 );
  lcd.print( "ENTER PASSWORD");
  int cursor_value=0;
  String value="";
  char customKey;
  int waiting_time=0; 
  if(number_of_test<5)
  {
    while(cursor_value<5)
    {
      //get key value if pressed
      customKey = customKeypad.getKey();
      if (customKey)
      {
        cursor_value++;
        value+=customKey;
        lcd.setCursor(cursor_value,1);
        lcd.print( "*" );
        Serial.print(customKey);
      }
    }
    if(value!="01010"){
      number_of_test++;
      lcd.clear();
      lcd.print("ACCESS DENIED!!");
      Serial.println("ACCESS DENIED!!");
      digitalWrite( 13, HIGH );
      servo.write( -60 );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay( 500 );
      digitalWrite( 13, HIGH );
      servo.write( -120 );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay( 500 );
      digitalWrite( 13, HIGH );
      servo.write( -180 );
      delay( 500 );
      digitalWrite( 13, LOW );
      delay(1000);
      lcd.clear();
        
    }
    else
    {
      lcd.clear();
      lcd.print("ACCESS PERMITTED!!");
      digitalWrite( 10, HIGH );
      servo.write( 60 );
      delay( 500 );
      digitalWrite( 10, LOW );
      //servo.write( 120 );
      delay( 500 );
      digitalWrite( 10, HIGH );
      servo.write( 120 );
      delay( 500 );
      digitalWrite( 10, LOW );
      //servo.write( 240 );
      delay( 500 );
      digitalWrite( 10, HIGH );
      servo.write( 180 );
      delay( 500 );
      digitalWrite( 10, LOW );
      //servo.write( 360 );
      delay(1000);
      servo.write( 0 );
      lcd.clear();
    }
   }
   else
   {
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