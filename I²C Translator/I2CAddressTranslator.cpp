//####################################################
//  Configuration
#ifndef __AVR_ATtiny10__
#define __AVR_ATtiny10__
#endif

#define inAddress 0x70
#define outAddress 0x6A

#define controllerSDApin PIN0
#define peripheralSDApin PIN2
#define sclPin PIN1
//####################################################


extern "C" {
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/power.h>
}

#pragma GCC optimize ("O3") //this must be enabled for the program to be fast enough
#ifndef uint8_t
  typedef unsigned char uint8_t;
#endif

//####################################################
//  Error Checking
#if(inAddress > 127)
#error "inAddress is higher than maximum"
#elif(inAddress < 0)
#error "inAddress cannot be negative"
#elif(inAddress < 127 && inAddress > 0)
#else
#error "inAddress is invalid"
#endif

#if(outAddress > 127)
#error "outAddress is higher than maximum"
#elif(outAddress < 0)
#error "outAddress cannot be negative"
#elif(outAddress < 127 && inAddress > 0)
#else
#error "outAddress is invalid"
#endif

#if(controllerSDApin == peripheralSDApin || controllerSDApin == sclPin || peripheralSDApin == sclPin)
#error "Cannot have duplicate pin assignments"
#elif(controllerSDApin > 3 || peripheralSDApin > 3 || sclPin > 3)
#warning "Pin selection invalid for ATTINY10, if not using ATTINY10 then disregard"
#elif(controllerSDApin == 3 || peripheralSDApin == 3 || sclPin == 3)
#warning "Pin 3 cannot be used on ATTINY10 because it is RESET, if not using ATTINY10 then disregard"
#elif(controllerSDApin < 0 || peripheralSDApin < 0 || sclPin < 0)
#error "Pin assignment cannot be negative"
#elif((controllerSDApin < 3 && controllerSDApin >= 0) & (peripheralSDApin < 3 && peripheralSDApin >= 0) && (sclPin < 3 && sclPin >= 0))
#else
#error "Invalid pin assignment"
#endif
//####################################################

constexpr uint8_t Reverse(const uint8_t number){ //flip all the bits in a byte
  return  ((number & 0b00000001) << 7) +
          ((number & 0b00000010) << 5) +
          ((number & 0b00000100) << 3) +
          ((number & 0b00001000) << 1) +
          ((number & 0b00010000) >> 1) +
          ((number & 0b00100000) >> 3) +
          ((number & 0b01000000) >> 5) +
          ((number & 0b10000000) >> 7);
}

const uint8_t rInAddress = Reverse(inAddress) >> (8-7); //must do >> 1 because the address is only 7 bits long
const uint8_t rOutAddress = Reverse(outAddress) >> (8-7); //must do >> 1 because the address is only 7 bits long
const uint8_t rXorAddress = rInAddress ^ rOutAddress;

inline bool digitalReadFast(const uint8_t pin){
  if((PINB & _BV(pin)) != 0){
    return true;
  } else {
    return false;
  }
}

#define INPUT 0
#define OUTPUT 1
//change the state of a single pin
inline void pinModeFast(const uint8_t pin, bool state){
    if(!state){ //INPUT or OUTPUT
        DDRB &= ~(_BV(pin)); //Set pin to input = HI-Z = HIGH
    } else {
        DDRB |= _BV(pin); //Set pin to output = LOW
    } 
}

inline void openCollectorWrite(const uint8_t pin, const bool state){
    if(state){ //output High or Low
        DDRB &= ~(_BV(pin)); //Set pin to input = HI-Z = HIGH
    } else {
        DDRB |= _BV(pin); //Set pin to output = LOW
    }
}

inline void TransmitByte(const uint8_t inputPin, const uint8_t outputPin, uint8_t& bitCount, bool& sdaState){
  pinModeFast(inputPin, INPUT);

  for(; bitCount < 8; ++bitCount){ //Send 8 Bits total

    while(digitalReadFast(sclPin) == 0){//Transmit input SDA to output SDA
      openCollectorWrite(outputPin, digitalReadFast(inputPin));
    }  //Do this continuously while clock is low

    while(digitalReadFast(sclPin) == 1); //Wait for the clock cycle to end
  }

  pinModeFast(outputPin, INPUT);
}

inline void TransmitACK(const uint8_t inputPin, const uint8_t outputPin, bool& sdaState){
  while(digitalReadFast(sclPin) == 1); //wait for the previous clock cycle to end
  pinModeFast(inputPin, INPUT);
  do{ //continuously passthrough data while clock is low
    sdaState = digitalReadFast(inputPin);
    openCollectorWrite(outputPin, sdaState);
  } while (digitalReadFast(sclPin) == 0);

  while(digitalReadFast(sclPin) == 1); //freeze while clock is high
  pinModeFast(outputPin, INPUT);
}

inline bool checkAddressBit(uint8_t bit, bool& sdaState){
  while(digitalReadFast(sclPin) == 1); //wait for the previous clock cycle to end
  do{
    //Note: This if statement should be evaluated at compile time
    if(rXorAddress & _BV(bit)){ //need to flip the bit
      pinModeFast(peripheralSDApin, digitalReadFast(controllerSDApin)); //Passthrough the opposite 
    } else { //do not need to flip the bit
      openCollectorWrite(peripheralSDApin, digitalReadFast(controllerSDApin)); //Passthrough 
    }
  }while(digitalReadFast(sclPin) == 0);

  //check if the bit matched the expected In Address. Returns 1 if bit did not match.
  if(digitalReadFast(controllerSDApin) == static_cast<bool>(rInAddress & _BV(bit))){ 
    return 0;
  } else {
    return 1;
  }
}

int main(void){
  PORTB = 0b00000000; //set all outputs to LOW
  pinModeFast(sclPin, INPUT); //SCL pin is always input
  pinModeFast(controllerSDApin, INPUT); // For Reading
  pinModeFast(peripheralSDApin, INPUT); //Hi-z
  power_all_disable(); //disable the ADC, timer, etc.

  cli(); //global interrupt disable

  CCP = 0xD8; //turn clock register protection off for next 4 clock cycles
  CLKMSR &= 0b11111100; //set clock to main 8MHz oscillator
  clock_prescale_set(clock_div_1); //Set clock prescaler to 1:1
  CCP = 0xD8; //turn clock register protection off for next 4 clock cycles
  OSCCAL = 0xFF; //enable max overclock

  wdt_enable(WDTO_30MS); //enable watchdog in system reset mode with a period of 16ms
  VLMCSR &= 0b10111000; //disable vcc voltage monitoring
  DIDR0 = 0b00000000; //enable digital input on all pins

  uint8_t bitCount; //stores current bit number in message
  bool sdaState;    //stores the current SDA state
  union{
    bool previousSDAState;  //stores the last SDA state
    bool isWrongAddress; //set to TRUE if the wrong address was recieved
    bool readOrWrite; //stores the state of the current communication
  } scratchVar; //only stores 1 in byte total
  
  
  while(true){
    start:
    //State 0: IDLE. Note* This ignores STOP Condition, but passes it on to the Peripheral device
    sdaState = digitalReadFast(controllerSDApin);
    do{
      wdt_reset(); //This is the defualt state, so a watchdog reset should not occur

      //Need to detect a falling edge for START
      scratchVar.previousSDAState = sdaState;

      //This logic must occur within a maximum of 600ns for 400kHz, and 4000ns for 100kHz
      sdaState = digitalReadFast(controllerSDApin);


      //Pass signal to Peripheral Device 
      openCollectorWrite(peripheralSDApin, sdaState);

      if(digitalReadFast(sclPin)){ //START or STOP is allowed only while clock is high
        if(scratchVar.previousSDAState == 1 && sdaState == 0){ //Falling-Edge means START Condition
          break;
        }
      }
      //End time sensitive logic

    } while(true);


  repeatedStart:
    pinModeFast(controllerSDApin, INPUT); // For Reading
    wdt_reset(); //a repeated start and stop are well defined, so if either is detected then we are definitely here correctly

    //State 1: Read Peripheral Device Address. Note*: a repeated start or stop can not be detected during this state because it cannot be passed on to the device anyway
    scratchVar.isWrongAddress = false;
    //Bit 0:
    if(checkAddressBit(0, sdaState)){
      scratchVar.isWrongAddress = true;
    }

    //Bit 1:
    if(checkAddressBit(1, sdaState)){
      scratchVar.isWrongAddress = true;
    }

    //Bit 2:
    if(checkAddressBit(2, sdaState)){
      scratchVar.isWrongAddress = true;
    }

    //Bit 3:
    if(checkAddressBit(3, sdaState)){
      scratchVar.isWrongAddress = true;
    }

    //Bit 4:
    if(checkAddressBit(4, sdaState)){
      scratchVar.isWrongAddress = true;
    }

    //Bit 5:
    if(checkAddressBit(5, sdaState)){
      scratchVar.isWrongAddress = true;
    }

    

    //Bit 6:
    if(checkAddressBit(6, sdaState)){
      scratchVar.isWrongAddress = true;
    }

    if(scratchVar.isWrongAddress == true){ //wrong address detected -> wait for next communication
      continue;
    }

    //Bit 7: Read/Write Bit gets special treatment
    while(digitalReadFast(sclPin) == 1); //wait for the previous clock cycle to end

    do{
      scratchVar.readOrWrite = digitalReadFast(controllerSDApin);
      openCollectorWrite(peripheralSDApin, scratchVar.readOrWrite);
    }while(digitalReadFast(sclPin) == 0);

    //State 2: Reply with Peripheral ACK Response
    TransmitACK(peripheralSDApin, controllerSDApin, sdaState);
    if(sdaState == 1){ //NACK
      continue; //Restart I2C Transmission
    }

    if(scratchVar.readOrWrite == 1){ //State 3R: Read
        do{ // This allows for autoincrement behaivor
            bitCount = 0;
            TransmitByte(peripheralSDApin, controllerSDApin, bitCount, sdaState);

            //State 4R: Reply with Controller ACK Response
            TransmitACK(controllerSDApin, peripheralSDApin, sdaState);
            if(sdaState == 1){ //Controller NACK always means stop
                break;
            }
        } while(true);
    } else{ //State 3W: Write
        pinModeFast(controllerSDApin, INPUT);
        do{
            bitCount = 1;
            do{
                scratchVar.previousSDAState = digitalReadFast(controllerSDApin);
                openCollectorWrite(peripheralSDApin, scratchVar.previousSDAState);
            } while(digitalReadFast(sclPin) == 0);

            do{ //check if the data pin changes while the clock is high
                sdaState = digitalReadFast(controllerSDApin);
                if(sdaState ^ scratchVar.previousSDAState){ //START OR STOP = PANIC
                    openCollectorWrite(peripheralSDApin, sdaState);
                    if(scratchVar.previousSDAState){ //repeated start
                        goto repeatedStart;
                    } else {
                        goto start;
                    }
                }
            } while(digitalReadFast(sclPin) == 1);

            TransmitByte(controllerSDApin, peripheralSDApin, bitCount, sdaState);

            //State 4W: Reply with Peripheral ACK Response
            TransmitACK(peripheralSDApin, controllerSDApin, sdaState);
            if(sdaState == 1){ //Peripheral NACK always means stop
                pinModeFast(controllerSDApin, INPUT);
                break;
            }
        } while(true);
    }
  }
}
