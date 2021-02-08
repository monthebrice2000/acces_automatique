#include <Servo.h>

#include <Wire.h>
#include <LiquidCrystal.h>

#include <Keypad.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo servo ;

const byte ROWS = 4;
const byte COLS = 4;


int number_of_test=1;
int multiple_time=0;


char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {A1, A2, A3, A4};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


void setup()
{

  Serial.begin(9600);

 
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
  {while(cursor_value<5)
    {customKey = customKeypad.getKey();
      if (customKey)
      {ccursor_value++;
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
    }else
    {
      lcd.clear();
      lcd.print("ACCESS PERMITTED!!");
      digitalWrite( 10, HIGH );
      servo.write( 60 );
      delay( 500 );
      digitalWrite( 10, LOW );
      delay( 500 );
      digitalWrite( 10, HIGH );
      servo.write( 120 );
      delay( 500 );
      digitalWrite( 10, LOW );
      delay( 500 );
      digitalWrite( 10, HIGH );
      servo.write( 180 );
      delay( 500 );
      digitalWrite( 10, LOW );
      delay(1000);
      servo.write( 0 );
      lcd.clear();
    }
   }
   else{
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
