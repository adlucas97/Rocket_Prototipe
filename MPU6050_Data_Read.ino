#include "Wire.h"
 
//ADDR MPU6050 
#define MPU_ADDR 0x68
 
//Conversion Ratio
#define Acc_R 16384.0   // 32768/2
#define Gyro_R 131.0     // 32768/250
#define E_gravity 9.81  //Earth gravity
 
//Rad to Grad
#define RAD_TO_DEG 57.295779
 
//RAW values
int16_t acc_x, acc_y, acc_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature; 
 
//variables useful to determinde Yaw, Pitch, Roll
float acc[3];
float ang_acc[3]; 
float gyro[3];
float angle[3];
 
long tiempo_prev;
float dt;

String valores;
 
void setup()
{
 Wire.begin(); // D2(GPIO4)=SDA / D1(GPIO5)=SCL
 Wire.beginTransmission(MPU_ADDR);
 Wire.write(0x6B);
 Wire.write(0);
 Wire.endTransmission(true);
 Serial.begin(115200);
}
 
void loop()
{
   
   Wire.beginTransmission(MPU_ADDR);
   Wire.write(0x3B); //starting with register 0x3B (ACCEL_XOUT_H)
   Wire.endTransmission(false); //The parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
   Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers

   acc_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
   acc_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
   acc_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
   
   temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
   
   gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
   gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
   gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L) 

   //Acceleration Calculation
   acc[0] = (acc_x/Acc_R)*E_gravity;
   acc[1] = (acc_y/Acc_R)*E_gravity;
   acc[2] = (acc_z/Acc_R)*E_gravity;
   
   //Roll and Pitch calculation
   ang_acc[1] = atan(-1*(acc[0])/sqrt(pow((acc[1]),2) + pow((acc[3]),2)))*RAD_TO_DEG;
   ang_acc[0] = atan((acc[1])/sqrt(pow((acc[0]),2) + pow((acc[3]),2)))*RAD_TO_DEG;

   //Angular Rate Calculation
   gyro[0] = gyro_x/Gyro_R;
   gyro[1] = gyro_y/Gyro_R;
   gyro[2] = gyro_z/Gyro_R;
 
   dt = (millis() - tiempo_prev) / 1000.0;
   tiempo_prev = millis();
 
   //Aplicar el Filtro Complementario
   angle[0] = 0.98 *(angle[0]+gyro[0]*dt) + 0.02*gyro[0];
   angle[1] = 0.98 *(angle[1]+gyro[1]*dt) + 0.02*gyro[1];
 
   //Integración respecto del tiempo paras calcular el YAW
   angle[2] = angle[2]+gyro[2]*dt;
 
   //Mostrar los valores por consola
   valores = "90, " +String(angle[0]) + "," + String(angle[1]) + "," + String(angle[2]) + ", -90";
   Serial.println(valores);
   
   delay(10);
}
