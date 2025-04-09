void testMotor() {
  // Print naar de seriële monitor dat de motor omhoog gaat bewegen
  Serial.println("Motor beweegt omhoog.");

  // Stel de draairichting van de motor in op 'omhoog'
  digitalWrite(dirPin, HIGH);

  // Laat de motor 1000 stappen omhoog bewegen
  for (int i = 0; i < 1000; i++) {
    digitalWrite(stepPin, HIGH);          // Zet de stap-pin hoog (begin van een stap)
    delayMicroseconds(500);               // Wacht 500 microseconden
    digitalWrite(stepPin, LOW);           // Zet de stap-pin laag (eind van een stap)
    delayMicroseconds(500);               // Wacht nog eens 500 microseconden
  }

  // Print naar de seriële monitor dat de motor omlaag gaat bewegen
  Serial.println("Motor beweegt omlaag.");

  // Verander de draairichting van de motor naar 'omlaag'
  digitalWrite(dirPin, LOW);

  // Laat de motor 1000 stappen omlaag bewegen
  for (int i = 0; i < 1000; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}
