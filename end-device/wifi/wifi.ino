#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define CONNECT 0
#define TEST 2

const char *host = "140.118.110.164";
const int port = 4444; 
const char *ssid = "Andrew";
const char *pw = "andrewli315";

int c_size = 3;
int r_size = 3;
int len;

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
        delay(500);
    }

    digitalWrite (CONNECT, 1);
}

void w_send() {
    String data = "{\"data\":\"" + (String)tile + "\"}";
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
        HTTPClient http;  //Declare an object of class HTTPClient
        
        http.begin("http://140.118.110.164:4444/broadcast"); //Specify request destination
        
        int httpCode = http.POST(data); //Send the request
        
        http.end();   //Close connection
    }

}

void loop()
{
    char ret;
    do {
        ret = 'A';
        if (Serial.available ()) {
            ret = Serial.read ();
        }
    } while (ret != 'S');
    for (int i=0; i<r_size; i++) {
        for (int o=0; o<c_size; o++) {
            char buf;
            while (!Serial.available ());
            if (i & 0x1) {
                buf = *(tile + i * c_size + c_size - o - 1) = (char)Serial.read ();
            } else {
                buf = *(tile + i * c_size + o) = (char)Serial.read (); 
            }
        }
    }

    tile[len] = '\0';
    w_send ();
    Serial.print ('E');
}
