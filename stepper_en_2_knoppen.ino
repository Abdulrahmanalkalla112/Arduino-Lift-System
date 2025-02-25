
// Define pin numbers for the stepper driver and buttons
const int stepPin = 8;   // STEP pin
const int dirPin = 9;    // DIR pin
const int enablePin = 10; // EN pin (optional)
const int button1Pin = 2; // Button 1 Pin
const int button2Pin = 3; // Button 2 Pin

// Variables for button states
int button1State = 0;
int button2State = 0;

void setup() {
  // Set the stepper control pins as outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Set the button pins as inputs
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  // Enable the driver (assuming LOW enables)
  digitalWrite(enablePin, LOW); // LOW = Enabled

  // Set the initial direction for the stepper motor
  digitalWrite(dirPin, HIGH); // HIGH = Clockwise (change as needed)
}

void loop() {
  // Read the state of Button 1
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  // If Button 1 is pressed, move 50 steps at a slower speed
  if (button1State == LOW) {  // Button 1 is active when pressed (LOW)
    moveStepper(3000, 80);  // Move 50 steps with slower speed (1000 microseconds per step)
  }

  // If Button 2 is pressed, move 50 steps at a faster speed
  if (button2State == LOW) {  // Button 2 is active when pressed (LOW)
    moveStepper(6000, 80);   // Move 50 steps with faster speed (200 microseconds per step)
  }
}

// Function to move the stepper motor a given number of steps at a specified speed (delay in microseconds)
void moveStepper(int steps, int delayTime) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);  // Trigger step pulse
    delayMicroseconds(delayTime); // Wait for the defined delay time
    digitalWrite(stepPin, LOW);   // End step pulse
    delayMicroseconds(delayTime); // Wait for the defined delay time
  }
}
