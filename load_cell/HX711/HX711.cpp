#include "HX711.h"

HX711::HX711() {}

HX711::~HX711() {}

void HX711::begin(byte dout, byte pd_sck) {
  PD_SCK = pd_sck;
  DOUT = dout;

  // set pin modes
  pinMode(PD_SCK, OUTPUT);
  pinMode(DOUT, INPUT);

  // initialize PD_SCK pin
  digitalWrite(PD_SCK, LOW);
  delayMicroseconds(100);

  // read initial data
  read();
}

long HX711::read() {
  // wait for the input pin to go low
  while (digitalRead(DOUT) == HIGH);

  unsigned long data = 0;
  // read 24 bits of data
  for (unsigned char j = 0; j < 24; ++j) {
    digitalWrite(PD_SCK, HIGH);
    delayMicroseconds(1);
    digitalWrite(PD_SCK, LOW);
    bitWrite(data, 23 - j, digitalRead(DOUT));
  }

  // additional clock pulse
  digitalWrite(PD_SCK, HIGH);
  delayMicroseconds(1);
  digitalWrite(PD_SCK, LOW);

  // convert two's complement to signed long
  data ^= 0x800000;

  return (long)data;
}

long HX711::read_average(byte times) {
  long sum = 0;
  // take the average of multiple readings
  for (byte i = 0; i < times; ++i) {
    sum += read();
    delay(0);
  }
  return sum / times;
}

double HX711::get_value(byte times) {
  // subtract offset from the average reading
  return read_average(times) - OFFSET;
}

float HX711::get_units(byte times) {
  // convert reading to units using the scale
  return get_value(times) / SCALE;
}

void HX711::tare(byte times) {
  // set the offset using the average reading
  double sum = read_average(times);
  set_offset(sum);
}

void HX711::set_scale(float scale) {
  // set the scale factor
  SCALE = scale;
}

void HX711::set_offset(long offset) {
  // set the offset value
  OFFSET = offset;
}

void HX711::power_down() {
  // put the HX711 into low power mode
  digitalWrite(PD_SCK, LOW);
  digitalWrite(PD_SCK, HIGH);
}

void HX711::power_up() {
  // wake up the HX711 from low power mode
  digitalWrite(PD_SCK, LOW);
}
