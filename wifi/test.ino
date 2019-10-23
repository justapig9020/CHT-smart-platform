#define LED 13

void setup()
{
    Serial.begin(115200);
    pinMode (LED, OUTPUT);
}

void loop()
{
    if (Serial.available ()) {
        if (Serial.read () == 'c') {
            digitalWrite (LED, 1);
        }  
    }
}
