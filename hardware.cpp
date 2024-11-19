#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>

// Firebase configuration
FirebaseConfig config;
FirebaseAuth auth;

// Replace with your Firebase project URL and leave auth empty for anonymous authentication
#define FIREBASE_HOST "mission-possible-22dcb-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyDfKDE-PpJhQ3Tolv2vkguWqK9ZrIV5Lo8"

// WiFi credentials
const char* ssid = "hello"; // Replace with your WiFi SSID
const char* password = "12345678"; // Replace with your WiFi password

// Define pins for DHT11 sensor
#define DHTPIN 4 // GPIO4
#define DHTTYPE DHT11

// Define pin for MQ2 sensor
#define MQ2PIN 34 // Analog pin A0

// Define pins for HC-SR04 Sonar sensor
#define TRIGPIN 12 // GPIO12
#define ECHOPIN 13 // GPIO13

// Define pins for L298N Motor Driver
#define IN1 14 // GPIO14
#define IN2 27 // GPIO27

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize Firebase
FirebaseData firebaseData;

// Motor status variable
String motorStatus = "off"; // Default value

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Configure Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Initialize DHT sensor
  dht.begin();
  
  // Setup MQ2 pin
  pinMode(MQ2PIN, INPUT);
  
  // Setup sonar sensor pins
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  // Setup motor driver pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  Serial.println("ESP32 with DHT11, MQ2, Sonar Sensor, and Motor Driver");
}

void loop() {
  // Reading temperature and humidity from DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Reading gas level from MQ2 sensor
  int gasLevel = analogRead(MQ2PIN);

  // Reading distance from Sonar sensor
  long duration;
  float distance;

  // Trigger the sonar sensor
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  // Measure the echo time
  duration = pulseIn(ECHOPIN, HIGH);
  distance = duration * 0.034 / 2; // Convert to distance in centimeters

  // Check if DHT readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%, Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
  }

  Serial.print("Gas Level (MQ2): ");
  Serial.println(gasLevel);

  Serial.print("Distance (Sonar): ");
  Serial.print(distance);
  Serial.println(" cm");

  // Update sensor data in Firebase
  if (Firebase.setFloat(firebaseData, "/sensorData/humidity", humidity)) {
    Serial.println("Humidity updated in Firebase");
  } else {
    Serial.print("Failed to update humidity: ");
    Serial.println(firebaseData.errorReason());
  }
  
  if (Firebase.setFloat(firebaseData, "/sensorData/temperature", temperature)) {
    Serial.println("Temperature updated in Firebase");
  } else {
    Serial.print("Failed to update temperature: ");
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.setInt(firebaseData, "/sensorData/gasLevel", gasLevel)) {
    Serial.println("Gas Level updated in Firebase");
  } else {
    Serial.print("Failed to update gas level: ");
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.setFloat(firebaseData, "/sensorData/distance", distance)) {
    Serial.println("Distance updated in Firebase");
  } else {
    Serial.print("Failed to update distance: ");
    Serial.println(firebaseData.errorReason());
  }

  // Read motor status from Firebase
  if (Firebase.getString(firebaseData, "/motorStatus")) {
    motorStatus = firebaseData.stringData();
    Serial.print("Motor Status from Firebase: ");
    Serial.println(motorStatus);

    // Control motor based on motorStatus
    if (motorStatus == "on") {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      Serial.println("Motor is ON");
    } else {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      Serial.println("Motor is OFF");
    }
  } else {
    Serial.print("Failed to get motor status: ");
    Serial.println(firebaseData.errorReason());
  }

  // Delay to avoid flooding the serial monitor
  delay(2000);
}
