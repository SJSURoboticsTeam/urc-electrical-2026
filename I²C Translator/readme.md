# I²C Translator 
Author - Brendan Parvin  
## Summary  
This devices allows for a signle, selectable I²C address to be translated to a different, selectable I²C address --- on the fly. This allows slaves with the same hardwired address to coexist on a single I²C bus.  
![image](https://github.com/user-attachments/assets/3a0603a6-0fbe-471c-bf71-87b2919359b6)
## PCB Implementation Instructions   
1. The code was optimized and tested for an ATTINY10 Microcontroller (Programming Instructions). However, the code should run on any AVR based microcontroller (with minor modifications)   
2. The ATTINY10 microcontroller can only be programmed at 5V, so connect the VCC of the microcontroller to a 5V net/power source.   
3. Ensure that the periperhal I²C device has 5V tolerant SDA and SCL pins, or program the microcontroller before placing the I²C peripheral.   
4. Pin 3 (RESET) of the microcontroller cannot be used   
5. Pin 0 (TPIDATA), Pin 1 (TPICLK), and Pin 3 (RESET) of the ATTINY10 must be accessible for programming   
6. An additionall pull-up resistor must be placed on the output SDA line.   
7. The chosen output address must be the only device wired to the output side of the microcontroller, as the specific address will be the only device that can communicate through the translator.   
### Schematic Example   
![image](https://github.com/user-attachments/assets/d5dff7b4-3a7f-4783-b8b8-ca2350691f94)
## Programming Instructions  
The ATTINY10 Uses the proprietary TPI interface and is only supported by newer firmware versions of the USBASP programmer.   
However, the process of configuring the USBASP programmer is extremely tedious, and I instead recommend using an Ardunio UNO for programming.
