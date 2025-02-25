
// Define pin numbers for the stepper driver and buttons
const int stepPin = 8;    // STEP pin
const int dirPin = 9;     // DIR pin
const int enablePin = 10; // EN pin (optional)
const int button1Pin = 2; // Button 1 Pin (Floor 1)
const int button2Pin = 3; // Button 2 Pin (Floor 2)
const int reedNCPin = 4;  // Reed sensor (Normally Closed)
const int reedNOPin = 5;  // Reed sensor (Normally Open)

// Variables for button states
int button1State = HIGH;
int lastButton1State = HIGH;
int button2State = HIGH;
int lastButton2State = HIGH;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
const unsigned long debounceDelay = 50;

// Variables for reed sensor states
int reedNCState = HIGH;    // NC reed sensor state
int lastReedNCState = HIGH;

int reedNOState = HIGH;    // NO reed sensor state

void setup() {
  // Set the stepper control pins as outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Set the reed sensor and button pins as inputs
  pinMode(reedNCPin, INPUT_PULLUP);  // Reed sensor (normally closed)
  pinMode(reedNOPin, INPUT_PULLUP);  // Reed sensor (normally open)
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  // Enable the driver (assuming LOW enables)
  digitalWrite(enablePin, LOW); // LOW = Enabled

  // Set the initial direction for the stepper motor
  digitalWrite(dirPin, HIGH); // HIGH = Clockwise (you can change this if needed)
}

void loop() {
  // Read reed sensor states
  reedNCState = digitalRead(reedNCPin);
  reedNOState = digitalRead(reedNOPin);

  // If the normally closed reed sensor is open, stop the motor
  if (reedNCState == HIGH) {
    stopStepper();  // Stop motor if NC sensor is open
    return;         // Exit loop to ensure motor doesn't run
  }

  // If the normally open reed sensor is closed, stop the motor
  if (reedNOState == LOW) {
    stopStepper();  // Stop motor if NO sensor is closed
    return;         // Exit loop to ensure motor doesn't run
  }

  // Handle Button 1 (Floor 1)
  int currentButton1State = digitalRead(button1Pin);
  if (currentButton1State == LOW && lastButton1State == HIGH && (millis() - lastDebounceTime1) > debounceDelay) {
    moveStepper(10000, 100, false);  // Move 1000 steps (Floor 1)
    lastDebounceTime1 = millis();
  }
  lastButton1State = currentButton1State;

  // Handle Button 2 (Floor 2)
  int currentButton2State = digitalRead(button2Pin);
  if (currentButton2State == LOW && lastButton2State == HIGH && (millis() - lastDebounceTime2) > debounceDelay) {
    moveStepper(5000, 100, false);  // Move 2000 steps (Floor 2)
    lastDebounceTime2 = millis();
  }
  lastButton2State = currentButton2State;
}

// Function to move the stepper motor a given number of steps at a specified speed (delay in microseconds)
void moveStepper(int steps, int delayTime, bool reverse) {
  // Set motor direction
  if (reverse) {
    digitalWrite(dirPin, LOW);  // Reverse direction
  } else {
    digitalWrite(dirPin, HIGH); // Forward direction
  }

  for (int i = 0; i < steps; i++) {
    // Read reed sensor states during movement
    reedNCState = digitalRead(reedNCPin);
    reedNOState = digitalRead(reedNOPin);

    // Stop if either reed sensor triggers a stop condition
    if (reedNCState == HIGH || reedNOState == LOW) {
      stopStepper();
      return; // Exit function
    }

    digitalWrite(stepPin, HIGH);  // Trigger step pulse
    delayMicroseconds(delayTime); // Wait for the defined delay time
    digitalWrite(stepPin, LOW);   // End step pulse
    delayMicroseconds(delayTime); // Wait for the defined delay time
  }
}

// Function to stop the stepper motor
void stopStepper() {
  digitalWrite(stepPin, LOW);  // Stop step pulses
}

  
