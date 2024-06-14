// Define constants for sensor pin and LED pin
const int sensorPin = A2;
const int ledPin = 10;

// Variables to track clap count and timing
int clap = 0;
long detectionRangeStart = 0;
long detectionRange = 0;
boolean statusLights = false;

// Variables for laser system
const int ldrPin = A0;   // analog pin to which LDR is connected
int ldrThreshold = 70;   // set the threshold for laser interruption
int ldrValue = 0;        // variable to store LDR values
const int buzzer = 9;

// Setup function runs once at the beginning
void setup() {
  // Set the sensor pin as INPUT and LED pin as OUTPUT
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Laser Setup
  Serial.begin(9600);  // start the serial monitor
}

// Loop function runs repeatedly
void loop() {
  // Clap Switch Logic
  int statusSensor = digitalRead(sensorPin);

  if (statusSensor == LOW) {
    if (clap == 0) {
      detectionRangeStart = detectionRange = millis();
      clap++;
    } else if (clap > 0 && millis() - detectionRange >= 50) {
      detectionRange = millis();
      clap++;
    }
  }

  if (millis() - detectionRangeStart >= 400) {
    if (clap == 2) {
      statusLights = !statusLights;
      digitalWrite(ledPin, statusLights ? HIGH : LOW);
    }
    clap = 0;
  }
}