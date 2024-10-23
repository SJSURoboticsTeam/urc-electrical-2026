# Main Arm Board

![Top View](https://github.com/user-attachments/assets/2846094a-2b24-4493-96c2-ea83b116c498)
![Bottom View](https://github.com/user-attachments/assets/6349db9e-a966-4c8f-b6c0-2b1a4ba87a84)


## Authors
Board Design: Brendan Parvin with review and assistance by Shin Umeda

Documentation: Brendan Parvin

## Active Revisions
Revision 1, 8/21/2024: [Implementation Specifics](#revision-1)

Revision 2, 9/18/2024: [Implementation Specifics](#revision-2)  
  -Removed can hotfix as it is not needed  
  -Fixed micromod connector  
  -Changed positioning of U4 and JTAG connector to not interfere with optional C4  
  -Length matched JTAG traces

Revision 3, 10/19/2024  
  -Fixed USB_DET connection

## Summary
This board is both a power distribution and controller board for the arm. It is the interface between the chassis CAN bus and all arm modules.

## Application Description
  There are five main application notes:  
  1. It accepts 40V power, CAN, and 5V from the chassis with connectors on the left side of the board  
  2. It outputs 40V power and CAN to the arm motors with connectors on the bottom of the board  
  3. It outputs 40V power, 5V, and I2C up the arm using connectors on the top of the board  
  4. It contains a micromod connector to control the arm — and allows programming using either USB-C or JTAG

## Implementation Details
### Mounting Points
There are three main M3 mounting holes located at the corners of the board. These are shown in the image below.
![image](https://github.com/user-attachments/assets/2c9618ef-6c92-4d86-a2a7-d6b61338bbbd)

There is one additional M3 mounting hole located near the left middle of the board. This hole was included just in case, but is not in a very standard location.

### Arm Outputs
There are two connectors that output up the arm towards the end effector. One of these is a 40V passthrough intended to power any high-power motor devices. The other connector carries both 5V and I<sup>2</sup>C. As such, all communication from the end effector to the main arm board should be done through I<sup>2</sup>C. Note that the 40V, 5V, and I2C lines are not galvanically isolated. In order to avoid large ground loops, the 5V connector's ground should be connected to the 40V connector's ground anywhere that both are used.

### Indicator LEDs
The board contains 5× user programmable indicator LEDs + 1× 3.3V power-on indicator LED. LEDs are labeled with their respective Micromod Connector pin. However, it might be necessary to consult the datasheet of your respective micromod processor board to determine the actual pin connection. Each LED draws approximately 1-2mA while on.

### Micromod Programming
All Micromod boards support programming through the on board USB-C port. Note that the USB-C port will power the 5V rail, outputs, and inputs on the board. Ensure that there are no loads greater than 500mA connected to 5V.

In addition, a 10-pin JTAG Connector is included. This connector is wired only on ARM-based Micromod processor boards. 5V power must be supplied through another connector to program over JTAG.

### 40V Bypass Capacitors
All 40V Bypass capacitors are left as DNP in this design because it is likely that any 40V device will already contain sufficient input capacitance. However, if large voltage transients are measured, a through-hole electrolytic capacitor can be added adjacent to the 40V input connector (low-frequency filtering), and additional 0603 capacitors can be added adjacent to every output connector (high-frequency filtering).

# Schematic Diagrams

## Programming
![image](https://github.com/user-attachments/assets/61e425b3-9079-43ef-a848-478fa1d02c94)

![image](https://github.com/user-attachments/assets/b0e3e57f-5459-4d97-8d91-0fced84ab500)

## Connectors
![image](https://github.com/user-attachments/assets/143b922b-309e-44e8-b406-cc63869cef18)

![image](https://github.com/user-attachments/assets/9077bcef-52fe-4668-be39-2eec73de0c35)

![image](https://github.com/user-attachments/assets/31d9db14-f846-4562-9538-c8d98fe4929a)

## Micromod and Supporting Circuitry
![image](https://github.com/user-attachments/assets/f44cc8bc-c38b-4b54-8d00-4c6d26113a4b)

![image](https://github.com/user-attachments/assets/e0b15a30-d3ff-4a4c-8856-0bd8409ad513)

![image](https://github.com/user-attachments/assets/9aa6b836-9152-43ff-b3ec-0e235738c203)

![image](https://github.com/user-attachments/assets/f2e525d0-8a49-49ac-bf63-bb989ba90364)

# Old Revision Implementation Specifics

## Revision 1

### Can Hotfix
On the back of the board are two solder jumpers that provide a hotfix in case CAN TX and CAN RX are swapped on the specific Micromod processor board.  
Note that the micromod pin should not be soldered to both TX and RX at the same time. The default connection is Pin 43 <-> TX, Pin 41 <-> RX and is shown below.

<img width="295" alt="image" src="https://github.com/user-attachments/assets/98ce5628-155a-455e-84ed-8241d1435d7a">

### Power Error 
1. Pin 74 of the micromod is supposed to be connected to 3.3V, but is instead connected to the ground.  
To solve this problem, you must remove the pin from the micromod connector before soldering it to the board.  
<img width="400" alt="image" src="https://github.com/user-attachments/assets/55808f19-8cd1-4a9b-aeef-18302ffa6ba2">

### USB Error
2. Pin 9 should be connected to VBUS, but was left unconnected
<img width="200" alt="image" src="https://github.com/user-attachments/assets/4b47dd09-1c86-41cc-96a8-79f1b62e9683">

To solve this problem, you must solder a wire or resistor to an exposed power joint as shown.  
<img width="300" alt="resistor connected between pin 9 and 5V" src="https://github.com/user-attachments/assets/d9e86e6e-f6b3-4c7f-9ffa-8885ba5622b5">

## Revision 2

2. Pin 9 should be connected to VBUS, but was left unconnected  
<img width="200" alt="image" src="https://github.com/user-attachments/assets/4b47dd09-1c86-41cc-96a8-79f1b62e9683">

To solve this problem, you must solder a wire or resistor to an exposed power joint as shown.

<img width="300" alt="resistor connected between pin 9 and 5V" src="https://github.com/user-attachments/assets/d9e86e6e-f6b3-4c7f-9ffa-8885ba5622b5">
