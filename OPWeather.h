class OPWeather {
/* For Establish HTTP client and Jason */
#include <HTTPClient.h>
//#include <Arduino_JSON.h>
#include <ArduinoJson.h>
#include "Globals.h"
/* For Establish Wifi Connection */
#include <WiFi.h>
#include <WiFiClient.h>

public:

void OPWsetup(){
  timerDelay = 0;
  GETOPWeather();
  delay(100);
  GETOPForcast();
  timerDelay = 10000;
}
void OPWloop(){}

void GETOPWeather(){
      
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://pro.openweathermap.org/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&cnt=7&appid=" + openWeatherMapApiKey + "&units=metric";

      DynamicJsonDocument myObject(12288);
      DeserializationError error = deserializeJson(myObject, httpGETRequest(serverPath.c_str()));

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;}

      /* Var assign*/ 
        OPW_temp = myObject["main"]["temp"];
        OPW_feels_like = myObject["main"]["feels_like"];
        OPW_temp_min = myObject["main"]["temp_min"];
        OPW_temp_max = myObject["main"]["temp_max"];
        OPW_pressure = myObject["main"]["pressure"];
        OPW_humidity = myObject["main"]["humidity"];

        OPW_visibility = myObject["visibility"];

        OPW_Wspeed = myObject["wind"]["speed"];
        OPW_Wdeg = myObject["wind"]["deg"];

        OPW_clouds = myObject["clouds"]["all"];

        sun_rise = myObject["sys"]["sunrise"];
        sun_set  = myObject["sys"]["sunset"];

        OPW_name = (const char*)myObject["name"];

        OPW_id = myObject["weather"][0]["id"];
        OPW_ico = (const char*)myObject["weather"][0]["icon"];         
        OPW_mainweather = (const char*)myObject["weather"][0]["main"];
        OPW_description = (const char*)myObject["weather"][0]["description"];
      /*Print ALL*/
            Serial.println("Current Data:");
            Serial.print("Temperature: ");
            Serial.println(OPW_temp);
            Serial.print("Feels like: ");
            Serial.println(OPW_feels_like);
            Serial.print("Minimum temperature: ");
            Serial.println(OPW_temp_min);
            Serial.print("Maximum temperature: ");
            Serial.println(OPW_temp_max);
            Serial.print("Pressure: ");
            Serial.println(OPW_pressure);
            Serial.print("Humidity: ");
            Serial.println(OPW_humidity);
            Serial.print("Visibility: ");
            Serial.println(OPW_visibility);
            Serial.print("Wind speed: ");
            Serial.println(OPW_Wspeed);
            Serial.print("Wind degree: ");
            Serial.println(OPW_Wdeg);
            Serial.print("Clouds: ");
            Serial.println(OPW_clouds);
            Serial.print("Sunrise: ");
            Serial.println(sun_rise);
            Serial.print("Sunset: ");
            Serial.println(sun_set);
            Serial.print("City Name: ");
            Serial.println(OPW_name);
            Serial.print("Weather ID: ");
            Serial.println(OPW_id);
            Serial.print("Weather Icon: ");
            Serial.println(OPW_ico);
            Serial.print("Main Weather: ");
            Serial.println(OPW_mainweather);
            Serial.print("Description: ");
            Serial.println(OPW_description);
    }
          else {
            Serial.println("WiFi Disconnected");
          }
          lastTime = millis();
  }

}

void GETOPForcast(){
  /*OPEN WEATHER*/
      // Send an HTTP GET request
      if ((millis() - lastTime) > timerDelay) {
        // Check WiFi connection status
        if(WiFi.status()== WL_CONNECTED){
         String serverPath = "http://pro.openweathermap.org/data/2.5/forecast/daily?lat=" + lat + "&lon=" + lon + "&cnt=7&appid=" + openWeatherMapApiKey + "&units=metric";
          
          DynamicJsonDocument myObject(12288);
          DeserializationError error = deserializeJson(myObject, httpGETRequest(serverPath.c_str()));

          if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
          }
        
  /* Var assign */
        for (int i = 0; i < 8; i++) {
          OPW_dtA[i] = myObject["list"][i]["dt"];

          OPW_temp_minA[i] = myObject["list"][i]["temp"]["min"];
          OPW_temp_maxA[i] = myObject["list"][i]["temp"]["max"];
          OPW_temp_dayA[i] = myObject["list"][i]["temp"]["day"];
          OPW_temp_nightA[i] = myObject["list"][i]["temp"]["night"];
          OPW_temp_eveA[i] = myObject["list"][i]["temp"]["eve"];
          OPW_temp_mornA[i] = myObject["list"][i]["temp"]["morn"];

          OPW_feels_like_dayA[i] = myObject["list"][i]["feels_like"]["day"];
          OPW_feels_like_nightA[i] = myObject["list"][i]["feels_like"]["night"];
          OPW_feels_like_eveA[i] = myObject["list"][i]["feels_like"]["eve"];
          OPW_feels_like_mornA[i] = myObject["list"][i]["feels_like"]["morn"];

          OPW_pressureA[i] = myObject["list"][i]["pressure"];
          OPW_WspeedA[i] = myObject["list"][i]["speed"];
          OPW_WdegA[i] = myObject["list"][i]["deg"];

          OPW_humidityA[i] = myObject["list"][i]["humidity"];
          OPW_cloudsA[i] = myObject["list"][i]["clouds"];
          OPW_PopA[i] = myObject["list"][i]["pop"];
          sun_riseA[i] = myObject["list"][i]["sunrise"];
          sun_setA[i] = myObject["list"][i]["sunset"];

          OPW_idA[i] = myObject["list"][i]["weather"][0]["id"];
          OPW_icoA[i] = (const char*)myObject["list"][i]["weather"][0]["icon"];
          OPW_mainweatherA[i] = (const char*)myObject["list"][i]["weather"][0]["main"];
          OPW_descriptionA[i] = (const char*)myObject["list"][i]["weather"][0]["description"];
        }

    
    /*Print ALL*/
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
      Serial.print("RISE:");
      Serial.print(sun_riseA[i]);
      Serial.print(sun_setA[i]);
      Serial.print(OPW_idA[i]);
      Serial.print(OPW_icoA[i]);
      Serial.print(OPW_mainweatherA[i]);
      Serial.print(OPW_descriptionA[i]);}

    }
        else {
          Serial.println("WiFi Disconnected");
        }
        lastTime = millis();
      }
      }
  

    String httpGETRequest(const char* serverName){
        WiFiClient client;
        HTTPClient http;
          
        // Your Domain name with URL path or IP address with path
        http.begin(client, serverName);
        
        // Send HTTP POST request
        int httpResponseCode = http.GET();
        
        String payload = "{}"; 
        
        if (httpResponseCode>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          payload = http.getString();
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();

        return payload;
    }
  
  
  

    
};

OPWeather OPW;  