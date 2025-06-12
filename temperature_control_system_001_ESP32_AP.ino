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
 // Listen for incoming clients
  WiFiClient client = server.available();

  // If a new client connects
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    // loop while the client's connected
    while (client.connected()) {
      // if there's bytes to read from the client,
      if (client.available()) {
        // read a byte, then
        char c = client.read();
        Serial.write(c);
        header += c;
        // if the byte is a newline character
        if (c == '\n') {
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // palce for functional code
}
