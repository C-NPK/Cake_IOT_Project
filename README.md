# IOT-Project |
# Automatic Lamp with Weather station and Display Screen

Software and API

•	Arduino IDE

•	Apple HomeKit

•	Blynk

•	Open weather Map

•	NTP Time server
       
Components

•	ESP32 									x 1 piece

•	DHT11 or DHT22 	(Depend on availability)			x 1 piece

•	OLED or LCD Display	(Depend on availability)			x 1 piece

•	Relay									x 1 piece

•	Lamp or light bulb	(Depend on availability)			x 1 piece

The Automatic Lamp with Weather station and Display Screen project is the integrated project that are the combination of The Automatic Lamp, and Weather station. In the automatic lamp part, it is the automatic lamp that we can set the time for turning it on and off via the Blynk application, for the iOS and android user that can control from outside. Moreover, the lamp is also can be control by the Apple HomeKit with Siri voice control and/or the shortcut app in iOS devices. Also, the screen display can show the time that we set for the lamp in order to close or open, together with the time that ESP32 is synced with the NTP Time server. The automatic lamp that received the time data sync to NTP time server which then will use the relay to control the lamp on and off at higher voltage

In Weather station it will come with the screen display to show the time, indoor temperature, indoor humidity, and indoor H-Index measured by DHT11 or DHT22 device. Moreover, the weather station can also show the  outdoor weather and weather forecast which consist of temperature, humidity, wind speed, visibility sunset, sunrise and etc. That retrieve from the OpenWeatherMap (https://openweathermap.org/) via API. Also, those data collected from DHT device or from API of OpenWeatherMap can be display both  on Apple HomeKit, and Blynk application, which can display the temperature and humidity data in the room when we go outside of the house.  And the Blynk application will use for controlling the screen display for changing theme, cosmetic and function display in the screen.  
