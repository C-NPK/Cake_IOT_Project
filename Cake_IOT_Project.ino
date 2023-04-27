/*************************************************************
 * Project by Nattapat Kulwattho 
 *
 * BME - KMITL
 *
 * IOT Project - DIGITAL ELECTRONICS AND MICROCONTROLLER
 *
*************************************************************/

  #include "Globals.h"
/* Fill-in information from Blynk Device Info here */
  #define BLYNK_TEMPLATE_ID "TMPL6bvrw02T_"
  #define BLYNK_TEMPLATE_NAME "IOT Project"
  #define BLYNK_AUTH_TOKEN "W7z1ukhyNAsK-7__ykxDKfXKQgQJMgjW"

/* Comment this out to disable prints and save space */
  #define BLYNK_PRINT Serial

/* Color Define use in Blynk LED 
  #define BLYNK_GREEN     "#23C48E"
  #define BLYNK_BLUE      "#04C0F8"
  #define BLYNK_YELLOW    "#ED9D00"
  #define BLYNK_RED       "#D3435C"
  #define BLYNK_DARK_BLUE "#5F7CD8"*/

/* For Establish Wifi Connection */
  //#include <WiFi.h>
  #include <WiFiClient.h>

/* For Establish HTTP client and Jason */
  #include <HTTPClient.h>
  #include <ArduinoJson.h>

/*Wire.h for MPU6010 and OLED_SSD1306 SCL to Pin D22, SDA to Pin D21 */
  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SH110X.h>

  #include "D_Fonts.h"
  #include "Image_Bitmap.h"

  /* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
  #define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
  //#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

  #define SCREEN_WIDTH 128 // OLED display width, in pixels
  #define SCREEN_HEIGHT 64 // OLED display height, in pixels
  #define OLED_RESET -1   //   QT-PY / XIAO
  Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Blynk Essential and Widget Vitral Pin*/
  #include <BlynkSimpleEsp32.h>
  //WidgetLED led1(V6);
  WidgetTerminal terminal(V7);

/*Var Define*/

  int mode = 0;
  int date_forcast = 1;
  int Setting_stage = 0;

  //extern int sun_rise;

/*Your WiFi credentials. Set password to "" for open networks.*/
  char ssid[] = "PORN";
  char pass[] = "porn08122546";

  #include "OPWeather.h"
  #include "Change_Data.h"

  #define Relay_Pin 4

/*NTP Server connection*/
  const char* ntpServer = "pool.ntp.org";
  const long  gmtOffset_sec = 3600*7;
  const int   daylightOffset_sec = 0;

  time_t now;
  struct tm startt; //change newyear to any var
  struct tm stopp; //change newyear to any var
  double seconds;
  int Pushed = 0;

/* Include Home Span Libary*/
  #include "HomeSpan.h" 
  #include "DEV_Identify.h"      
  #include "DEV_Sensors.h"
  #include "DEV_LED.h" 

/*Write at Virtual PinV0 (LED)*/
BLYNK_WRITE(V0)
  {
    int pinValue = param.asInt();
    // Set incoming value from pin V0 to a variable
    int value = param.asInt();
    Light_stage = value;
    Pushed = value;
  }
/*BLYNK_WRITE(V6)
  {
    int pinValue = param.asInt();
    // Set incoming value from pin V0 to a variable
    int value = param.asInt();
    Serial.print("LED value is");
    //Serial.println(pinValue);
    //digitalWrite(2,pinValue);
  }*/

BLYNK_WRITE(V1) {
    TimeInputParam t(param);
    time(&now);
    startt = *localtime(&now);
    stopp = *localtime(&now);
    time_t T_rise = sun_rise;
    time_t T_set = sun_set;

    

    // Process start time
    if (t.hasStartTime())
    {
      Serial.println(String("Start: ") + t.getStartHour() + ":" + t.getStartMinute() + ":" + t.getStartSecond());
      startt.tm_hour = t.getStartHour(); startt.tm_min = t.getStartMinute(); startt.tm_sec = t.getStartSecond();
      Serial.println(&startt, "%A, %B %d %Y %H:%M:%S");
      Starttime = String(" ") + t.getStartHour() + ":" + t.getStartMinute() + ":" + t.getStartSecond();
      
    }
    else if (t.isStartSunrise())
    {
      startt = *localtime(&T_rise);
      Starttime = "Sun Rise";
    }
    else if (t.isStartSunset())
    {
      startt = *localtime(&T_set);
      Starttime = "Sun Set";
    }
    else
    {
      // Do nothing
    }

    // Process stop time

    if (t.hasStopTime())
    {
      Serial.println(String("Stop: ") + t.getStopHour() + ":" + t.getStopMinute() + ":" + t.getStopSecond());
      stopp.tm_hour = t.getStopHour(); stopp.tm_min = t.getStopMinute(); stopp.tm_sec = t.getStopSecond();
      Serial.println(&stopp, "%A, %B %d %Y %H:%M:%S");
      Stoptime = String(" ") + t.getStopHour() + ":" + t.getStopMinute() + ":" + t.getStopSecond();
    }
    else if (t.isStopSunrise())
    {
      stopp = *localtime(&T_rise);
      Stoptime = "Sun Rise";
    }
    else if (t.isStopSunset())
    {
      stopp = *localtime(&T_set);
      Stoptime = "Sun Set";
    }
    else
    {
      // Do nothing: no stop time was set
    }

    // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)

    Serial.println();
  }
  
//Terminal
BLYNK_WRITE(V7){
   String menuSelection = param.asStr();
    // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (menuSelection.startsWith("H!")) {
    terminal.println("Type to Select Mode \n Deafult : D! \n Weather : W! \n Forcast : F! \n (Replace ! with Date you want to forcast 1 - 7) \n Timer Setting : T! \n Location Setting : L! \n Close Screen: C! \n Setting: S!");
  } 
  if (menuSelection.startsWith("D!")) {
    mode = 0;
    terminal.println("Deafult Mode");
  } 
  else if (menuSelection.startsWith("W!")) {
    mode = 1;
    terminal.println("Weather Mode");
  } 
  else if (menuSelection.startsWith("F")) {
    char lastChar = menuSelection.charAt(menuSelection.length() - 1);

    if (menuSelection.startsWith("F!")){
      mode = 2;
      terminal.println("Forcast Mode");}

    else if (lastChar >= '1' && lastChar <= '7'){
      date_forcast = menuSelection.substring(1).toInt();
      mode = 3;
      terminal.print("Forcast Mode Day : ");
      terminal.println(date_forcast);}
    else  {terminal.println("Error Menu not found! For help Type !H");}
  } 
  else if (menuSelection.startsWith("T!")) {
    //mode = 4;
    terminal.println("Timer Setting");
  } 
  else if (menuSelection.startsWith("L!")) {
    terminal.println("Location Setting");
    terminal.println("Please Input Latitude (-90 - +90) : ");
    Setting_stage = Setting_stage + 1;
  }
  else if (Setting_stage == 1) {
    lat = param.asStr();
    terminal.print("Set Latitude at ");terminal.println(lat);
    terminal.println("Please Input Longitude (-180 - +180) : ");
    Setting_stage = Setting_stage + 1;
  }
  else if (Setting_stage == 2) {
    lon = param.asStr();
    terminal.print("Set Longitude at ");terminal.println(lon);
    terminal.println("Finish Setting");
    Setting_stage = 0;
  } 
  else if (menuSelection.startsWith("S!")) {
    if(Homekit_over_Blynk){
      Homekit_over_Blynk = false;
      terminal.println("Changed to Blynk over Homekit");
    }
    else{
      Homekit_over_Blynk = true;
      terminal.println("Changed to Homekit over Blynk");
    }
  } 
  else if (menuSelection.startsWith("C!")) {
    mode = 9;
    terminal.println("Screen is close");
  } 
  else {terminal.println("Error Menu not found! For help Type !H");}

  // Ensure everything is sent
  terminal.flush();
}

  BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

  void myTimerEvent()
  { 
    Current_temp = dht.readTemperature();
    Current_humid = dht.readHumidity();
    Blynk.virtualWrite(V9, Current_temp);
    Blynk.virtualWrite(V8, Current_humid);
    // You can send any value at any time.
    // Please don't send more that 10 values per second.    
      if(mode == 9){
        display.clearDisplay();
        display.drawBitmap(0, 0, image_data_Clear, 128, 64, 1);
        display.display();
        Serial.println("mode9");}
      if(mode == 0){
        CGE.GETTime();
        Serial.print("mode0");}
      if(mode == 1){
        CGE.Change2OPW();
        OPW.GETOPWeather(); 
        Serial.print("mode1");}
      if(mode == 2){
        //CGE.Change2OPWF_ALL();
        OPW.GETOPForcast(); 
        Serial.print("mode2");}
      if(mode == 3){
        CGE.Change2OPWF(date_forcast);
        OPW.GETOPForcast(); 
        Serial.print("mode3");}
      if(mode == 4){
        CGE.Change2OPWF(date_forcast);
        OPW.GETOPForcast(); 
        Serial.print("mode4");}

      //Serial.println(&startt, "%A, %B %d %Y %H:%M:%S");
      Serial.println(time(&now)); // time(&now) get time now

      if (!Homekit_over_Blynk){
      if(time(&now) > mktime(&startt) && time(&now) < mktime(&stopp)) {Light_stage = 1;}
      else if(Pushed == 0) {Light_stage = 0;} 
      digitalWrite(Relay_Pin,Light_stage);}

      if (Homekit_over_Blynk){
        Serial.print("Hk");
        if(digitalRead(Relay_Pin) == HIGH){
          Light_stage = 1;
          Serial.print("H");}
        else if(digitalRead(Relay_Pin) == LOW){Light_stage = 0;}
        }
      
  }

void setup() {
  // Debug console
    Serial.begin(115200);
homeSpan.begin(Category::Bridges,"AZDelivery Temp Sensor Bridge");

  new SpanAccessory();  
    new DEV_Identify("AZDelivery HomeKit","SmartHomeFactory","123-ABC","HS Bridge","0.9",3);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");
      
  new SpanAccessory();                                                          
    new DEV_Identify("DHT22 Temp Sensor","SmartHomeFactory","123-ABC","Sensor","0.9",1);
    // Create a Temperature Sensor (see DEV_Sensors.h for definition)
    new DEV_TempSensor(); 
        

  new SpanAccessory();
    new DEV_Identify("DHT22 Humidity Sensor","SmartHomeFactory","123-ABC","Sensor","0.9",1);
    // Create a Humidity Sensor (see DEV_Sensors.h for definition)
    new DEV_HumSensor();

  new SpanAccessory();                            // This second Accessory is the same as the first Accessory in Example 7, with the exception that Characteristic::Name() now does something
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Cake LED");     // Note that unlike in Example 7, this use of Name() is now utilized by the Home App since it is not the first Accessory (the Bridge above is the first)
    new DEV_LED(Relay_Pin);  

  //Print Globals Var
    printGlobals();

  // Define pinD2 as Output
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    pinMode(Relay_Pin, OUTPUT);
    digitalWrite(Relay_Pin, LOW);

  /*Estabish Server connection*/
    Serial.println("A");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); //Connect to ntp server
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); //Connect to Blynk
    
  //Begin the Wire
    Serial.println("B");
    Wire.begin(); 

  // Setup a function to be called every second
    Serial.println("C");
    timer.setInterval(1000L, myTimerEvent);

  // Setup for ALL Clases
    Serial.println("D");
    OPW.OPWsetup();
    Serial.println("E");
    CGE.CHsetup();

  //Terminal Setup
    terminal.clear();
    terminal.flush();
    terminal.println("Type to Select Mode") ;
    terminal.println("For Help press H!") ;

  /*Oled initial*/
      if (!display.begin(i2c_Address, true)) { // Address 0x3C for 128x32
      Serial.println(F("SSD1306 allocation failed"));
      for (;;)
        ; // Don't proceed, loop forever
    }
    
    Serial.println(F("SSD1306 allocation"));   

  /*Set Defult display*/
    display.display();
    delay(300); // Pause for 2 seconds
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setRotation(0); 

  }

  void loop()
  {
    homeSpan.poll();
    Blynk.run(); 
    timer.run(); // Initiates BlynkTimer
    OPW.OPWloop();
    CGE.CHloop();
  }
