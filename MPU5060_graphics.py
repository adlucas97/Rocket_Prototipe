import serial
import time
import matplotlib.pyplot as plt
from drawnow import *

ser = serial.Serial('COM7',57600,timeout=1)
ser.close()
ser.open()

time.sleep(1)

data_ax = list(0 for i in range(0,100))
data_ay = list(0 for i in range(0,100))
data_az = list(0 for i in range(0,100))

plt.ion()
count = 0

def plotValues():
	plt.title('Aceleracion X vs Tiempo')
	plt.grid(True)
	plt.ylabel('Aceleracion')
	plt.plot(data_ax, label='a_x')
	plt.plot(data_ay, label='a_y')
	plt.plot(data_az, label='a_z')
	plt.legend(loc='upper right')
	plt.ylim(-15, 15)

def shift_list(data,value): 
	data.append(value) 
	data.pop(0)
	return data

while True: 

	data = ser.readline()
	if data: 

		string = data.decode().strip()
		a_xyz = list(string.split(","))

		a_x = float(a_xyz[0])
		a_y = float(a_xyz[1])
		a_z = float(a_xyz[2])

		data_ax = shift_list(data_ax,a_x)
		data_ay = shift_list(data_ay,a_y)
		data_az = shift_list(data_az,a_z)
		drawnow(plotValues)

ser.close()

