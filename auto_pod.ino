#include <LiquidCrystal.h>
#include <SD.h>

const int chipSelect = 53;
const char gpsTag[] = "$GPRMC";

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
  delay(1000);
}

void poll_gps() {
  String gps = "";
  
  while(Serial1.available()) {
    gps += String((char)Serial1.read());
  }
  
  if(check_gps(gps)==1){
    if(gps[18]=='A'){
      lcd.clear();
      lcd.print("Time: " + time(gps.substring(7, 13)));
      lcd.setCursor(0,1);
      lcd.print("Date: " + date(gps.substring(57, 63)));
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
  String day   = gps_date.substring(0,2);
  String month = gps_date.substring(2,4);
  String year  = gps_date.substring(4,6);
  
  String date  = String(month + "-" + day + "-" + "20" + year);
  return date; 
}

String time(String gps_time) {
  String hour    = gps_time.substring(0,2);
  String miniute = gps_time.substring(2,4);
  String second  = gps_time.substring(4,6);
  String time    = String(hour + ":" + miniute + ":" + second);
  return time;
}
