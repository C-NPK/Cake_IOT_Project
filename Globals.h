#ifndef GLOBALS_H
#define GLOBALS_H

  extern String openWeatherMapApiKey;

  extern String city;
  extern String countryCode;

  extern String lat;
  extern String lon; 

  extern unsigned long lastTime;
  extern unsigned long timerDelay;

  extern String jsonBuffer;

  extern String Starttime;
  extern String Stoptime;

  extern int Light_stage; 

  extern float Current_temp;
  extern float Current_humid;
  extern float Current_heat_index;

  extern bool Homekit_over_Blynk;

/* Current data from Open Weather*/
  extern float OPW_temp;
  extern float OPW_feels_like;
  extern float OPW_temp_min;
  extern float OPW_temp_max;
  extern float OPW_pressure;
  extern float OPW_visibility;
  extern float OPW_Wspeed;
  extern float OPW_Wdeg;

  extern int OPW_humidity;
  extern int OPW_clouds;
  extern int sun_rise;
  extern int sun_set;
  extern int OPW_id;

  extern String OPW_name;
  extern String OPW_ico;
  extern String OPW_mainweather;
  extern String OPW_description;
  

/* Forcast Data */
  extern long OPW_dtA[8];

  extern float OPW_temp_minA[8];
  extern float OPW_temp_maxA[8];
  extern float OPW_temp_dayA[8];
  extern float OPW_temp_nightA[8];
  extern float OPW_temp_eveA[8];
  extern float OPW_temp_mornA[8];

  extern float OPW_feels_like_dayA[8];
  extern float OPW_feels_like_nightA[8];
  extern float OPW_feels_like_eveA[8];
  extern float OPW_feels_like_mornA[8];

  extern float OPW_pressureA[8];
  extern float OPW_WspeedA[8];
  extern float OPW_WdegA[8];
  extern float OPW_PopA[8];

  extern int OPW_humidityA[8];
  extern int OPW_cloudsA[8];
  extern int sun_riseA[8];
  extern int sun_setA[8];
  extern int OPW_idA[8];

  extern String OPW_icoA[8];
  extern String OPW_mainweatherA[8];
  extern String OPW_descriptionA[8];

void printGlobals();

#endif