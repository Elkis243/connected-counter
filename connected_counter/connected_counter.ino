#include <HTTPClient.h>
#include "ACS712.h"
#include "ZMPT101B.h"
#include "EmonLib.h"
#include <WiFi.h>

HTTPClient http;
ACS712 currentSensor(32);
ZMPT101B voltageSensor(35);
EnergyMonitor emon;

float V, I, P;
double E;
unsigned long t, y;
String apiEndpoint = "http://192.168.91.143:8000/counter/";

void setupWifi(char *ssid, char *password);
void emonlib();

void setup() {
   analogReadResolution(10);
   Serial.begin(115200);
   
   emon.current(32, 200);
   emon.voltage(35, 268.97, 1.7);

   t = millis();
   E = 0;

   setupWifi("Personal work", "kisWifi2024");
}

void loop() {
   emonlib();
   delay(5000);
}


void setupWifi(char *ssid, char *password) {
    WiFi.begin(ssid, password);
    int runtime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println(WiFi.status());
        Serial.print("Tentative de connexion à WiFi...");
        if (millis() > runtime + 10000) {
            Serial.println("Échec de la connexion à WiFi");
            return;
        }
    }
    Serial.println("Connecté à WiFi");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());
}


void emonlib() {
   emon.calcVI(20, 2000);
   V = emon.Vrms;
   I = (emon.calcIrms(1480)) / 10.0;
   P = (V * I) / 1000.0;
   y = millis();
   double deltaT = (y - t) / 3600000.0;
   E += P * deltaT;
   t = y;

   http.begin(apiEndpoint);
   http.addHeader("Content-Type", "application/json");
   String requestBody = "{\"intensity\":\"" + String(I, 2) + "\",\"voltage\":\"" + String(V, 2) + "\",\"power\":\"" + String(P, 2) + "\",\"energy\":\"" + String(E, 2) + "\"}";
   int httpResponseCode = http.PUT(requestBody);

   if (httpResponseCode > 0) {
        Serial.print("Réponse du serveur : ");
        Serial.println(httpResponseCode);
   } else {
        Serial.println("Erreur de connexion au serveur");
   }

   http.end();
}