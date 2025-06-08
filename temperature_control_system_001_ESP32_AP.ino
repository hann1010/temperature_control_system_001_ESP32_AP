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
  Serial.println("Setup start.. ");
  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP address is: ");
  Serial.println(IP);

  server.begin();

  Serial.println("Setup done");
}

void loop() {
  // put your main code here, to run repeatedly:

}
