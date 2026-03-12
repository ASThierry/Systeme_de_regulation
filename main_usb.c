#include <stdio.h>
#include <stdlib.h>

#include<unistd.h>

#include "releve.h"
#include "commande.h"

#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"


// Voir le fichier trace.txt pour comprendre la baisse de température

int main() {

    temp_t temperature; // initialisation de la température
    temperature.exterieure = 14.0; // initialisation de la température extérieure à 14.0°C
    temperature.interieure = 15.0; // initialisation de la température intérieure à 15.0°C

    float cmd = 0; // initialisation de la commande du chauffage à 0%

    int nT = 50;
    float tabT[50];
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    float consi = 10;
    float consi_avant = 10;

    int i = 0;
    int k=0;
   

    ftStatus = FT_Open(0, &ftHandle);

    FT_SetBaudRate(ftHandle, 115200); 
    FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
  
   

    if (ftStatus != FT_OK){
        printf("Pas de connection USB detecter.");
        return ftStatus;
    }
    else {
        while (1) {
            temperature = releve(ftHandle);

            consi_avant = consi;
            consi = consigne(consi_avant);

            if (consi == 5) {
                cmd=0;
                break;
            }

            if (i < nT - 1) {
                tabT[i] = temperature.interieure;
                i++;
            } else {
                for (int j = 0; j < nT - 1; j++) {
                    tabT[j] = tabT[j + 1];
                }
                tabT[nT - 1] = temperature.interieure;
            }

            cmd = regulationTest(1, consi, tabT, nT);
            commande(cmd,ftHandle);

            visualisationC(cmd);
            visualisationT(temperature);

            usleep(40000);
            k++;
            printf("tint: %f; text: %f; consigne: %f\n",temperature.interieure,temperature.exterieure, consi);
            

        }
        FT_Close(&ftHandle);

        return EXIT_SUCCESS;
    }
}