#implementation of ESP8266 NodeMcu ,MQ2 sensor, Buzzer using IFTTT(IOT mail notification alert). 

#include <ESP8266WiFi.h>
WiFiClient client;
String MakerIFTTT_Key ;
;String MakerIFTTT_Event;
char *append_str(char *here, String s) {  int i=0; while (*here++ = s[i]){i++;};return here-1;}
char *append_ul(char *here, unsigned long u) { char buf[20]; return append_str(here, ultoa(u, buf, 10));}
char post_rqst[256];char *p;char *content_length_here;char *json_start;int compi;
int Gas_pin = A0; 
int buzzer = D1;
void setup()
{
  Serial.begin(9600);
  WiFi.disconnect();
  delay(3000);
  Serial.println("start........");
   WiFi.begin("Nokia 6.1","password");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
  }
   pinMode(Gas_pin,INPUT);
  Serial.println(".................");
  Serial.println("connected");
  
}


void loop()
{
int Gas_state = analogRead(Gas_pin);
Serial.println(Gas_state);

   if (Gas_state >=20)
  
 {  
  if (client.connect("maker.ifttt.com",80)) {
    MakerIFTTT_Key ="g4R4lfE4yvFQaTlnRiGJwHnL8AToD7xqtjy68LZwXuT";
    MakerIFTTT_Event ="Fire_Security_System";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "NodeMCU");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "hi keshav how are you......");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "FIRE EMERGENCY ALERT");
    p = append_str(p, "\"}");

    compi= strlen(json_start);
    content_length_here[0] = '0' + (compi/10);
    content_length_here[1] = '0' + (compi%10);
    client.print(post_rqst);
     
   
    tone(buzzer, 3000, 500);
  }
  else
  {
    noTone(buzzer);
  }
  delay(5);

  
  Serial.println("your email has been sent...");
  Serial.println("Gas leakage is detected");
  delay(5000);
  }
   
   else 
   
    Serial.println("No gas");
  
   }