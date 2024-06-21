# 40V Servo

![Top of PCB](https://sjsuroboticsteam.github.io/urc-electrical-2026/resources/40Vservo-out/top.png)

## Features

- Position measurement
- Current sensing
- 50V tolerant H-bridge
- I<sup>2</sup>C communication

## Authors

Board Design: Shin Umeda  
Documentation: Shin Umeda

## Active Revisions

N/A, still in production

## Summary

The 40V servo was conceived to fulfill the purpose of a high-voltage tolerant
high-torque small "smart" motor. It is intended to communicate over I2C, and
is capable of position control, velocity control, torque control, and more.

Any motor can be used with this, since current is controlled by the H-bridge.

## Design Notes

- R2 is the current limiting resistor. See schematic and datasheet on selecting
    resistor size.

## Additional Resources

### PCB Images

![Top of PCB](https://sjsuroboticsteam.github.io/urc-electrical-2026/resources/40Vservo-out/top.png)
![Bottom of PCB](https://sjsuroboticsteam.github.io/urc-electrical-2026/resources/40Vservo-out/bottom.png)

### Schematic

[Schematic](https://sjsuroboticsteam.github.io/urc-electrical-2026/resources/40Vservo-out/40Vservo.pdf)

### Datasheets

- SPI Magnetic Encoder: [TMAG5170-Q1](https://www.ti.com/lit/ds/symlink/tmag5170-q1.pdf?ts=1718980511538&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FTMAG5170-Q1%253Fbm-verify%253DAAQAAAAJ_____zMmkPwHZV65omkmDMfWsKhNCW7OsutlH_rh1k2x93WbOfbfJPjfC--pIB9nB9r8_1eOU1ksnWsXo0SiZatW4efrRY94ky1N_JZ-IC6djIteCFnFNbPwZmJBys3g5uqeiVnHnRNt7hATPXdY8hkSaVj-zyJ8DJVcHbsx5yVanDy1-nNSUmsq7_Hugddjh5o4mIBShVQAPBYPLyTDgqe1pB5IfqsMjpy-QMaPjhkNexe_TUfnM2gt5sQN_pMA6OzUMoH95bwZ9-gWf8nYwywAGO4Rm24jLaasu0wirjUY0HcYzL0a)
- H-Bridge: [DRV8251A](https://www.ti.com/lit/ds/symlink/drv8251a.pdf?ts=1647896037237&ref_url=https%253A%252F%252Fwww.ti.com%252Fstore%252Fti%252Fen%252Fp%252Fproduct%252F%253Fp%253DDRV8251ADDAR%2526keyMatch%253DDRV8251ADDAR%2526tisearch%253Dsearch-everything%2526usecase%253DO)
- Microcontroller: [ATmega328PB](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/40001906C.pdf)
- LDO: [MCP1792T-3302H/CB](https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/MCP1792-Family-Data-Sheet-DS20006229D.pdf)
