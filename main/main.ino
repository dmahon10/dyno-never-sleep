#include <WiFi.h>

// Wifi config
const char* ssid     = "YourWifiName";
const char* password = "YourWifiPassword";

// HTTP request config
const char* host = "example.com";
String request = "GET / HTTP/1.1\r\nHost: " + String(host) + "\r\nConnection: close\r\n\r\n";
const int httpPort = 80;
const int timeout_limit = 5000;

// Repetition config 
// (Heroku dyno sleeps after 30 minutes of inactivity)
const int period = 60000 * 20; // 60000 ms == 1 minute

void setup()
{   
    // Set baud rate for serial communication
    Serial.begin(115200);
    delay(100);

    // Print to serial
    Serial.print("\n\nConnecting to ");
    Serial.println(ssid);

    // Connect to wifi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}


void loop()
{ 

    // Wait period ms between requests
    delay(period);

    Serial.println("\nConnecting to ");
    Serial.println(host);

    // Establish TCP connections
    WiFiClient client;
    if (!client.connect(host, httpPort)) {
        Serial.println("Connection failed");
        return;
    }

    // Print HTTP request to serial
    Serial.println("\nRequest:");
    Serial.print(request);

    // Send HTTP request
    client.print(request);
    
    // Check for timeout
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > timeout_limit) {
            Serial.println("\n***********************");
            Serial.println("\n<<< Client Timeout! >>>");
            Serial.println("\n***********************");
            client.stop();
            return;
        }
    }

    // Read the response and print it to serial
    Serial.println("Response:");
    while(client.available()) {
        Serial.print(client.readStringUntil('\r'));
    }

    Serial.println("\nClosing connection");
}
