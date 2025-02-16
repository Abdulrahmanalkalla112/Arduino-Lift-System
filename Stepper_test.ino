void testMotor() {
  Serial.println("Motor beweegt omhoog.");
  digitalWrite(dirPin, HIGH); 
  for (int i = 0; i < 1000; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500); 
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  Serial.println("Motor beweegt omlaag.");
  digitalWrite(dirPin, LOW); 
  for (int i = 0; i < 1000; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500); 
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}
