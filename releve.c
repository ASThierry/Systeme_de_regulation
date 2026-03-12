#include "releve.h"
temp_t releve(FT_HANDLE ftHandle){
 
    FT_STATUS ftStatus; 
    DWORD TxBytes; 
    DWORD RxBytes; 
    DWORD BytesReceived; 
    unsigned char RxBuffer[6];
    temp_t temperature={0.0,0.0};
    float tint;
    float text;
    ftStatus = FT_Read(ftHandle,RxBuffer,6,&BytesReceived); 
    if (ftStatus == FT_OK) { 
        tint =(float)(((RxBuffer[0]&0x0F)<<8)|((RxBuffer[1]&0x0F)<<4)|(RxBuffer[2]&0x0F));
        tint =(float)(((RxBuffer[3]&0x0F)<<8)|((RxBuffer[4]&0x0F)<<4)|(RxBuffer[5]&0x0F));
    } 
    temperature.exterieure=-39.64+0.04*text;
    temperature.interieure=-39.64+0.04*tint;
    return temperature;
}