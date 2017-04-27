#include <Arduino.h>

/*
  Code based on Sparkfun WeatherShield v1.4 source from
  https://github.com/sparkfun/USB_Weather_Board/
  The libaraies included with the Sparkfun source code,
  for the temperature sensor (SHT1x) and pressure sensor  (SFE_BMP085)
  are required to be installed in the Arduino library folder
  in order to compile the code.

  In addition, the Wifly-MQTT library from
  https://github.com/greenthegarden/WiFly
  is used to provide the MQTT interface.
*/

/*
  To compile Set Tools/Board in the Arduino IDE to
  Board: "Arduino Pro or Pro Mini"
  Processor: ATmega328 (3.3V 8MHz)"

  While uploading to code to the Weather Board, remove the WiFly module and
  ensure the Comm switch is set to 'USB'

  Once code is uploaded, before powering up ensure the Comm switch is set to 'RF' and
  WiFly module is re-connected
*/

/*
  Function notes

  dtostrf function details
    dtostrf(floatVar, minStringWidthIncDecimalPoint, numVarsAfterDecimal, charBuf);

  itoa function details
    char* itoa (int val, char *buf, int radix)
    where radix is the number base, ie. 10
*/


#include "debug.h"

#include "config.h"

void publish_measurements(void)
{
  #if 0
  publish_sht15_measurements();
  if (pressureSensorStatus) {
    publish_bmp085_measurements();
  }
  publish_temt6000_measurement();
  #endif
#if ENABLE_WEATHER_METERS
  publish_weather_meter_measurement();
#endif
#if ENABLE_DHT22
  publish_dht22_measurements();
#endif
#if ENABLE_POWER_MONITOR
  publish_sunairplus_measurement();
#endif
}


/*--------------------------------------------------------------------------------------
  setup()
  Called by the Arduino framework once, before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup()
{
  Serial.begin(BAUD_RATE);      // Start hardware serial interface for debugging

  // Switch of STATUS LED
//  pinMode(STATUS_LED, OUTPUT);
//  digitalWrite(STATUS_LED, LOW);

//  rfpins_init();                // configure rf pins on weatherboard

#if ENABLE_WEATHER_METERS
  weatherboard_meters_init();

  // turn on interrupts
  interrupts();
#endif

#if ENABLE_POWER_MONITOR
  ina3221.begin();
#endif
}
/*--------------------------------------------------------------------------------------
  end setup()
  --------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
  loop()
  Arduino main loop
  --------------------------------------------------------------------------------------*/
void loop()
{
  unsigned long currentMillis = millis();

  // use arduino timer to publish reports
  if (currentMillis - previousMeasurementMillis >= MEASUREMENT_INTERVAL) {
    previousMeasurementMillis = currentMillis;
    publish_measurements();
//    reset_cummulative_measurements();
  }

#if ENABLE_WEATHER_METERS && ENABLE_WIND_MEASUREMENT_AVERAGING
  if (currentMillis - previousWindMeasurementMillis >= WIND_MEASUREMENT_INTERVAL) {
    previousWindMeasurementMillis = currentMillis;
    wind_spd_avg.addValue(windRpm);
    wind_dir_avg.addValue(get_wind_direction());
  }
#endif  /* ENABLE_WEATHER_METERS && ENABLE_WIND_DIR_AVERAGING */

#if ENABLE_WEATHER_METERS
  // handle weather meter interrupts
  static unsigned long windStopped = 0UL;

  // an interrupt occurred, handle it now
  if (gotWindSpeed) {
    gotWindSpeed = false;
    windRpm = word(tempWindRpm);
    if (windRpm > windRpmMax) {
      windRpmMax = windRpm;
    }
    windStopped = millis() + ZERODELAY;  // save this timestamp
  }

  // zero wind speed RPM if a reading does not occur in ZERODELAY ms
  if (millis() > windStopped) {
    windRpm = 0;
    windIntCount = 0;
  }
#endif  /* ENABLE_WEATHER_METERS */
}
/*--------------------------------------------------------------------------------------
  end loop()
  --------------------------------------------------------------------------------------*/
