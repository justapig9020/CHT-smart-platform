#include <ESP8266WiFi.h>
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
  Serial.print('c');
}
void loop() {
  
}
