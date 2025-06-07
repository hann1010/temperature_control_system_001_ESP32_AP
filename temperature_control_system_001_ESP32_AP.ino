// Access Point for temperature control 001
// en Hanna P 2025

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network ID
const char* ssid     = "Temp_Cont_Sys-AP";
const char* password = "987236170";

// Set web server port number
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Variable to temperatures
float heating_burner;
float heating_tanktop;
float heating_inline;
float heating_hotwater;
float outdoor;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
