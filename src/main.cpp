
#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

String readserialinput();
void wifiinit();
void getID(String *);
void firebaseinit();
void analyze(String,bool*);


#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Insert your network credentials
String ssid;
String pass;
String deviceID;


#define API_KEY "AIzaSyDSW-xhGkKcTcu2UEL38D1QyYvJK0luLiA"
#define DATABASE_URL "https://smartmeter-ids-default-rtdb.asia-southeast1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;
bool valid = false;

void setup()
{
  Serial.begin(115200);
  wifiinit();
  delay(1500);
  while (1)
  {
  getID(&deviceID);
  analyze(deviceID,&valid);
  if (valid == true)
  {
  firebaseinit();
  if (Firebase.ready() && signupOK )
  {

  String macAddress = WiFi.macAddress();
  String path = String("/") + macAddress + "/deviceID";

  if (Firebase.RTDB.setString(&fbdo, path.c_str(), deviceID)) 
  {
    Serial.println("Device Registered Successfully!");
  } 
  else 
  {
    Serial.print("Failed to write data, reason: ");
    Serial.println(fbdo.errorReason());
  }

  }
  break;
  }
  else
  {
    Serial.println("Enter the Sensor ID Again ");
  }
  }

}


String readserialinput()
{
  String input = "";
  while(1){
  if (Serial.available() > 0)
  {
    char c = Serial.read();
    if(c == '\n')
    {
      break;
    }
    else
    {
      input += c;
      Serial.print(c);
    }
  }
  delay(10);
  }
  Serial.println();
  input.trim(); // Remove any leading or trailing whitespace
  return input; // Return the input string
}
String readpass()
{
  String input = "";
  while(1){
  if (Serial.available() > 0)
  {
    char c = Serial.read();
    if(c == '\n')
    {
      break;
    }
    else
    {
      input += c;
      Serial.print("*");
    }
  }
  delay(10);
  }
  Serial.println();
  input.trim(); // Remove any leading or trailing whitespace
  return input; // Return the input string
}
void wifiinit()
{ 
    // Prompt user for SSID
  Serial.println("Enter WiFi SSID: ");
  ssid = readserialinput();  // Call function to read input

  // Prompt user for Password
  Serial.println("Enter WiFi Password: ");
  pass = readpass();  // Call function to read input
  WiFi.begin(ssid, pass);
  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    delay(500);
  }
  Serial.printf("Connected to [%s]\n",ssid);

}
void getID(String *deviceID)
{
  Serial.println("SensorID for single slots : SM-yyy (yyy -> unique 3 digit ID)");
  Serial.println("SensorID for 1/3/6/8/9/12 slots : SMx-yy (x -> # of slots (1/3/6/8/9/12) , (yyy -> unique 3 digit ID)");
  Serial.println("Enter Sensor ID : ");
  *deviceID = readserialinput();
}
void firebaseinit()
{
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}
void analyze(String deviceID,bool *valid)
{
 const char* did_cstr = deviceID.c_str();
 if (did_cstr[0] == 83 && did_cstr[1] == 77)
 {
 if ((did_cstr[2] == '-' || did_cstr[2] == '1') || (did_cstr[2] == '3') || (did_cstr[2] == '6') || (did_cstr[2] == '8') || (did_cstr[2] == '9') || (did_cstr[3] == '2'))
 {
  Serial.println("It is Valid ID");
  *valid = 1;
 }
 else
 {
  Serial.println("ERROR : InValid ID Format");
 }}
 else
 {
  Serial.println("ERROR : [s,m] LOWER CASE LETTERS NOT ALLOWED");
  Serial.println("s -> S , m -> M");
 }
}
void loop()
{

}