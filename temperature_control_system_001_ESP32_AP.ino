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

// Assign input variables to GPIO pins
const int input25 = 25;
const int input26 = 26;
const int input27 = 27;

// Variable to temperatures
float heating_burner;
float heating_tanktop;
float heating_inline;
float heating_hotwater;
float outdoor;

// Define TX and RX pins for UART (change if needed)
#define TXD1 19
#define RXD1 21

// Use Serial1 for UART communication
HardwareSerial mySerial(2);

void setup() {
  Serial.println("Setup start.. ");
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, RXD1, TXD1);  // UART setup

  // Initialize the inpur variables as input
  pinMode(input25, INPUT);
  pinMode(input26, INPUT);
  pinMode(input27, INPUT);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP("");
  WiFi.softAP(ssid, password);
  //WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP address is: ");
  Serial.println(IP);

  server.begin();

  Serial.println("Setup done");
}

void loop() {
  testReadData(); // for Uart testing
  //readData(); // for Uart read all temperatures
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

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: left;}");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println("</style></head>");

            // Web Page Heading
            client.println("<body><h1>Access Point for temperature control 001</h1>");

            // Web Page content
            client.print("<p>Heating burner: ");
            client.print(heating_burner);
            client.println("</p>");
            client.print("<p>Heating tanktop: ");
            client.print(heating_tanktop);
            client.println("</p>");
            client.print("<p>Heating inline: ");
            client.print(heating_inline);
            client.println("</p>");
            client.print("<p>Heating hotwater: ");
            client.print(heating_hotwater);
            client.println("</p>");
            client.print("<p>Outdoor: ");
            client.print(outdoor);
            client.println("</p>");
            client.print("<p>Up time (min): ");
            client.print(millis()/60000);
            client.println("</p>");
            client.print("<p>Version: TCS_001_2025 ");
            client.println("</p>");

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();

            // Break out of the while loop
            break;

          } else { // if you got a newline, then clear currentLine
          currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
        currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void testReadData() {
  // Check if data is available to read
  if (mySerial.available()) {
    // Read data and display it
    String message = mySerial.readStringUntil('\n');
    Serial.println("Received: " + message);
  }
}

void readData() {
  // Check if data is available to read
  if (mySerial.available()) {
    // Read data to dataTemp
    String dataTemp = mySerial.readStringUntil('\n');
    if (input25 == false && input26 == false && input27 == false) { //00H
      heating_burner = dataTemp;
    }
    if (input25 == true && input26 == false && input27 == false) { //01H
      heating_tanktop = dataTemp;
    }
    if (input25 == false && input26 == true && input27 == false) { //02H
      heating_inline = dataTemp;
    }
    if (input25 == true && input26 == true && input27 == false) { //03H
      heating_hotwater = dataTemp;
    }
    if (input25 == false && input26 == false && input27 == true) { //04H
      outdoor = dataTemp;
    }
  }
}