# Main Arm Board

![Top View](https://github.com/user-attachments/assets/c60b8f97-a574-4b91-9901-5bb7a6004de8)
![image](https://github.com/user-attachments/assets/50dce78b-11dc-4757-9c59-fcb91f6249a2)

## Authors
Board Design: Brendan Parvin with review and assistance by Shin Umeda

Documentation: Brendan Parvin

## Active Revisions
Revision 1, 8/21/2024

## Summary
This board is both a power distribution and controller board for the arm. It is the interface between the chassis CAN bus and all arm modules.

## Application Description
  There are five main application notes
  1. It accepts 40V power, CAN, and 5V from the chassis with connectors on the left side of the board
  2. It outputs 40V power and CAN to the arm motors with connectors on the bottom of the board
  3. It outputs 40V power, 5V, and I2C up the arm using connectors on the top of the board
  4. It contains a micromod connector to control the arm — and allows programming using USB-C or JTAG

## Implementation Details
### Mounting Points
There are three main M3 mounting holes located at the corners of the board. These are shown in the image below.
![image](https://github.com/user-attachments/assets/2c9618ef-6c92-4d86-a2a7-d6b61338bbbd)

There is one additional M3 mounting hole located near the left middle of the board. This hole was included just in case, but is not in a very standard location.

### Arm Outputs
There are two connectors that output up the arm towards the end effector. One of these is a 40V passthrough inteded to power any high power motor devices. The other connector carries both 5V and I<sup>2</sup>C. As such, all communication from the end effector to the main arm board should be done through I<sup>2</sup>C. Note that the 40V, 5V, and I2C lines are not galvanically isolated. In order to avoid large ground loops, the 5V connector's ground should be connected to the 40V connector's ground anywhere that both are used.

### Indicator LEDs
The board contains 5× user programmable indicator LEDs + 1× 3.3V power-on indicator LED. LEDs are labelled with their respective Micromod Connector pin. However, it might be necessary to consult the datasheet of your respective micromod processor board to determine the actual pin connection. Each LED draws approximately 1mA while on.

### Micromod Programming
All Micromod boards support programming through the on board USB-C port. Note that the USB-C port will power the 5V rail, outputs, and inputs on the board. Ensure that there are no loads greater than 500mA connected to 5V.

Other than that, there is also an included 10 pin JTAG Connector. This connector is correctly wired only on ARM based Micromod processor boards. 5V power must be supplied through another connector in order to program over JTAG.

### Can Hotfix
On the back of the board are two solder jumpers that provide a hotfix in case CAN TX and CAN RX are swapped on the specific Micromod processor board.

Note that the micromod pin should not be soldered to both TX and RX at the same time. The default connection is Pin 43 <-> TX, Pin 41 <-> RX and is shown below.

<img width="295" alt="image" src="https://github.com/user-attachments/assets/98ce5628-155a-455e-84ed-8241d1435d7a">

### 40V Bypass Capacitors
All 40V Bypass capacitors are left as DNP in this design because it is likely that any 40V device will already contain sufficient input capacitance. However, if large voltage transients are measured, a through hole electrolytic capacitor can be added adjacent to the 40V input connector (low frequency filtering), and additional 0603 capacitors can be added adjacent to every output connector (high frequency filtering).

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
