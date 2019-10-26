#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define CONNECT 0
#define TEST 2

const char *host = "172.20.10.2";
const int port = 8000; 
const char *ssid = "Andrew";
const char *pw = "andrewli315";
int c_size = 3;
int r_size = 3;
int len;
int d;
char *tile;
char tmp;

WiFiClient client;
void setup()
{
    pinMode (CONNECT, OUTPUT);
    pinMode (TEST, OUTPUT);
    digitalWrite (TEST, 1);
    Serial.begin(115200);
    WiFi.begin(ssid, pw);
    len = c_size * r_size;
    tile = (char *)malloc (len+1);
    memset (tile, 0, len);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println ("connecting");
        delay(500);
    }
    Serial.println ("connected");
    digitalWrite (CONNECT, 1);
    digitalWrite (TEST, 0);
    d = 500;
}

void loop()
{
    if (Serial.available ()) {
        char r;
        r = Serial.read ();
        d = (r-'0') * 1000;
    }
    delay (d);
    memset (tile, 'A', len);
    tile[len] = '\0';
    digitalWrite (TEST, 1);
    String data = "{\"data\":\"" + (String)tile + "\"}";
    //Serial.println(data);
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
        HTTPClient http;  //Declare an object of class HTTPClient
        
        http.begin("http://140.118.110.164:4444/broadcast"); //Specify request destination
        
        int httpCode = http.POST(data); //Send the request
        /*if (httpCode > 0) { //Check the returning code

            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);             //Print the response payload
        
        }*/
        http.end();   //Close connection
    }
    Serial.println ("sent");
}
