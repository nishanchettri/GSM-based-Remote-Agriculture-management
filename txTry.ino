#include <RH_ASK.h>
#include<stdlib.h>
#include <SPI.h> 
RH_ASK rf_driver;
char soilValue[20];
#define soil A0
int soilRead;
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
}
 
void loop()
{
    soilRead=analogRead(soil);
    soilRead=map(soilRead,0,1023,0,100);
    constrain(soilRead,0,90);
    itoa(soilRead,soilValue,10);
    if(soilRead>40)
    {
    rf_driver.send((uint8_t *)soilValue, strlen(soilValue));
    rf_driver.waitPacketSent();
    delay(1000);
    }
}
