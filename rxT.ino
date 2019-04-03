#include <RH_ASK.h>

#include <SPI.h> 
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial mySerial(18,17);//A3,A4

const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint8_t buf[3];
uint8_t buflen = sizeof(buf);

#define waterSensePin A0     
#define tankLevelPin A1
#define rainPin A2
#define motorPin A5

#define rainThreshold 30

#define stateReset 0
#define stateSoil 1
#define stateRain 2
#define stateWatering 3
int S1=stateReset;

 

RH_ASK rf_driver;
 
void setup()
{
    rf_driver.init();
    lcd.begin(16, 2);
    mySerial.begin(9600);
    Serial.begin(9600);
    lcd.setCursor(0, 1);
}
 
void loop()
{
  int rain=analogRead(rainPin);
  rain=map(rain,0,1023,0,100);
  constrain(rain,0,100);
switch(S1)
{

 case stateReset:

    if (rf_driver.recv(buf, &buflen))
    {
      messageSoil();
      S1=stateWatering;
    }
      if(rain<rainThreshold)
      {
          S1=stateRain;
      }
     
     break;
 case stateRain:
 lcd.clear();
 lcd.setCursor(0,1);
 delay(100);
 lcd.print("Rain");
      messageRain();
      delay(1000);
      S1=stateReset;
      break;
 
 case stateWatering:
      lcd.clear();
      lcd.setCursor(0,1);
      digitalWrite(motorPin,HIGH);
      delay(2000);
      if(analogRead(waterSensePin)>50)
      {
        if(analogRead(tankLevelPin)>10)
        {
          motorSick();
        }
        else 
        {
          tankEmpty();
        }
      }
      lcd.print("Waterng");
      delay(10000);
      S1=stateReset;
      break;
}
}

void messageRain()
    {
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
      Serial.println("AT+CMGS=\"+916297357195\"\r"); // Replace x with mobile number
     mySerial.println("AT+CMGS=\"+916297357195\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("Hello its Raining");// The SMS text you want to send
     Serial.println("hello");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
    }

void motorSick()
    {
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
      Serial.println("AT+CMGS=\"+916297357195\"\r"); // Replace x with mobile number
     mySerial.println("AT+CMGS=\"+916297357195\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("Hello maybe the motor is sick");// The SMS text you want to send
     Serial.println("hello");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
    }
    void tankEmpty()
    {
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
      Serial.println("AT+CMGS=\"+916297357195\"\r"); // Replace x with mobile number
     mySerial.println("AT+CMGS=\"+916297357195\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("No water in Tank");// The SMS text you want to send
     Serial.println("hello");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
    }
    void messageSoil()
    {
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
      Serial.println("AT+CMGS=\"+916297357195\"\r"); // Replace x with mobile number
     mySerial.println("AT+CMGS=\"+916297357195\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("Time to water");// The SMS text you want to send
     Serial.println("hello");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
    }
        void call()
    {
           Serial.println("Calling through GSM Modem");
          mySerial.begin(9600);//setting baudrate at 9600;
          delay(1000);
          mySerial.println("ATD6297357195;"); // ATDxxxxxxxxxx; semicolon should be at the last ;AT command that follows UART protocol;
          Serial.println("Called ATD6297357195");
          delay(1000);
    }
   

