#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = ""; //Enter the authentication code sent by Blynk to your Email
char ssid[] = ""; //Enter your WIFI SSID
char pass[] = ""; //Enter your WIFI Password
int flag=0;



void notifyOnButtonPress()
{
  int isButtonPressed = digitalRead(D1);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("Someone Opened the door");
    Blynk.notify("Alert : Someone Opened the door");
    digitalWrite(D2,HIGH);//buzzer
    digitalWrite(D6,HIGH);//led red
    digitalWrite(D7,LOW);//LED GREEN OFF
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    digitalWrite(D2,LOW);
    digitalWrite(D6,LOW);//LED RED ON
    digitalWrite(D7,HIGH);//led green
    flag=0;
  }
}
void setup()
{
Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
pinMode(D1,INPUT_PULLUP);//reed switch
pinMode(D2,OUTPUT);//buzzer
pinMode(D6,OUTPUT);//led red
pinMode(D7,OUTPUT);//led green
timer.setInterval(2000L,notifyOnButtonPress); 
}
void loop()
{
  Blynk.run();
  timer.run();
}
