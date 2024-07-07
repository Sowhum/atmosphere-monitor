#ifndef KY015_H
#define  KY015_H
#include <stdint.h>
#include <Arduino.h>

class KY015{
    private:
    float temp_data;
    float humidity_data;
    int KY_PIN;
    bool checksum;
    byte data;
    byte data_arr[5];
    byte get_byte();

    public:
        KY015(int pin){
            KY_PIN=pin;
        }

        //functions
        void begin();
        float get_temp();
        float get_humidity();
        bool get_checksum();
};
#endif