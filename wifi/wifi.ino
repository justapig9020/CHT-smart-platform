#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* host = "192.168.2.75";
const int port = 8000; 
const String url = "/broadcast";
WiFiClient client;
void setup() {
  Serial.begin(115200);

  WiFi.begin("prlab5G", "csc0123456789");

  //Serial.println ("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.println ("ReConnecting");
    delay(500);
  }
  //Serial.println("");
  //Serial.println("IP address: ");
  //Serial.print(WiFi.localIP());
  //Serial.println("WiFi status:");
  //WiFi.printDiag(Serial);
  delay(5000);
  Serial.print('c');
  
}
void loop() {
  char data[2];
  int index = 0;
  /*
  if( Serial.read() == '\xAF'){
    // start get data
    while(1){
      
      char tmp = Serial.read();
      if (tmp == '\xFF')break;
      data[index] = tmp;
      ++index;      
    }    
  }
  
*/
   if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://192.168.2.75:8000/broadcast"); //Specify request destination
 
    int httpCode = http.POST("{\"data\": 2}"); //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
 
    }else Serial.println("An error ocurred");
 
    http.end();   //Close connection

  }

 
  delay(10000);  

  
}
