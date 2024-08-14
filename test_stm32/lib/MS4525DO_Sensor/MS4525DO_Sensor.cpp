#include "MS4525DO_Sensor.hpp"

MS4525DO_Sensor::MS4525DO_Sensor(const uint8_t address) :
    sensor_address(address),
    i2c(address)
    {}

void MS4525DO_Sensor::update_sensor_package()
{
    std::vector<uint8_t> data = {0,0,0,0};
    i2c.read();
    data = i2c.get_raw_data();

    /*Status - 2 Bits*/
    sensor_package.raw.status = (uint8_t) (data.at(0) >> 6); 
    /*Pressure - 14 Bits*/
    sensor_package.raw.pressure = (((uint16_t)data.at(0) << 8) & 0x3F00) + ((uint16_t)data.at(1) << 0); //Combines High and Low Pressure. Clears status bits
    /*Temperature - 11 Bits*/
    sensor_package.raw.temperature = ((uint16_t)data.at(2) << 3) + ((uint16_t)data.at(3) >> 5); //Combines High and Low Temperature. Clears last 5 bits.

    sensor_package.converted.status = sensor_package.raw.status; 
    //Assign correct transfer function
    if(TYPE) {
        /*Type A*/
        sensor_package.converted.pressure_psi = ((((double)sensor_package.raw.pressure-1638.3)*(PMAX_PSI-PMIN_PSI))/13106.4)+PMIN_PSI;
    } else {
        /*Type B*/
        sensor_package.converted.pressure_psi = ((((double)sensor_package.raw.pressure-819.15)*(PMAX_PSI-PMIN_PSI))/14744.7)+PMIN_PSI;
    }
    sensor_package.converted.temperature_C = (((double)sensor_package.raw.temperature*200.0)/2047.0)-50.0;

    /*Output swings positive when Port 1> Port 2, negative vice versa. Output is 50% (8192D) when Port 1 = Port 2*/ 
    if(sensor_package.converted.pressure_psi >= 0) {
        //Positive to denote Port 1 > Port 2
         sensor_package.converted.airspeed_ms = sqrt((2*6894.7*sensor_package.converted.pressure_psi)/AIR_DENSITY);
    } else {
        //Negative to denote Port 1 < Port 2
        sensor_package.converted.airspeed_ms = -sqrt((2*6894.7*abs(sensor_package.converted.pressure_psi))/AIR_DENSITY);
    }
}

data_t MS4525DO_Sensor::fetch_sensor_package() const
{
    return sensor_package;
}