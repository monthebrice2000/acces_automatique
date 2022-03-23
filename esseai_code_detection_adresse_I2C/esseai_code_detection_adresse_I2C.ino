//#include <Wire.h>
// 
//void setup() {
//  Wire.begin();
//  Serial.begin(115200);
//  Serial.println("\nI2C Scanner");
//}
// 
//void loop() {
//  byte error, address;
//  Serial.println("Scanning...");
//  int nDevices = 0;
//  for(address = 1; address < 127; address++ ) 
//  {
//    // The i2c_scanner uses the return value of
//    // the Write.endTransmisstion to see if
//    // a device did acknowledge to the address.
//    Wire.beginTransmission(address);
//    error = Wire.endTransmission();
//    if (error == 0) {
//      Serial.print("I2C device found at address 0x");
//      if (address<16) {
//        Serial.print("0");
//      }
//      Serial.println(address,HEX);
//      nDevices++;
//    }
//    else if (error==4) {
//      Serial.print("Unknow error at address 0x");
//      if (address<16) {
//        Serial.print("0");
//      }
//      Serial.println(address,HEX);
//    }    
//  }
//  if (nDevices == 0) {
//    Serial.println("No I2C devices found\n");
//  }
//  else {
//    Serial.println("done\n");
//  }
//  delay(5000);          
//}
//
#include <Wire.h>
void setup()
{
Wire.begin();
Serial.begin(9600);
Serial.println("\nI2C Scanner");
}
void loop()
{
byte error, address;
int Devices;
Serial.println("Scanning...");
Devices = 0;
for(address = 1; address < 127; address++ )
{

Wire.beginTransmission(address);
error = Wire.endTransmission();
if (error == 0)
{
Serial.print("I2C device found at address 0x");
if (address<16)
Serial.print("0");
Serial.print(address,HEX);
Serial.println("  !");
Devices++;
}
else if (error==4)
{
Serial.print("Unknown error at address 0x");
if (address<16)
Serial.print("0");
Serial.println(address,HEX);
}
}
if (Devices == 0)
Serial.println("No I2C devices found\n");
else
Serial.println("done\n");
delay(5000);          
}