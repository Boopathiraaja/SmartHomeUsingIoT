#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "homeiot-c2458.firebaseio.com"
#define FIREBASE_AUTH "F80tgfdvJzO8YyMH6YmnTBdRtevJHVzZaCOhPEPR"
#define WIFI_SSID "wifi_name"
#define WIFI_PASSWORD "wifi_password"
int temp;
void setup()
 {
   int a=0;
   int n=0;
   int k=0;
   Serial.begin(9600);
   pinMode(D7,OUTPUT);
   pinMode(D5,OUTPUT);
   pinMode(D6,OUTPUT);
   WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
   Serial.print("connecting");
   while (WiFi.status() != WL_CONNECTED)
     {
       Serial.print(".");
       delay(500);
     }
   Serial.println();
   Serial.print("connected: ");
   Serial.println(WiFi.localIP());
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 }
void loop()
 {
  temp= A0;
  int n=Firebase.getInt("Light");
  int a=Firebase.getInt("Fan");
  int k=Firebase.getInt("AC");
  if (n==1)
   {
     Serial.println("Light ON");
     digitalWrite(D7,HIGH);
     delay(100);
   }
  else
   {
     Serial.println("Light OFF");
     digitalWrite(D7,LOW);
   }
  if (a==1)
    {
     Serial.println("Fan ON");
     digitalWrite(D5,HIGH);
     delay(100);
    }
  else
   {
    Serial.println("Fan OFF");
    digitalWrite(D5,LOW);
   }
  if (k==1)
   {
    Serial.println("AC ON");
    digitalWrite(D6,HIGH);
    delay(100);
   }
  else
   {
    Serial.println("AC OFF");
    digitalWrite(D6,LOW);
   }
  int analogValue = analogRead(temp);
  float millivolts = (analogValue/1024.0) * 3300;
  float celsius = millivolts/10;
  Serial.print("Temperature : ");
  Serial.println(celsius);
  Firebase.setFloat("Temperature",celsius);
}
