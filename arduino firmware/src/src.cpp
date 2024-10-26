// #include "I2C_Interface.hpp"
#include "MS4525DO_Sensor.hpp"
void setup() {
  Wire.setSDA(I2C_SDA);
  Wire.setSCL(I2C_SCL);
  Wire.begin();
  Serial.begin(BAUD_RATE);
  pinMode(PB5, OUTPUT);
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
  // MS4525DO_Sensor sensor(MS4525DO_ADDRESS);
  // sensor.update_sensor_package();
  // data_t sensor_package = sensor.fetch_sensor_package();
  // // print_converted(sensor_package); //orange - a10 
  // // pl();
  // // p(micros()); p(",");
  // p(sensor_package.raw.pressure); p(", "); p(sensor_package.converted.pressure_psi); p(", "); pl(sensor_package.converted.airspeed_ms);

  // p(", "); pl(sensor_package.converted.airspeed_ms);

  //p(sensor_package.raw.temperature); p(", "); pl(sensor_package.converted.temperature_C);
  

//TODO: 
  //namespaces for organization
  //use Interrupt pin to avoid reading stale data
  digitalWrite(PB5, HIGH);
  delay(5000);
  digitalWrite(PB5, LOW);
  delay(5000);
}

