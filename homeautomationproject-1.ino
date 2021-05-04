#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#include "DHT.h" //DHT11
#define DHTPIN 4 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int led1=12;
int led2=0;
int fan1=2;
int fan2=15;
void setup() {
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(fan1,OUTPUT);
 pinMode(fan2,OUTPUT);
  Serial.begin(9600);
  delay(2000);
Serial.println("oled test");
Serial.println(F("DHTxx test!"));
 dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  delay(2000);
  
}

void loop() {
  int LDRValue=analogRead(32);
  double dV=LDRValue; 
  Serial.println(LDRValue);
  double le=(dV/4095)*100;
  int level=le;
  Serial.print("ldr value is");
  Serial.print(level);
  Serial.print("%");
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Light level=");
  display.print(level);
   display.print("%");
   delay(1000);
     display.display(); 
display.setCursor(3, 25);
  if(level>=0 && level<=10){
    display.print("DARK");
    delay(1000);
    //display.setCursor(4, 10);
    display.println("LIGHT STATUS:ON");
    delay(2000);
      display.display(); 
    display.clearDisplay();
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
  }
  else if(level>10 && level<50){
    display.println(" MODERATELY BRIGHT ");
    delay(1000);
    display.println("LIGHT STATUS:ON ");
    delay(1000);
      display.display(); 
    display.clearDisplay();
   digitalWrite(led1,200);
   digitalWrite(led2,200);
  }
  else{
    display.println("EXTREMELY BRIGHT");
    delay(1000);
    display.println("LIGHT STATUS:OFF ");
    delay(1000);
      display.display(); 
    display.clearDisplay();
    digitalWrite(led1,LOW);
   digitalWrite(led2,LOW);
  }
  
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); // Read temperature as Celsius (the default)
  float f = dht.readTemperature(true); // Read temperature as Fahrenheit (isFahrenheit = true)
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
}

  Serial.print(F("Humidity: "));
  Serial.println(h);
  Serial.print(F("%  Temperature: "));
  Serial.println(t);
  Serial.print(F("°F "));
  Serial.println(f);
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
 // display.setCursor(0,10);
  display.print("TEMPERATURE = ");
  display.println(t);
  //display.setCursor(2,10);
  display.print("°F =");
  display.println(f);
  display.setCursor(3,10);
  display.print("HUMIDITY = ");
  display.println(h);
    display.display(); 
  delay(2000);
  display.clearDisplay();
  
  int maxtemp=50;
  int maxhumid=80;
  display.setCursor(3,30  );
 
      if((t>=maxtemp) || (h>=maxhumid)){
    display.println("TEMPERATURE IS HIGH OUTSIDE");
    delay(1000);
    display.println("FAN STATUS:ON ");
    delay(1000);
      display.display(); 
    display.clearDisplay();
    digitalWrite(fan1,HIGH);
   digitalWrite(fan2,HIGH);
      }
       else if((t>=5&&t<20) ||(h==0) ){
    display.println("TEMPERATURE IS LOW OUTSIDE");
    delay(1000);
    display.println("FAN STATUS:OFF ");
    delay(1000);
      display.display(); 
    display.clearDisplay();
    digitalWrite(fan1,LOW);
    digitalWrite(fan2,LOW);
       }
      else{
    display.println("TEMPERATURE IS MODERATE OUTSIDE");
    delay(1000);
    display.println("FAN STATUS:ON ");
    delay(1000);
      display.display(); 
    display.clearDisplay();
    digitalWrite(fan1,HIGH);
    digitalWrite(fan2,300);
      }
       
      
  //display.display(); 
  
}
