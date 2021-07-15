// SOCIAL DISTANCE  + TEMPERATURE MONITORING SYSTEM

#include <Adafruit_NeoPixel.h>

int ledPin= 3;
int ledNo= 12;

Adafruit_NeoPixel strip= Adafruit_NeoPixel(ledNo,ledPin,NEO_RGB+NEO_KHZ800);

//Distancing
int buzzerPin= 2;
int echoPin= 6;
int trigPin= 5;
int minDistance = 100;
int maxDistance = 300;

//Temp
int tempPin = 0;
float temp;
#define redLED 10
float volt;

//Temp1
int tempPin_1 = 1;
float temp_1;
float volt_1;

void setup() 
{
  pinMode(redLED, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial. begin(9600);  
  strip.begin();
  for(int i = 0; i < ledNo; i++)
  {
   strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
}

void loop() 
{
  int distance = calcDistance();
  Serial.println(distance);
  int ledsToGlow = map(distance, minDistance, maxDistance, ledNo, 1);
  Serial.println(ledsToGlow);
  
   //TEMP1
   volt_1 = analogRead(tempPin_1);
   // read analog volt from sensor and save to variable temp
   temp_1 = volt_1 * 0.48828125;
   // convert the analog volt to its temperature equivalent
   Serial.print("TEMPERATURE_1 = ");
   Serial.print(temp_1); // display temperature value
   Serial.print("*C");
   Serial.println();
  
  if(ledsToGlow == 12 && 43>temp_1>38 )
  {
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }
  for(int i = 0; i < ledsToGlow; i++)
  {
    if(i < 4)
    {
      strip.setPixelColor(i,strip.Color(50,0,0));//green,red,blue
    }
    else if(i >= 4 && i < 8)
    {
      strip.setPixelColor(i,strip.Color(50,50,0));//green,red,blue
    }
    else if(i >= 8 && i < 12)
    {
      strip.setPixelColor(i,strip.Color(0,50,0));//green,red,blue
    }
  }
  for(int i = ledsToGlow; i < ledNo; i++)
  {
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
  delay(50);
  
  //TEMP
   volt = analogRead(tempPin);
   // read analog volt from sensor and save to variable temp
   temp = volt * 0.48828125;
   // convert the analog volt to its temperature equivalent
   Serial.print("TEMPERATURE = ");
   Serial.print(temp); // display temperature value
   Serial.print("*C");
   Serial.println();
  if(temp>38) {digitalWrite(redLED,HIGH); }
  else {digitalWrite(redLED,LOW); }
   delay(1000); // update sensor reading each one second
}

int calcDistance()
{
  long distance,duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/29/2;
  if(distance >= maxDistance)
  {
    distance = maxDistance;
  }
  if(distance <= minDistance)
  {
    distance = minDistance;
  }
  return distance;
}
