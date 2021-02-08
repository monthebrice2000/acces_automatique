////#include <SoftwareSerial.h>
////
////SoftwareSerial ArduinoMaster(11,10);
////char cmd="";
////char old_cmd;
////
////void setup(){
////  ArduinoMaster.begin(9600);    
////}
////
////void loop(){
////  Serial.println( "Slave is reading to broche ");
////  //old_cmd=cmd;
////  // Read data from master
//////  if (ArduinoMaster.available()){
//////    
//////  } 
////  cmd=ArduinoMaster.read();
////  // Send answer to master
//////  if(cmd!=old_cmd){
//////    ArduinoMaster.write(cmd);
//////  }
////   
////}
//
//#include <SoftwareSerial.h>
//
//SoftwareSerial mySerial(10,11); // RX, TX
//
//void setup()
//{
//  // Open serial communications and wait for port to open:
//  Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Native USB only
//  }
//
//
//  Serial.println("Goodnight moon!");
//
//  // set the data rate for the SoftwareSerial port
//  mySerial.begin(9600);
//  mySerial.println("Hello, world?");
//}
//
//void loop() // run over and over
//{
//  if (mySerial.available())
//    Serial.write(mySerial.read());
//  if (Serial.available())
//    mySerial.write(Serial.read());
//}

/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and
  clears it.

  A good test for this is to try it with a GPS receiver
  that sends out NMEA 0183 sentences.

  Created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialEvent

*/
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial SWrecv(2,3); //(rx,tx)
String strSSID = "";         // a string to hold incoming data
String strPWD = "";
bool keepSSID = false;
bool keepPWD = false;
boolean stringComplete = false;  // whether the string is complete

void setup() {
  pinMode( 11, OUTPUT );
  digitalWrite( 11, LOW );
  // initialize serial:
  Serial.begin(9600);
  SWrecv.begin(4800);
}

void loop() {
  // print the string when a newline arrives:
  SWrecvEvent();
//  if (stringComplete) {
//    Serial.println("SSID:" + strSSID  + ", PWD:" + strPWD);
//    if (strSSID == "")
//    {
//      Serial.println("SSID:not config");
//    }
//    strSSID = "";         // a string to hold incoming data
//    strPWD = "";
//    stringComplete = false;
//  }
}

void SWrecvEvent() {
   while (SWrecv.available()) {
    // get the new byte:
    char inChar = (char)SWrecv.read();
    if( inChar == '1' ){
      Serial.println("I recieved 1");
      digitalWrite( 11, HIGH );
      delay( 500 );
      digitalWrite( 11, LOW );
      delay( 500 );
      digitalWrite( 11, HIGH );
      delay( 500 );
      digitalWrite( 11, LOW );
    }
    Serial.print(inChar);
//    // add it to the inputString:
//    switch (inChar ) {
//      case '*':
//        {
//
//          keepSSID = true;
//          keepPWD = false;
//
//        }
//        break;
//      case '!':
//        {
//          keepSSID = false;
//          keepPWD = true;
//        }
//        break;
//      default:
//        {
//          if (inChar == '\n') {
//            stringComplete = true;
//            keepSSID = false;
//            keepPWD = false;
//            return;
//          }
//          if (keepSSID == true )
//          {
//            strSSID += inChar;
//          }
//          else if (  keepPWD == true )
//          {
//            strPWD += inChar;
//
//          }
//
//        }
//        break;
//    }
  }
}
