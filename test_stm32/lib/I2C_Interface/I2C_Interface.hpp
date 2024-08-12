#ifndef I2C_INTERFACE
#define I2C_INTERFACE

#include <Wire.h> //I2C interface
#include <vector>
#include <stdint.h>

#define I2C_SDA PB7
#define I2C_SCL PB8    
#define BAUD_RATE 9600 //Serial print and debugging    

/*Differential Pressure Transducer: MS4525DO-DS3BK001DPL*/     
#define MS4525DO_ADDRESS (uint8_t) 0x46 //MS4525DO I2C address
#define MS4525DO_INT PB1                //MS4525DO I2C interrupt Blue Pill pin

class I2C_Interface {
    private:
        uint8_t address_device;
        int SDA_pin;
        int SCL_pin;
        std::vector<uint8_t> raw_data;
    public:
    I2C_Interface(const uint8_t addr_dev, const int pin_SDA, const int pin_SCL);
    
};


#endif