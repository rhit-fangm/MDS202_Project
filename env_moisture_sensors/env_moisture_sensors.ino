/*MDS202 Environmental Sensor Code
Written on 6/11/2024
Written by: Michael Fang, Theo Mitz, Iman Noorani*/

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define PHOTORES A1
#define DHTTYPE DHT11   // DHT 11
#define MOISTURE_PIN 0  //moisutre sensor connected to A0
#define LED_PIN 13      //pin assignment for LED
#define MOISTURE_LED_THRESHOLD 800 //threshold for turning on/off led for moisture

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

int light_val; //reading of light from photoresistor

void setup() {
  pinMode(MOISTURE_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(500);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  int m=0; //value for moisture sensor readings/avg calculations

  for (int i = 0; i < 10; i++) {
    delay(1000);
    delay(300);

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    h += dht.readHumidity();
    // Read temperature as Celsius (the default)
    t += dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    f += dht.readTemperature(true);
    //read moisture sensor
    m += analogRead(MOISTURE_PIN);
  }

    }
  h = h/10;
  t = t/10;
  f = f/10;

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  // read light value from photoresistor
  light_val = analogRead(PHOTORES);

  if(analogRead(MOISTURE_PIN) < MOISTURE_LED_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
  } 
  else {
    digitalWRITE(LED_PIN, LOW);
  }
    } 
    else {
      digitalWRITE(LED_PIN, LOW);
    }

<<<<<<< Updated upstream
  //calculate average values for moisture probe
  int nums[10];
  for (int i=0; i<10; i++) {
    nums[i] = analogRead(MOISTURE_PIN);
    delay(100);
  }
  int sum=0;
  int avg=0;
  for (int i=0; i<10; i++) {
    sum+=nums[i];
  }
  avg=sum/10;
  Serial.print("Moisture (avg): ");
  Serial.println(avg);

=======
  //calculate average value for moisture probe readings
  m=m/10;

  Serial.print("Soil moisture (avg): ");
  Serial.println(m);

>>>>>>> Stashed changes
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.print(F("°F  "));
  Serial.print("Photoresistor value: ");
  Serial.println(light_val);
}
