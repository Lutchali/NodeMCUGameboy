#include <SPI.h>  
#include <TFT_eSPI.h>
#include <MPU9250.h>

int X = 155;
int Y = 115;
int prevX = 0;
int prevY = 0;
int accelX = 0;
int accelY = 0;

MPU9250 Sensor(Wire,0x68); 
TFT_eSPI tft = TFT_eSPI();

void setup() {  
  Serial.begin(115200);
  Sensor.begin(); 
  Sensor.setAccelRange(MPU9250::ACCEL_RANGE_8G);      
  Sensor.setGyroRange(MPU9250::GYRO_RANGE_500DPS);   
  Sensor.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  Sensor.setSrd(19);     
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(TFT_RED);                             
}
void loop() {  
  Sensor.readSensor();     
  Serial.print(Sensor.getAccelX_mss(),0);             
  Serial.print("\t");  
  Serial.print(Sensor.getAccelY_mss(),0);  
  Serial.print("\t");  
  Serial.print(Sensor.getAccelZ_mss(),0);  
  Serial.print("\t");  
  Serial.print(Sensor.getGyroX_rads(),0);  
  Serial.print("\t");  
  Serial.print(Sensor.getGyroY_rads(),0);  
  Serial.print("\t");  
  Serial.print(Sensor.getGyroZ_rads(),0);  
  Serial.print("\t");  
  Serial.print(Sensor.getMagX_uT(),0);  
  Serial.print("\t");  
  Serial.print(Sensor.getMagY_uT(),0);  
  Serial.print("\t");  
  Serial.print(Sensor.getMagZ_uT(),0);  
  Serial.print("\t");  
  Serial.println(Sensor.getTemperature_C(),0);  
  accelY = 10 * -Sensor.getAccelX_mss();
  accelX = 10 * Sensor.getAccelY_mss();
   if ((X + accelX < 321) and (X + accelX > 0)){
    X = X + accelX;  
  }
  else{
    X = 155;
  }
  if ((Y + accelY < 200) and (Y + accelY > 0)){
    Y = Y + accelY;  
  }
  else{
    Y = 115;
  }
  tft.fillRect(prevX,prevY,10,10,TFT_BLACK);
  tft.fillRect(X,Y,10,10,TFT_RED);
  tft.fillRect(1,200,320,40,TFT_GREEN);
  prevX = X;
  prevY = Y;
  delay(20);
}
