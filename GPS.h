#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

static const uint32_t GPSBaud = 9600; 
 
TinyGPSPlus gps;      // The TinyGPS++ object
WidgetMap myMap(V15);  // V0 for virtual pin of Map Widget
 
HardwareSerial mygps(2);  // The serial connection to the GPS device
 
BlynkTimer timer;
 
float latitude;   
float longitude;    
float velocity;   
float sats;        
String bearing;            
 
unsigned int move_index = 1;     
 
void checkGPS()
{
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    Blynk.virtualWrite(V16, "GPS ERROR");  // Value Display widget  on V3 if GPS not detected
  }
}

void displayInfo()
{
  if (gps.location.isValid() )
  {
    sats = gps.satellites.value();    
    latitude = (gps.location.lat());   
    longitude = (gps.location.lng());
    velocity = gps.speed.kmph();     
    bearing = TinyGPSPlus::cardinal(gps.course.value());
    Serial.print("SATS:  ");
    Serial.println(sats);  // float to x decimal places
    Serial.print("LATITUDE:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONGITUDE: ");
    Serial.println(longitude, 6);
    Serial.print("SPEED: ");
    Serial.print(velocity);
    Serial.println("kmph");
    Serial.print("DIRECTION: ");
    Serial.println(bearing);
 
    Blynk.virtualWrite(V13, String(latitude, 6));
    Blynk.virtualWrite(V14, String(longitude, 6));
    Blynk.virtualWrite(V16, sats);
    Blynk.virtualWrite(V17, velocity);
    Blynk.virtualWrite(V18, bearing);
    myMap.location(move_index, latitude, longitude, "GPS_Car");
  }
  Serial.println();
}

void repeat()
{
  while (mygps.available() > 0)
  {
    if (gps.encode(mygps.read()))
      displayInfo();
  }
  timer.run();
}
 
#endif
