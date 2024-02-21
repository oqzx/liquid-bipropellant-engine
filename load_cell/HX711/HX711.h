#ifndef HX711_h
#define HX711_h

#include <Arduino.h>

class HX711 {
  public:
    HX711(); // constructor
    virtual ~HX711(); // destructor

    void begin(byte dout, byte pd_sck); // initialize HX711

    void set_gain(byte gain = 128); // set amplification factor

    bool is_ready(); // check if HX711 is ready
    void set_offset(long offset); // set tare weight
    void set_scale(float scale = 1.f); // set conversion scale

    long read(); // read raw data
    long read_average(byte times = 10); // read average data
    double get_value(byte times = 1); // get weight value
    float get_units(byte times = 1); // get weight in specified units

    void tare(byte times = 10); // tare the scale
    void set_reading_timeout(unsigned long timeout); // set timeout for reading
    void set_interrupt_pin(byte interrupt); // set interrupt pin
    bool wait_ready_timeout(unsigned long timeout = 1000); // wait for HX711 to be ready with timeout
    void wait_ready_retry(int retries = 3, unsigned long timeout = 100); // retry waiting for HX711 to be ready

  private:
    byte PD_SCK; // power Down and Serial Clock Input Pin
    byte DOUT; // serial Data Output Pin

    byte GAIN; // amplification factor

    unsigned long OFFSET = 0; // used for tare weight
    float SCALE = 1; // used to return weight in grams, kg, ounces, whatever
    unsigned long TIMEOUT = 1000; // waits for the chip to be ready

    bool _wait_ready(unsigned long timeout = 1000); // internal method for waiting for readiness
    void _set_gain(byte gain = 128); // internal method for setting gain
    long _read(); // internal method for reading raw data
    void _shift_in(byte data_pin, byte clock_pin, byte order, byte data_bits); // internal method for shifting data
    void _set_data_mode(byte mode = 0); // internal method for setting data mode
};

#endif /* HX711_h */
