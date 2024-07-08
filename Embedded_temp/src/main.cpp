#include "helpers.h"

void setup(){
  WIRE.begin();
  Serial.begin(115200);
  SD.begin(CS);
  mpu.readFail=false;
  mpu.pwr_setup();

  delay(1000);    
}

void loop(){
  //temp, humidity from KY015
  float temperatureKY = ky.get_temp();
  float humidityKY = ky.get_humidity();

  //temp from MPU6050
  float temperatureMPU = t.TempC;

  checkData(temperatureKY,temperatureMPU);
  
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

void logData(char data[]) {
  File logFile = SD.open(fileName, FILE_WRITE);
  if (logFile) {
    logFile.println(data);
    logFile.close();
  } else {
    Serial.println("Error opening log.txt");
  }
}