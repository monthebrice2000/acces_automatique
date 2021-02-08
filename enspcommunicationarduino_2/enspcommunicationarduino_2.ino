#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial SWrecv(2,3); //(rx,tx)

int buzzer = 7;

void setup() {
  Serial.begin(9600);
  pinMode( 11, OUTPUT );
  digitalWrite( 11, LOW );
  // initialize serial:
  pinMode( 5, OUTPUT ); // led verte 
  digitalWrite(5, LOW);
  pinMode( 6, OUTPUT ); //led rouge
  digitalWrite(6, LOW);
  SWrecv.begin(4800);
}

void loop() {  
  // print the string when a newline arrives:
  Serial.println(SWrecv.read());
  SWrecvEvent();
}

void SWrecvEvent() {
   while (SWrecv.available()) {
    // get the new byte:
    char inChar = (char)SWrecv.read();
    Serial.print(inChar);
    if( inChar == '1' ){
      Serial.println("I recieved 1");
      digitalWrite( 5, HIGH );
      tone(buzzer, 450 );
      delay( 500 );
      noTone(buzzer);
      
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
      
//      openDoor();
      delay(5000);
    }
    if (inChar == '0') {
      digitalWrite( 6, HIGH );
      tone(buzzer, 450 );
      delay( 500 );
      noTone(buzzer);
      
      digitalWrite( 6, LOW );
      delay( 500 );
      
      digitalWrite( 6, HIGH );
      tone(buzzer, 450 );
      delay( 500 );
      noTone(buzzer);
      
      digitalWrite( 6, LOW );
      delay( 500 );
      
      digitalWrite( 6, HIGH );
      tone(buzzer, 450 );
      delay( 500 );
      noTone(buzzer);
      
      digitalWrite( 6, LOW );
      delay(1000);
    }
    

  }

  Serial.println("I doen't recieved 1");
}


//void openDoor(){
//  int val =300;
//  stepper.setSpeed(500);
//  stepper.step(val);
//  delay(2000);
//  stepper.step(-val);
//  delay(2000);
//  stepper.step(0);
//}
