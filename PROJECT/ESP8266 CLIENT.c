// Include necessary libraries
#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h> 

// WiFi credentials
const char* ssid = "ESP8266-Access-Point"; 
const char* password = "123456789"; 

// Server details
const char* serverName = "http://192.168.4.1/value";  

// Variables for timing
unsigned long previousMillis = 0; 
const long interval = 5000;  // 5 seconds interval

// Pin definition
int a=16; 

void setup() { 
  // Initialize serial communication
  Serial.begin(115200); 
  Serial.println(); 
  
  // Set pin 16 as output
  pinMode(16,OUTPUT); 
  
  // Connect to WiFi
  Serial.print("Connecting to "); 
  Serial.println(ssid); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  } 
  
  // Print WiFi connection details
  Serial.println(); 
  Serial.println("WiFi connected."); 
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());   
} 

void loop() { 
  unsigned long currentMillis = millis(); 
  
  // Check if it's time to make a request (every 5 seconds)
  if(currentMillis - previousMillis >= interval) { 
    // Check WiFi connection
    if (WiFi.status() == WL_CONNECTED) { 
      // Make GET request and get value
      String value = httpGETRequest(serverName); 
      Serial.println("Value: " + value); 
      
      // Control pin 16 based on received value
      if(value=="1"){ 
        Serial.println("UART"); 
        digitalWrite(16,LOW); 
        delay(5000); 
      } 
      else{ 
        digitalWrite(16,HIGH); 
        delay(5000); 
      } 
 
      // Update timing
      previousMillis = currentMillis; 
    } else { 
      // Reconnect if WiFi is disconnected
      Serial.println("WiFi Disconnected, reconnecting..."); 
      WiFi.reconnect(); 
    } 
  } 
} 

// Function to make HTTP GET request
String httpGETRequest(const char* serverName) { 
  WiFiClient client; 
  HTTPClient http; 
  
  // Initialize HTTP request
  http.begin(client, serverName); 
  
  // Send GET request
  int httpResponseCode = http.GET(); 
  String payload = "--";  
  
  // Process response
  if (httpResponseCode > 0) { 
    Serial.print("HTTP Response code: "); 
    Serial.println(httpResponseCode); 
    payload = http.getString();  
  } else { 
    Serial.print("Error code: "); 
    Serial.println(httpResponseCode); 
  } 
  
  // Close connection
  http.end(); 
  
  // Return response payload
  return payload; 
}