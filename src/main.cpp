#include <Arduino.h>
#include <WiFi.h>
#include <TridentTD_LineNotify.h>

#define SSID "BTC2020-B"                                         //ใส่ชื่อ Wifi
#define PASSWORD "11111111"                                  //ใส่รหัส Wifi
#define LINE_TOKEN "ue2b1LRtbrk4FPny0FJCDx8GLAJPju929F2RH9Nga2k" //ใส่ TOKEN

const int trigPin = 19;
const int echoPin = 18;
const int led = 23; //D23

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
float distanceInch;

void setup()
{
  Serial.begin(115200);     // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting ", SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
}

void loop()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;

  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;

  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);

  if (distanceCm < 5)
  { //หากน้อยกว่า 20cm แจ้งเตือนไลน์
    digitalWrite(led, HIGH);
    Serial.println("Led: ON ");
    LINE.notify("ระยะ = " + String(distanceCm) + " cm");
  }
  else
  {
    digitalWrite(led, LOW);
    Serial.println("Led: OFF ");
  }
  delay(1000);
}