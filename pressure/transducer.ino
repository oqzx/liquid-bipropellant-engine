#include <Arduino.h>

const int pressureInput = A1; // analog input pin for the pressure transducer
const int pressureZero = 102.4; // analog reading of pressure transducer at 0 psi
const int pressureMax = 921.6; // analog reading of pressure transducer at 100 psi
const int pressuretransducermaxPSI = 200; // maximum PSI value of the transducer
const int baudRate = 9600; // baud rate for serial communication
const int sensorreadDelay = 50; // delay for sensor readings in milliseconds

float pressureValue = 0; // variable to store pressure value

void setup() {
  Serial.begin(baudRate); // initialize serial communication
}

void loop() {
  pressureValue = analogRead(pressureInput); // read analog value from pressure transducer
  pressureValue = ((pressureValue - pressureZero) * pressuretransducermaxPSI) / (pressureMax - pressureZero) + 13.3; // convert analog reading to PSI
  Serial.print(pressureValue, 1); // print pressure value to serial monitor
  Serial.println("  psi"); // print unit label
  delay(sensorreadDelay); // delay between readings
}
