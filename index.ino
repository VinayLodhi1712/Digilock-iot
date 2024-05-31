const int trigPin = 5;
const int echoPin = 4;
#define ON 1
#define OFF 0
int present_condition = 0;
int previous_condition = 0;
int vibration_Sensor = 16;
long duration;
int distance;
int LED = 13;

#define BLYNK_TEMPLATE_ID "TMPL3e5x_Lq8M"
#define BLYNK_TEMPLATE_NAME "Ultra"
#define BLYNK_AUTH_TOKEN "mtPZPLi1GELkJl-NndewnEYy5ZbKfwZ3"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "mtPZPLi1GELkJl-NndewnEYy5ZbKfwZ3";
char ssid[] = "Vinay";
char pass[] = "patterns";

void setup() {
  Serial.begin(9600);
  pinMode(vibration_Sensor, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(12, OUTPUT);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V2) {
  bool value1 = param.asInt();
  Serial.println(value1);
  // Check these values and turn the relay1 ON and OFF
  if (value1 == 0) {
    digitalWrite(12, LOW);
    Blynk.logEvent("Lockclose");
  } else {
    digitalWrite(12, HIGH);
    Blynk.logEvent("Lockopen");
  }

}
void led_blink(void);
void loop() {
  previous_condition = present_condition;
  present_condition = digitalRead(16);
  Serial.println(present_condition);  // Reading digital data from the A5 Pin of the Arduino.
  if (previous_condition != present_condition) {
    led_blink();
    Blynk.logEvent("Doorknock");
  } else {
    digitalWrite(LED, OFF);
    digitalWrite(15, LOW);
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance < 25) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(2, HIGH);
      delay(50);
      digitalWrite(2, LOW);
      delay(50);
    }
    delay(1000);
  } else {
    digitalWrite(0, LOW);
  }
  Blynk.run();
  Blynk.virtualWrite(V0, distance);
  Blynk.virtualWrite(V1, present_condition);
  delay(100);
}

void led_blink(void) {
  digitalWrite(LED, ON);
  digitalWrite(15, HIGH);
  delay(250);
  digitalWrite(LED, OFF);
  digitalWrite(15, LOW);
  delay(250);
  digitalWrite(LED, ON);
  digitalWrite(15, HIGH);
  delay(250);
  digitalWrite(LED, OFF);
  digitalWrite(15, LOW);
  delay(250);
  digitalWrite(LED, ON);
  digitalWrite(15, HIGH);
  delay(250);
  digitalWrite(LED, OFF);
  digitalWrite(15, LOW);
  delay(250);
  digitalWrite(LED, ON);
  digitalWrite(15, HIGH);
  delay(250);
  digitalWrite(LED, OFF);
  digitalWrite(15, LOW);
  delay(250);
}
