#include <LiquidCrystal.h>
#include <SD.h>

const int chipSelect = 53;        // SD pin
const char gpsTag[] = "$GPRMC";   // Start of GPS command

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  lcd.begin(16,2);
 
  delay(200);
  Serial1.println("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29");
  delay(200);
  Serial1.println("$PMTK220,1000*1F");
 
  pinMode(53, OUTPUT);
  if(!SD.begin(chipSelect)) {
    lcd.print("SD failed!");
    return;
  }
  
  lcd.print("SD initialized");
}

void loop() {
  poll_gps();
  //keypad();
  delay(1000);
}

void poll_gps() {
  String gps = "";
  
  while(Serial1.available()) {
    gps += String((char)Serial1.read());
  }
  
  if(check_gps(gps)==1){
    if(gps[18]=='A'){
      Serial.println(gps);
      Serial.println(time(gps.substring(7, 13)) + " - " + date(gps.substring(56, 62)) + " - " + lat(gps.substring(20, 32)) + " - " + lng(gps.substring(32, 44)));
      lcd.clear();
      lcd.print("Time: " + time(gps.substring(7, 13)));
      lcd.setCursor(0,1);
      lcd.print("Date: " + date(gps.substring(56, 62)));
      delay(5000);
      lcd.clear();
      lcd.print("Lat: " + lat(gps.substring(20, 32)));
      lcd.setCursor(0,1);
      lcd.print("Lng: " + lng(gps.substring(32, 44)));
      delay(5000);
    } else {
      lcd.clear();
      lcd.print("No Lock!");
      lcd.setCursor(9, 0);
      lcd.print(gps.substring(7, 13));
      lcd.setCursor(0,1);
      lcd.print(gps.substring(57, 63));
    } 
  }
}

int check_gps(String data){
  for(int i=0;i<6;i++){
    if(data[i]!=gpsTag[i]){
      return 0;
    }
   }
  return 1;
}

String date(String gps_date) {
  Serial.println(gps_date);
  String day   = gps_date.substring(0,2);
  String month = gps_date.substring(2,4);
  String year  = gps_date.substring(4,6);
  
  String date  = String(month + "-" + day + "-" + "20" + year);
  Serial.println(date);
  return date; 
}

String time(String gps_time) {
  String hour    = gps_time.substring(0,2);
  String miniute = gps_time.substring(2,4);
  String second  = gps_time.substring(4,6);

  String time    = String(hour + ":" + miniute + ":" + second);
  return time;
}

String lat(String gps_lat) {
  String deg = gps_lat.substring(0, 2);
  String minutes = gps_lat.substring(2, 4);
  String decimal = gps_lat.substring(5, 9);
  String heading = gps_lat.substring(10, 11);
  
  String lat = String(deg + " " + minutes + " " + decimal + heading);
  return lat; 
}

String lng(String gps_lng) {
  String deg = gps_lng.substring(0,3);
  String minutes = gps_lng.substring(3, 5);
  String decimal = gps_lng.substring(6, 10);
  String heading = gps_lng.substring(11, 12);

  String lng = String(deg + " " + minutes + " " + decimal + heading);
  return lng;   
}

void keypad() {
  
}
