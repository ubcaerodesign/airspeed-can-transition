// #include <Wire.h> // For I2C interface

// // Functions
// byte fetch_pressure(unsigned int *p_Pressure, unsigned int *p_Temp);

// // Constants
// #define TRUE 1
// #define FALSE 0
// #define SDA_pin PB_7
// #define SCL_pin PB_6
// void setup() {

//   // Begins serial monitor and I2C interface
//   delay(500);
//   Serial.begin(115200); // Starts serial monitor
//   //set pins
//   Wire.setSDA(SDA_pin); //Configure I2C Pins
//   Wire.setSCL(SCL_pin);
//   Wire.begin(); // Starts I2C
//   delay(500);

// }

// void loop() {

//   // This points to the start of the code, sometimes won't appear on flash, should appear on reset
//   delay(3000);
//   Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>");

//   // Declaring variables for data being collected
//   byte _status; // Connection status
//   unsigned int P_dat; // Pressure raw data
//   unsigned int T_dat; // Temp raw data
//   double VV; // Airspeed
//   double TR;
//   // Checks status, displays based on result
//   while (1)
//   {
//     _status = fetch_pressure(&P_dat, &T_dat); // Gets data

//     switch (_status)
//     {
//       case 0: Serial.println("Ok "); // All is well, data transmitting
//         break;
//       case 1: Serial.println("Busy"); // idk, I have never gotten it to output this
//         break;
//       case 2: Serial.println("Slate"); // When this appears, the data transmitted is duplicate from a previous transmit
//         break;
//       default: Serial.println("Error"); // Likely no connection to sensor
//         break;
//     }

//     // This if/else block interpolates using wind tunnel data and the formula below to go
//     // from raw pressure data to airspeed.
//     // y = y1 + (y2-y1) x [(x-x1) / (x2-x1)]
//     if (P_dat >= 8247.32) {
//       VV = 0;
//     }
//     else if (P_dat >= 8234.05) {
//       VV = 0 + (4.45-0) * ((P_dat-8247.32) / (8234.05-8247.32));
//     }
//     else if (P_dat >= 8204.93) {  
//       VV = 4.45 + (8.82-4.45) * ((P_dat-8234.05) / (8204.93-8234.05));
//     }
//     else if (P_dat >= 8166.49) {  
//       VV = 8.82 + (11.96-8.82) * ((P_dat-8204.93) / (8166.49-8204.93));
//     }
//     else if (P_dat >= 8126.05) {  
//       VV = 11.96 + (14.36-11.96) * ((P_dat-8166.49) / (8126.05-8166.49));
//     }
//     else if (P_dat >= 8080.05) {  
//       VV = 14.36 + (16.71-14.36) * ((P_dat-8126.05) / (8080.05-8126.05));
//     }
//     else if (P_dat >= 8033.10) {  
//       VV = 16.71 + (18.73-16.71) * ((P_dat-8080.05) / (8033.10-8080.05));
//     }
//     else if (P_dat >= 7984.15) {  
//       VV = 18.73 + (20.62-18.73) * ((P_dat-8033.10) / (7984.15-8033.10));
//     }
//     else if (P_dat >= 7931.62) {  
//       VV = 20.62 + (22.59-20.62) * ((P_dat-7984.15) / (7931.62-7984.15));
//     }
//     else if (P_dat >= 7873.72) {  
//       VV = 22.59 + (24.50-22.59) * ((P_dat-7931.62) / (7873.72-7931.62));
//     }
//     else if (P_dat >= 7807.64) { 
//       VV = 24.50 + (26.45-24.50) * ((P_dat-7873.72) / (7807.64-7873.72)); 
//     }
//     else if (7807.64 > P_dat) {  
//       VV = 24.50 + (26.45-24.50) * ((P_dat-7873.72) / (7807.64-7873.72));
//     }
//     else {
//       Serial.println("Error :("); // No data received
//     }
    
//     // Converts raw temp to temperature (C)
//     TR = (double)((T_dat*0.09770395701));
//     TR = TR-50;
    
    
//    // Displayes all data, pick and choose what you want 
//    Serial.print("\nraw pressure: ");
//    Serial.println(P_dat);
//    //Serial.println(P_dat,DEC);
//    //Serial.println(P_dat,BIN);
//    //Serial.print("raw Temp:");
//    //Serial.println(T_dat);
//    //Serial.print("temp:");
//    //Serial.println(TR);
//    Serial.print("speed m/s: ");
//    Serial.println(VV,5);

//    delay(100); // This determines how often we collect data
//   }
// }

// byte fetch_pressure(unsigned int *p_P_dat, unsigned int *p_T_dat)
// {

//   // Declaring variables
//   byte address, Press_H, Press_L, Temp_H, Temp_L, _status;
//   unsigned int P_dat;
//   unsigned int T_dat;

//   // Begins transmission with sensor address through I2C
//   address = 0x46; // Datasheet I2C address for airspeed sensor
//   Wire.beginTransmission(address);
//   delay(100);

//   // Requests bytes and passes them to variables
//   Wire.requestFrom((int)address, (int) 4);
//   Press_H = Wire.read();
//   Press_L = Wire.read();
//   Temp_H = Wire.read();
//   Temp_L = Wire.read();
//   Wire.endTransmission();

//   // Debugging
//   /*
//   Serial.println(Press_H, BIN);
//   Serial.println(Press_L, BIN);
//   Serial.println(Temp_H, BIN);
//   Serial.println(Temp_L, BIN);
//   */

//   // Combines the high and lower pressure bytes and assigns them to pointer, also checks status
//   _status = (Press_H >> 6) &0x03; // Gets the leftmost two bits from the first byte and uses that as status
//   Press_H = Press_H &0x3f; // I don't know what this does, and it changes nothing
//   P_dat = (((unsigned int)Press_H) << 8) | Press_L;
//   *p_P_dat = P_dat; 

//   // Combines the high and low temp bytes and assigns them to pointer
//   Temp_L = (Temp_L >> 5);
//   T_dat = (((unsigned int)Temp_H) << 3) | Temp_L;
//   *p_T_dat = T_dat;
//   return (_status);
 
// }