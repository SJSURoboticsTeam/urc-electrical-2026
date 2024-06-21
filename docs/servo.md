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
