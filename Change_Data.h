class Change_Data {

  #include <Adafruit_GFX.h>
  #include <Adafruit_SH110X.h>
  #include "Globals.h"
  //#include <Fonts/FreeMono9pt7b.h>

  public:
  // Variable Decare
    int Runtime = 0;
    int x = 4;
    int y = 10;
    int h = 32;
    int w = 32;

    uint8_t Deg_sing = 0xB0;
    void CHloop(){}
    void CHsetup(){}
  
  void GETTime(){
    struct tm timeinfo;
    
    if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
      return;
    }

    display.clearDisplay();

    if (Light_stage == 1){display.drawBitmap(92, 32, image_data_light_open_A, 32, 32, 1);}
    else if (Starttime != " "){display.drawBitmap(92, 32, image_data_Timer, 32, 32, 1);}
    else{display.drawBitmap(92, 32, image_data_light_close_A, 32, 32, 1);}
    
    display.setCursor(0, 10);display.setFont();display.setTextSize(1);

    display.print(&timeinfo, "%a, %B %d %Y");

    display.setCursor(0, 28);
    display.setFont(&ROBOTO_BOLD16pt7b);display.print(&timeinfo, "%H:%M:%S");
    //display.println(" ");
    display.setFont(&ROBOTO_MEDIUM6pt7b);
    
   
    if ((Starttime != " " || Stoptime != " ")&& Runtime <= 12){
    //display.print("HeatI : ");display.print(Current_heat_index);display.setFont();display.print((char)247);display.setFont(&ROBOTO_MEDIUM6pt7b);display.println("C ");
    display.setFont(&ROBOTO_MEDIUM6pt7b);
    display.print("Set on  :");display.println(Starttime);
    display.print("Set off :");display.print(Stoptime);}

    //display.fillRect(92, 38, 24, 24, SH110X_WHITE);
    else{
    display.print("Temp  : ");display.print(Current_temp);display.setFont();display.print((char)247);display.setFont(&ROBOTO_MEDIUM6pt7b);display.println("C ");
    display.print("Humid : ");display.print(Current_humid);display.println(" % ");}

    display.display();

    if(Runtime == 24 || Runtime > 24) {Runtime = 0;}
    Runtime = Runtime+1;
  }
  
  void Change2OPW(){
    
    time_t T_rise = sun_rise;
    time_t T_set = sun_set;
    struct tm timeinfo;
    struct tm timeinfo_rise;
    struct tm timeinfo_set;
    timeinfo_rise = *localtime(&T_rise);
    timeinfo_set = *localtime(&T_set);
    
    if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
      return;
    }

    display.clearDisplay();
    //ddd, mmm dd yyyy
    display.setCursor(0, 0);display.setFont();display.setTextSize(1);
    display.println(&timeinfo, "%a, %B %d %Y");
    //30.0 C
    display.setCursor(42, 28);
    display.setFont(&ROBOTO_BOLD16pt7b);display.print(OPW_temp, 1);display.setFont();display.setCursor(108, 12);display.setTextSize(1);display.setFont();display.print((char)247);display.setCursor(114, 12);display.setTextSize(2);display.print("C");    
    
    display.setCursor(0, 34);
    display.setTextSize(1);display.setFont(&ROBOTO_MEDIUM5pt7b);display.println(" "); 
    if (Runtime <= 20){
      display.print(OPW_mainweather);display.print(", ");display.println(OPW_description);}
    if (Runtime <= 4){
      display.print("Feels like ");display.print(OPW_feels_like, 1);display.print("C ");}
    else if (Runtime <= 8){
      display.print("HIGH ");display.print(OPW_temp_max, 1);display.print("C ");display.print("LOW ");display.print(OPW_temp_min, 1);display.print("C ");}
    else if (Runtime <= 12){
      display.print("W SPD ");display.print(OPW_Wspeed, 1);display.print("m/s");display.print(" DEG ");display.print(OPW_Wdeg, 1);}
    else if (Runtime <= 16){
      display.print("HUM ");display.print(OPW_humidity);display.print("% ");display.print("Pa");display.print(OPW_humidity);display.print("hPa ");}
    else if (Runtime <= 20){
      display.print("VIS ");display.print(OPW_visibility/1000, 1);display.print("Km ");display.print("Clounds ");display.print(OPW_clouds, 1);display.print("% ");}
    else if (Runtime <= 24){
      display.print("Sun rise : ");display.println(&timeinfo_rise, "%H:%M");
      display.print("Sun set  : ");display.print(&timeinfo_set, "%H:%M");}
    if(Runtime == 24 || Runtime > 24) {Runtime = 0;}
    display.setFont();
    //display.drawRect(1, 55, 8, 8, SH110X_WHITE);
    draw_icon(4,10,32,32, OPW_id, OPW_ico);
    display.display();

    Runtime = Runtime + 1;
    }

  void Change2OPWF(int d){

    time_t T_dt = OPW_dtA[d];
    time_t T_dt_rise = sun_riseA[d];
    time_t T_dt_set = sun_setA[d];
    struct tm timeinfo;
    struct tm timeinfo_riseA;
    struct tm timeinfo_setA;
    timeinfo_riseA = *localtime(&T_dt_rise);
    timeinfo_setA = *localtime(&T_dt_set);
    timeinfo = *localtime(&T_dt);

    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    display.clearDisplay();
    display.setCursor(0, 0);display.setFont();display.setTextSize(1);

    display.println(&timeinfo, "%a, %B %d %Y");

    display.setCursor(38, 28);

    if (Runtime <= 12){

      display.setFont(&ROBOTO_BOLD16pt7b);display.print(OPW_temp_maxA[d], 1);display.setFont();display.setCursor(104, 28);display.setTextSize(1);display.setFont(&ROBOTO_MEDIUM5pt7b);display.print("HIGH");    

      display.setFont();display.setCursor(108, 12);display.setTextSize(1);display.setFont();display.print((char)247);display.setCursor(114, 12);display.setTextSize(2);display.print("C");}

    else if (Runtime <= 24){

      display.setFont(&ROBOTO_BOLD16pt7b);display.print(OPW_temp_minA[d], 1);display.setFont();display.setCursor(104, 28);display.setTextSize(1);display.setFont(&ROBOTO_MEDIUM5pt7b);display.print("LOW");    

      display.setFont();display.setCursor(108, 12);display.setTextSize(1);display.setFont();display.print((char)247);display.setCursor(114, 12);display.setTextSize(2);display.print("C");}
    

    display.setCursor(0, 34);

    display.setTextSize(1);display.setFont(&ROBOTO_MEDIUM5pt7b);display.println(" "); 

    if (Runtime <= 5){ 

    display.print(OPW_mainweatherA[d]);display.print(", ");display.println(OPW_descriptionA[d]);
    display.print("Clouds ");display.print(OPW_cloudsA[d]);display.print("%    ");display.print("POP ");display.print(OPW_PopA[d]*100,0);display.print("%");
    }
    else if (Runtime <= 10){ 

    display.print("HUM ");display.print(OPW_humidityA[d]);display.print("% ");display.print("  Pa ");display.print(OPW_pressureA[d], 1);display.println("hPa ");
    display.print("W SPD ");display.print(OPW_WspeedA[d], 1);display.print("m/s ");display.print(" DEG ");display.print(OPW_WdegA[d], 1);}

    else if (Runtime <= 15){    
    display.print("DAY ");display.print(OPW_temp_dayA[d], 1);display.print("C ");display.print("   NIG ");display.print(OPW_temp_nightA[d], 1);display.println("C");

    display.print("HI D ");display.print(OPW_feels_like_dayA[d], 1);display.print("C ");display.print("   HI N ");display.print(OPW_feels_like_nightA[d], 1);display.print("C");}

    else if (Runtime <= 20){
    display.print("MOR ");display.print(OPW_temp_dayA[d], 1);display.print("C ");display.print("   EVE ");display.print(OPW_temp_nightA[d], 1);display.println("C");

    display.print("HI M ");display.print(OPW_feels_like_mornA[d], 1);display.print("C ");display.print("   HI E ");display.print(OPW_feels_like_eveA[d], 1);display.print("C");}

    else if (Runtime <= 24){
    display.print("Sun rise : ");display.println(&timeinfo_riseA, "%H:%M");
    display.print("Sun set  : ");display.print(&timeinfo_setA, "%H:%M");}
    if (Runtime == 24 || Runtime > 24){ Runtime = 0;}
    
    display.setFont();
    draw_icon(4,10,32,32,OPW_idA[d],OPW_icoA[d]);
    //display.drawRect(4, 10, 32, 32, SH110X_WHITE);
    display.display();
    Runtime = Runtime+1;
    }
  
  void draw_icon(int x, int y, int h, int w, int draw_id, String draw_ico){

      if (draw_id == 200 || draw_id == 201 || draw_id == 202 || draw_id == 210 || draw_id == 211 || draw_id == 212 || draw_id == 221 || draw_id == 230 || draw_id == 231 || draw_id == 232) {
        if (draw_ico == "11d") {
        display.drawBitmap(x, y, image_data_id_11d, h, w, 1);}
        else if (draw_ico == "11n") {
        display.drawBitmap(x, y, image_data_id_11n, h, w, 1);}
      }
      else if (draw_id == 300 || draw_id == 301 || draw_id == 302 || draw_id == 310 || draw_id == 311 || draw_id == 312 || draw_id == 313 || draw_id == 314 || draw_id == 321) {
        if (draw_ico == "09d") {
        display.drawBitmap(x, y, image_data_id_09d, h, w, 1);}
        else if (draw_ico == "09n") {
        display.drawBitmap(x, y, image_data_id_09n, h, w, 1);}
      }
      else if (draw_id == 500 || draw_id == 501 || draw_id == 502 || draw_id == 503 || draw_id == 504 || draw_id == 511 || draw_id == 520 || draw_id == 521 || draw_id == 522 || draw_id == 531) {
        if (draw_ico == "10d") {
        display.drawBitmap(x, y, image_data_id_10d, h, w, 1);}
        else if (draw_ico == "10n") {
        display.drawBitmap(x, y, image_data_id_10n, h, w, 1);}
      }
      else if (draw_id == 600 || draw_id == 601 || draw_id == 602 || draw_id == 611 || draw_id == 612 || draw_id == 613 || draw_id == 615 || draw_id == 616 || draw_id == 620 || draw_id == 621 || draw_id == 622) {
        display.drawBitmap(x, y, image_data_id_13dn, h, w, 1);
      }
      else if (draw_id == 701 || draw_id == 711 || draw_id == 721 || draw_id == 731 || draw_id == 741 || draw_id == 751 || draw_id == 761 || draw_id == 762 || draw_id == 771 || draw_id == 781) {
        display.drawBitmap(x, y, image_data_id_50dn, h, w, 1);
      }
      else if (draw_id == 800) {
        if (draw_ico == "01d") {
          display.drawBitmap(x, y, image_data_id_01d, h, w, 1);}
        else if (draw_ico == "01n") {
          display.drawBitmap(x, y, image_data_id_01n, h, w, 1);}
      }
      else if (draw_id == 801) {
          if (draw_ico == "02d") {
          display.drawBitmap(x, y, image_data_id_02d, h, w, 1);}
          else if (draw_ico == "02n") {
          display.drawBitmap(x, y, image_data_id_02n, h, w, 1);}
      }
      else if (draw_id == 802) {
          display.drawBitmap(x, y, image_data_id_03dn, h, w, 1);}

      else if (draw_id == 803 || draw_id == 804) {
          display.drawBitmap(x, y, image_data_id_04dn, h, w, 1);}
      else{
          display.drawBitmap(x, y, image_data_id_0x0, h, w, 1);}         
  }
  
  };

  Change_Data CGE;