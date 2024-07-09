#include "helpers.h"

void setup(){
  WIRE.begin();
  Serial.begin(115200);
  mpu.readFail=false;
  mpu.pwr_setup();
  if(!SD.begin(CS)){
    sdFail = true;
  }
  lcd.init();
  lcd.backlight();
  delay(1000);    
}

void loop(){
  //temp, humidity from KY015
  float temperatureKY = ky.get_temp();
  float humidityKY = ky.get_humidity();

  //temp from MPU6050
  float temperatureMPU = t.TempC;

  checkData(temperatureKY,temperatureMPU);
  
  //display 
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.printf("T1: %.1fC, T2: %.1fC", round(temperatureKY * 10) / 10, round(temperatureMPU * 10) / 10);
    lcd.setCursor(0,1);
    lcd.printf("Humidity: %.2f %", round(humidityKY*100)/100);
 
  //logging
  currentTime = millis();
  sprintf(
        data, outputFormat,
        temperatureKY, temperatureMPU, humidityKY,(temperatureKY+temperatureMPU)/2  ,currentTime);
  if (currentTime - lastLog >= LOGFREQ) {  
    logData(data);
    lastLog = currentTime;
  }
}

