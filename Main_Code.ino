#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "Airport-EXT";
const char* password = "Ricky@325";
boolean PIRstate;
boolean lastPIRstate = HIGH;
int PIR = D0;
 
void setup () {
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nConnected to WiFi");
    pinMode(PIR, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Long delay started");
    delay(30000);
    Serial.println("Long delay ended");
}
 
void loop()
{
    PIRstate = digitalRead(PIR);
    if (PIRstate != lastPIRstate)
    {
        Serial.println("Detected");
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("Message sent");
            HTTPClient http;
            http.begin("https://maker.ifttt.com/trigger/Walked/with/key/jnwSYzCxECP1GFRdOAsUZ");
            http.GET();
            http.end();
        }
    lastPIRstate = PIRstate;
    }
}
