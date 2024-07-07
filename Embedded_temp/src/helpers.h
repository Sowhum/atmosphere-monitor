////    Includes    ////
#include <Arduino.h>
#include "Wire.h"
#include <MPU6050.h>
#include <KY015.h>
#include <LiquidCrystal_I2C.h>

////    Defines     ////
#define LCD_ADDR      0x27
#define KY_PIN        5
#define BUZZER        PIN_A12
#define LED           PIN_A11 
#define SERIAL_MONITOR_BAUD 115200

String file_name = "log.txt";
MPU mpu;
KY015 ky = KY015(KY_PIN);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDR, 16, 2);