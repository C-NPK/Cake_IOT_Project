#include <Arduino.h>
#include "Globals.h"

  extern String openWeatherMapApiKey = "c3f5b70542701bdae20db85abea971bc";

  extern String city = "Bangkok";
  extern String countryCode = "TH";

  extern String lat = "13.727591";
  extern String lon = "100.499613"; 

  extern unsigned long lastTime = 0;
  extern unsigned long timerDelay = 10000;

  extern String jsonBuffer = " ";

  extern String Starttime = " ";
  extern String Stoptime = " ";

  extern int Light_stage = 0;

  extern float Current_temp = 0.0;
  extern float Current_humid = 0.0;
  extern float Current_heat_index = 0.0;

  extern bool Homekit_over_Blynk = true;

/* Current data */
  extern float OPW_temp = 0.0;
  extern float OPW_feels_like = 0.0;
  extern float OPW_temp_min = 0.0;
  extern float OPW_temp_max = 0.0;
  extern float OPW_pressure = 0.0;
  extern float OPW_visibility = 0.0;
  extern float OPW_Wspeed = 0.0;
  extern float OPW_Wdeg = 0.0;

  extern int OPW_humidity = 0;
  extern int OPW_clouds = 0;
  extern int sun_rise = 0;
  extern int sun_set = 0;
  extern int OPW_id = 0;

  extern String OPW_name = " ";
  extern String OPW_ico = " ";
  extern String OPW_mainweather = " ";
  extern String OPW_description = " ";

/* Forcast Data */

  extern long OPW_dtA[8] = {0};

  extern float OPW_temp_minA[8] = {0};
  extern float OPW_temp_maxA[8] = {0};
  extern float OPW_temp_dayA[8] = {0};
  extern float OPW_temp_nightA[8] = {0};
  extern float OPW_temp_eveA[8] = {0};
  extern float OPW_temp_mornA[8] = {0};

  extern float OPW_feels_like_dayA[8] = {0};
  extern float OPW_feels_like_nightA[8] = {0};
  extern float OPW_feels_like_eveA[8] = {0};
  extern float OPW_feels_like_mornA[8] = {0};

  extern float OPW_pressureA[8] = {0};
  extern float OPW_WspeedA[8] = {0};
  extern float OPW_WdegA[8] = {0};
  extern float OPW_PopA[8] = {0.0};

  extern int OPW_humidityA[8] = {0};
  extern int OPW_cloudsA[8] = {0};
  extern int sun_riseA[8] = {0};
  extern int sun_setA[8] = {0};
  extern int OPW_idA[8] = {0,0,0,0,0,0,0,0};

  extern String OPW_icoA[8] = {""};
  extern String OPW_mainweatherA[8] = {""};
  extern String OPW_descriptionA[8] = {""};


void printGlobals(){
  Serial.println(openWeatherMapApiKey);

  Serial.println(city);
  Serial.println(countryCode);

  Serial.println(lat);
  Serial.println(lon);

  Serial.println(lastTime);
  Serial.println(timerDelay);

  Serial.println(jsonBuffer);

  Serial.println(Starttime);
  Serial.println(Stoptime);  

  Serial.println(Light_stage);
  
  Serial.print(Current_temp);
  Serial.print(Current_humid);
  Serial.print(Current_heat_index);

  Serial.print(OPW_temp);


/* Current data */
  Serial.print(OPW_feels_like);
  Serial.print(OPW_temp_min);
  Serial.print(OPW_temp_max);
  Serial.print(OPW_pressure);
  Serial.print(OPW_humidity);
  Serial.print(OPW_visibility);
  Serial.print(OPW_Wspeed);
  Serial.print(OPW_Wdeg);
  Serial.print(OPW_clouds);
  Serial.print(sun_rise);
  Serial.print(sun_set);
  Serial.print(OPW_name);
  Serial.print(OPW_ico);
  Serial.print(OPW_mainweather);
  Serial.print(OPW_description);

/* Forcast Data */
for (int i = 0; i < 8; i++) {
  Serial.print(OPW_dtA[i]);
  Serial.print(OPW_temp_minA[i]);
  Serial.print(OPW_temp_maxA[i]);
  Serial.print(OPW_temp_dayA[i]);
  Serial.print(OPW_temp_nightA[i]);
  Serial.print(OPW_temp_eveA[i]);
  Serial.print(OPW_temp_mornA[i]);
  Serial.print(OPW_feels_like_dayA[i]);
  Serial.print(OPW_feels_like_nightA[i]);
  Serial.print(OPW_feels_like_eveA[i]);
  Serial.print(OPW_feels_like_mornA[i]);
  Serial.print(OPW_pressureA[i]);
  Serial.print(OPW_WspeedA[i]);
  Serial.print(OPW_WdegA[i]);
  Serial.print(OPW_humidityA[i]);
  Serial.print(OPW_cloudsA[i]);
  Serial.print(OPW_PopA[i]);
  Serial.print(sun_riseA[i]);
  Serial.print(sun_setA[i]);
  Serial.print(OPW_icoA[i]);
  Serial.print(OPW_mainweatherA[i]);
  Serial.print(OPW_descriptionA[i]);
}
}
