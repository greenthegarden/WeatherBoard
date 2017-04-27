#ifndef XBEEWEATHERBOARD_RUNNINGAVERAGECONFIG_H_
#define XBEEWEATHERBOARD_RUNNINGAVERAGECONFIG_H_


#include "RunningAverage.h"

byte WIND_MEASUREMENT_AVERAGING_SIZE = 10;    // averaged over this many samples

// create instances to store samples
RunningAverage wind_spd_avg(WIND_MEASUREMENT_AVERAGING_SIZE);
RunningAverage wind_dir_avg(WIND_MEASUREMENT_AVERAGING_SIZE);


#endif  /* XBEEWEATHERBOARD_RUNNINGAVERAGECONFIG_H_ */
