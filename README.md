# System configuration
## power supply
PC - Arduino Uno - Air pressure sensor  
　　　　　　　　- Relay - Solenoid Valve - Airbags  
Power Supply (24V) 」 

## master PC　（When you get the value of the air pressure sensor）
1. Comment out and in the specified area of the code
2. White exhibition.ino in Arduino (Don't forget to put rosserial_arduino library in Arduino IDE)
3. Start roscore
4. Start commuication through rosserial 
```
  rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=57600   
```
