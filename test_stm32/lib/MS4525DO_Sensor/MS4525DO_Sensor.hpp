#ifndef MS4525DO_SENSOR
#define MS4525DO_SENSOR

/*Differential Pressure Transducer: MS4525DO-DS3BK001DPL*/ 

#include "I2C_Interface.hpp"

/**
 * @brief Status bits and diagnostics 
 * Please see the interface application note https://www.amsys.de/downloads/notes/I2C-Interface-to-Digital-Pressure-Sensors-AMSYS-an802e.pdf pg.5
 */
enum class Status: int {
    normal = 0,     //Normal operation. Good data packet
    reserved = 1,   //Reserved
    stale = 2,      //Stale Data
    fault = 3       //Fault Detected
};
/**
 * @brief fetched data structure, follows Read_DF4 
 * Please see the interface application note https://www.amsys.de/downloads/notes/I2C-Interface-to-Digital-Pressure-Sensors-AMSYS-an802e.pdf pg.4
 */
struct data_t {
    struct raw_t {
        uint8_t status;
        uint16_t pressure;
        uint16_t temperature;
    } raw;
    struct converted_t {
        double pressure_psi;
        double temperature_C;
        double airspeed_ms;
    } converted;
} data;

class MS4525DO_Sensor {
    private:

    public:
    //uses the interrupt pin to control reading traffic 
};
#endif