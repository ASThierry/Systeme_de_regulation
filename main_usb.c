#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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

    //initialise le tableau qui stocke les températures et une variable qui représente sa longueur
    int nT = 50;
    float tabT[50];


    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    //initialise la consigne et sa valeur précédente
    float consi = 10;
    float consi_avant = 10;

    //cet index permet de déterminer le taux de remplissage du tableau afin de déterminer quand le décalage doit commencer
    int i = 0;
    int k=0;
   
    //ouvre l'accès au port  USB et définit ses caractéristiques
    ftStatus = FT_Open(0, &ftHandle);

    FT_SetBaudRate(ftHandle, 115200); 
    FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
  
   

    if (ftStatus != FT_OK){
        printf("Pas de connection USB detecter.");
        return ftStatus;
    }
    else {
        while (1) {
            //récupère les températures de la carte
            temperature = releve(ftHandle);

            //mets à jour la consigne dans consigne.txt en gardant trace de la consigne précédente
            consi_avant = consi;
            consi = consigne(consi_avant);

            //arrête le programme quand la consigne est 5
            if (consi == 5) {
                cmd=0;
                break;
            }

            //remplis le tableau de températures
            if (i < nT - 1) {
                tabT[i] = temperature.interieure;
                i++;
            } else {

                //le tableau est plein, les valeurs sont donc décalées vers la gauche
                for (int j = 0; j < nT - 1; j++) {
                    tabT[j] = tabT[j + 1];
                }
                tabT[nT - 1] = temperature.interieure;
            }

            //effectue la régulation de la puissance avec la méthode de Ziegler-Nichols et la transmets ensuite vers la carte
            cmd = regulationTest(1, consi, tabT, nT);
            commande(cmd,ftHandle);

            //écrit les températures et le témions dans data.txt
            visualisationC(cmd);
            visualisationT(temperature);

            sleep(40);
            k++;
            printf("tint: %f; text: %f; consigne: %f\n",temperature.interieure,temperature.exterieure, consi);
            

        }
        FT_Close(&ftHandle);

        return EXIT_SUCCESS;
    }
}