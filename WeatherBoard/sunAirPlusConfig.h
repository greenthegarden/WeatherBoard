#ifndef XBEEWEATHERBOARD_SUNAIRPLUSCONFIG_H_
#define XBEEWEATHERBOARD_SUNAIRPLUSCONFIG_H_


#include <Wire.h>
#include <SDL_Arduino_INA3221.h>

SDL_Arduino_INA3221 ina3221;

// the three channels of the INA3221 named for SunAirPlus Solar Power Controller channels (www.switchdoc.com)
#define LIPO_BATTERY_CHANNEL    1
#define SOLAR_CELL_CHANNEL      2
#define OUTPUT_CHANNEL          3

// sunairplus measurement topics
const char INA3221_SENSOR_STRING[] PROGMEM = "INA3221";

//tables to refer to strings
PGM_P const SUNAIRPLUS_SENSORS[] PROGMEM = {
  INA3221_SENSOR_STRING, // idx = 0
};

/* SUNAIRPLUS_TOPICS indices, must match table above */
typedef enum {
  INA3221_SENSOR_STRING_IDX = 0,
} sunairplus_sensors;

// sunairplus measurement topics
const char BATTERY_VOLTAGE_TOPIC[]    PROGMEM = "bat_vol";
const char BATTERY_CURRENT_TOPIC[]    PROGMEM = "bat_cur";
const char SOLAR_VOLTAGE_TOPIC[]      PROGMEM = "sol_vol";
const char SOLAR_CURRENT_TOPIC[]      PROGMEM = "sol_cur";
const char OUTPUT_VOLTAGE_TOPIC[]     PROGMEM = "out_vol";
const char OUTPUT_CURRENT_TOPIC[]     PROGMEM = "out_cur";

//tables to refer to strings
PGM_P const SUNAIRPLUS_TOPICS[]       PROGMEM = {
  BATTERY_VOLTAGE_TOPIC,     // idx = 0
  BATTERY_CURRENT_TOPIC,     // idx = 1
  SOLAR_VOLTAGE_TOPIC,       // idx = 2
  SOLAR_CURRENT_TOPIC,       // idx = 3
  OUTPUT_VOLTAGE_TOPIC,      // idx = 4
  OUTPUT_CURRENT_TOPIC,      // idx = 5
};

/* SUNAIRPLUS_TOPICS indices, must match table above */
typedef enum {
  BATTERY_VOLTAGE_TOPIC_IDX  = 0,
  BATTERY_CURRENT_TOPIC_IDX  = 1,
  SOLAR_VOLTAGE_TOPIC_IDX    = 2,
  SOLAR_CURRENT_TOPIC_IDX    = 3,
  OUTPUT_VOLTAGE_TOPIC_IDX   = 4,
  OUTPUT_CURRENT_TOPIC_IDX   = 5,
} sunairplus_topics;

void publish_sunairplus_measurement()
{
  StaticJsonBuffer<400> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();

  topicBuffer[0] = '\0';
  strcpy_P(topicBuffer, (char*)pgm_read_word(&(STRINGS[SYSTEM_STRING_IDX])));
  payloadBuffer[0] = '\0';
  strcpy_P(payloadBuffer, (char*)pgm_read_word(&(VALUES[SYSTEM_VALUE_IDX])));
  root[topicBuffer] = payloadBuffer;

  topicBuffer[0] = '\0';
  strcpy_P(topicBuffer, (char*)pgm_read_word(&(STRINGS[SENSOR_STRING_IDX])));
  payloadBuffer[0] = '\0';
  strcpy_P(payloadBuffer, (char*)pgm_read_word(&(SUNAIRPLUS_SENSORS[INA3221_SENSOR_STRING_IDX])));
  root[topicBuffer] = payloadBuffer;

#if 0
  float measurement = 0.0;

  //LIPO battery measurements
  measurement = ina3221.getBusVoltage_V(LIPO_BATTERY_CHANNEL);
  buf[0] = '\0';
  strcpy_P(buf, (char*)pgm_read_word(&(SUNAIRPLUS_TOPICS[BATTERY_VOLTAGE_TOPIC_IDX])));
  mqttClient.publish(progBuffer, buf);

  measurement = ina3221.getCurrent_mA(LIPO_BATTERY_CHANNEL);
  buf[0] = '\0';
  dtostrf(measurement,1,FLOAT_DECIMAL_PLACES, buf);
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(SUNAIRPLUS_TOPICS[1])));
  mqttClient.publish(progBuffer, buf);

  // Solar cell measurements
  measurement = ina3221.getBusVoltage_V(SOLAR_CELL_CHANNEL);
  buf[0] = '\0';
  dtostrf(measurement,1,FLOAT_DECIMAL_PLACES, buf);
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(SUNAIRPLUS_TOPICS[2])));
  mqttClient.publish(progBuffer, buf);

  measurement = ina3221.getCurrent_mA(SOLAR_CELL_CHANNEL);
  buf[0] = '\0';
  dtostrf(measurement,1,FLOAT_DECIMAL_PLACES, buf);
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(SUNAIRPLUS_TOPICS[3])));
  mqttClient.publish(progBuffer, buf);

  // SunAirPlus output measurements

  measurement = ina3221.getBusVoltage_V(OUTPUT_CHANNEL);
  buf[0] = '\0';
  dtostrf(measurement,1,FLOAT_DECIMAL_PLACES, buf);
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(SUNAIRPLUS_TOPICS[4])));
  mqttClient.publish(progBuffer, buf);

  measurement = ina3221.getCurrent_mA(OUTPUT_CHANNEL);
  buf[0] = '\0';
  dtostrf(measurement,1,FLOAT_DECIMAL_PLACES, buf);
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(SUNAIRPLUS_TOPICS[5])));
  mqttClient.publish(progBuffer, buf);
#endif

  root.printTo(Serial);

#if (DEBUG_LEVEL > 0)
  Serial.println();
  root.prettyPrintTo(Serial);
#endif
}


#endif  /* XBEEWEATHERBOARD_SUNAIRPLUSCONFIG_H_ */
