#ifndef HELPERS_H
#define HELPERS_H

////    Includes    ////
#include <Arduino.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <MPU6050.h>
#include <KY015.h>
#include <LiquidCrystal_I2C.h>

////    Defines     ////
#define LCD_ADDR      0x27
#define KY_PIN        4
#define CS            5
#define BUZZER        9
#define LED1          10
#define LED2          11
#define WIRE          Wire
#define MAX_VALUE     32.5
#define LOGFREQ       5000
#define SERIAL_MONITOR_BAUD 115200

////    Objects/Variables     ////
TStruct t;
char data[256];
String fileName = "log.txt";
unsigned long currentTime;
unsigned long lastLog=0;
const char outputFormat[] =
    R"""(Temp1: %f, Temp2: %f, Humidity: %f, Avg: %f, Time Stamp: %lu
)""";

MPU mpu;
KY015 ky = KY015(KY_PIN);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDR, 16, 2);

////    Fucntions   ////
void checkData(float tKY, float tMPU){
    if(!ky.get_checksum()){
        digitalWrite(LED1,HIGH);
        delay(1000);
        digitalWrite(LED1,LOW);
    }
    if(mpu.readFail==true){
        digitalWrite(LED2,HIGH);
        delay(1000);    
        digitalWrite(LED2,LOW);
    }

    if(tKY >= MAX_VALUE | tMPU >=MAX_VALUE){
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,HIGH);
        digitalWrite(BUZZER,HIGH);

        delay(1000);
        digitalWrite(BUZZER,LOW);
    }
    else{
        digitalWrite(LED1,LOW);
        digitalWrite(LED2,LOW);
        digitalWrite(BUZZER,LOW);
    }
}
#endif HELPERS_H
