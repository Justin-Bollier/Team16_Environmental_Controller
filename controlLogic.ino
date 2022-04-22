#include peripheralLibraries.h //placeholder

//define pin definitions, numbers are placeholders and need proper definitions
#define LIGHT_RELAY 2
#define LAMP_RELAY 3
#define FAN_RELAY 4
#define MIST_RELAY 5
#define WATER_PUMP 6
#define TEMP_SENSOR 7
#define WATER_SENSOR 8
#define HUMIDITY_SENSOR 9
#define LIGHT_SENSOR 10 //assuming PAR sensor included

//define global variables
float waterLevel;
float humidityLevel;
float currentTemp;
float lightLevel; //assuming PAR sensor included

void setup() {
  // put your setup code here, to run once:
  pinMode (LIGHT_RELAY, OUTPUT);
  pinMode (LAMP_RELAY, OUTPUT);
  pinMode (FAN_RELAY, OUTPUT);
  pinMode (MIST_RELAY, OUTPUT);
  pinMode (WATER_PUMP, OUTPUT);
  pinMode (TEMP_SENSOR, INPUT);
  pinMode (WATER_SENSOR, INPUT);
  pinMode (HUMIDITY_SENSOR, INPUT);
  pinMode (LIGHT_SENSOR, INPUT);

  //fetch thresholds from mobile app UI
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTemp = analogRead (TEMP_SENSOR);
  waterLevel = analogRead (WATER_SENSOR);
  humidityLevel = analogRead (HUMIDITY_SENSOR);
  lightLevel = analogRead (LIGHT_SENSOR); //assuming PAR sensor included

  //fetch thresholds from mobile app UI, else use previous definitions

  if (waterLevel <= waterThreshold)
    digitalWrite (WATER_PUMP, HIGH);
  else
    digitalWrite (WATER_PUMP, LOW);

  if (humidityLevel <= humidityThreshold)
    digitalWrite (MIST_RELAY, HIGH);
  else
    digitalWrite (MIST_RELAY, LOW);

  if (currentTemp <= tempThreshold_low)
    digitalWrite (LAMP_RELAY, HIGH);
  else{
    digitalWrite (LAMP_RELAY, LOW);
    if (currentTemp >= tempThreshold_high) //add periodic fan enable regardless of temp (promotes healthy plant growth)
      digitalWrite (FAN_RELAY, HIGH);
    else
      digitalWrite (FAN_RELAY, LOW);

  if (lightLevel <= lightThreshold) //add light schedule and tune LIGHT_RELAY for non-binary changes (lower or raise light level instead of on/off)
    digitalWrite (LIGHT_RELAY, HIGH);
  else
    digitalWrite (LIGHT_RELAY, LOW);

  delay(30000); //time before loop repeats in ms
}
