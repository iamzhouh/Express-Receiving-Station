/*
温湿度传感器引脚：GPIO:2  VCC:3v
TTS语音模块  软串口：GPIO:5  6 VCC:5v 
超声波 lv物：GPIO:Trig->8  Echo->9  VCC:5v
超声波 lan人:GPIO: Trig->10 Echo->11  VCC:5V
*/
#include "DHT.h"  
#include "cn.c"
#include <SoftwareSerial.h>
#include <DFRobot_URM10.h>

DFRobot_URM10 urm101(8,9);
DFRobot_URM10 urm102(10,11);

//软串口
SoftwareSerial softwareserial1(5,6);//rx:5  tx:6

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  softwareserial1.begin(9600);
  softwareserial1.listen();
  dht.begin();
}
void loop() {
  bool urm1;
  bool urm2;
  int Temperature = dht.readTemperature();
  int Humidity = dht.readHumidity();
  String data = "";
/*温湿度串口输出*/
//  Serial.print("Temperature:");
//  Serial.print(Temperature);
//  Serial.print("  Humidity:");
//  Serial.println(Humidity);

/*语音输出*/
//  softwareserial1.print(cn[0]);
//  delay(1500);

/*超声波输出*/
//  Serial.print((urm101.getDistanceCM()));
//  Serial.print("   ");
//  Serial.println((urm102.getDistanceCM()));

  if((urm101.getDistanceCM())>30)  //绿色  检测物
    urm1 = 0;
   else 
   {
    urm1 = 1;
    softwareserial1.print(cn[0]);
    delay(2000);
   }

  if((urm102.getDistanceCM())>30)  //蓝色  检测人
    urm2 = 0;
  else
    urm2 = 1;

  data = "#"+ String(Temperature) + "#" + String(Humidity) + "#" + String(urm1) + "#" + String(urm2) + "#";
  if(data.length()>=9)
  {
    Serial.println(data);
  }
}
