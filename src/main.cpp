#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
const char *ssid = "BTS_CIEL";
const char *password = "ERIR1234";
// Set LED GPIO
const int ledH = 4;
const int ledB = 2;
const int ledG = 18;
const int ledD = 19;
// Stores LED state
String ledState;

AsyncWebServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(ledH, OUTPUT);
    pinMode(ledB, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledD, OUTPUT);
    //---------------------------SPIFFS-------------------
    if (!SPIFFS.begin()) /* Démarrage du gestionnaire de fichiers SPIFFS */
    {
        Serial.println("Erreur SPIFFS...");
        return;
    }

    //-----------------------WIFI-----------------------------
    WiFi.begin(ssid, password); /* Connexion au réseau Wifi */
    Serial.print("Tentative de connexion...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }
    Serial.println("\n");
    Serial.println("Connexion etablie!");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());

    //--------------------------SERVEUR--------------------------
    /* Lorsque le serveur est actif , la page index.html est chargée */
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", String(), false); });
    // Chemin pour chager le fichier style.css
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });
    // Page pour le haut
    server.on("/haut", HTTP_GET, [](AsyncWebServerRequest *request)
              {
digitalWrite(ledH, HIGH);
digitalWrite(ledB, LOW);
digitalWrite(ledG, LOW);
digitalWrite(ledD, LOW);
request->send(SPIFFS, "/index.html", String(), false); });
    // Page pour le bas
    server.on("/bas", HTTP_GET, [](AsyncWebServerRequest *request)
              {
digitalWrite(ledB, HIGH);
digitalWrite(ledH, LOW);
digitalWrite(ledG, LOW);
digitalWrite(ledD, LOW);
request->send(SPIFFS, "/index.html", String(), false); });
    // Page pour la droite
    server.on("/droite", HTTP_GET, [](AsyncWebServerRequest *request)
              {
digitalWrite(ledD, HIGH);
digitalWrite(ledH, LOW);
digitalWrite(ledB, LOW);
digitalWrite(ledG, LOW);
request->send(SPIFFS, "/index.html", String(), false); });
// Page pour la gauche
    server.on("/gauche", HTTP_GET, [](AsyncWebServerRequest *request)
              {
digitalWrite(ledG, HIGH);
digitalWrite(ledD, LOW);
digitalWrite(ledH, LOW);
digitalWrite(ledB, LOW);
request->send(SPIFFS, "/index.html", String(), false); });
    // Démarrage du serveur
    server.begin();
}
void loop()
{
}