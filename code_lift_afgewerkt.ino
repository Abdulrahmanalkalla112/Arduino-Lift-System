// Define pin numbers for the stepper driver
const int stepPin = 8;    // STEP pin
const int dirPin = 9;     // DIR pin
const int enablePin = 10; // EN pin (optional)

// Define pin numbers for the buttons (6 buttons for floors)
const int buttonPins[6] = {5, 6, 7, 4, 3, 2}; // Pins for floor buttons 0, 1, 2, 3, 4, and 5

// Define pin numbers for the floor sensors (Normally Open)
const int floorSensorPins[6] = {A5, A4, A3, A2, A1, A0}; // Pins for 6 floor sensors

// Define the steps for each floor
const int floorSteps[6] = {0, 16000, 32000, 48000, 64000, 80000}; // Steps for floor 0, 1, 2, 3, 4, and 5

// Speed settings
const int stepsPerSecond = 2000;  // Speed of the motor (steps per second)
const int delayTime = 1000000 / stepsPerSecond; // Delay time for each step in microseconds

// State variables
int currentFloor = 0; // Start at floor 0 (ground floor)
int targetFloor = 0;  // Target floor to move to

// Variables for button debouncing
int lastButtonStates[6] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}; // Last state of each button
unsigned long lastDebounceTimes[6] = {0, 0, 0, 0, 0, 0}; // Last debounce time for each button
const unsigned long debounceDelay = 50; // Debounce delay in milliseconds

void setup() {
  // Stepper motor pins
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // Enable the motor driver

  // Button pins
  for (int i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Buttons as input with pull-up resistors
  }

  // Floor sensor pins
  for (int i = 0; i < 6; i++) {
    pinMode(floorSensorPins[i], INPUT_PULLUP); // Sensors as input with pull-up resistors
  }

  Serial.begin(9600); // Start the serial monitor for debugging
  Serial.println("Lift system initialized. Ready.");
}

void loop() {
  // Detect the current floor based on the sensors
  int detectedFloor = detectCurrentFloor();
  if (detectedFloor != -1 && detectedFloor != currentFloor) {
    currentFloor = detectedFloor; // Update the current floor
    Serial.print("Lift detected at floor: ");
    Serial.println(currentFloor);
  }

  // Check for button presses and debounce
  for (int i = 0; i < 6; i++) {
    int buttonState = digitalRead(buttonPins[i]);

    if (buttonState == LOW && lastButtonStates[i] == HIGH && (millis() - lastDebounceTimes[i]) > debounceDelay) {
      targetFloor = i; // Set the target floor
      Serial.print("Button pressed. Target floor set to: ");
      Serial.println(targetFloor);
      lastDebounceTimes[i] = millis(); // Update debounce time
    }

    lastButtonStates[i] = buttonState;
  }

  // If the target floor is different from the current floor, move the lift
  if (targetFloor != currentFloor) {
    moveLift();
  }
}

// Function to detect the current floor based on floor sensors
int detectCurrentFloor() {
  for (int i = 0; i < 6; i++) {
    if (digitalRead(floorSensorPins[i]) == LOW) { // Sensor is activated (NO sensor triggered)
      return i; // Return the detected floor
    }
  }
  return -1; // No sensor is activated (error or between floors)
}

// Function to move the lift
void moveLift() {
  int stepsToMove = floorSteps[targetFloor] - floorSteps[currentFloor]; // Calculate steps to move
  int direction = (stepsToMove > 0) ? HIGH : LOW; // Determine direction (HIGH = UP, LOW = DOWN)
  stepsToMove = abs(stepsToMove); // Get the absolute step count

  Serial.print("Moving from floor ");
  Serial.print(currentFloor);
  Serial.print(" to floor ");
  Serial.println(targetFloor);

  digitalWrite(dirPin, direction); // Set the direction

  // Move the motor the required number of steps
  for (int i = 0; i < stepsToMove; i++) {
    // Continuously check sensors to ensure safety
    int detectedFloor = detectCurrentFloor();
    if (detectedFloor != -1 && detectedFloor != currentFloor) {
      currentFloor = detectedFloor; // Update current floor based on sensor
    }
    digitalWrite(stepPin, HIGH);      // Step pulse
    delayMicroseconds(delayTime);    // Delay for step duration
    digitalWrite(stepPin, LOW);       // Step pulse end
    delayMicroseconds(delayTime);    // Delay for next step
  }

  // Update the current floor after moving
  currentFloor = targetFloor;
  Serial.print("Arrived at floor: ");
  Serial.println(currentFloor);
}
