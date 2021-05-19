#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

int motor=2;  //LED
char incoming_BT_value =0;
int trigpin=4;
int echopin=5;

void setup() {
   Serial.println("data");
   SerialBT.begin("ESP32test"); //Bluetooth device name
   Serial.println("The device has started, now you can pair it with bluetooth!");
   pinMode(motor, OUTPUT);
   Serial.begin(115200);
   pinMode(trigpin,OUTPUT);
   pinMode(echopin,INPUT);
   delay(1000);
   
}

void loop() {
  if(Serial.available()){
    SerialBT.write(Serial.read());
  }
  if(SerialBT.available()){
    SerialBT.write(SerialBT.read());
  }
  
 digitalWrite(trigpin,HIGH);
 delay(1000);
 digitalWrite(trigpin,LOW);
int duration=pulseIn(echopin,HIGH);
int distance=duration*0.343/2;  //velocity of air=0.343
 Serial.println("the distance is");
 Serial.print(distance);
 char incoming_value=1;
     if(SerialBT.available()==1){  
       incoming_value=SerialBT.read(); 
     
 if(distance<100)
 {
      SerialBT.print("the water pump level = ");
 SerialBT.println(distance);
 delay(2000);
     
   SerialBT.println("Water Tank  is Full ");
   delay(1000);
      SerialBT.println("water overflow: TURN OFF THE MOTOR ");
    delay(1000); 
 }
 
  else if(distance>=100)
 {
   SerialBT.println("the water pump level = ");
 SerialBT.print(distance);
 delay(2000);
     
 
  SerialBT.println("LOW Water Level"); 
  delay(1000);
  SerialBT.println("water underflow: TURN ON THE MOTOR ");
  delay(1000);
     
}
     }
     if(SerialBT.available()>0){
       incoming_BT_value=SerialBT.read(); 
     }
        if(incoming_BT_value=='1'){
          digitalWrite(motor,HIGH);
      }
    else if(incoming_BT_value=='0'){
      digitalWrite(motor,LOW);
      }

}
