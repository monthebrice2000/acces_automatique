//#include <SoftwareSerial.h>
//
//SoftwareSerial ArduinoSlave(10, 11);
//
//void setup(){
//  Serial.begin(9600);
//  //Serial.println("ENTER Commands:");
//  ArduinoSlave.begin(9600);            
//}
//
//void loop(){
//  //Read command from monitor
////  if (Serial.available()){
////    cmd=Serial.read();
////  } 
//  //Read answer from slave
////  if (ArduinoSlave.available()){
////    answer=ArduinoSlave.read();
////  } 
//  //Send data to slave
////  if(cmd!=old_cmd){
////    
////    Serial.println('b');
////    ArduinoSlave.write(cmd);
////  }
//  Serial.print("Master sent : ");
//  int value = ArduinoSlave.write("baba");
//  Serial.println( value );
//  Serial.println( "Slave received ");
//  //Send answer to monitor
////  if(answer!=old_answer){
////    Serial.print("Slave received : ");
////    Serial.println(answer);
////  }
//}
//
///*
//  Software serial multple serial test
//
// Receives from the hardware serial, sends to software serial.
// Receives from software serial, sends to hardware serial.
//
// The circuit:
// * RX is digital pin 2 (connect to TX of other device)
// * TX is digital pin 3 (connect to RX of other device)
//
// Note:
// Not all pins on the Mega and Mega 2560 support change interrupts,
// so only the following can be used for RX:
// 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
//
// Not all pins on the Leonardo support change interrupts,
// so only the following can be used for RX:
// 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
//
// created back in the mists of time
// modified 25 May 2012
// by Tom Igoe
// based on Mikal Hart's example
//
// This example code is in the public domain.
//
// */
//
//
//
#include <SoftwareSerial.h>
SoftwareSerial SWsend(2,3); // (rx,tx)

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   SWsend.begin(4800);
   //pinMode(12,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
    SWsend.print("1");
    Serial.println("sender give");
}
