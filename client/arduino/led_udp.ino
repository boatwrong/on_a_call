#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// UDP configuration
WiFiUDP udp;
const unsigned int localUdpPort = 4210;  // Port to listen on
char incomingPacket[255];

// LED pin
const int LED_PIN = 13;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to WiFi SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    // Start listening for UDP messages
    udp.begin(localUdpPort);
    Serial.printf("Now listening at IP %s UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  } else {
    Serial.println("\nFailed to connect to WiFi");
  }
}

void loop() {
  // Check if data is available
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    // Read incoming packet
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;  // Null terminate
    }
    
    Serial.printf("Received %d bytes from %s:%d\n", packetSize, udp.remoteIP().toString().c_str(), udp.remotePort());
    Serial.printf("Data: %s\n", incomingPacket);
    
    // Control LED based on received message
    if (incomingPacket[0] == '1') {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED turned ON");
    } else if (incomingPacket[0] == '0') {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED turned OFF");
    }
  }
}
