# I²C Translator 
Author - Brendan Parvin  
## Summary  
This devices allows for a signle, selectable I²C address to be translated to a different, selectable I²C address --- on the fly. This allows slaves with the same hardwired address to coexist on a single I²C bus.  
![image](https://github.com/user-attachments/assets/3a0603a6-0fbe-471c-bf71-87b2919359b6)
## PCB Implementation Instructions   
1. The code was optimized and tested for an ATTINY10 Microcontroller. However, the code should run on any AVR based microcontroller (with minor modifications)   
2. The ATTINY10 microcontroller can only be programmed at 5V, so connect the VCC of the microcontroller to a 5V net/power source.   
3. Ensure that the periperhal I²C device has 5V tolerant SDA and SCL pins, or program the microcontroller before placing the I²C peripheral.   
4. Pin 3 (RESET) of the microcontroller cannot be used   
5. Pin 0 (TPIDATA), Pin 1 (TPICLK), and Pin 3 (RESET) of the ATTINY10 must be accessible for programming   
6. An additionall pull-up resistor must be placed on the output SDA line.   
7. The chosen output address must be the only device wired to the output side of the microcontroller, as the specific address will be the only device that can communicate through the translator.   
### Schematic Example   
![image](https://github.com/user-attachments/assets/d7cd1e41-f194-4fd0-b017-3fd010141ad3)  
## Code Modification Instructions  
All relevent configuration options are located at the top of the supplied code  
![image](https://github.com/user-attachments/assets/a1b8ac34-270f-44cf-ad0f-af9dc620b64b)

If using a different microcontroller, remove the following lines:  
#ifndef __AVR_ATtiny10__  
#define __AVR_ATtiny10__  
#endif  

## Code Compilation Instructions  
Start by downloading the cpp file and placing it in its own folder. Edit the file to include the required I2C Addresses. 
![image](https://github.com/user-attachments/assets/4be3bf14-690e-4bdd-8d27-389d9b306f65)  

Next, download the latest 8-bit AVR toolchain from Microchip at https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers and extract it into the folder.    
![image](https://github.com/user-attachments/assets/eeb273c5-1d05-4bd6-afeb-dfba89dc3cad)  

Next, open a command prompt by typing "cmd" in the path bar  
![image](https://github.com/user-attachments/assets/003a0d46-6c1c-4f8a-9e83-08c5e001050c)  

Finally, run the following commands to compile and build your file  
1. ```"avr8-gnu-toolchain-win32_x86_64\bin\avr-gcc.exe" -o "output.o" -c -fno-threadsafe-statics -mmcu=attiny10 -O3 -Wall -flto -DF_CPU=1000000L -Isrc "I2CAddressTranslator.cpp"```  
2. ```"avr8-gnu-toolchain-win32_x86_64\bin\avr-gcc.exe" -g -O3 -w -mmcu=attiny10 "output.o" -o "output.elf"```
3. ```"avr8-gnu-toolchain-win32_x86_64\bin\avr-objcopy" -O ihex "output.elf" "output.hex"```

```"output.hex"``` contains the compiled binary.  
![image](https://github.com/user-attachments/assets/2a624e45-f6b9-4c1c-a40e-fa8b69737c0d)

## ATTINY10 Programming Instructions  
The ATTINY10 Uses the proprietary TPI interface and is only supported by newer firmware versions of the USBASP programmer.   
However, the process of configuring the USBASP programmer is extremely tedious, and I instead recommend using an Ardunio UNO for programming.
### Step 1:
Connect the ATTINY10 to the Arduino Uno as shown  
![image](https://github.com/user-attachments/assets/fff65086-e519-4714-888d-d45532debae9)
### Step 2: 
Upload the sketch provided at https://github.com/james-tate/Arduino-TPI-Programmer/blob/master/TPI_Programmer.ino to the Arduino Uno  
Check to serial monitor to see if the connection was successsful  
<img width="947" alt="image" src="https://github.com/user-attachments/assets/a4474cb2-e34a-4ff7-8940-08206eefeca0">  

### Step 3:
Type "P" into the serial monitor and paste the compiled hex code
