
#include <WiFi.h>


const char* ssid     = "Rares";
const char* password = "123456789";

const char* ssidToConnect     = "Rares";
const char* passwordToConnect = "123456789";
int speed = 150;

// Set web server port number to 80
WiFiServer server(80);

const byte led_gpio = 17; // the PWM pin the LED is attached to
const byte led_gpio1 = 5; // the PWM pin the LED is attached to

const byte back1 = 16; // the PWM pin the LED is attached to
const byte back2 = 18; // the PWM pin the LED is attached to

// Variable to store the HTTP request
String header;

void setup() {
  Serial.begin(115200);
  
  //-------------------MOTORS SETUP-----------------
  
  ledcAttachPin(led_gpio, 0); // assign a led pins to a channel
  ledcAttachPin(led_gpio1, 1); // assign a led pins to a channel
  ledcAttachPin(back1, 2); // assign a led pins to a channel
  ledcAttachPin(back2, 3); // assign a led pins to a channel
  ledcSetup(0, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(1, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(3, 4000, 8); // 12 kHz PWM, 8-bit resolution

  

    Serial.print("Setting Access Point…");

    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("Our IP address: ");
    Serial.println(IP);
  
    server.begin();

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssidToConnect);

    WiFi.begin(ssidToConnect, passwordToConnect);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address for controlling this robot is : ");
    Serial.println(WiFi.localIP());
}

void loop(){


  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
        
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            
            // Web Page
            client.println("<body><h1>Control the fantastic robot :)) </h1>");
            client.print("<h2 class='button'><a href=\"/F\">go forward</a></h2>");
            client.print("<h2 class='button'><a href=\"/S\">to stop</a></h2>");
            client.print("<h2 class='button'><a href=\"/B\">go back</a></h2>");
            client.print("<h2 class='button'><a href=\"/R\">turn right</a></h2>");
            client.print("<h2 class='button'><a href=\"/L\">turn left</a></h2>");
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
        
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /F")) {
          ledcWrite(0, 0); 
          ledcWrite(1, speed); 
          ledcWrite(2, speed); 
          ledcWrite(3, 0);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /S")) {
          ledcWrite(0, 0); 
          ledcWrite(1, 0); 
          ledcWrite(2, 0); 
          ledcWrite(3, 0);                  // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /B")) {
          ledcWrite(0, speed); 
          ledcWrite(1, 0); 
          ledcWrite(2, 0); 
          ledcWrite(3, speed);                  // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /R")) {
          ledcWrite(0, 0); 
          ledcWrite(1, 0); 
          ledcWrite(2, speed); 
          ledcWrite(3, speed); 
        }
        if (currentLine.endsWith("GET /L")) {
           ledcWrite(0, speed); 
           ledcWrite(1, speed); 
           ledcWrite(2, 0); 
           ledcWrite(3, 0);             // GET /L turns the LED off
        }
      }
    }
    
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  } 
}
