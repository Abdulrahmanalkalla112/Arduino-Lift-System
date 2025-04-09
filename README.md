# Arduino Lift Systeem 🚀

## 📌 Functies
- Ondersteuning voor 6 verdiepingen (0 t/m 5)  
- Nauwkeurige beweging met stepper motor en driver  
- Verdiepingskeuze via drukknoppen met debounce-logica  
- Positiedetectie met normaal open (NO) sensoren  

## 🛠️ Benodigde Componenten
- Arduino Uno of Nano  
- Stepper motor met driver (bijv. A4988)  
- Eindschakelaars als vloersensoren  
- Drukknoppen voor verdiepingselectie  

## 📜 Code Uitleg
Het bestand `lift_system.ino` regelt:  
- Detectie van knopindrukken  
- Beweging van de stepper motor  
- Vloerdetectie en veiligheidcontroles  

## 🚀 Installatie
1. Upload `lift_system.ino` naar de Arduino  
2. Verbind de stepper driver, knoppen en sensoren  
3. Schakel de voeding in en test het systeem  
