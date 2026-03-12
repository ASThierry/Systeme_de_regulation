#include "commande.h"

void commande(float puis,FT_HANDLE ftHandle) {
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    DWORD BytesWritten;
    unsigned char puissance;


    if (puis > 100.0){
        puis = 100.0;
    }
         
    if (puis < 0.0){
        puis = 0.0;
    } 
    puissance = (unsigned char)((puis * 127.0) / 100.0);

    // Envoi de la puissance
    ftStatus = FT_Write(ftHandle, &puissance, 1, &BytesWritten);
    if (ftStatus == FT_OK) {
         printf("Puissance envoyée : %d\n", puissance);
    }


}
