#include "releve.h"

temp_t releve(FT_HANDLE ftHandle) {
    FT_STATUS ftStatus; 
    DWORD BytesReceived; 
    // buffer de recupération des binaire de mais température
    unsigned char RxBuffer[6];
    temp_t temperature = {0.0, 0.0};
    
    // Variable de stokage de la températue.
    float text = 0.0;
    // leture des donnee envoyee par e microprosseceur
    ftStatus = FT_Read(ftHandle, RxBuffer, 6, &BytesReceived); 
    printf("bytes recieve: %d\n",BytesReceived);
    if (ftStatus == FT_OK ) { 
        float tint = (float)(((RxBuffer[0] & 0x0F) << 8) | ((RxBuffer[1] & 0x0F) << 4) | (RxBuffer[2] & 0x0F));
        float text = (float)(((RxBuffer[3] & 0x0F) << 8) | ((RxBuffer[4] & 0x0F) << 4) | (RxBuffer[5] & 0x0F));
        temperature.interieure = -39.64 + 0.04 * tint;
        temperature.exterieure = -39.64 + 0.04 * text;
    }
    
    // vide le suplus du buffer
    //FT_Purge(ftHandle, FT_PURGE_RX);

    return temperature;
}
