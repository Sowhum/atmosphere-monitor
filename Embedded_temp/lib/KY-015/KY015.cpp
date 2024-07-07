#include "KY015.h"

byte KY015::get_byte(){
    data=0;
    for(int i=0;i<8;i++){
        while(digitalRead(KY_PIN)==LOW);
        delayMicroseconds(30);

        if(digitalRead(KY_PIN)==HIGH){
            data |=1<<(8-i);
        }
        while(digitalRead(KY_PIN==HIGH));
    }
    return data;
}
void KY015::begin(){
    pinMode(KY_PIN, OUTPUT);

    digitalWrite(KY_PIN, LOW); 
    delay(30);              
    digitalWrite(KY_PIN, HIGH);
    delayMicroseconds(40);  

    pinMode(KY_PIN, INPUT);    
    while (digitalRead(10) == HIGH);    
    delayMicroseconds(80); 
    if (digitalRead(KY_PIN) == LOW){
        delayMicroseconds(80);
        for (int i = 0; i < 5; i++){ // receive temperature and humidity values
         data_arr[i] = get_byte();
        }
    }
    
    pinMode(KY_PIN, OUTPUT);   
    digitalWrite(KY_PIN, HIGH); 

    temp_data = int(data_arr[0]) + int(data_arr[1])/100;
    humidity_data = int(data_arr[2]) + int(data_arr[3])/100;

    if(data_arr[4]==data_arr[0]+data_arr[1]+data_arr[2]+data_arr[3]){checksum=true;}
    else{checksum=false;}
}

float KY015::get_temp(){
    return(temp_data);
}

float KY015::get_humidity(){
    return(humidity_data);
}

bool KY015::get_checksum(){
    return(checksum);
}