#include <DHT.h>

// Define the type of DHT sensor you're using (DHT11)
#define DHT_TYPE DHT11

// Define the pin connected to the DHT sensor
#define DHT_PIN 2

// Define the pin connected to the relay module
const int relayPin = 7;

// Temperature thresholds in Celsius
const float highTempThreshold = 23.0;  // Turn on relay above this temperature
const float lowTempThreshold = 21.0;   // Turn off relay below this temperature

// Initialize DHT sensor object
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Ensure relay is initially off
}

void loop() {
  // Read temperature in Celsius
  float temperatureC = dht.readTemperature();
  
  // Check if read failed
  if (isnan(temperatureC)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return;
  }
  
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  
  // Check temperature and control relay
  if (temperatureC > highTempThreshold) {
    digitalWrite(relayPin, HIGH);  // Turn on relay
    Serial.println("Relay ON");
  } else if (temperatureC < lowTempThreshold) {
    digitalWrite(relayPin, LOW);   // Turn off relay
    Serial.println("Relay OFF");
  }
  
  delay(2000);  // Delay between readings
}
