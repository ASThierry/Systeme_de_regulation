#include "commande.h"
void commande( float puis){
    FT_STATUS ftStatus;
    FT_HANDLE ftHandle; 
    DWORD numDevs; 
    DWORD BytesWritten; 
    // create the device information list
    unsigned char puissance;
    ftStatus = FT_CreateDeviceInfoList(&numDevs); 
    if (ftStatus == FT_OK) { 
        puissance = (puis*127)/100.0;
    //controle du débordement de la puissance 
        if(puissance >127){
            puissance=127;
        }
        if(puissance <0){
            puissance = 0;
        }
        // Envoi de la puissanse
        ftStatus = FT_Write(ftHandle, &puissance, 1, &BytesWritten); 
        if (ftStatus == FT_OK) { 
            printf("La puissance a bien été envoyee.\n");
        } 
    
    FT_Close(ftHandle); 
  }    

}
