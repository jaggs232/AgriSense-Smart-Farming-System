#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD and DHT Sensor Setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address and size
#define DHTPIN 2                    // DHT11 data pin
#define DHTTYPE DHT11               // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);           // Initialize DHT sensor

// Pin Definitions
const int moistureSensorPin = A0;
const int gasSensorPin = A1;
const int relayPin = 3;        // Pin to control relay
const int waterLevelPin = 6;   // Water level sensor pin

int displayState = 0; // State for display switching

void setup() {
  pinMode(relayPin, OUTPUT);        // Set relay pin as output
  pinMode(waterLevelPin, INPUT);    // Set water level pin as input

  lcd.begin(16, 2);                 // Initialize LCD display
  lcd.backlight();                  // Turn on backlight

  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();

  Serial.begin(9600);  // Start serial communication for debugging
  dht.begin();          // Initialize DHT sensor
}

void loop() {
  controlMotorAndRelay();  // Control relay based on soil moisture

  switch (displayState) {
    case 0: displayMoisture(); break;
    case 1: displayCO2(); break;
    case 2: displayAgriSense(); break;
    case 3: showTeamCredits(); break;
  }

  displayState = (displayState + 1) % 4; // Rotate display states
  delay(1500);
}

// Function to control motor and relay based on soil moisture
void controlMotorAndRelay() {
  int sensorValue = analogRead(moistureSensorPin);
  int moisturePercent = map(sensorValue, 1018, 413, 0, 100);

  if (moisturePercent <= 40) {
    digitalWrite(relayPin, LOW);  // Turn motor ON (assuming active-low)
    displayMessage("Moisture Low", "Motor ON");
  } else {
    digitalWrite(relayPin, HIGH); // Turn motor OFF
    displayMessage("Moisture High", "Motor OFF");
  }

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");
}

// Display soil moisture percentage
void displayMoisture() {
  int sensorValue = analogRead(moistureSensorPin);
  int moisturePercent = map(sensorValue, 1018, 413, 0, 100);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture:");
  lcd.setCursor(0, 1);
  lcd.print(moisturePercent);
  lcd.print("%");

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");
}

// Display CO2 level
void displayCO2() {
  int sensorValue = analogRead(gasSensorPin);
  float ppm = map(sensorValue, 1065, 400, 0, 960);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CO2 Level:");
  lcd.setCursor(0, 1);
  lcd.print(ppm);
  lcd.print(" ppm");

  Serial.print("CO2: ");
  Serial.print(ppm);
  Serial.println(" ppm");
}

// Display AGRI SENSE and SMART FARMING
void displayAgriSense() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AGRI SENSE");
  lcd.setCursor(0, 1);
  lcd.print("SMART FARMING");
  delay(1500);
}

// Display team credits
void showTeamCredits() {
  const char* credits[] = {"PROJECT DONE BY", "JAGANATHAN V", "MRITHULA R", "LACSHAN KK", "KEERTHIVASAN A"};
  for (int i = 0; i < 5; i++) {
    displayMessage(credits[i], "");
    delay(600);
  }
}

// Display message on LCD
void displayMessage(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(1000);
}

// Check water level and log it
void checkWaterLevel() {
  int waterLevel = digitalRead(waterLevelPin);

  if (waterLevel == LOW) {
    digitalWrite(relayPin, HIGH);  // Water level full, turn motor OFF
    Serial.println("Water Level: Full (Motor OFF)");
  } else {
    digitalWrite(relayPin, LOW);   // Water level low, turn motor ON
    Serial.println("Water Level: Low (Motor ON)");
  }
  delay(400);
}
