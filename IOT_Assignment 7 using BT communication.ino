#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int led=2;  
int fan=0;   
char incoming_BT_value = 0;
char incoming_value = 0;
void setup() {
   Serial.begin(9600);
    pinMode(led,OUTPUT);
  pinMode(fan,OUTPUT);
   Serial.println("data");
   SerialBT.begin("ESP32test"); //Bluetooth device name
   Serial.println("The device has started, now you can pair it with bluetooth!");


  delay(2000);
 Serial.println("oled test");
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  delay(2000);
  
}

void loop() {
   if(SerialBT.available()){
    SerialBT.write(SerialBT.read());
  }

  //LIGHT STATUS
  if(SerialBT.available()>0){
       incoming_BT_value=SerialBT.read(); 
     }
        if(incoming_BT_value=='1'){
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(3, 25);
          digitalWrite(led,HIGH);
          display.print("Light ON");
          delay(1000);
          display.clearDisplay();
          display.display(); 
         
      }
    else if(incoming_BT_value=='0'){
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(3, 25);
          digitalWrite(led,LOW);
          display.print("Light OFF");
          delay(1000);
          display.clearDisplay();
          display.display();       
      }

 //FAN STATUS
      if(SerialBT.available()>0){
       incoming_value=SerialBT.read(); 
     }
        if(incoming_value=='1'){
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(3, 25);
          digitalWrite(fan,HIGH);
          display.print("Fan ON");
          delay(1000);
          display.clearDisplay();
          display.display(); 
         
      }
    else if(incoming_value=='0'){
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(3, 25);
          digitalWrite(fan,LOW);
          display.print("Fan OFF");
          delay(1000);
          display.clearDisplay();
          display.display();       
      }
}
  
 
