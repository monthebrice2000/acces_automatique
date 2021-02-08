//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define FIREBASE_HOST "react-my-burger-5f179-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "5jIGSve2GUJgJ9OTzJHz9AaG9obkmpiFVTxdz5H1"
#define WIFI_SSID "TONTON_LA_FORCE"
#define WIFI_PASSWORD "collegedulevant"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJsonArray arr;
FirebaseJson json;
QueryFilter query;

int nb_users = 2;

SoftwareSerial NodeMCU(D2,D3);

void setup()
{
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  NodeMCU.begin(9600);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);

}

void check_user_authentification(){
//  StaticJsonBuffer<1000> jsonBuffer;
//  JsonObject& root = jsonBuffer.parseObject( NodeMCU );
//  if (root == JsonObject::invalid())
//    return;
// 
//  Serial.println("JSON received and parsed");
//  //root.prettyPrintTo(Serial);
//  Serial.println("---------------------xxxxx--------------------");
//  String str = root["code_rfid"];
  //delay(30);
  
//  arr.add( json );
  //json.add("password", root["password"]);
  //json.add("code_rfid", root["code_rfid"] );
  
  //insert_user( "MONTHE", "123455", " dsfsdfedgs");

//  //Query any child that its value begins with 2 (number), assumed that its data type is float or integer
//  query.startAt( "30 50 4" );
//  //query.endAt(" 15 64 50 49");
//  
//  //Limit the maximum query result to return only the last 5 nodes
//  //query.limitToFirst(1);
//
////
//  if (Firebase.getJSON(firebaseData, "/Utilisateurs", query)){
//    //Success, then try to read the JSON payload value
//    Serial.println(firebaseData.jsonString());
//    Serial.println("Authentification reussie");
//  }
//  else
//  {
//    //Failed to get JSON data at defined database path, print out the error reason
//    Serial.println(firebaseData.errorReason());
//    Serial.println("Authentification refusée");
//  }
//
//  //Clear all query parameters
//  query.clear();

}

void loop() {
  check_user_authentification(); 
  get_users(); 
  delay(100);
}

void insert_user( String nom, String password, String code_rfid ){
  json.add("id", nb_users+1 ).add("nom", nom).add("password", password).add("code_rfid" ,code_rfid);
  int id = nb_users++;
  if (Firebase.setJSON(firebaseData, "/Utilisateurs/user_", json ))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

}

void insert_history( String date, String heure, String code, String statut ) {
  json.add("id", nb_users+1 ).add("date", date).add("heure", heure).add("code" ,code).add( "statut", statut ) ;
  int id = nb_users++;
  if (Firebase.setJSON(firebaseData, "/Historiques/hist_", json ))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}

void get_users(){

  FirebaseJsonData firebaseJsonData;
  FirebaseJsonArray arr;
  Firebase.getJSON(firebaseData, "/Utilisateurs");
  //firebaseJsonData.getArray(arr);
//
//if(jsonData.success)
//{
//  //Type of parsed data
//  Serial.println(jsonData.type);
//  //Its value
//  Serial.println(jsonData.stringValue);
//  //Serial.println(jsonData.intValue);
//  //Serial.println(jsonData.boolValue);
//  //Serial.println(jsonData.floatValue);
//  //Serial.println(jsonData.doubleValue);
//
//}
//
////The above code will show
///*
//string
//salad
//*/
//
//
////To get the JSON object at array index 1 from FirebaseJsonArray
//arr.get(jsonData, "[1]");// or arr.get(jsonData, 1);
//
////Prepare FirebaseJson to take the JSON object from FirebaseJsonArray
//FirebaseJson myJson;
//
////Get FirebaseJson data
//jsonData.getJSON(myJson);
//
////Parse the JSON object as list
////Get the number of items
//size_t len = myJson.iteratorBegin();
//String key, value = "";
//int type = 0;
//for (size_t i = 0; i < len; i++)
//{
//  //Get the item at index i, whereas key and value are the returned data
//  myJson.iteratorGet(i, type, key, value);
//  //Print the data
//  Serial.print(i);
//  Serial.print(", ");
//  Serial.print("Type: ");
//  Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
//  if (type == FirebaseJson::JSON_OBJECT)
//  {
//    Serial.print(", Key: ");
//    Serial.print(key);
//  }
//  Serial.print(", Value: ");
//  Serial.println(value);
//}
////Clear all list to free memory
//myJson.iteratorEnd();
//}

}
