#include <VirtualWire.h>
#include <VirtualWire_Config.h>
#include <MPU6050.h>
#include <I2Cdev.h>

MPU6050 sensor;

// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int ax, ay, az;
int gx, gy, gz;
String a_xyz = "";
String filtro_complemento = ""; 

long tiempo_prev;
float dt;
float ang_x, ang_y;
float ang_x_prev, ang_y_prev;

void setup() {
  Serial.begin(57600);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor
}

void loop() {
  // Leer las aceleraciones y velocidades angulares
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);

  float ax_m_s2 = ax * (9.81/16384.0);
  float ay_m_s2 = ay * (9.81/16384.0);
  float az_m_s2 = az * (9.81/16384.0);
  float gx_deg_s = gx * (250.0/32768.0);
  float gy_deg_s = gy * (250.0/32768.0);
  float gz_deg_s = gz * (250.0/32768.0);

  a_xyz = String(ax_m_s2)+","+String(ay_m_s2)+","+String(az_m_s2);

  //Mostrar las lecturas separadas por un [tab]
  //Serial.print("a[x y z] g[x y z]:\t");
  Serial.println(a_xyz);
  //Serial.print(ay); Serial.print("\t");
  //Serial.print(az); Serial.print("\t");
  //Serial.print(gx); Serial.print("\t");
  //Serial.print(gy); Serial.print("\t");
  //Serial.println(gz);

  delay(100);
}
