#include "I2C_Interface.hpp"
#include "MS4525DO_Sensor.hpp"
void setup() {
  Wire.setSDA(I2C_SDA);
  Wire.setSCL(I2C_SCL);
  Wire.begin();
  Serial.begin(BAUD_RATE);
  pinMode(PB5, INPUT);
}
void print_converted(data_t package) {
  p("Status: \t");      pl(package.converted.status);
  p("Pressure: \t");    pl(package.converted.pressure_psi);
  p("Temperature: \t"); pl(package.converted.temperature_C);
  p("Airspeed: \t");    pl(package.converted.airspeed_ms);
}
void print_raw(data_t package) {
  p("Status: \t");      pl(package.raw.status);
  p("Pressure: \t");    pl(package.raw.pressure);
  p("Temperature: \t"); pl(package.raw.temperature);
}
void loop() {
  MS4525DO_Sensor sensor(MS4525DO_ADDRESS);
  sensor.update_sensor_package();
  // if(digitalRead(PB5)){
  //   pl("HIGH");
  // } else {
  //   pl("na");
  // }
  //  data_t sensor_package = sensor.fetch_sensor_package();
  // print_converted(sensor_package); //orange - a10 
  // pl();
  // p(micros()); p(",");
  // p(sensor_package.raw.pressure); p(", "); p(sensor_package.converted.pressure_psi); p(", "); pl(sensor_package.converted.airspeed_ms);

  // p(", "); 
  // pl(sensor_package.converted.airspeed_ms);

  // p(sensor_package.raw.temperature); p(", "); pl(sensor_package.converted.temperature_C);
  // pl("--------------------------------------------------------");
  // pl(sensor_package.raw.status);
  // pl(sensor_package.raw.pressure);
  // pl(sensor_package.raw.temperature);
  //  pl(sensor_package.converted.airspeed_ms);
 
//TODO: 
  //namespaces for organization
  //use Interrupt pin to avoid reading stale data
  // digitalWrite(PB5, HIGH);
  // delay(5000);
  // digitalWrite(PB5, LOW);
  // delay(5000);
}


// #include <Wire.h>


// void setup() {

//   Serial.begin(9600);
//   Wire.begin();
//   Serial.println("\nI2C Scanner");
// }


// void loop() {
//   byte error, address;
//   int nDevices;

//   Serial.println("Scanning...");

//   nDevices = 0;
//   for(address = 1; address < 127; address++) {
//     // The i2c_scanner uses the return value of
//     // the Write.endTransmisstion to see if
//     // a device did acknowledge to the address.

//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();

//     if (error == 0) {
//       Serial.print("I2C device found at address 0x");
//       if (address < 16)
//         Serial.print("0");
//       Serial.println(address, HEX);

//       nDevices++;
//     }
//     else if (error == 4) {
//       Serial.print("Unknown error at address 0x");
//       if (address < 16)
//         Serial.print("0");
//       Serial.println(address, HEX);
//     }
//   }
//   if (nDevices == 0)
//     Serial.println("No I2C devices found");
//   else
//     Serial.println("done");

//   delay(5000);           // wait 5 seconds for next scan
// }