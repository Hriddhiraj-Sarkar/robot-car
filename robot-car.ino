// Pin definitions for ESP32
const int trigPin = 5;   // Ultrasonic sensor trigger pin
const int echoPin = 18;  // Ultrasonic sensor echo pin
const int motorA1 = 19;  // L298N IN1 (left motor)
const int motorA2 = 21;  // L298N IN2 (left motor)
const int motorB1 = 22;  // L298N IN3 (right motor)
const int motorB2 = 23;  // L298N IN4 (right motor)

// Variables
long duration;
float distance;
const float obstacleDistance = 20.0; // Distance threshold in cm

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
}

void loop() {
  // Measure distance
  distance = getDistance();

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check for obstacle
  if (distance < obstacleDistance && distance > 0) {
    stopMotors();
    delay(500); // Stop for 0.5 seconds
    reverseWithTurn();
    delay(1000); // Reverse and turn for 1 second
  } else {
    moveForward();
  }

  delay(100); // Small delay for stability
}

// Function to measure distance using ultrasonic sensor
float getDistance() {
  // Clear trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10us pulse to trigger
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance (speed of sound = 343 m/s or 0.0343 cm/us)
  float dist = (duration * 0.0343) / 2;
  return dist;
}

// Function to move the car forward (reversed motor direction)
void moveForward() {
  digitalWrite(motorA1, LOW);  // Left motor forward (reversed)
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);  // Right motor forward (reversed)
  digitalWrite(motorB2, HIGH);
}

// Function to stop the car
void stopMotors() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

// Function to reverse while cutting one motor (turn, reversed motor direction)
void reverseWithTurn() {
  digitalWrite(motorA1, HIGH); // Left motor reverse (reversed)
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);  // Right motor off (cut)
  digitalWrite(motorB2, LOW);
}
