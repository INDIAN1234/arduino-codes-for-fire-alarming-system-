#Code for arduino implementation of Arduino Uno ,MQ2 sensor ,BMP180 sensor, Buzzer.



#include <Wire.h>
#include <MQ2.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
int Analog_Input = A0;
int lpg, co, smoke;
MQ2 mq2(Analog_Input);
int buzzer = 10;
int smokeA0 = A0;
int sensorThres = 50;
void setup(void) 
{
    Serial.begin(9600);
  mq2.begin();
  Serial.begin(9600);
  Serial.println("Pressure Sensor Test"); Serial.println("");
  if(!bmp.begin())
  {
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
}
void loop(void) 
{ 
  float* values= mq2.read(true);
  lpg = mq2.readLPG();
  co = mq2.readCO();
  smoke = mq2.readSmoke();
  delay(5);
  sensors_event_t event;
  bmp.getEvent(&event);
  int analogSensor = analogRead(smokeA0);
  if (analogSensor > sensorThres)
  {
    tone(buzzer, 1100, 700);
  }
  else
  {
    noTone(buzzer);
  }
  delay(5);
  if (event.pressure)
  {
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure)); 
    Serial.println(" m");
    Serial.println("");
  }
  else
  {
    Serial.println("Sensor error");
  }
  delay(100);
}
