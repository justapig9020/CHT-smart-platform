#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* host = "172.20.10.4";
const int port = 8000; 
char ttt[100]={0};
const String url = "/broadcast";
char tmp;

WiFiClient client;
void setup() {
  Serial.begin(115200);
  Serial.println ("initing");
  WiFi.begin("jup9020", "127.0.0.1");

  Serial.println ("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println ("ReConnecting");
    delay(500);
  }
  //Serial.println("");
  //Serial.println("IP address: ");
  //Serial.print(WiFi.localIP());
  //Serial.println("WiFi status:");
  //WiFi.printDiag(Serial);
  
  delay(1000);
  Serial.print('c');
  //Serial.println("inited");
  
}
void loop() {
  
  int index = 0;
  
  while (1) {
    if (Serial.available ()) {
      //Serial.println ("in");
      ttt[index++] = (char)Serial.read();      
      if (ttt[index-1] == 'Z'){
        ttt[index-1] = '\x00';
        break;
      }
    }
  }    
  
  String data = "{\"data\":\"" + (String)ttt + "\"}";
  //Serial.println(data);
   if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    
    http.begin("http://192.168.2.75:8000/broadcast"); //Specify request destination
    
    int httpCode = http.POST(data); //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      //Serial.println(payload);             //Print the response payload
 
    }
    http.end();   //Close connection

  }                                                                                                                                                             
  delay(500);

  
}
