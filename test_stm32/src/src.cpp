// #include "CAN.hpp"
// #include "header.hpp"
// #include <elapsedMillis.h>

// //faster to type
// #define p(msg)        Serial.print(msg)
// #define pd(msg,fill)  Serial.print(msg,fill)
// #define pdl(msg,fill) Serial.println(msg,fill)
// #define pl(msg)       Serial.println(msg)

// uint8_t counter = 0;
// uint8_t frameLength = 8;
// unsigned long previousMillis = 0;     // stores last time output was updated
// const long interval = 1000;           // transmission interval (milliseconds)
// elapsedMillis time_elapsed; 

// void setup() {
//   Serial.begin(9600);
  
//   //bool ret = CANInit(CAN_500KBPS, 0);  // CAN_RX mapped to PA11, CAN_TX mapped to PA12
//   bool ret = CANInit(CAN_500KBPS, 2);  // CAN_RX mapped to PB8, CAN_TX mapped to PB9
//   //bool ret = CANInit(CAN_500KBPS, 3);  // CAN_RX mapped to PD0, CAN_TX mapped to PD1
//   //bool ret = CANInit(CAN_1000KBPS, 0);  // CAN_RX mapped to PA11, CAN_TX mapped to PA12
//   //bool ret = CANInit(CAN_1000KBPS, 2);  // CAN_RX mapped to PB8, CAN_TX mapped to PB9
//   //bool ret = CANInit(CAN_1000KBPS, 3);  // CAN_RX mapped to PD0, CAN_TX mapped to PD1
//   if (!ret) while(true);
// }

// void loop() {
// #ifdef CAN_EXPERIMENT
//   #ifdef NODE_1 //transmitting 
//     CAN_msg_t CAN_TX_msg;
//     CAN_TX_msg.type = DATA_FRAME;
//     CAN_TX_msg.format = STANDARD_FORMAT;
//     CAN_TX_msg.id = 0x000; //highest priority id 
//     CAN_TX_msg.len = frameLength;
//     CAN_TX_msg.data[0] = 0x02;
//     CAN_TX_msg.data[1] = 0x04;
//     CAN_TX_msg.data[2] = 0x06;
//     CAN_TX_msg.data[3] = 0x08;
//     CAN_TX_msg.data[4] = 0x10;
//     CAN_TX_msg.data[5] = 0x12;
//     CAN_TX_msg.data[6] = 0x14;
//     CAN_TX_msg.data[7] = 0x16;  

//     unsigned long currentMillis = millis();
//   //send CAN msg with ID 0x000 every 1 second
//     if (currentMillis - previousMillis >= interval) {
//       previousMillis = currentMillis;
//       CANSend(&CAN_TX_msg);
//       p(time_elapsed/1000);
//       pl(" Sent CAN message");
//     }
//   #endif 

//   #ifdef NODE_2 //receiving
//     CAN_msg_t CAN_RX_msg;

//     if(CANMsgAvail()) {
//       CANReceive(&CAN_RX_msg);

//       if (CAN_RX_msg.format == STANDARD_FORMAT) {
//         p(time_elapsed/1000);
//         p(" Msg income from ID ");
//         p(CAN_RX_msg.id);
//         p(" of length ");
//         pl(CAN_RX_msg.len);
//       }

//       if (CAN_RX_msg.type == DATA_FRAME) {
//         p(" Data: ");
//         for(int i=0; i<CAN_RX_msg.len; i++) {
//           p("0x"); 
//           pd(CAN_RX_msg.data[i], HEX); 
//           if (i != (CAN_RX_msg.len-1))  p(" ");
//         }
//         pl();
//       }
//     }
//   #endif
// #endif
//   //pl((static_cast<double>(analogRead(PA0))/4096.0)*3.3); //analog sensor reading MS4515  
// }
  

//pressure sensor test 
// Includes
// Includes

// #include <Wire.h> //I2C interface
// #include <vector>
// #include <stdint.h>

// #define I2C_SDA PB7
// #define I2C_SCL PB8      
// #define BAUD_RATE 9600 //Serial print and debugging    

// /*Differential Pressure Transducer: MS4525DO-DS3BK001DPL*/     
// #define MS4525DO_ADDRESS (uint8_t) 0x46 //MS4525DO I2C address
// #define MS4525DO_INT PB1                //MS4525DO I2C interrupt Blue Pill pin

// #define p(msg) Serial.print(msg)
// #define pl(msg) Serial.println(msg)

// std::vector<uint8_t> fetch_data();
// void setup() {
// //i2c
//   Wire.setSDA(I2C_SDA);
//   Wire.setSCL(I2C_SCL);
//   Wire.begin();
// //Serial  
//   Serial.begin(BAUD_RATE);
// }

// void loop() {
//   std::vector<uint8_t>raw_data = fetch_data();
//   for(uint8_t i:raw_data) {
//     p(i);
//     p(", ");
//   }
//   pl();
// }

// std::vector<uint8_t> fetch_data() {
//   std::vector<uint8_t> raw_data = {0,0,0,0};
//   int number_bytes = Wire.requestFrom(MS4525DO_ADDRESS, size_t(4), true);
//   while(true) {
//     int bytes_available = Wire.available(); 
//     if (bytes_available == 0) {
//       break;
//     } 
//     uint8_t data_byte = Wire.read();
//     switch(bytes_available) {
//       case 4:
//         raw_data.at(0) = data_byte;
//         break;
//       case 3:
//         raw_data.at(1) = data_byte;
//         break;
//       case 2:
//         raw_data.at(2) = data_byte;
//         break;
//       case 1:    
//         raw_data.at(3) = data_byte;
//         break;
//       case 0:
//         break;    
//       default: 
//         break; 
//     }
//   }
//   return raw_data;

// }
  
#include "I2C_Interface.hpp"

void setup() {
  Wire.setSDA(I2C_SDA);
  Wire.setSCL(I2C_SCL);
  Wire.begin();
  Serial.begin(BAUD_RATE);
}
void loop() {
  I2C_Interface i2c(MS4525DO_ADDRESS);
  i2c.read();
  std::vector<uint8_t> data = i2c.get_raw_data();
  for(int i =0; i++; i<4) {
    // if(i==2) {
    //   p(", ");
    // }
    // pbin(data.at(i));
    p(data.at(i));
  }
  pl();
}

