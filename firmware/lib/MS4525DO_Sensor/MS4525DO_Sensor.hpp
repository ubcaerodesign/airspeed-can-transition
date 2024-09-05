#ifndef MS4525DO_SENSOR
#define MS4525DO_SENSOR

/*Differential Pressure Transducer: MS4525DO-DS3BK001DPL*/ 

#include "I2C_Interface.hpp"
#include <cmath>
/*MS4525DO Sensor Configuration*/
#define TYPE     (bool)     0 /*1 - Type A, 0 - Type B*/
#define PMAX_PSI (double)   1 //casted to double for transfer function
#define PMIN_PSI (double)   -1
#define AIR_DENSITY (double) 1.225 //kg/m^3
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
        uint8_t status;
        double pressure_psi; /*range: [-1,1], steps at  */
        double temperature_C; /*range: []*/
        double airspeed_ms; 
    } converted;
};

class MS4525DO_Sensor {
    private:
        uint8_t sensor_address;
        data_t sensor_package;
        I2C_Interface i2c;
    public:
    //uses the interrupt pin to control reading traffic 
    MS4525DO_Sensor(const uint8_t address);
    void update_sensor_package();
    data_t fetch_sensor_package() const;
};
#endif