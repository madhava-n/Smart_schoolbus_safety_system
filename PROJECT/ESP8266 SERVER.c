// Blynk template and authentication details
#define BLYNK_TEMPLATE_ID "TMPL32KjgGstq" 
#define BLYNK_TEMPLATE_NAME "Heart Rate" 
#define BLYNK_AUTH_TOKEN "2ws_9yh16G8Tk_T9j_2Z1hlD1Wch2MYx" 

// Telegram bot token and chat ID
#define "7004804455:AAEYCtW2SwxNhKaQxNU3iSLvpduKJWFAymQ" 
#define CHAT_ID "2040191695" 

// Include necessary libraries
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 
#include <UniversalTelegramBot.h> 
#include <WiFiClientSecure.h> 
#include <DHT.h> 
#include "ESPAsyncWebServer.h" 

// Define DHT sensor pins and type
#define DHTPIN D4 
#define DHTTYPE DHT11 
BOT_TOKEN 

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE); 

// Define pins for pulse sensor and buzzer
const int pulsePin = A0; 
const int buzzer = D5; 

// Blynk authentication token
char auth[] = "2ws_9yh16G8Tk_T9j_2Z1hlD1Wch2MYx"; 

// WiFi credentials
char ssid[] = "Wattstrons"; 
char pass[] = "Wattstrons10823"; 

// Telegram bot token and chat ID
char 
telegramBotToken[] 
"7004804455:AAEYCtW2SwxNhKaQxNU3iSLvpduKJWFAymQ"; 
char telegramChatID[] = "2040191695"; 

// Initialize WiFi client and Telegram bot
WiFiClientSecure client; 
UniversalTelegramBot bot(telegramBotToken, client); 

// Access Point credentials
const char* AP_ssid = "ESP8266-Access-Point"; 
const char* AP_password = "123456789"; 

// Initialize AsyncWebServer
AsyncWebServer server(80); 

// Variable to track heart attack detection
int heartAttackDetected = 0;   
= 

// Function to read heart attack detection status
String readValue() { 
  return String(heartAttackDetected); 
} 

void setup() { 
  // Initialize serial communication
  Serial.begin(9600); 
  
  // Set buzzer pin as output
  pinMode(buzzer, OUTPUT); 
  
  // Initialize DHT sensor
  dht.begin(); 
  
  // Connect to WiFi
  WiFi.begin(ssid, pass); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000); 
    Serial.println("Connecting to WiFi..."); 
  } 
  Serial.println("Connected to WiFi"); 
  
  // Initialize Blynk
  Blynk.begin(auth, ssid, pass); 
  
  // Set WiFi client as insecure (not recommended for production)
  client.setInsecure(); 
  
  // Set up Access Point
  WiFi.softAP(AP_ssid, AP_password); 
  IPAddress IP = WiFi.softAPIP(); 
  Serial.print("AP IP address: "); 
  Serial.println(IP); 
  
  // Set up web server route
  server.on("/value", HTTP_GET, [](AsyncWebServerRequest *request){ 
    request->send(200, "text/plain", readValue().c_str()); 
  }); 
  
  // Start web server
  server.begin(); 
} 

void loop() { 
  // Run Blynk
  Blynk.run(); 
  
  // Read pulse sensor value
  int a = analogRead(pulsePin); 
  int b = abs(60 - (a / 16)); 
  
  // Send pulse data to Blynk
  Blynk.virtualWrite(V0, b); 
  Blynk.virtualWrite(V3, a); 
 
  // Read temperature and humidity
  float humidity = dht.readHumidity(); 
  float temperature = dht.readTemperature(); 
 
  // Send temperature and humidity data to Blynk if valid
  if (!isnan(humidity) && !isnan(temperature)) { 
    Blynk.virtualWrite(V1, temperature); 
    Blynk.virtualWrite(V2, humidity); 
    Serial.print("Temperature: "); 
    Serial.print(temperature); 
    Serial.print(" °C, Humidity: "); 
    Serial.print(humidity); 
    Serial.println(" %"); 
  } else { 
    Serial.println("Failed to read from DHT sensor!"); 
  } 
 
  // Print pulse sensor values
  Serial.print("Analog Value: "); 
  Serial.println(b); 
  Serial.println(a); 
 
  // Check for heart attack condition
  if (a < 10 || b < 10) { 
    Serial.println("ON - Heart Attack Detected!"); 
    heartAttackDetected = 1;   
    digitalWrite(buzzer, HIGH); 
    delay(2000); 
    // Send Telegram message
    String message = "Emergency! Heart attack detected."; 
    bot.sendMessage(telegramChatID, message, ""); 
  } else { 
    Serial.println("OFF - Normal"); 
    heartAttackDetected = 0;  
    // Beep buzzer briefly
    digitalWrite(buzzer, HIGH); 
    delay(80); 
    digitalWrite(buzzer, LOW); 
  } 
 
  // Wait for 1 second before next loop
  delay(1000); 
}