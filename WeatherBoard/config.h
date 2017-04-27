#ifndef XBEEWEATHERBOARD_CONFIG_H_
#define XBEEWEATHERBOARD_CONFIG_H_


#include "debug.h"

#include "jsonConfig.h"

const byte FLOAT_DECIMAL_PLACES               = 1;

const byte BUFFER_SIZE = 20;
char topicBuffer[BUFFER_SIZE];
char payloadBuffer[BUFFER_SIZE];

// Serial parameters
const unsigned long BAUD_RATE                 = 9600;

// program constants
const unsigned long MEASUREMENT_INTERVAL_SECS = 10UL;
const unsigned long MEASUREMENT_INTERVAL      = MEASUREMENT_INTERVAL_SECS * 1000UL;   // conversion to milliseconds

// global variable definitions
unsigned long previousMeasurementMillis       = 0UL;
unsigned long previousWindMeasurementMillis   = 0UL;

const char END_STRING[] PROGMEM = "end";
const char ERROR_STRING[] PROGMEM = "error";
const char OK_STRING[] PROGMEM = "ok";
const char SENSOR_STRING[] PROGMEM = "sensor";
const char START_STRING[] PROGMEM = "start";
const char SYSTEM_STRING[] PROGMEM = "system";

PGM_P const STRINGS[] PROGMEM = {
  END_STRING,
  ERROR_STRING,  // idx = 1
  OK_STRING,     // idx = 0
  SENSOR_STRING,
  START_STRING,  // idx = 2
  SYSTEM_STRING,
};

/* SUNAIRPLUS_TOPICS indices, must match table above */
typedef enum {
  END_STRING_IDX = 0,
  ERROR_STRING_IDX = 1,
  OK_STRING_IDX = 2,
  SENSOR_STRING_IDX = 3,
  START_STRING_IDX = 4,
  SYSTEM_STRING_IDX = 5,
} strings;

const char SYSTEM_VALUE[] PROGMEM = "weatherboard";

PGM_P const VALUES[] PROGMEM = {
  SYSTEM_VALUE,
};

/* SUNAIRPLUS_TOPICS indices, must match table above */
typedef enum {
  SYSTEM_VALUE_IDX = 0,
} values;

// Define use of weather board sensors
#define ENABLE_WEATHER_METERS     false
#define ENABLE_WIND_DIR_AVERAGING false
#define ENABLE_EXTERNAL_LIGHT     false

//#include "weatherBoardConfig.h"

// Define user of external sensors
#define ENABLE_POWER_MONITOR      true    // for use with SwitchDoc Lab SunAirPlus
#define ENABLE_DHT22              false

#if ENABLE_POWER_MONITOR
#include "sunAirPlusConfig.h"
#endif

#if ENABLE_DHT22
#include "dht22Config.h"
#endif


#endif  /* XBEEWEATHERBOARD_CONFIG_H_ */
