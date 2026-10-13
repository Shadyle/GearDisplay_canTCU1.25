
#include <SPI.h>
#include <mcp_can.h>



String readString;

char gmode;
char gear;
char lastgear;
char lastgmode;
int temp;
bool bRefresh;


#define iGearPosTop 60
#define iGearPosLeft 30 
#define iGearModeTop 20
#define iGearModeLeft 70
#define iTemperatureTop 60
#define iTemperatureLeft 80




// CAN RX Variables
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[64];                        // Array to store serial string
bool bCanOK;
#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(SS);                               // Set CS to pin 10

void setup() {


  Serial.begin(115200);
  
  // Initialize MCP2515 running at 8MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK){
    Serial.println("MCP2515 Initialized Successfully!");
    bCanOK = 1;
  }else{
    Serial.println("Error Initializing MCP2515...");
  }
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.



InitDisplay();



}
 
void loop() {

 
  if(CAN_MSGAVAIL == CAN0.checkReceive())                        // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
    if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  
    Serial.print(msgString);
  
    if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {
      for(byte i = 0; i<len; i++){
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }
        
    Serial.println();
  }

if(rxId == 0x702 && rxBuf[2] == 0x01){
     
  gear = '1';}

else if (rxId == 0x702 && rxBuf[2] == 0x02){
  gear = '2';
     } 
else if (rxId == 0x702 && rxBuf[2] == 0x03){
  gear = '3';
     } 
else if (rxId == 0x702 && rxBuf[2] == 0x04){
  gear = '4';
     } 
else if (rxId == 0x702 && rxBuf[2] == 0x05){
  gear = '5';
     } 
else if (rxId == 0x702 && rxBuf[2] == 0x06){
  gear = '6';
     } 
else if (rxId == 0x702 && rxBuf[2] == 0x07){
  gear = '7';
     }
else if (rxId == 0x702 && rxBuf[2] == 0x08){
  gear = '8';
     }
else if (rxId == 0x702 && rxBuf[2] == 0xFD){
  gear = 'N';
     }
else if (rxId == 0x702 && rxBuf[2] == 0xFF){
  gear = 'P';
     }
else if (rxId == 0x702 && rxBuf[2] == 0xFE){
  gear = 'R';
     }


if(rxId == 0x705 && rxBuf[4] == 0x00){
  gmode = 'E';
}

if(rxId == 0x705 && rxBuf[4] == 0x01){
  gmode = 'C';
}
{
if(rxId == 0x705 && rxBuf[4] == 0x02){
  gmode = 'S';
}

if(rxId == 0x705 && rxBuf[4] == 0x03){
  gmode = 'R';
  }
}
if(rxId == 0x705){
  temp = rxBuf[2];
}





if (gear != lastgear){
  bRefresh = 1;
  lastgear = gear;
}

if (gmode != lastgmode ){
  bRefresh = 1;
  lastgmode = gmode;
}



 LoopDisplay();

}




