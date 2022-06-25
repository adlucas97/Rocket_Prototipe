###Read a single byte 
##clc;clear;
##pkg load instrument-control # comment this line, if you want to use this script in Matlab
##testport=serial("COM7");
###delay of 1sec
##pause(1); 
##
### Serial Settings
##set(testport,'baudrate',9600);
##set(testport,'bytesize',8);
##set(testport,'parity','n');
##set(testport,'stopbits',1);
##set(testport,'timeout',50); % timeout in seconds
##srl_flush(testport);
##
##for cnt= 1:10
##[rxdata,count]=srl_read(testport,8); # read 1 byte from COM port every 100ms
##recieved = char(rxdata)
##pause(0.1);
##end
##fclose(testport);


#puerto_serial = serial('COM7',9600);
#puerto_serial.BaudRate = 9600;

fopen(puerto_serial);
fwrite(puerto_serial,'a');

while 1
	P = fscanf(puerto_serial,'%f')
end
