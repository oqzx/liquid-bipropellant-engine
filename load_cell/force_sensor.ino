#include <Arduino.h>
#include "HX711.h"

// define pins for HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 4;

HX711 scale; // create an instance of the HX711 class

void setup() {
  Serial.begin(57600); // initialize serial communication
  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // initialize the scale

  // print initial scale readings
  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20)); // print average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5)); // print average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1); // print average of 5 readings from the ADC minus tare weight (not set) divided by the SCALE parameter (not set yet)

  scale.set_scale(14100); // set the scale (this value is obtained by calibrating the scale with known weights)
  //scale.set_scale(); // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare(); // reset the scale to 0

  // print scale readings after setup
  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20)); // print average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5)); // print average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1); // print average of 5 readings from the ADC minus tare weight, divided by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.println(scale.get_units(), 4); // print one reading of weight measurement
  delay(0); // delay before taking the next reading
}
