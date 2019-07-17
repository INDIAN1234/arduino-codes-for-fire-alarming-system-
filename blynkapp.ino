#implementation of fire security system using ESP8266 NodeMcu ,MQ2 sensor using Blynk app.

#define BLYNK_PRINT Serial
#include <MQ2.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "e33ee9c19e474249b496cc52f7e7f3e4";              //Your Project authentication key
char ssid[] = "Nokia 6.1";                                       // Name of your network (HotSpot or Router name)
char pass[] = "password";                                      // Corresponding Password
MQ2 mq2(A0);
int gas_value;
int gas_avalue;
void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  mq2.begin();
  BLYNK_READ(V6);
  BLYNK_READ(V5);
  BLYNK_READ(V4);
}
void loop()
{
  Blynk.run();
  gas_avalue = analogRead(A0);
  float* values = mq2.read(true);
  Serial.println("READING");
  if (gas_avalue > 1)
  {
        float lpg = mq2.readLPG(); //reading the sensor on A0
        float co = mq2.readCO(); //reading the sensor on A0
        float smoke = mq2.readSmoke(); //reading the sensor on A0
        delay(100);
        Blynk.virtualWrite(V6, lpg); //sending to Blynk
        Blynk.virtualWrite(V5, co); //sending to Blynk
        Blynk.virtualWrite(V4, smoke); //sending to Blynk
   }
  // else {
   //Serial.println("NO LEAKAGE");
// }
 //delay(100);
  
}
